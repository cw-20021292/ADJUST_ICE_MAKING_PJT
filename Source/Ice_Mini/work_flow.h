#ifndef _WORK_FLOW_H_
#define _WORK_FLOW_H_

#include "Macrodriver.h"

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
void SetDrainPrevFlowHz(U16 u16FlowHz);
U16 GetDrainPrevFlowHz(void);
void SetDrainCurFlowHz(U16 u16FlowHz);
U16 GetDrainCurFlowHz(void);
F32 SetValidGain(void);

#endif
