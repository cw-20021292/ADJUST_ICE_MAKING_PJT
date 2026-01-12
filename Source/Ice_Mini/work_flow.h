#ifndef _WORK_FLOW_H_
#define _WORK_FLOW_H_

#include "Macrodriver.h"

typedef enum {
    FLOW_STACK_STEP_INIT,
    FLOW_STACK_STEP_TRAY_UP,
    FLOW_STACK_STEP_TANK_EMPTY,
    FLOW_STACK_STEP_WATER_IN,
    FLOW_STACK_STEP_TANK_DRAIN,
    FLOW_STACK_STEP_TRAY_DOWN,
    FLOW_STACK_STEP_TRAY_DOWN_CHECK,
    FLOW_STACK_STEP_TRAY_WATER_CAL,
    FLOW_STACK_STEP_FINISH,
} FLOW_STACK_STEP;

void DrainFlowStart(void);
void DrainFlowStop(void);
void DrainFlowInputCount(void);
void DrainFlowInput(void);
void SetFlowInitStep(FLOW_STACK_STEP u8Step);
FLOW_STACK_STEP GetFlowInitStep(void);
void SetFlowInitFlowHz(F32 f32FlowHz);
F32 GetFlowInitFlowHz(void);

void SetDrainBeforeFlowHz(F32 f32FlowHz);
F32 GetDrainBeforeFlowHz(void);
void SetDrainAfterFlowHz(F32 f32FlowHz);
F32 GetDrainAfterFlowHz(void);
F32 GetDrainFlow(void);
F32 GetCCToHz(U16 u16CC);
void SetDrainPrevFlowHz(F32 f32FlowHz);
F32 GetDrainPrevFlowHz(void);
void SetDrainCurFlowHz(F32 f32FlowHz);
F32 GetDrainCurFlowHz(void);
F32 SetValidGain(void);

void InitFlowHzDecrease(void);
U8 IceMakeFlowDataStack(void);

// 좆
extern void down_tray_motor(void);
extern void up_tray_motor(void);
extern bit F_TrayMotorDOWN;
extern bit F_TrayMotorUP;
#endif
