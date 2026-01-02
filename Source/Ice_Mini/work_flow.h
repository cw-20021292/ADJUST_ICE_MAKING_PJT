#ifndef _WORK_FLOW_H_
#define _WORK_FLOW_H_

#include "Macrodriver.h"

void DrainFlowStart(void);
void DrainFlowStop(void);
void DrainFlowInputCount(void);
void DrainFlowInput(void);

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

#endif
