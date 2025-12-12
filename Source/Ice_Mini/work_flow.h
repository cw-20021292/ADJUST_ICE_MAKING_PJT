#ifndef _WORK_FLOW_H_
#define _WORK_FLOW_H_

#include "Macrodriver.h"

void DrainFlowStart(void);
void DrainFlowStop(void);
void DrainFlowInputCount(void);
void DrainFlowInput(void);

void SetDrainBeforeFlowHz(I16 i16FlowHz);
I16 GetDrainBeforeFlowHz(void);
void SetDrainAfterFlowHz(I16 i16FlowHz);
I16 GetDrainAfterFlowHz(void);
I16 GetDrainFlow(void);
U16 GetCCToHz(U16 u16CC);
void SetDrainPrevFlowHz(I16 i16FlowHz);
I16 GetDrainPrevFlowHz(void);
void SetDrainCurFlowHz(I16 i16FlowHz);
I16 GetDrainCurFlowHz(void);
F32 SetValidGain(void);

#endif
