/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _FLOW_SENSOR_INPUT_H_
#define _FLOW_SENSOR_INPUT_H_


//

extern void R_INTC11_Start(void);
extern void R_INTC11_Stop(void);
extern void clac_extract_amount(void);






extern bit F_Effluent_OK;
extern U8 u8Extract_Continue;
extern bit F_WaterOut;
extern bit F_WaterOut_Disable_State;
extern U16 gu16_Ice_Tray_Fill_Hz;
extern U16 u16_user_effluent_hz;
extern U16 gu16_hot_display_hz;

extern ICE_STEP gu8IceStep;

extern bit F_Hot_Filling_Finish;
extern U16 gu16_Filling_Hz;
extern bit bit_tray_pump_output;

extern U8 gu8_ice_tank_ster_step;
extern U16 gu16_Ice_Tank_Ster_Hz;
extern WATER_OUT_STEP gu8_Water_Out_Step;
extern ICE_OUT_STEP gu8_Ice_Out_Step;
extern bit F_IceOut;
extern U16 u16Efluent_Time;

extern bit bit_ice_tank_ster_start;
extern ICE_STER_MODE gu8_ice_ster_mode;
extern U8 gu8_hot_input_ster_step;
extern U16 gu16_Tray_Ster_Hz;
extern U16 gu16_Hot_Ster_Hz;

extern U8 gu8_drain_input_ster_step;


void DrainFlowStart(void);
void DrainFlowStop(void);
void DrainFlowInputCount(void);
void DrainFlowInput(void);

void SetDrainBeforeFlowHz(U16 u16FlowHz);
U16 GetDrainBeforeFlowHz(void);
void SetDrainAfterFlowHz(U16 u16FlowHz);
U16 GetDrainAfterFlowHz(void);
U16 GetDrainFlow(void);
U16 GetCCToHz(U16 u16CC);
#endif

