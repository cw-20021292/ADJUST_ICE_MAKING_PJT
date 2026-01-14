
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "work_flow.h"
#include    "M8_Ice_Making.h"
#include    "api_debug.h"

#define FLOW_INIT_DATA_SIZE 10

typedef struct _drain_flow_
{
    U8  u8FlowMeter;                   /* 제빙수 유량센서 플래그 */
    F32 f32IceMakeBeforeFlowHz;       /* 제빙수 전 유량센서 측정값 */
    F32 f32IceMakeAfterFlowHz;        /* 제빙수 후 유량센서 측정값 */
    F32 f32VIcePrevFlowHz;            /* 제빙수 이전 유량센서 측정값 */
    F32 f32VIceCurFlowHz;             /* 제빙수 현재 유량센서 측정값 */
    F32 f32DebugFlowHz;               /* 디버그 유량센서 측정값 */
} DRAIN_FLOW_T;
DRAIN_FLOW_T DrainFlow;


typedef struct _flow_init_
{
    FLOW_STACK_STEP  u8Step;                       /* 측정 스텝 */
    U8  u8FlowDataStackCycle;
    F32 F32DefaultFillHz;
    F32 f32InitFlowHzData[FLOW_INIT_DATA_SIZE];    /* 제품별 특성 파악용 유량 측정 */
    F32 f32InitFlowHz;                             /* 적응형 유량센서 측정 후 확정한 드레인펌프 기준 트레이 입수유량 최종값 */
    F32 f32TempFlowHz;                             /* 임시 유량센서 측정값 */
} FLOW_INIT_T;
FLOW_INIT_T FlowInit;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 제빙수 입수유량 설정
***********************************************************************************************************************/
void SetDrainBeforeFlowHz(F32 f32FlowHz)
{
    DrainFlow.f32IceMakeBeforeFlowHz = f32FlowHz;
}

F32 GetDrainBeforeFlowHz(void)
{
    return DrainFlow.f32IceMakeBeforeFlowHz;
}

void SetDrainAfterFlowHz(F32 f32FlowHz)
{
    DrainFlow.f32IceMakeAfterFlowHz = f32FlowHz;
}

F32 GetDrainAfterFlowHz(void)
{
    return DrainFlow.f32IceMakeAfterFlowHz;
}

void SetDrainPrevFlowHz(F32 f32FlowHz)
{
    DrainFlow.f32VIcePrevFlowHz = f32FlowHz;
}

F32 GetDrainPrevFlowHz(void)
{
    return DrainFlow.f32VIcePrevFlowHz;
}

void SetDrainCurFlowHz(F32 f32FlowHz)
{
    DrainFlow.f32VIceCurFlowHz = f32FlowHz;
}

F32 GetDrainCurFlowHz(void)
{
    return DrainFlow.f32VIceCurFlowHz;
}

void SetFlowInitFlowHz(F32 f32FlowHz)
{
    FlowInit.f32InitFlowHz = f32FlowHz;
}

F32 GetFlowInitFlowHz(void)
{
    return FlowInit.f32InitFlowHz;
}

void SetFlowInitStep(FLOW_STACK_STEP u8Step)
{
    FlowInit.u8Step = u8Step;
}

FLOW_STACK_STEP GetFlowInitStep(void)
{
    return FlowInit.u8Step;
}

void InitFlowHzDecrease(void)
{
    if(GetFlowInitStep() == FLOW_STACK_STEP_WATER_IN)
    {
        if(FlowInit.F32DefaultFillHz > 0)
        {
            FlowInit.F32DefaultFillHz--;
        }
    }
}

// 총 제빙에 사용된 물량 계산 (Hz단위를 cc단위로 변환해야됨)
F32 GetDrainFlow(void)
{
    if((DrainFlow.f32IceMakeBeforeFlowHz - DrainFlow.f32IceMakeAfterFlowHz) > 0)
    {
        return (DrainFlow.f32IceMakeBeforeFlowHz - DrainFlow.f32IceMakeAfterFlowHz);
    }
    else
    {
        return 0;
    }
}

// CC단위를 Hz단위로 변환
F32 GetCCToHz(U16 u16CC)
{
    F32 f32OneCC = C_ICE_MAKING;
    return (F32)(u16CC * f32OneCC);
}

// 배수유량이 입수유량의 +5%보다 크면 OK
// SET : 케이스 사용 가능
// CLEAR : 케이스 사용 불가
F32 SetValidGain(void)
{
    F32 mf32_isvalid = INVALID;

    F32 f32_cur_flow = GetDrainCurFlowHz();
    F32 f32_prev_flow = GetDrainPrevFlowHz();
    F32 mf32_diff = 0.0F;
    mf32_diff = (f32_cur_flow - f32_prev_flow);

    // 배수유량이 입수유량의 +5%보다 크면 NG
    if(DrainFlow.f32IceMakeAfterFlowHz > (F32)((DrainFlow.f32IceMakeBeforeFlowHz * 1.05)))
    {
        mf32_isvalid = INVALID;
    }
    // 배수유량이 입수유량보다 큰데 +5% 이하면 의심
    else if(DrainFlow.f32IceMakeAfterFlowHz > DrainFlow.f32IceMakeBeforeFlowHz)
    {
        mf32_isvalid = SUSPECT;
    }
    else    // 정상
    {
        mf32_isvalid = VALID;
    }

    return mf32_isvalid;
}

/**
 * @brief 제빙수 드레인 유량센서 시작
 *
 * @return void
 */
void DrainFlowStart(void)
{
    R_INTC10_Start();
}

/**
 * @brief 제빙수 드레인 유량센서 종료
 *
 * @return void
 */
void DrainFlowStop(void)
{
    R_INTC10_Stop();
}

/**
 * @brief 제빙수 드레인 유량센서 입력 카운트 (F_Flow_Meter == SET)
 *
 * @return void
 */
void DrainFlowInputCount(void)
{
    if(DrainFlow.u8FlowMeter == SET)
    {
        DrainFlow.u8FlowMeter = CLEAR;

        DrainFlowStart();
    }
    else{}
}

/**
 * @brief 제빙수 드레인 유량센서 입력 (INTPn에 적용)
 *
 * @return void
 */
void DrainFlowInput(void)
{
    DrainFlow.u8FlowMeter = SET;

    if(GetIceStep() == STATE_41_DRAIN_FLOW_CALCUATE)
    {
        DrainFlow.f32IceMakeAfterFlowHz++;
        DrainFlow.f32DebugFlowHz = 0;
    }
    else
    {
        if(GetFlowInitStep() == FLOW_STACK_STEP_TRAY_WATER_CAL)
        {
            FlowInit.f32TempFlowHz++;
        }
    }

    DrainFlowStop();
}

/**
 * @brief 제빙수 입수량 측정을 위한 드레인동작 조건 확인
 *
 * @return U8
 */
U8 AutoIceMake_CheckFlowInitDrainCondition(void)
{
    U8 mu8Return = CLEAR;

    if( GetFlowInitFlowHz() == 0 )
    {
        if((GetFlowInitStep() == FLOW_STACK_STEP_INIT)
        || (GetFlowInitStep() == FLOW_STACK_STEP_TANK_DRAIN)
        || (GetFlowInitStep() == FLOW_STACK_STEP_TRAY_WATER_CAL)
        || (GetFlowInitStep() == FLOW_STACK_STEP_TANK_EMPTY)
        )
        {
            mu8Return = SET;
        }
    }

    return mu8Return;
}

/**
 * @brief 제빙수 입수량 설정 (드레인탱크 기준)
 *
 * @return void
 */
void AutoIceMake_SetTrayInWaterAmount(void)
{
    SetDrainBeforeFlowHz(GetFlowInitFlowHz());

    // 버려지는 물의 Hz값은 0부터 시작
    SetDrainAfterFlowHz(0);
}

/**
 * @brief 초기 드레인단 기준 제빙수 입수유량 측정 (더미탈빙 이후 진행필요)
 *
 * @return U8
 */
U8 AutoIceMake_IceMakeFlowDataStack(void)
{
    int i = 0;
    F32 f32MaxFlowHz = 0;  // 최대값을 저장할 임시 변수
    U8 u8Return = CLEAR;

    switch(FlowInit.u8Step)
    {
        case FLOW_STACK_STEP_INIT:
            // 드탱 비우고 시작
            if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
            {
                FlowInit.f32TempFlowHz = 0;
                FlowInit.F32DefaultFillHz = C_ICE_TRAY_FILL_200CC;
                FlowInit.u8FlowDataStackCycle++;
                FlowInit.u8Step = FLOW_STACK_STEP_TRAY_UP;
            }
            break;

        case FLOW_STACK_STEP_TRAY_UP:
            up_tray_motor();
            FlowInit.u8Step = FLOW_STACK_STEP_TANK_EMPTY;
            break;

        case FLOW_STACK_STEP_TANK_EMPTY:
            if((u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
            && (F_TrayMotorUP == CLEAR)
            )
            {
                FlowInit.u8Step = FLOW_STACK_STEP_WATER_IN;
            }
            break;

        case FLOW_STACK_STEP_WATER_IN:
            // DEFAULT 물량으로 입수해보기
            if(FlowInit.F32DefaultFillHz <= 0)
            {
                FlowInit.u8Step = FLOW_STACK_STEP_TRAY_DOWN;
            }
            break;

        case FLOW_STACK_STEP_TANK_DRAIN:
            if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
            {
                FlowInit.u8Step = FLOW_STACK_STEP_TRAY_DOWN;
            }
            break;

        case FLOW_STACK_STEP_TRAY_DOWN:
            if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
            {
                down_tray_motor();
                FlowInit.u8Step = FLOW_STACK_STEP_TRAY_DOWN_CHECK;
            }
            break;

        case FLOW_STACK_STEP_TRAY_DOWN_CHECK:
            if(F_TrayMotorDOWN == CLEAR)
            {
                FlowInit.u8Step = FLOW_STACK_STEP_TRAY_WATER_CAL;
            }
            break;

        case FLOW_STACK_STEP_TRAY_WATER_CAL:
            if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
            {
                // 10회 측정 완료 후 평균 계산
                if(FlowInit.u8FlowDataStackCycle < FLOW_INIT_DATA_SIZE)
                {
                    FlowInit.f32InitFlowHzData[FlowInit.u8FlowDataStackCycle] = FlowInit.f32TempFlowHz;
                    FlowInit.u8Step = FLOW_STACK_STEP_INIT;
                }
                else
                {
                    FlowInit.u8Step = FLOW_STACK_STEP_FINISH;
                }
            }
            break;


        case FLOW_STACK_STEP_FINISH:
            // 10회 측정 완료 후 평균 계산
            if(FlowInit.f32InitFlowHz == 0)
            {
                /* 평균값 적용 */
                for(i = 0; i < FLOW_INIT_DATA_SIZE; i++)
                {
                    FlowInit.f32InitFlowHz += FlowInit.f32InitFlowHzData[i];
                }
                FlowInit.f32InitFlowHz /= FLOW_INIT_DATA_SIZE;

                // /* 최대값 적용 */
                // // 첫 번째 값으로 초기화
                // f32MaxFlowHz = FlowInit.f32InitFlowHzData[0];

                // // 나머지 값들과 비교하여 최대값 찾기
                // for(i = 1; i < FLOW_INIT_DATA_SIZE; i++)
                // {
                //     if(FlowInit.f32InitFlowHzData[i] > f32MaxFlowHz)
                //     {
                //         f32MaxFlowHz = FlowInit.f32InitFlowHzData[i];
                //     }
                // }

                // // 최대값을 최종 결과에 할당
                // FlowInit.f32InitFlowHz = f32MaxFlowHz;

                // CLI 디버깅 출력
                dlog(SYSMOD, INFO, ("CLI - FlowInitFlowHz : %.1f \r\n", FlowInit.f32InitFlowHz));
            }
            break;
    }

    if(GetFlowInitFlowHz() > 0)
    {
        u8Return = SET;
    }

    return u8Return;
}
