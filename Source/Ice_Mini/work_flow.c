
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "work_flow.h"
#include    "M8_Ice_Making.h"

typedef struct _drain_flow_
{
    U8  u8FlowMeter;                   /* 제빙수 유량센서 플래그 */
    I16 gu16IceMakeBeforeFlowHz;       /* 제빙수 전 유량센서 측정값 */
    I16 gu16IceMakeAfterFlowHz;        /* 제빙수 후 유량센서 측정값 */
    I16 gu16VIcePrevFlowHz;            /* 제빙수 이전 유량센서 측정값 */
    I16 gu16VIceCurFlowHz;             /* 제빙수 현재 유량센서 측정값 */
} DRAIN_FLOW_T;
DRAIN_FLOW_T DrainFlow;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 제빙수 입수유량 설정
***********************************************************************************************************************/
void SetDrainBeforeFlowHz(U16 u16FlowHz)
{
    DrainFlow.gu16IceMakeBeforeFlowHz = u16FlowHz;
}

U16 GetDrainBeforeFlowHz(void)
{
    return DrainFlow.gu16IceMakeBeforeFlowHz;
}

void SetDrainAfterFlowHz(U16 u16FlowHz)
{
    DrainFlow.gu16IceMakeAfterFlowHz = u16FlowHz;
}

U16 GetDrainAfterFlowHz(void)
{
    return DrainFlow.gu16IceMakeAfterFlowHz;
}

void SetDrainPrevFlowHz(U16 u16FlowHz)
{
    DrainFlow.gu16VIcePrevFlowHz = u16FlowHz;
}

U16 GetDrainPrevFlowHz(void)
{
    return DrainFlow.gu16VIcePrevFlowHz;
}

void SetDrainCurFlowHz(U16 u16FlowHz)
{
    DrainFlow.gu16VIceCurFlowHz = u16FlowHz;
}

U16 GetDrainCurFlowHz(void)
{
    return DrainFlow.gu16VIceCurFlowHz;
}

// 총 제빙에 사용된 물량 계산 (Hz단위를 cc단위로 변환해야됨)
U16 GetDrainFlow(void)
{
    if(((DrainFlow.gu16IceMakeBeforeFlowHz - DrainFlow.gu16IceMakeAfterFlowHz) - GetCCToHz(15)) > 0)
    {
        // 트레이에 남는 물, 드레인탱크에 남는 물, 오차(기타손실) 등을 생각해서 +10cc 보정
        //    return ((DrainFlow.gu16IceMakeBeforeFlowHz - DrainFlow.gu16IceMakeAfterFlowHz) + GetCCToHz(10));
        // 오차 -15cc로 보정
        return (U16)((DrainFlow.gu16IceMakeBeforeFlowHz - DrainFlow.gu16IceMakeAfterFlowHz) - GetCCToHz(15));
    }
    else
    {
        return 0;
    }
}

// CC단위를 Hz단위로 변환
U16 GetCCToHz(U16 u16CC)
{
    F32 OneCC = 3.32F;
    return (U16)(u16CC * OneCC);
}

// 배수유량이 입수유량의 +5%보다 크면 OK
// SET : 케이스 사용 가능
// CLEAR : 케이스 사용 불가


F32 SetValidGain(void)
{
    F32 mf32_isvalid = INVALID;

    U16 mu16_cur_flow = GetDrainCurFlowHz();
    U16 mu16_prev_flow = GetDrainPrevFlowHz();
    F32 mf32_diff = 0.0F;

    // 현재 유량이 이전 유량보다 크면 차이를 계산
    if(mu16_cur_flow > mu16_prev_flow)
    {
        mf32_diff = (F32)(mu16_cur_flow - mu16_prev_flow);
    }
    else
    {
        mf32_diff = (F32)(mu16_prev_flow - mu16_cur_flow);
    }

    // 배수유량이 입수유량의 +5%보다 크면 NG
    if(DrainFlow.gu16IceMakeAfterFlowHz > (U16)(DrainFlow.gu16IceMakeBeforeFlowHz * 1.05))
    {
        return INVALID;
    }
    // 배수유량이 입수유량보다 크거나, 차이가 80cc 이상이면 의심
    else if((DrainFlow.gu16IceMakeAfterFlowHz > DrainFlow.gu16IceMakeBeforeFlowHz)
    || (mf32_diff > (F32)GetCCToHz(80))         // 80cc 이상 차이나면 케이스 의심
    )
    {
        return SUSPECT;
    }
    // 정상
    else
    {
        return VALID;
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
        DrainFlow.gu16IceMakeAfterFlowHz++;
    }

    DrainFlowStop();
}
