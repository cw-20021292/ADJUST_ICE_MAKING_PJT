#include "work_ice_make.h"
#include "Macrodriver.h"
#include "Global_Variable.h"
#include "Port_Define.h"
#include "work_flow.h"
#include "Global_header.h"

// 기술과제 2 (제빙테이블 미적용)
typedef struct
{
    F32 f32Gain;
    U8  u8Cycle;
    F32 f32Target;
    F32 f32Ratio;
    U16 u16NextIceMakeTime;
    U16 u16ThisTimeIceMakeTime;
    F32 f32IceMakeAvgFlow;
    F32 f32IceMakeFlowHistory[3];    // 최근 3회 제빙물량 저장
    U8 u8ErrorCount;                 // 에러 카운트
} ICE_ADJUST_T;
ICE_ADJUST_T IceAdjust;

void SetGain(F32 f32Gain)
{
    IceAdjust.f32Gain = f32Gain;
}

F32 GetGain(void)
{
    return IceAdjust.f32Gain;
}

void SetRatio(F32 f32Ratio)
{
    IceAdjust.f32Ratio = f32Ratio;
}

F32 GetRatio(void)
{
    return IceAdjust.f32Ratio;
}

void SetTarget(F32 Target)
{
    IceAdjust.f32Target = Target;
}

F32 GetTarget(void)
{
    return IceAdjust.f32Target;
}

void SetNextIceMakeTime(U16 NextIceMakeTime)
{
    IceAdjust.u16NextIceMakeTime = NextIceMakeTime;
}

U16 GetNextIceMakeTime(void)
{
    return IceAdjust.u16NextIceMakeTime;
}

void SetThisTimeIceMakeTime(U16 ThisTimeIceMakeTime)
{
    IceAdjust.u16ThisTimeIceMakeTime = ThisTimeIceMakeTime;
}

U16 GetThisTimeIceMakeTime(void)
{
    return IceAdjust.u16ThisTimeIceMakeTime;
}

U8 GetErrorCount(void)
{
    return IceAdjust.u8ErrorCount;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 제빙수에 사용된 물량 평균 계산
***********************************************************************************************************************/
void ProcessIceMaking(void)
{
    U16 mu16DeltaTimeLimit = 600;
    U8 count = 0;
    F32 sum = 0;
    U8 i = 0;

    if(GetDrainFlow() > 0)
    {
        sum = 0;
        // 평균 Flow 계산
        if(IceAdjust.u8Cycle < 3)
        {
            IceAdjust.f32IceMakeFlowHistory[IceAdjust.u8Cycle] = GetDrainFlow();
            IceAdjust.u8Cycle++;

            for(i = 0; i < IceAdjust.u8Cycle; i++)
            {
                sum += IceAdjust.f32IceMakeFlowHistory[i];
            }

            IceAdjust.f32IceMakeAvgFlow = (sum / IceAdjust.u8Cycle);
        }
        else
        {
            // FIFO shift
            IceAdjust.f32IceMakeFlowHistory[0] = IceAdjust.f32IceMakeFlowHistory[1];
            IceAdjust.f32IceMakeFlowHistory[1] = IceAdjust.f32IceMakeFlowHistory[2];
            IceAdjust.f32IceMakeFlowHistory[2] = GetDrainFlow();

            // 3개 평균
            sum  = IceAdjust.f32IceMakeFlowHistory[0];
            sum += IceAdjust.f32IceMakeFlowHistory[1];
            sum += IceAdjust.f32IceMakeFlowHistory[2];

            IceAdjust.f32IceMakeAvgFlow = (sum / 3);
        }

        IceAdjust.u8ErrorCount = 0;
    }
    else
    {
        IceAdjust.u8ErrorCount++;
        if(IceAdjust.u8ErrorCount >= 10)
        {
            IceAdjust.u8ErrorCount = 10;
        }
        else {  }
    }

    // 보정 Gain 설정
    if(IceAdjust.f32IceMakeAvgFlow > GetCCToHz(120))              // 120ml 이상 제빙 (남은 물량 80ml)
    {
        // zone 1 (심각 과제빙) : 강하게 줄이기
        SetGain(ZONE_1_GAIN);
    }
    else if(IceAdjust.f32IceMakeAvgFlow > GetCCToHz(75))         // 75ml 이상 제빙 (남은 물량 125ml)
    {
        // zone 2 (살짝 과제빙) : 부드럽게 줄이기
        SetGain(ZONE_2_GAIN);
    }
    else if(IceAdjust.f32IceMakeAvgFlow < GetCCToHz(35))         // 35ml 이하 제빙 (남은 물량 165ml)
    {
        // zone 4 (심각 부족) : 강하게 늘리기
        SetGain(ZONE_4_GAIN);
    }
    else if(IceAdjust.f32IceMakeAvgFlow < GetCCToHz(50))         // 50ml 이하 제빙 (남은 물량 150ml)
    {
        // zone 3 (살짝 부족) : 부드럽게 늘리기
        SetGain(ZONE_3_GAIN);
    }
    else
    {
        // OK (거의 맞음) : 살살 보정
        // 60 ~ 70ml 제빙이 목표
        SetGain(ZONE_5_GAIN);
    }

    // 평균 유량을 확인하고 줄일지 말지 결정
    SetTheoryRatio(IceAdjust.f32IceMakeAvgFlow);
    SetNextIceMakeTime((U16)(GetThisTimeIceMakeTime() * GetRatio()));

    // 상한치 하한치 제한
    if(GetNextIceMakeTime() < ICE_MAKE_TIME_MIN )
    {
        SetNextIceMakeTime(ICE_MAKE_TIME_MIN);
    }
    else if(GetNextIceMakeTime() > ICE_MAKE_TIME_MAX)
    {
        SetNextIceMakeTime(ICE_MAKE_TIME_MAX);
    }

    // 너무 과격하게 변하지 않게 1회 변화량 1분으로 제한 (안정화)
    if((GetNextIceMakeTime() > mu16DeltaTimeLimit + GetThisTimeIceMakeTime()))
    {
        SetNextIceMakeTime((GetThisTimeIceMakeTime() + mu16DeltaTimeLimit));
    }
    else if((GetNextIceMakeTime() < GetThisTimeIceMakeTime() - mu16DeltaTimeLimit))
    {
        SetNextIceMakeTime((GetThisTimeIceMakeTime() - mu16DeltaTimeLimit));
    }
}

/**
 * @brief Set the Theory Ratio object
 *
 * @param Avg : 제빙에 사용된 물량 (입수된 물의 양 [고정값] - 제빙완료되고 버려진 물의 양)
 */
static void SetTheoryRatio(F32 Avg)
{
    F32 mf32_min_avg = 0;
    F32 mf32_avg = 0;
    F32 mf32_ratio_theory = 0;
    F32 mf32_eff_ratio = 0;
    F32 mf32_target = GetCCToHz(ICE_V_TARGET);   /* 63~70ml에 해당하는 유량값(Hz or pulse) */
    F32 mf32_final_ratio = 1.0F;

    // 1) 센서/계산 값 이상 여부 체크
    if (Avg <= 0)
    {
        // 유효하지 않은 값 → 보정하지 않고 현재 시간 유지 (ratio = 1.0)
        SetTarget(mf32_target);
        SetRatio(1.0F);
        return;
    }

    // 2) 최소 평균 유량 클램핑 (너무 작으면 의미 없다고 보고)
    mf32_min_avg = (F32)GetCCToHz(10);   // 10ml 기준 (필요하면 조정)
    mf32_avg     = (F32)Avg;

    if (mf32_avg < mf32_min_avg)
    {
        mf32_avg = mf32_min_avg;
    }

    // 3) 이론 ratio 계산 (목표 / 평균)
    // [2025.12.18] 기준으로 Target은 94Hz
    mf32_ratio_theory = (mf32_target / mf32_avg);

    // 4) 유효 Gain (유량의 오차를 보고 30%만 보정할지 100%만 보정할지 판단)
    mf32_eff_ratio = SetValidGain() * GetGain();   // SetValidGain → GetValidGain 추천

    // 5) 최종 ratio
    mf32_final_ratio = 1.0F + (mf32_eff_ratio * (mf32_ratio_theory - 1.0F));
    // [2026.01.07] V4, 항상 제빙시간을 +2%로 하향 적용 (OFFSET 적용)
    mf32_final_ratio += 0.02F;

    SetTarget(mf32_target);
    SetRatio(mf32_final_ratio);
}
