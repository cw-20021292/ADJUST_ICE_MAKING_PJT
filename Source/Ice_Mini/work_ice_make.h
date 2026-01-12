#ifndef _WORK_ICE_MAKE_H_
#define _WORK_ICE_MAKE_H_

#include "Macrodriver.h"

#define            ICE_FINGER_NUM       7
#define            ICE_IDEAL_GRAM       9
#define            ICE_V_TARGET         (U16)(ICE_FINGER_NUM * ICE_IDEAL_GRAM)    // 70ml

#define            ICE_MAKE_TIME_MIN        2000
#define            ICE_MAKE_TIME_MAX        21000


#define ZONE_1_GAIN (0.7F)      // 강하게 늘리기
#define ZONE_2_GAIN (0.2F)      // 부드럽게 늘리기
#define ZONE_3_GAIN (0.2F)      // 부드럽게 줄이기
#define ZONE_4_GAIN (0.7F)      // 강하게 줄이기
#define ZONE_5_GAIN (0.05F)     // (정상) 살살 보정 (목표: 60~70ml)


void ProcessIceMaking(void);
void SetInterruption(U8 u8Interruption);
U8 GetInterruption(void);
void SetGain(F32 f32Gain);
F32 GetGain(void);
void SetRatio(F32 f32Ratio);
F32 GetRatio(void);
void SetTarget(F32 Target);
F32 GetTarget(void);
void SetNextIceMakeTime(U16 NextIceMakeTime);
U16 GetNextIceMakeTime(void);
void SetThisTimeIceMakeTime(U16 ThisTimeIceMakeTime);
U16 GetThisTimeIceMakeTime(void);
static void SetTheoryRatio(F32 Avg);
U8 GetErrorCount(void);

#endif
