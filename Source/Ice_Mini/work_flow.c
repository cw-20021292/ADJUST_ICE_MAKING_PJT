
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "work_flow.h"
#include    "M8_Ice_Making.h"

typedef struct _drain_flow_
{
    U8  u8FlowMeter;                   /* 제빙수 유량센서 플래그 */
    F32 f32IceMakeBeforeFlowHz;       /* 제빙수 전 유량센서 측정값 */
    F32 f32IceMakeAfterFlowHz;        /* 제빙수 후 유량센서 측정값 */
    F32 f32VIcePrevFlowHz;            /* 제빙수 이전 유량센서 측정값 */
    F32 f32VIceCurFlowHz;             /* 제빙수 현재 유량센서 측정값 */
} DRAIN_FLOW_T;
DRAIN_FLOW_T DrainFlow;

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

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 제빙수 드레인 유량센서 시작
***********************************************************************************************************************/
void DrainFlowStart(void)
{
    R_INTC10_Start();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 제빙수 드레인 유량센서 종료
***********************************************************************************************************************/
void DrainFlowStop(void)
{
    R_INTC10_Stop();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 제빙수 드레인 유량센서 입력 카운트
***********************************************************************************************************************/
void DrainFlowInputCount(void)
{
    if(DrainFlow.u8FlowMeter == SET)
    {
        DrainFlow.u8FlowMeter = CLEAR;

        DrainFlowStart();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 제빙수 드레인 유량센서 입력 처리
***********************************************************************************************************************/
void DrainFlowInput(void)
{
    DrainFlow.u8FlowMeter = SET;

    if(GetIceStep() == STATE_41_DRAIN_FLOW_CALCUATE)
    {
        DrainFlow.f32IceMakeAfterFlowHz++;
    }

    DrainFlowStop();
}
