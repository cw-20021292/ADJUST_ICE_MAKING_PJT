
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "work_flow.h"
#include    "M8_Ice_Making.h"

typedef struct _drain_flow_
{
    U8  u8FlowMeter;                   /* 제빙수 유량센서 플래그 */
    I16 i16IceMakeBeforeFlowHz;       /* 제빙수 전 유량센서 측정값 */
    I16 i16IceMakeAfterFlowHz;        /* 제빙수 후 유량센서 측정값 */
    I16 i16VIcePrevFlowHz;            /* 제빙수 이전 유량센서 측정값 */
    I16 i16VIceCurFlowHz;             /* 제빙수 현재 유량센서 측정값 */
} DRAIN_FLOW_T;
DRAIN_FLOW_T DrainFlow;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 제빙수 입수유량 설정
***********************************************************************************************************************/
void SetDrainBeforeFlowHz(I16 i16FlowHz)
{
    DrainFlow.i16IceMakeBeforeFlowHz = i16FlowHz;
}

I16 GetDrainBeforeFlowHz(void)
{
    return DrainFlow.i16IceMakeBeforeFlowHz;
}

void SetDrainAfterFlowHz(I16 i16FlowHz)
{
    DrainFlow.i16IceMakeAfterFlowHz = i16FlowHz;
}

I16 GetDrainAfterFlowHz(void)
{
    return DrainFlow.i16IceMakeAfterFlowHz;
}

void SetDrainPrevFlowHz(I16 i16FlowHz)
{
    DrainFlow.i16VIcePrevFlowHz = i16FlowHz;
}

I16 GetDrainPrevFlowHz(void)
{
    return DrainFlow.i16VIcePrevFlowHz;
}

void SetDrainCurFlowHz(I16 i16FlowHz)
{
    DrainFlow.i16VIceCurFlowHz = i16FlowHz;
}

I16 GetDrainCurFlowHz(void)
{
    return DrainFlow.i16VIceCurFlowHz;
}

// 총 제빙에 사용된 물량 계산 (Hz단위를 cc단위로 변환해야됨)
I16 GetDrainFlow(void)
{
    if((DrainFlow.i16IceMakeBeforeFlowHz - DrainFlow.i16IceMakeAfterFlowHz) > 0)
    {
        return (DrainFlow.i16IceMakeBeforeFlowHz - DrainFlow.i16IceMakeAfterFlowHz);
    }
    else
    {
        return 0;
    }
}

// CC단위를 Hz단위로 변환
U16 GetCCToHz(U16 u16CC)
{
    F32 OneCC = C_ICE_MAKING;
    return (U16)(u16CC * OneCC);
}

// 배수유량이 입수유량의 +5%보다 크면 OK
// SET : 케이스 사용 가능
// CLEAR : 케이스 사용 불가
F32 SetValidGain(void)
{
    F32 mf32_isvalid = INVALID;

    I16 i16_cur_flow = GetDrainCurFlowHz();
    I16 i16_prev_flow = GetDrainPrevFlowHz();
    F32 mf32_diff = 0.0F;
    mf32_diff = (F32)(i16_cur_flow - i16_prev_flow);

    // 배수유량이 입수유량의 +5%보다 크면 NG
    if(DrainFlow.i16IceMakeAfterFlowHz > (I16)((DrainFlow.i16IceMakeBeforeFlowHz * 1.05)))
    {
        mf32_isvalid = INVALID;
    }
    // 배수유량이 입수유량보다 큰데 +5% 이하면 의심
    else if(DrainFlow.i16IceMakeAfterFlowHz > DrainFlow.i16IceMakeBeforeFlowHz)
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
        DrainFlow.i16IceMakeAfterFlowHz++;
    }

    DrainFlowStop();
}
