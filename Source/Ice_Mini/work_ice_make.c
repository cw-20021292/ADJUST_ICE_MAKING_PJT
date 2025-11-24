#include "work_ice_make.h"
#include "Macrodriver.h"
#include "Global_Variable.h"
#include "Port_Define.h"
#include "work_flow.h"

// 기술과제 2 (제빙테이블 미적용)
typedef struct
{
    F32 f32Gain;
    U8  u8Cycle;
    F32 f32Target;
    F32 f32Ratio;
    U16 u16NextIceMakeTime;
    U16 u16ThisTimeIceMakeTime;
    U16 u16IceMakeAvgFlow;
    U16 u16IceMakeFlowHistory[3];    // 최근 3회 제빙물량 저장
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

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 제빙수에 사용된 물량 평균 계산
***********************************************************************************************************************/
void ProcessIceMaking(void)
{
    U16 mu16DeltaTimeLimit = 600;

    // 로직에 사용
    // 제빙수에 사용된 물량 저장
    // 음수일 때는 반영안함
    if(GetDrainFlow() > 0)
    {
        if(IceAdjust.u8Cycle < 3)
        {
            // 3 미만일 때만 증가
            IceAdjust.u8Cycle++;
            // 1회, 2회일 때의 평균 제빙시간 적용
            IceAdjust.u16IceMakeAvgFlow = (GetDrainFlow() / IceAdjust.u8Cycle);
        }
        else
        {
            // 배열을 왼쪽으로 shift (FIFO)
            IceAdjust.u16IceMakeFlowHistory[0] = IceAdjust.u16IceMakeFlowHistory[1];
            IceAdjust.u16IceMakeFlowHistory[1] = IceAdjust.u16IceMakeFlowHistory[2];
            IceAdjust.u16IceMakeFlowHistory[2] = GetDrainFlow();

            // 최근 3회 평균 계산
            IceAdjust.u16IceMakeAvgFlow = (U16)((IceAdjust.u16IceMakeFlowHistory[0] +
                                                    IceAdjust.u16IceMakeFlowHistory[1] +
                                                    IceAdjust.u16IceMakeFlowHistory[2]) / 3);
        }
    }

    // 보정 Gain 설정
    if(IceAdjust.u16IceMakeAvgFlow > GetCCToHz(120))              // 110ml 이상 제빙
    {
        // zone 1 (심각 과제빙) : 강하게 줄이기
        SetGain(ZONE_1_GAIN);
    }
    else if(IceAdjust.u16IceMakeAvgFlow > GetCCToHz(70))         // 90ml 이상 제빙
    {
        // zone 2 (살짝 과제빙) : 부드럽게 줄이기
        SetGain(ZONE_2_GAIN);
    }
    else if(IceAdjust.u16IceMakeAvgFlow < GetCCToHz(35))         // 30ml 이하 제빙
    {
        // zone 4 (심각 부족) : 강하게 늘리기
        SetGain(ZONE_4_GAIN);
    }
    else if(IceAdjust.u16IceMakeAvgFlow < GetCCToHz(60))         // 50ml 이하 제빙
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

    SetTheoryRatio(IceAdjust.u16IceMakeAvgFlow);
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
    else
    {
        SetNextIceMakeTime(GetNextIceMakeTime());
    }
}



static void SetTheoryRatio(U16 Avg)
{
    F32 mf32_target = (F32)GetCCToHz(ICE_V_TARGET);     /* 70ml 핑거 7개 */
    F32 mf32_ratio_theory = (F32)(mf32_target / Avg);
    F32 mf32_eff_ratio = (SetValidGain() * GetGain());
    F32 mf32_final_ratio = 0;

    mf32_final_ratio = (1.0F + (mf32_eff_ratio * (F32)(mf32_ratio_theory - 1.0F)));
    SetTarget(mf32_target);
    SetRatio(mf32_final_ratio);
}
