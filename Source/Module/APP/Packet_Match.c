#include "Packet_Match.h"

#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M8_Ice_Making.h"
#include    "M9_Front_Communication.h"

#if 1
/* @TODO : 유저용) 외부 변수 참조 및 헤더 참조 */
extern U8 gu8_Amb_Front_Temperature_One_Degree;
extern U8 gu8_Room_Temperature_One_Degree;
extern U8 gu8_Amb_Temperature_One_Degree;
extern U8 gu8_Cold_Temperature_One_Degree;
extern U8 gu8_Hot_Heater_Temperature_One_Degree;
extern U8 gu8_Hot_Out_Temperature_One_Degree;
extern U8 get_cold_mode_comp_rps(void);
extern U8 get_ice_mode_comp_rps(void);
extern U8 gu8BLDCErrorNum;
extern bit F_Cold_Operation_Init;
extern U16 gu16_Ice_Tray_Fill_Hz;
extern U8 gu8_Cold_Temperature_One_Degree;
extern U8 gu8_Hot_Heater_Temperature_One_Degree;
extern U8 gu8_Hot_Out_Temperature_One_Degree;
extern bit bit_nos_output;
extern U8 u8RoomInValveON;
extern bit F_Drain_Pump_Output;
extern bit F_Tank_Cover_Input;
extern U16 gu16IceMakeTime;
extern U16 gu16CompOffDelay;
extern U8 gu8_bldc_target_hz;
extern U16 gu16_test_cold_on_temp;
extern U16 gu16_test_cold_off_temp;
extern U16 gu16_test_cold_delay_time;
extern U8 gu8_cristal_timer;
extern bit F_Safety_Routine;
extern U8 gu8IceLEV;
extern bit bit_cold_first_op;
extern bit F_IceInit;
extern bit bit_filter_reed;
extern bit bit_filter_cover;
extern U8 gu8_GasSwitch_Status;
extern bit F_Comp_Output;
#endif

F0_COMMON_SYSTEM_DATA_FIELD F0Data = {0, };
F1_COLD_SYSTEM_DATA_FIELD F1Data = {0, };
F2_HEATING_SYSTEM_DATA_FIELD F2Data = {0, };
B1_COLD_TABLE_DATA_FIELD B1Data = {0, };
B2_ICE_MAKE_TABLE_DATA_FIELD B2Data = {0, };
B4_ICE_STORAGE_TABLE_DATA_FIELD B4Data = {0, };
Freezing_Table_T FreezingTable;

/* F0Data를 바이트 배열로 복사하는 함수 241212 */
void Get_F0_Data_Bytes(U8 *dest_buf, U8 length)
{
    U8 u8Index = 0;
    // U8 copy_length = (length < PROTOCOL_F0_LENGTH) ? length : PROTOCOL_F0_LENGTH;

    for(u8Index = 0; u8Index < length; u8Index++)
    {
        dest_buf[u8Index] = ((U8*)&F0Data)[u8Index];
    }
}

/* F1Data를 바이트 배열로 복사하는 함수 241212 */
void Get_F1_Data_Bytes(U8 *dest_buf, U8 length)
{
    U8 u8Index = 0;
    // U8 copy_length = (length < PROTOCOL_F1_LENGTH) ? length : PROTOCOL_F1_LENGTH;

    for(u8Index = 0; u8Index < length; u8Index++)
    {
        dest_buf[u8Index] = ((U8*)&F1Data)[u8Index];
    }
}

/***************************************************************************************/
/**
* @brief 커맨드 F0의 프로토콜 데이터필드
* @details 커맨드 F0의 프로토콜 데이터필드를 사용자의 변수를 채우는 함수
*/
void Parse_F0_Protocol(void)
{
    /* 센서류 (DATAFIELD 1-13) */
    F0Data.u8AmbTemp1 = gu8_Amb_Front_Temperature_One_Degree;        // CMD 1: 외기온도 1
    F0Data.u8InletWaterTemp = gu8_Room_Temperature_One_Degree;      // CMD 2: 입수온도
    F0Data.u8PurifiedWaterTemp = 0;                                  // CMD 3: 정수온도
    F0Data.u8AmbTemp2 = gu8_Amb_Temperature_One_Degree;                                           // CMD 4: 외기온도 2
    F0Data.u8ColdWaterTemp = gu8_Cold_Temperature_One_Degree;       // CMD 5: 냉수온도
    F0Data.u8HeaterInternalTemp = gu8_Hot_Heater_Temperature_One_Degree; // CMD 6: 히터 내부온도
    F0Data.u8HotWaterOutletTemp = gu8_Hot_Out_Temperature_One_Degree; // CMD 7: 온수 출수온도

    /* 밸브 상태 (DATAFIELD 14-38) */
    // NOS 밸브: 1=CLOSE, 0=OPEN
    F0Data.u8ValveNOS1 = pVALVE_NOS;                                 // CMD 75: 밸브 NOS 1
    F0Data.u8ValveNOS2 = pVALVE_HOT_DRAIN;                                           // CMD 76: 밸브 NOS 2
    F0Data.u8ValveNOS3 = pVALVE_COLD_DRAIN;                                           // CMD 77: 밸브 NOS 3
    F0Data.u8ValveNOS4 = pVALVE_HOT_COLD_OVERFLOW;                                           // CMD 78: 밸브 NOS 4
    F0Data.u8ValveNOS5 = 1;                                           // CMD 79: 밸브 N
    // FEED 밸브: 1=OPEN, 0=CLOSE
    F0Data.u8ValveFEED1 = pVALVE_ROOM_IN;                                          // CMD 80: 밸브 FEED 1
    F0Data.u8ValveFEED2 = pVALVE_HOT_IN;                                          // CMD 81: 밸브 FEED 2
    F0Data.u8ValveFEED3 = pVALVE_COLD_IN;                                          // CMD 82: 밸브 FEED 3
    F0Data.u8ValveFEED4 = pVALVE_ICE_TRAY_IN;                                          // CMD 83: 밸브 FEED 4
    F0Data.u8ValveFEED5 = pVALVE_ROOM_COLD_EXTRACT;                                          // CMD 84: 밸브 FEED 5
    F0Data.u8ValveFEED6 = pVALVE_HOT_OUT;                                          // CMD 85: 밸브 FEED 6
    F0Data.u8ValveFEED7 = pVALVE_ICE_WATER_EXTRACT;                                          // CMD 86: 밸브 FEED 7
    F0Data.u8ValveFEED8 = 0;                                          // CMD 87: 밸브 FEED 8
    F0Data.u8ValveFEED9 = 0;                                          // CMD 88: 밸브 FEED 9
    F0Data.u8ValveFEED10 = 0;                                         // CMD 89: 밸브 FEED 10
    F0Data.u8ValveFEED11 = 0;                                         // CMD 90: 밸브 FEED 11
    F0Data.u8ValveFEED12 = 0;                                         // CMD 91: 밸브 FEED 12
    F0Data.u8ValveFEED13 = 0;                                         // CMD 92: 밸브 FEED 13
    F0Data.u8ValveFEED14 = 0;                                         // CMD 93: 밸브 FEED 14
    F0Data.u8ValveFEED15 = 0;                                          // CMD 94: 밸브 FEED 15

    F0Data.u8FilterReed = bit_filter_reed;                                // CMD 95: 필터 리드
    F0Data.u8FrontReed = bit_filter_cover;                                  // CMD 96: 프론트 리드
}

/***************************************************************************************/
/**
* @brief 커맨드 F1의 프로토콜 데이터필드
* @details 커맨드 F1의 프로토콜 데이터필드를 사용자의 변수를 채우는 함수
*/
void Parse_F1_Protocol(void)
{
    /* 공조시스템 (DATAFIELD 1-13) */
    F1Data.u8RefValve1Pos = gu8_GasSwitch_Status;
    F1Data.u8RefValve2Pos = 0;
    F1Data.u8CompOutputStatus = ((F_Comp_Output == SET) ? 1 : 0);
    F1Data.u8CompStableTimeHigh = (U8)(gu16CompOffDelay >> 8);
    F1Data.u8CompStableTimeLow = (U8)(gu16CompOffDelay);
    F1Data.u8CompCurrentRPS = gu8_bldc_target_hz;
    F1Data.u8CompErrorCode = gu8BLDCErrorNum;
    F1Data.u8CompFanOutput = pDC_FAN;
    F1Data.u8IceTankFanOutput = 0;

    /* 냉각 데이터 (DATAFIELD 14-26) */
    F1Data.u8CoolingOpStatus = (U8)(Bit0_Cold_Make_Go);
    F1Data.u8CoolingInitStart = (U8)bit_cold_first_op;
    F1Data.u8CoolingTargetRPS = (B1Data.u8ColdTargetRPS > 0) ? B1Data.u8ColdTargetRPS : get_cold_mode_comp_rps();
    F1Data.u8CoolingOnTemp = (B1Data.u8ColdOnTemp > 0) ? B1Data.u8ColdOnTemp : (U8)gu16_test_cold_on_temp;
    F1Data.u8CoolingOffTemp = (B1Data.u8ColdOffTemp > 0) ? B1Data.u8ColdOffTemp : (U8)gu16_test_cold_off_temp;
    F1Data.u8CoolingAddStartTime_H = (B1Data.u16ColdDelayTime > 0) ? (U8)(B1Data.u16ColdDelayTime >> 8) : (U8)(gu16_test_cold_delay_time >> 8);
    F1Data.u8CoolingAddStartTime_L = (B1Data.u16ColdDelayTime > 0) ? (U8)(B1Data.u16ColdDelayTime) : (U8)(gu16_test_cold_delay_time);

    /* 제빙 데이터 (DATAFIELD 27-47) */
    if(F_IceInit == SET)
    {
        F1Data.u8IceMakingStep = 255;
    }
    else
    {
        F1Data.u8IceMakingStep = GetIceStep();
    }

    F1Data.u8IceMakingTargetRPS = get_ice_mode_comp_rps();
    F1Data.u8IceMakingTimeHigh = (U8)((gu16IceMakeTime >> 8) & 0xFF); // CMD 42: 제빙시간 [HIGH]
    F1Data.u8IceMakingTimeLow = (U8)(gu16IceMakeTime & 0xFF);         // CMD 43: 제빙시간 [LOW]
    F1Data.u8InletWaterCapHigh = GetB2TrayIn_Hz() > 0 ? (U8)((GetB2TrayIn_Hz() >> 8) & 0xFF) : (U8)((gu16_Ice_Tray_Fill_Hz >> 8) & 0xFF); // CMD 44: 입수 용량 [HIGH]
    F1Data.u8InletWaterCapLow = GetB2TrayIn_Hz() > 0 ? (U8)(GetB2TrayIn_Hz() & 0xFF) : (U8)(gu16_Ice_Tray_Fill_Hz & 0xFF);   // CMD 45: 입수 용량 [LOW]
    F1Data.u8SwingBarOnTime = GetB2SwingbarOn() > 0 ? GetB2SwingbarOn() : 2;                                      // CMD 46: 스윙바 ON 시간
    F1Data.u8SwingBarOffTime = GetB2SwingbarOff() > 0 ? GetB2SwingbarOff() : 6;                                     // CMD 47: 스윙바 OFF 시간
    F1Data.u8IceTrayPosition = gu8IceLEV;                                    // CMD 48: 제빙 트레이 위치
    F1Data.u8IceJamStatus = F_Safety_Routine;

    /* 보냉 데이터 (DATAFIELD 48-62) */
    F1Data.u8KeepColdStep = GetB4IceStorageTargetRPS() > 0 ? GetB4IceStorageTargetRPS() : 0;
    F1Data.u8KeepColdTargetRPS = GetB4IceStorageTargetRPS() > 0 ? GetB4IceStorageTargetRPS() : 0;
    F1Data.u8KeepColdTargetTemp = GetB4TargetTemp() > 0 ? GetB4TargetTemp() : 0;
    F1Data.u8KeepColdFirstTargetTemp = GetB4TargetTempFirst() > 0 ? GetB4TargetTempFirst() : 0;
    F1Data.u8KeepColdTrayPosition = GetB4TrayPosition() > 0 ? GetB4TrayPosition() : gu8IceLEV;

    /* 드레인 탱크 (DATAFIELD 63-71) */
    F1Data.u8DrainTankLowLevel = (Bit0_Drain_Water_Empty == SET) ? 1 : 0;
    F1Data.u8DrainTankFullLevel = (Bit2_Drain_Water_High == SET) ? 1 : 0;
    F1Data.u8DrainWaterLevelStatus = u8DrainWaterLevel;
    F1Data.u8DrainPumpOutput = F_Drain_Pump_Output;

    /* 기타 (DATAFIELD 72-74) */
    F1Data.u8IceTankCover = F_Tank_Cover_Input;
 }

void Parse_F2_Protocol(void)
{

}

/***************************************************************************************/
/**
* @brief 커맨드 B1 (냉각 디버깅 데이터)의 프로토콜 데이터필드
* @details PC → 제품 방향으로 고정값을 받아서 쓰는 함수
*/
void Parse_B1_Protocol(U8 *buf)
{
    B1Data.u8ColdTargetRPS = buf[4];
    B1Data.u8ColdOnTemp = buf[5];
    B1Data.u8ColdOffTemp = buf[6];
    B1Data.u16ColdDelayTime = (U16)((U16)buf[7] << 8 | buf[8]);
}

/***************************************************************************************/
/**
* @brief 커맨드 B2 (제빙 디버깅 데이터)의 프로토콜 데이터필드
* @details PC → 제품 방향으로 고정값을 받아서 쓰는 함수
*/
void Parse_B2_Protocol(U8 *buf)
{
    B2Data.u8IceMakeTargetRPS = buf[4];
    B2Data.u16TrayIn_Hz = (U16)((U16)buf[5] << 8 | buf[6]);
    B2Data.u8SwingbarOn = buf[7];
    B2Data.u8SwingbarOff = buf[8];
}

/***************************************************************************************/
/**
* @brief 커맨드 B4 (보냉 디버깅 데이터)의 프로토콜 데이터필드
* @details PC → 제품 방향으로 고정값을 받아서 쓰는 함수
*/
void Parse_B4_Protocol(U8 *buf)
{
    B4Data.u8IceStorageTargetRPS = buf[4];
    B4Data.u8TargetTemp = buf[5];
    B4Data.u8TargetTempFirst = buf[6];
    B4Data.u8TrayPosition = buf[7];
}

/***********************************************************************************************************************
* Function Name: FreezingTable_Init
* Description  : 제빙 시간 테이블 초기화
***********************************************************************************************************************/
void FreezingTable_Init(void)
{
    U8 i;
    SetUsedFreezingTable(CLEAR);

    for(i = 0; i < 46; i++)
    {
        FreezingTable.MakeTime[i] = 0;
    }
}

/***********************************************************************************************************************
* Function Name: SetFreezingTable
* Description  : 제빙 시간 테이블에 제빙 시간을 설정
* Input        : DataBuffer : 제빙 시간 데이터 버퍼 (92바이트: 46개의 U16 값)
* Output       : 제빙 시간 데이터 버퍼
* Return       : 제빙 시간 데이터 버퍼
***********************************************************************************************************************/
void SetFreezingTable(U8 *DataBuffer)
{
    U8 i;
    U8 dataIndex = 0;

    // DATAFIELD의 데이터를 2BYTE씩 받아서 FreezingTable.MakeTime[0]~[45]에 저장
    // 상위1BYTE, 하위1BYTE를 조합하여 U16 값 생성
    for(i = 0; i < 46; i++)
    {
        FreezingTable.MakeTime[i] = (U16)((U16)DataBuffer[dataIndex] << 8) | DataBuffer[dataIndex + 1];
        dataIndex += 2;
    }
}

/***********************************************************************************************************************
* Function Name: GetUsedFreezingTable
* Description  : 제빙 시간 테이블 사용 여부를 가져옴
***********************************************************************************************************************/
U8 GetUsedFreezingTable(void)
{
    return FreezingTable.Used;
}

/***********************************************************************************************************************
* Function Name: SetUsedFreezingTable
* Description  : 제빙 시간 테이블 사용 여부를 설정
* Input        : Used : 사용 여부
***********************************************************************************************************************/
void SetUsedFreezingTable(U8 Used)
{
    FreezingTable.Used = Used;
}

/*****************************************************************************
* Function Name: GetFreezingTime
* Description  : 제빙 시간 테이블에서 제빙 시간을 가져옴
* Input        : RoomInTemp : 입수온도
* Output       : 제빙 시간
* Return       : 제빙 시간
******************************************************************************/
U16 GetFreezingTime(U8 AmbTemp)
{
    return FreezingTable.MakeTime[AmbTemp];
}

U8 GetB1ColdTargetRPS(void)
{
    return B1Data.u8ColdTargetRPS;
}

void SetB1ColdTargetRPS(U8 *u8ColdTargetRPS)
{
    *u8ColdTargetRPS = B1Data.u8ColdTargetRPS;
}

U8 GetB1ColdOnTemp(void)
{
    return B1Data.u8ColdOnTemp;
}

void SetB1ColdOnTemp(U8 *u8ColdOnTemp)
{
    *u8ColdOnTemp = B1Data.u8ColdOnTemp;
}

U8 GetB1ColdOffTemp(void)
{
    return B1Data.u8ColdOffTemp;
}

void SetB1ColdOffTemp(U8 *u8ColdOffTemp)
{
    *u8ColdOffTemp = B1Data.u8ColdOffTemp;
}

U16 GetB1ColdDelayTime(void)
{
    return B1Data.u16ColdDelayTime;
}

void SetB1ColdDelayTime(U16 *u16ColdDelayTime)
{
    *u16ColdDelayTime = B1Data.u16ColdDelayTime;
}

void SetB2IceMakeTargetRPS(U8 *u8IceMakeTargetRPS)
{
    *u8IceMakeTargetRPS = B2Data.u8IceMakeTargetRPS;
}

U8 GetB2IceMakeTargetRPS(void)
{
    return B2Data.u8IceMakeTargetRPS;
}

void SetB2TrayIn_Hz(U16 *u16TrayIn_Hz)
{
    *u16TrayIn_Hz = B2Data.u16TrayIn_Hz;
}

U16 GetB2TrayIn_Hz(void)
{
    return B2Data.u16TrayIn_Hz;
}

void SetB2SwingbarOn(U8 *u8SwingbarOn)
{
    *u8SwingbarOn = B2Data.u8SwingbarOn;
}

U8 GetB2SwingbarOn(void)
{
    return B2Data.u8SwingbarOn;
}

void SetB2SwingbarOff(U8 *u8SwingbarOff)
{
    *u8SwingbarOff = B2Data.u8SwingbarOff;
}

U8 GetB2SwingbarOff(void)
{
    return B2Data.u8SwingbarOff;
}

void SetB4IceStorageTargetRPS(U8 *u8IceStorageTargetRPS)
{
    *u8IceStorageTargetRPS = B4Data.u8IceStorageTargetRPS;
}

U8 GetB4IceStorageTargetRPS(void)
{
    return B4Data.u8IceStorageTargetRPS;
}

void SetB4TargetTemp(U8 *u8TargetTemp)
{
    *u8TargetTemp = B4Data.u8TargetTemp;
}

U8 GetB4TargetTemp(void)
{
    return B4Data.u8TargetTemp;
}

void SetB4TargetTempFirst(U8 *u8TargetTempFirst)
{
    *u8TargetTempFirst = B4Data.u8TargetTempFirst;
}

U8 GetB4TargetTempFirst(void)
{
    return B4Data.u8TargetTempFirst;
}

void SetB4TrayPosition(U8 *u8TrayPosition)
{
    *u8TrayPosition = B4Data.u8TrayPosition;
}

U8 GetB4TrayPosition(void)
{
    return B4Data.u8TrayPosition;
}
