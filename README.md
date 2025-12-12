# ?? Ice-Making Auto Calibration Firmware
**Smart Ice-Making Time Adjustment Algorithm for Embedded Systems**

이 프로젝트는 **제빙 장치(Ice Maker)**에서 발생하는 환경 편차, 유량센서 오차, 냉동 효율 변화 등을 자동으로 보정하여
**항상 목표 제빙량(예: 70ml)을 달성하도록 제빙 시간을 자동 조정하는 펌웨어**입니다.

입수량·냉매 온도·환경 온도·유량센서 오차 때문에 제빙량이 변동되는 실제 상황에서
**Zone 기반 판단 + 비례 제어(Ratio Control)**를 조합한 Closed-loop 보정 시스템을 설계했습니다.

---

## ? 프로젝트 목적

- 제빙량이 부족하거나 과도할 때 **자동으로 제빙시간을 조절**하여 항상 목표 제빙량을 달성
- 유량센서 오차(±5~10%) 또는 계산 편차를 고려한 **강건 제빙 알고리즘(Robust Algorithm)** 구현
- 평균 제빙 유량 기반의 **3-Cycle Rolling Average 필터 적용**
- Zone 기반의 온건/강한 보정(Gain) 구조로 **안정성과 반응성 균형 확보**

---

## ? 주요 기능

### 1. **최근 3회 제빙량 기반 평균 유량 계산**
- 1~3사이클까지는 수집된 히스토리 개수만큼 평균
- 3회 이상부터는 FIFO 방식으로 최근 3개만 사용
- 비정상 흐름에 대한 필터링 효과

// 최근 3개 제빙 유량을 관리하는 FIFO 버퍼 + Rolling Average
IceAdjust.u16IceMakeFlowHistory[0..2]

2. Zone 기반 제빙 상태 판단 (5단계)
| Zone   | 조건      | 의미       | 보정 방향    |
| ------ | ------- | -------- | -------- |
| Zone 1 | > 120ml | 심각 과제빙   | 시간 크게 감소 |
| Zone 2 | > 75ml  | 살짝 과제빙   | 시간 감소    |
| Zone 5 | 50~75ml | 정상(O.K.) | 소폭 보정    |
| Zone 3 | < 50ml  | 부족       | 시간 증가    |
| Zone 4 | < 35ml  | 심각 부족    | 시간 크게 증가 |

3. 비례 제어 기반 자동 보정
ratio_theory = target / avg;
final_ratio  = 1 + gain * (ratio_theory - 1);
NextTime     = CurrTime * final_ratio;

Avg < Target → ratio > 1 → 제빙시간 증가
Avg > Target → ratio < 1 → 제빙시간 감소
즉, 매 제빙 사이클마다 Target에 자동 수렴하는 구조.

4. 센서 이상·극단값 보정 처리
Avg가 10ml 이하인 극단값은 자동 클램핑
Avg ≤ 0 → Ratio = 1.0 (보정 OFF)
유량센서 이상 상태에서는 Gain 자동 축소 → 과보정 방지

5. 안전 제한 로직

최소·최대 제빙시간 범위 강제 적용

한 사이클에서 변화 가능한 시간은 ±600 단위로 제한
→ 제어 안정성 확보(overshoot 방지)
if (NextTime > CurrTime + 600) NextTime = CurrTime + 600;
if (NextTime < CurrTime - 600) NextTime = CurrTime - 600;

? 소스 코드 구조
work_ice_make.c
├─ ProcessIceMaking()       // 메인 로직: 평균 계산 + Zone 판단 + Ratio 계산 + 시간 업데이트
├─ SetTheoryRatio()         // Ratio 계산 핵심 함수
├─ SetGain(), GetGain()     // Zone Gain 접근자
├─ SetNextIceMakeTime()     // 다음 제빙시간 업데이트
└─ IceAdjust (구조체)       // 제빙 로직 상태 저장

? ICE_ADJUST_T 구조체
typedef struct {
    F32 f32Gain;
    U8  u8Cycle;
    F32 f32Target;
    F32 f32Ratio;
    U16 u16NextIceMakeTime;
    U16 u16ThisTimeIceMakeTime;
    I16 i16IceMakeAvgFlow;
    I16 i16IceMakeFlowHistory[3];
} ICE_ADJUST_T;

? 제어 흐름도
DrainFlow 측정
      ↓
최근 3회 평균 계산 (Rolling Avg)
      ↓
Zone 판단 (1~5)
      ↓
Gain 결정
      ↓
Target / Avg 비례계산 (Ratio Control)
      ↓
Next Ice Making Time 결정
      ↓
제한값 적용 (min/max, Δlimit)

? 장점
적응형 제어: 환경 온도, 열교환 효율, 센서 편차 변화에도 자동 적응
안정적 수렴: overshoot 억제 & 빠른 수렴 양쪽 확보
센서 오차에 강함: 3-Cycle 평균 + 최소값 클램핑
유지보수 간편: Gain 변경만으로 튜닝 가능

? 향후 개선 방향 (TODO)
온도/부하 기반의 동적 Target 조정
센서 노이즈 제거용 IIR 필터 추가
제빙 시간?수율 맵핑 기반의 Model-based Control 적용
Web Dashboard(Log viewer) 개발

? Maintainer
Developer: (Park Chanheum)
Embedded Firmware / BLDC / 냉각시스템 제어 로직 설계

