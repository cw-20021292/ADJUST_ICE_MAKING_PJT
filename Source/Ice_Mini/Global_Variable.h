/***********************************************************************************************************************
 * Version      : BAS25(STEP_UP)
 * File Name    : Remote_Comm.c
 * Device(s)    : R5F100MG
 * Creation Date: 2015/07/31
 * Copyright    : Coway_Electronics Engineering Team (DH,Kim)
 * Description  :
 ***********************************************************************************************************************/

#ifndef _GLOBAL_VAR_H
#define _GLOBAL_VAR_H

/***********************************************************************************************************************/
#include "WIFI_DefUser.h"

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/

/***********************************************************************************************************************/
/* 占쌓쏙옙트占쏙옙占?? 占쏙옙占쏙옙 */
// #define _TEST_MODE_
#ifdef _TEST_MODE_
// #define __ERROR_CLEAR__                  /* 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙 (占쏙옙占쏙옙 占쏙옙占쏙옙) */
// #define __UART_TEST_MODE__               /* 占쌘듸옙占쏙옙占쏙옙占싯삼옙 占쏙옙체占쏙옙占쏙옙占쏙옙 (占쏙옙占쏙옙 占쏙옙占쏙옙) */
// #define _DISPLAY_FCT_SUB_LINE_           /* 占쏙옙占쏙옙트 占싯삼옙 SUB-LINE占쏙옙 */
// #define __DUMMY_PROGRAM__                /* 占쏙옙占쏙옙 占쏙옙占싸그뤄옙 */
// #define FEEDER_SCREW_DIRECTION_BEFORE    /* 占실댐옙占쏙옙크占쏙옙 占쏙옙占쏙옙 (占쏙옙占쏙옙) (占싱곤옙 占쏙옙占쏙옙째占?? 占쏙옙占쏙옙占쏙옙占쏙옙) */
// #define __COLD_OPERATION_LPP__              /* LPP 占쏙옙占쌩삼옙占쏙옙 占쏙옙占쏙옙 占시곤옙占쏙옙占싱븝옙 占쏙옙占쏙옙 (占쏙옙占쏙옙 占쏙옙占쏙옙) */

/* 占쌓쏙옙트占쏙옙占?? 占쏙옙占쏙옙 占싹놂옙占쏙옙 占쏙옙占?? */
// #define __AGING_TEST__
// #define __AC_MOTOR_TEST_MODE__

/* 占쏙옙 占쏙옙 占싹놂옙占쏙옙 占쏙옙占?? */
#ifdef __AGING_TEST__
// #define __HOT_WATER_ENDURANCE__             /* 占쏙옙占쏙옙占쏙옙占쏙옙占싸그뤄옙 : 占승쇽옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 */
// #define __ICE_OUT_ENDURANCE__               /* 占쏙옙占쏙옙占쏙옙占쏙옙占싸그뤄옙 : 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 */
// #define __TRAY_STER_ENDURANCE__             /* 占쏙옙占쏙옙占쏙옙占쏙옙占싸그뤄옙 : 트占쏙옙占쏙옙 占쏙옙占승삼옙占?? 占쏙옙占쏙옙占쏙옙 */
// #define __GYULRO_TEST_ENDURANCE__           /* 占쏙옙占쏙옙占쏙옙占쏙옙占싸그뤄옙 : 占쏙옙占쏙옙謬占쏙옙? 占쏙옙占싸그뤄옙 */
#endif

/* 占쏙옙占쏙옙 占싹놂옙占쏙옙 占쏙옙占?? */
#ifdef __AC_MOTOR_TEST_MODE__
// #define __SCREW_ACC_ENDURANCE__          /* 占쏙옙占쏙옙占쏙옙占쏙옙占싸그뤄옙 : 占쏙옙크占쏙옙 占쏙옙회占쏙옙 占쏙옙占쏙옙占쏙옙 */
// #define __SCREW_AC_ENDURANCE__           /* 占쏙옙占쏙옙占쏙옙占쏙옙占싸그뤄옙 : 占쏙옙크占쏙옙 占쏙옙회占쏙옙 占쏙옙占쏙옙占쏙옙 */
#endif

#endif

/***********************************************************************************************************************/
#define STX 2 // SONIX2349
#define ETX 3
/***********************************************************************************************************************/
#define SETTING_ENABLE 1
#define SETTING_DISABLE 0
/***********************************************************************************************************************/

/***********************************************************************************************************************/

/***********************************************************************************************************************/

typedef enum
{
    LED_Display__VERSION = 0,
    LED_Display__FILTER_COVER_OPEN,
    LED_Display__SLEEP,
    LED_Display__ICE_WATER_EXTRACT,             // 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙표占쏙옙
    LED_Display__MY_WATER_EXTRACT,               // my占쏙옙占쏙옙 占쏙옙占쏙옙표占쏙옙
    LED_Display__WATER_EXTRACT,
    LED_Display__ICE_EXTRACT,
    LED_Display__FLUSHING,
    LED_Display__ERROR,
    LED_Display__MAIN,                      // 占싹반삼옙占쏙옙
    LED_Display__SETTING,
    LED_Display__TIME_SETTING,
    LED_Display__TRAY_CLEAN,
    LED_Display__WIFI_PAIRING,
    LED_Display__ALL_LOCK,
    LED_Display__FOTA_START,
    LED_Display__VOLUME_SETTING,
    LED_Display__MEMENTO,               /* Memento Here! */
    LED_Display__BUTTON_SET,
    LED_Display__MANUAL_DRAIN,          /* 占쏙옙占쏙옙占썲레占쏙옙 */
    LED_Display__SELF_TEST,
    LED_Display__CODY_WATER_LINE_CLEAN, /* Cody Water Line Clean Service */
    LED_Display__INSTRUCTION,
    LED_Display__BRIGHT_TEST,
} LED_STEP;

typedef enum
{
    DISPLAY_TEST_NONE = 0,
    DISPLAY_TEST_START,
    DISPLAY_TEST_BTN1,            // ice 클占쏙옙
    DISPLAY_TEST_BTN2,            // icewater
    DISPLAY_TEST_BTN3,            // hot
    DISPLAY_TEST_BTN4,            // pure
    DISPLAY_TEST_BTN5,            // cold
    DISPLAY_TEST_BTN6,            // amount
    DISPLAY_TEST_BTN6_2,          // MY
    DISPLAY_TEST_BTN7,            // ice size
    DISPLAY_TEST_BTN8,            // ice off
    DISPLAY_TEST_BTN9,            // hot lock
    DISPLAY_TEST_BTN10,           // fast ice
    DISPLAY_TEST_BTN11,           // cold temp
    DISPLAY_TEST_BTN12,           // sleep mode
    DISPLAY_TEST_BTN13,           // ice lock
    DISPLAY_TEST_BTN14,           // all lock
    DISPLAY_TEST_BTN15,           // cold off
    DISPLAY_TEST_BTN_ICE_EXTRACT, // 占쏙옙占쏙옙 占쏙옙占쏙옙
    DISPLAY_TEST_BTN_EXTRACT,     // 占쏙옙 占쏙옙占쏙옙
    DISPLAY_TEST_FINISH,
} DISPLAY_TEST_STEP;

/* Memento Here! */
typedef enum
{
    MEMENTO_DISPLAY_START = 0,
    MEMENTO_DISPLAY_ERROR_1,
    MEMENTO_DISPLAY_ERROR_2,
    MEMENTO_DISPLAY_ERROR_3,
    MEMENTO_DISPLAY_ERROR_4,
    MEMENTO_DISPLAY_ERROR_5,
    MEMENTO_DISPLAY_END,
} DISPLAY_MEMENTO_STEP;

typedef enum
{
    STATE_0_STANDBY = 0,

    STATE_5_PREHEAT_HOTGAS_MOVE = 5,
    STATE_6_CALC_PREHEAT_TIME = 6,
    STATE_7_PREHEAT_OPERATION = 7,

    STATE_10_ICE_TRAY_MOVE_UP = 10,
    STATE_11_WAIT_ROOM_WATER_FULL = 11,
    STATE_12_CONT_ICE_SWITCH_MOVE = 12, /////
    STATE_13_CONT_RPS_SETTING = 13,
    STATE_14_CHECK_ICE_TRAY_HZ = 14,

    STATE_20_WATER_IN_ICE_TRAY = 20,
    STATE_21_ICE_SWITCH_MOVE = 21,

    STATE_22_WAIT_ICE_MAKING_TIME = 22,

    STATE_30_CALC_ICE_MAKING_TIME = 30,
    STATE_31_MAIN_ICE_MAKING = 31,

    STATE_32_DRAIN_EMPTY = 32,         /* [기술과제] 제빙수 투입 전 드레인탱크 비우기 */

    STATE_40_ICE_TRAY_MOVE_DOWN = 40,

    STATE_41_DRAIN_FLOW_CALCUATE = 41,  /* [기술과제] 제빙수 드레인 유량센서 계산 */
    STATE_42_NEXT_ICE_AMOUNT_CAL = 42,  /* [기술과제] 다음 제빙시간 계산 */

    STATE_43_GAS_SWITCH_HOT_GAS = 43,
    STATE_44_CALC_HOT_GAS_TIME = 44,
    STATE_45_ICE_TAKE_OFF = 45,
    STATE_46_FEEDER_OPERATION = 46,

    STATE_50_ICE_FULL_IR_CHECK = 50,
    STATE_51_FINISH_ICE_MAKE = 51,
} ICE_STEP;

typedef enum
{
    ICETRAY_STATE_ICEMAKING = 0,
    ICETRAY_STATE_ICETHROW,
    ICETRAY_STATE_MOVING,
    ICETRAY_STATE_ERROR,
} ICETRAY_STATE;

typedef enum
{
    STATE_0_STANDBY_STATE = 0,

    STATE_10_WATER_IN_FEED_ON_STATE = 10,                      // 占쌉쇽옙占쏙옙占?? ON + OVERFLOW OPEN

    STATE_11_COLD_WATER_PRESSURE_PREVENT_STATE = 11,           // (占시쇽옙 占쏙옙占?? 占쏙옙) OVERFLOW VALVE CLOSE
    STATE_19_HOT_PRE_HEATING_FLOW_ON_STATE = 19,

    STATE_20_HOT_PRE_HEATING_STATE = 20,                       // (占승쇽옙占쏙옙占?? 占시울옙占쏙옙 占쏙옙占쏙옙) 占승쇽옙 占쏙옙占쏙옙
    STATE_21_HOT_PRE_HEATING_BUFFER_DRAIN_STATE = 21,          // (占승쇽옙占쏙옙占?? 占시울옙占쏙옙 占쏙옙占쏙옙) 占승쇽옙 占썲레占쏙옙
    STATE_22_HOT_PRE_HEATING_BUFFER_DRAIN_COMPLETE_STATE = 22, // (占승쇽옙占쏙옙占?? 占시울옙占쏙옙 占쏙옙占쏙옙) 占승쇽옙 占썲레占싸완뤄옙
    STATE_23_HOT_PRE_HEATING_PRESS_DOWN_STATE = 23,

    STATE_30_EXTRACT_VALVE_ON_STATE = 30, // 占쏙옙占쏙옙占쏙옙 ON
    STATE_31_WATER_EXTRACT_STATE = 31,    // 占쏙옙占쏙옙占싹뤄옙 체크
    STATE_32_WATER_AIR_VENT_STATE = 32,   // (占승쇽옙 占쏙옙占?? 占시울옙占쏙옙 占쏙옙占쏙옙) 占쏙옙占쏙옙 占쏙옙占쏘빼占쏙옙
    STATE_33_REMOVE_AIR_STATE = 33,       //
    STATE_40_EXTRACT_VALVE_OFF_STATE = 40, // 占쏙옙占쏙옙占쏙옙 OFF

    STATE_50_FIRST_STANDBY_STATE = 50,
    STATE_51_SECOND_STANDBY_STATE = 51,
} WATER_OUT_STEP;

typedef enum
{
    STATE_0_PREHEAT_PREPARE_STATE = 0,

    STATE_1_PREHEAT_CHECK_OUTAGE_STATE,

    STATE_2_PREHEAT_DRAIN_STATE,

    STATE_3_PREHEAT_CHECK_TIME,

    STATE_4_PREHEAT_OPERATE_STATE
} HOT_WATER_OUT_STEP;

typedef enum
{
    STATE_0_ICE_STANDBY_STATE = 0,

    STATE_10_ICE_EXTRACT_STATE = 10,
    STATE_11_ICE_DELAY_1S_STATE,

    STATE_20_ICEWATER_COLD_FFED_ON_STATE = 20,

    STATE_30_ICEWATER_EXTRACT_VALVE_ON_STATE = 30,
    STATE_31_ICEWATER_EXTRACT_STATE = 31,

    STATE_40_ICEWATER_EXTRACT_VALVE_OFF_STATE = 40,
    STATE_41_ICEWATER_COLD_FEED_OFF_STATE,

    // STATE_42_ICE_SCREW_MOTOR_BACK_STATE,

    STATE_50_ICEWATER_EXTRACT_FINISH_STATE = 50

} ICE_OUT_STEP;

typedef enum
{
    STATE_0_ICE_MELT_STANDBY_STATE = 0,

    STATE_10_ICE_MELT_COLD_FEED_STATE = 10,

    STATE_20_ICE_MELT_HOT_GAS_OPERATE_STATE = 20,

    STATE_30_ICE_MELT_HOT_GAS_WAIT_STATE = 30,

    STATE_40_ICE_MELT_ADD_COLD_FEED_STATE = 40,

    STATE_50_ICE_MELT_REPEAT_DECISION_STATE = 50

} ICE_MELT_STEP;

typedef enum
{
    COLD_TANK_FILL_HZ_SET = 0,      // 占시쇽옙占쏙옙크 채占쏙옙占?? 占쏙옙占쏙옙 확占쏙옙
    COLD_TANK_FILL_DRAIN,           // 占쏙옙占쏙옙占쏙옙? 占싱몌옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
    COLD_TANK_FILL_OVERFLOW_OPEN,   // 占쏙옙占쏙옙占시로울옙 OPEN
    COLD_TANK_FILL_COLD_OPEN,       // 占시쇽옙 占쌉쇽옙 OPEN
    COLD_TANK_FILL_COLD_CLOSE,      // 占시쇽옙 占쌉쇽옙 CLOSE
    COLD_TANK_FILL_OVERFLOW_CLOSE,  // 占쏙옙占쏙옙占시로울옙 CLOSE
} COLD_TANK_FILL_STEP;

typedef enum
{
    COLDTANK_FLUSHING_NONE = 0,     // 占시쇽옙占쏙옙크 占시뤄옙占쏙옙 占쏙옙占쏙옙
    COLDTANK_FLUSHING_INIT,         // 占시쇽옙占쏙옙크 占시뤄옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 확占쏙옙
    COLDTANK_FLUSHING_5MINUTE,      // 占시쇽옙占쏙옙크 占싱뱄옙占쏙옙 占싻어내占쏙옙
    COLDTANK_FLUSHING_DRAIN_READY,  // 占쏙옙占쏙옙占쏙옙? 占쏙옙占쏙옙 占쏙옙占쏙옙 占쌉쇽옙 占쏙옙占??
    COLDTANK_FLUSHING_DRAIN,        // 占쏙옙占쏙옙占쏙옙? 占쏙옙占쏙옙 (占쏙옙占쏙옙 on (占쏙옙占??), 占쌉쇽옙 占쏙옙占??)
    COLDTANK_FLUSHING_FINISH,       // 占시쇽옙占쏙옙크 占시뤄옙占쏙옙 占싹뤄옙
} COLDTANK_FLUSHING_STEP;

typedef enum
{
    HOT_STER_STEP_STANDBY = 0,
    HOT_STER_STEP_VALVE_ON,
    HOT_STER_STEP_WAIT_TRAY_FULL,
    HOT_STER_STEP_TRAY_DOWN,
    HOT_STER_STEP_FINISH,
} HOT_STER_STEP;

typedef enum
{
    TEMP_DISPLAY_0_INIT,
    TEMP_DISPLAY_1_LOW,
    TEMP_DISPLAY_2_MID,
    TEMP_DISPLAY_3_HIGH

} TEMP_DISPLAY;

typedef enum
{
    COOLING_DISPLAY_0_OFF,
    COOLING_DISPLAY_1_OPERATION,
    COOLING_DISPLAY_2_COMPLETE

} COOLING_DISPLAY;

typedef enum
{
    HEATING_DISPLAY_0_INIT,
    HEATING_DISPLAY_1_OFF,
    HEATING_DISPLAY_2_ON

} HEATING_DISPLAY;

typedef enum
{
    DISPLAY_NUM_0,
    DISPLAY_NUM_1,
    DISPLAY_NUM_2,
    DISPLAY_NUM_3,
    DISPLAY_NUM_4,
    DISPLAY_NUM_5,
    DISPLAY_NUM_6,
    DISPLAY_NUM_7,
    DISPLAY_NUM_8,
    DISPLAY_NUM_9,

    DISPLAY_NUM_LARGE_A,
    DISPLAY_NUM_LARGE_F,
    DISPLAY_NUM_SMALL_u,
    DISPLAY_NUM_SMALL_n,
    DISPLAY_NUM_SMALL_o,
    DISPLAY_NUM_LARGE_P,
    DISPLAY_NUM_SMALL_r,
    DISPLAY_NUM_SMALL_t,
    DISPLAY_BAR,
    DISPLAY_NUM_LARGE_E,
    DISPLAY_NUM_LARGE_O,
    DISPLAY_NUM_LARGE_C,
    DISPLAY_NUM_LARGE_H,
    DISPLAY_NUM_LARGE_L,
    DISPLAY_NUM_SMALL_d,
    DISPLAY_NUM_SMALL_b,
    DISPLAY_NUM_LARGE_N,
    DISPLAY_NUM_SMALL_v,

    DISPLAY_NUM_CONTINUE_100,
    DISPLAY_NUM_CONTINUE_010,
    DISPLAY_NUM_CONTINUE_001,

    DISPLAY_NUM_SQUARE_UP,
    DISPLAY_NUM_SQUARE_DOWN,

    DISPLAY_NUM_PREHEAT_UNDER_BAR,
    DISPLAY_NUM_PREHEAT_MIDDLE_BAR,
    DISPLAY_NUM_PREHEAT_UPPER_BAR,

    DISPLAY_OFF
} DISPLAY_DATA;

typedef enum
{
    DISPLAY_THOUSAND_OFF,
    DISPLAY_THOUSAND_UPPER,
    DISPLAY_THOUSAND_LOWER,

    DISPLAY_THOUSAND_NUM_1
} THOUSAND_DISPLAY_DATA;

typedef enum
{
    SETTING_TIME_HOUR,
    SETTING_TIME_MIN,
    SETTING_TIME_FINISH

} TIME_SETTING;

typedef enum
{
    CURRENT_TIME_SETTING_MODE,
    CLEAN_RESERVE_TIME_SETTING_MODE

} TIME_SETTING_MODE;

typedef enum
{
    RECIPE_RAMEN = 0,
    RECIPE_DRIPCOFFEE,
    RECIPE_TEA,
    RECIPE_MY1,
    RECIPE_MY2,
    RECIPE_MY3,
    MY_MAX
} MY_RECIPE_INDEX;

typedef enum
{
	ICEWATER_CUP_LEVEL_1_150ML = 1,
	ICEWATER_CUP_LEVEL_2_250ML = 2,
	ICEWATER_CUP_LEVEL_3_350ML = 3,
	ICEWATER_CUP_LEVEL_4_500ML = 4,
}ICEWATER_CUP_LEVEL;


#define DUTY_100_PERCENT 10
#define DUTY_20_PERCENT 1

#define FIXED_DISPLAY 0
#define DIRECT_DISPLAY 1

typedef enum
{
    DIMMING__PERCENT_ICE_SELECT,
    DIMMING__PERCENT_ICE_WATER_SELECT,

    DIMMING__PERCENT_HOT_SELECT,
    DIMMING__PERCENT_AMBIENT_SELECT,

    DIMMING__PERCENT_COLD_SELECT,
    DIMMING__PERCENT_AMOUNT_SELECT,

    DIMMING__PERCENT_SETTING_ICE_SIZE,
    DIMMING__PERCENT_SETTING_ICE_OFF,

    DIMMING__PERCENT_SETTING_ICE_FIRST,
    DIMMING__PERCENT_SETTING_COLD_TEMP,

    DIMMING__PERCENT_COLD_OFF,              // [占시쇽옙OFF] 2KG 占쌩곤옙 250211 CH.PARK

    DIMMING__PERCENT_SETTING_SLEEP_MODE,
    DIMMING__PERCENT_SETTING_ICE_LOCK,

    DIMMING__PERCENT_SETTING_ALL_LOCK,
    DIMMING__PERCENT_SETTING_HOT_LOCK,

    DIMMING__PERCENT_ICE_FULL_TEXT,         // [占쏙옙占쏙옙占쏙옙占쏙옙] 2KG 占쌩곤옙 250211 CH.PARK
    DIMMING__PERCENT_ICE_SHORTAGE_TEXT,     // [占쏙옙占쏙옙占쏙옙占쏙옙] 2KG 占쌩곤옙 250211 CH.PARK
    DIMMING__PERCENT_UV_STER_TEXT,          // [UV占쏙옙占??] 2KG 占쌩곤옙 250211 CH.PARK

    DIMMING__PERCENT_HOT_STER_TEXT,         // [占쏙옙占승삼옙占??] 2KG 占쌩곤옙 250211 CH.PARK
    DIMMING__PERCENT_SLEEP_ICON,            // [占쏙옙침占쏙옙占??] 2KG 占쌩곤옙 250211 CH.PARK

    DIMMING__PERCENT_EXT_FAUCET_TEXT,       // [占쏙옙占쏙옙커占쏙옙] 2KG 占쌩곤옙 250211 CH.PARK
    DIMMING__PERCENT_ICE_FAUCET_TEXT,       // [占쏙옙占쏙옙占식울옙占??] 2KG 占쌩곤옙 250211 CH.PARK
    DIMMING__PERCENT_ICE_TRAY_TEXT,         // [占쏙옙占쏙옙트占쏙옙占쏙옙] 2KG 占쌩곤옙 250211 CH.PARK
    DIMMING__PERCENT_ICE_STORAGE_BOX_TEXT,  // [占쏙옙占쏙옙占쏙옙占쏙옙占??] 2KG 占쌩곤옙 250211 CH.PARK

    DIMMING__PERCENT_STEP_TEXT,
    DIMMING__PERCENT_CLOCK_COLON_ICON,

    DIMMING__PERCENT_oC_ICON,               // ['C] 2KG 占쌩곤옙 250211 CH.PARK

    DIMMING__PERCENT_FILTER_CLEAN,          // [占쏙옙占쏙옙 占쏙옙척] 2KG 占쌩곤옙 250211 CH.PARK

    DIMMING__PERCENT_WIFI_WHITE_ICON,
    DIMMING__PERCENT_MY_SELECT,

    DIMMING__PERCENT_SUNNY_ICON,            // [占쏙옙占쏙옙] 2KG 占쌩곤옙 250211 CH.PARK
    DIMMING__PERCENT_CLOUD_ICON,            // [占썲림] 2KG 占쌩곤옙 250211 CH.PARK

    DIMMING__PERCENT_RAIN_ICON,             // [占쏙옙] 2KG 占쌩곤옙 250211 CH.PARK
    DIMMING__PERCENT_PERCENT_ICON,

    DIMMING__PERCENT_LITER_TEXT,
    DIMMING__PERCENT_ml_TEXT,

    DIMMING__PERCENT_TEMP_BAR_1_1,
    DIMMING__PERCENT_TEMP_BAR_1_2,

    DIMMING__PERCENT_TEMP_BAR_1_3,
    DIMMING__PERCENT_TEMP_BAR_1_4,
    DIMMING__PERCENT_TEMP_BAR_1_5,          // [占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙] 2KG 占쌩곤옙 250211 CH.PARK

    DIMMING__PERCENT_AMOUNT_BAR_2_1,
    DIMMING__PERCENT_AMOUNT_BAR_2_2,

    DIMMING__PERCENT_AMOUNT_BAR_2_3,
    DIMMING__PERCENT_AMOUNT_BAR_2_4,        // [占쏙옙占쏙옙 占쌓뱄옙째 占쏙옙] 2KG 占쌩곤옙 250211 CH.PARK
    DIMMING__PERCENT_AMOUNT_BAR_CONTINUE,

    DIMMING__PERCENT_RAMEN_TEXT,
    DIMMING__PERCENT_TEA_TEXT,              // [占쏙옙] 2KG 占쌩곤옙 250211 CH.PARK
    DIMMING__PERCENT_DRIP_COFFEE_TEXT,

    DIMMING__PERCENT_MY_1_TEXT,
    DIMMING__PERCENT_MY_2_TEXT,
    DIMMING__PERCENT_MY_3_TEXT,             // [MY3] 2KG 占쌩곤옙 250211 CH.PARK

    DIMMING__PERCENT_ICE_LARGE_TEXT,
    DIMMING__PERCENT_ICE_CENTER_BAR,

    DIMMING__PERCENT_ICE_SMALL_TEXT,

    DIMMING__PERCENT_COLD_HIGH_TEXT,
    DIMMING__PERCENT_COLD_CENTER_BAR,

    DIMMING__PERCENT_COLD_LOW_TEXT,

    DIMMING__PERCENT_ICE_LOCK_ICON,
    DIMMING__PERCENT_HOT_LOCK_ICON,

    DIMMING__PERCENT_COMP_WHITE_DOT,
    DIMMING__PERCENT_RIGHT_SEG_DOT,

    DIMMING__PERCENT_ICE_EXTRACT,
    DIMMING__PERCENT_WATER_EXTRACT,
    DIMMING__PERCENT_ICE_WATER_EXTRACT_OUTER,
    DIMMING__PERCENT_ICE_WATER_EXTRACT_INNER,

    DIMMING__PERCENT_WELCOME_LED,
    DIMMING__PERCENT_WELCOME_LED_2,

    DIMMING__PERCENT_ICE_NORMAL,        // [占싹뱄옙] 2KG 占쌩곤옙 250211 CH.PARK
    DIMMING__PERCENT_ICE_PIECE,         // [占쏙옙占쏙옙] 2KG 占쌩곤옙 250211 CH.PARK

    DIMMING__PERCENT_ICE_EXTRACT_INNER,

    DIMMING__PERCENT_SEG_LEFT_HUNDRED,
    DIMMING__PERCENT_SEG_LEFT_TEN,
    DIMMING__PERCENT_SEG_LEFT_ONE,

    DIMMING__PERCENT_SEG_RIGHT_HUNDRED,
    DIMMING__PERCENT_SEG_RIGHT_TEN,
    DIMMING__PERCENT_SEG_RIGHT_ONE,

    DIMMING__PERCENT_COMP_BLUE_DOT,
    DIMMING__PERCENT_FAST_ICE_ICON,


    DIMMING__PERCENT_MAX

} DIMMING_PERCENT_DATA;

typedef enum
{
    ANIMATION__DIMMING__WATER_OUT,
    ANIMATION__DIMMING__ICE_OUT,
    ANIMATION__DIMMING__FILTER_FLUSHING,
    ANIMATION__DIMMING__CURRENT,
    ANIMATION__DIMMING__PREPARING,
    ANIMATION__DIMMING__ICE_TANK_CLEAN,
    ANIMATION__DIMMING__UV_CARE_UNDERBAR,
    ANIMATION__DIMMING__WATER_TANK,
    ANIMATION__DIMMING__ICE_TRAY,
    ANIMATION__DIMMING__ICE_TANK,
    ANIMATION__DIMMING__LEFT_SEG_1_0_0,
    ANIMATION__DIMMING__LEFT_SEG_0_2_0,
    ANIMATION__DIMMING__LEFT_SEG_0_0_3,
    ANIMATION__DIMMING__RIGHT_SEG_1_0_0,
    ANIMATION__DIMMING__RIGHT_SEG_0_2_0,
    ANIMATION__DIMMING__RIGHT_SEG_0_0_3,

    ANIMATION__DIMMING__oF,
    ANIMATION__DIMMING__PERCENT,
    ANIMATION__DIMMING__oC,
    ANIMATION__DIMMING__Oz,
    ANIMATION__DIMMING__Min_Left,
    ANIMATION__DIMMING__mL,
    ANIMATION__DIMMING__Days_Left,
    // ANIMATION__DIMMING__LEFT_TEMP_BAR,
    // ANIMATION__DIMMING__RIGHT_AMOUNT_BAR,

    ANIMATION__DIMMING__LEFT_SETTING_BAR_1_1,
    ANIMATION__DIMMING__LEFT_SETTING_BAR_1_2,
    ANIMATION__DIMMING__LEFT_SETTING_BAR_1_3,
    ANIMATION__DIMMING__LEFT_SETTING_BAR_1_4,

    ANIMATION__DIMMING__AMOUNT_SETTING_BAR_2_1,
    ANIMATION__DIMMING__AMOUNT_SETTING_BAR_2_2,
    ANIMATION__DIMMING__AMOUNT_SETTING_BAR_2_3,
    ANIMATION__DIMMING__AMOUNT_SETTING_BAR_2_4,
    ANIMATION__DIMMING__AMOUNT_SETTING_BAR_CONTINUE,

    ANIMATION__DIMMING__SETTINGS,
    ANIMATION__DIMMING__ICE,
    ANIMATION__DIMMING__HOT,
    ANIMATION__DIMMING__AMBIENT,
    ANIMATION__DIMMING__COLD,
    ANIMATION__DIMMING__AMOUNT,

    ANIMATION__DIMMING__ECO_ICON,
    ANIMATION__DIMMING__WIFI_ICON,
    ANIMATION__DIMMING__ICE_FIRST_TEXT,
    ANIMATION__DIMMING__ICE_FULL_TEXT,
    ANIMATION__DIMMING__ICE_LOCK_ICON,
    ANIMATION__DIMMING__HOT_LOCK_ICON,

    ANIMATION__DIMMING__SETTING_ICE_FIRST,
    ANIMATION__DIMMING__SETTING_ICE_LOCK,
    ANIMATION__DIMMING__SETTING_HOT_LOCK,
    ANIMATION__DIMMING__SETTING_TOUCH_LOCK,
    ANIMATION__DIMMING__SETTING_ECO_MODE,

    ANIMATION__DIMMING__NEW_ICE_MAKING,
    ANIMATION__DIMMING__NEW_HOT_HEATING,
    ANIMATION__DIMMING__NEW_COLD_COOLING,
    ANIMATION__DIMMING__NEW_LOW_WATER,
    ANIMATION__DIMMING__NEW_REPLACE_FILTER_TEXT,
    ANIMATION__DIMMING__NEW_REPLACE_FILTER_1_NUM,
    ANIMATION__DIMMING__NEW_REPLACE_FILTER_2_NUM,
    ANIMATION__DIMMING__NEW_REPLACE_FILTER_3_NUM

} DIMMING_ANIMATION;

#define START_ANIMATION_DIIMMING 1
#define STOP_ANIMATION_DIIMMING 0

#define DIIMMING__0_PERCENT 0
#define DIIMMING__10_PERCENT 1
#define DIIMMING__20_PERCENT 2
#define DIIMMING__30_PERCENT 3
#define DIIMMING__40_PERCENT 4
#define DIIMMING__50_PERCENT 5
#define DIIMMING__60_PERCENT 6
#define DIIMMING__70_PERCENT 7
#define DIIMMING__80_PERCENT 8
#define DIIMMING__90_PERCENT 9
#define DIIMMING__100_PERCENT 10

#if 0
//1608
#define TOP_ICON__DIMMING__50_PERCENT 7
#define SEGMENT__DIMMING__90_PERCENT 9
#define CENTER_ICON__DIMMING__50_PERCENT 7
#define FUNCTION_ICON__DIMMING__70_PERCENT 7
#define SETTING_TEXT__DIMMING__50_PERCETN 5
#define EXTRACT__DIMMING__40_PERCETN 4
#define ICE_FULL__DIMMING__40_PERCETN 7
#endif

// 2012
#define TOP_ICON__DIMMING__50_PERCENT 7
#define CENTER_ICON__DIMMING__50_PERCENT 7

#define SETTING_TEXT__DIMMING__50_PERCETN 7

#define ICE_FULL__DIMMING__40_PERCETN 7

#define SEGMENT__DIMMING__90_PERCENT            7
#define EXTRACT__DIMMING__40_PERCETN            9
#define WATER_EXTRACT__DIMMING__60_PERCETN      6

#define FUNCTION_ICON__DIMMING__70_PERCENT      8
/*..hui [24-3-27占쏙옙占쏙옙 6:01:33] 占쏙옙占쏙옙占쏙옙.. 占쏙옙占쏙옙占쏙옙占쏙옙 LED 화占쏙옙트 10%, 占쏙옙占쏙옙 10%占쏙옙 占쏙옙占쏙옙 占쏙옙청..*/
#define WIFI_WHITE_LED_70_PERCENT 7
#define WIFI_BLUE_LED_100_PERCENT 10
#define WIFI_BLUE_WITH_WHITE_LED_10_PERCENT 1
#define SLEEP_MODE_DIMMING_PERCENT                  DIIMMING__20_PERCENT
#if 0
//mix
#define TOP_ICON__DIMMING__50_PERCENT 10
#define SEGMENT__DIMMING__90_PERCENT 9
#define CENTER_ICON__DIMMING__50_PERCENT 10
#define FUNCTION_ICON__DIMMING__70_PERCENT 9
#define SETTING_TEXT__DIMMING__50_PERCETN 10
#define EXTRACT__DIMMING__40_PERCETN 6
#define ICE_FULL__DIMMING__40_PERCETN 10
#endif

/*#define EXTRACT_TOTAL_STEP                          5*/
#define EXTRACT_TOTAL_STEP 4

// #define BREATH_ANIMATION_DUTY         40
// #define BREATH_ANIMATION_TIME         150

/*..hui [23-5-24占쏙옙占쏙옙 2:08:22] 1占쏙옙占쌍깍옙 占쏙옙占쏙옙占쏙옙占쏙옙..*/
// #define BREATH_ANIMATION_DUTY         50
// #define BREATH_ANIMATION_TIME         80

/*..hui [23-5-24占쏙옙占쏙옙 2:14:41] 1占쏙옙 占쌍깍옙..*/
// #define BREATH_ANIMATION_DUTY         40
// #define BREATH_ANIMATION_TIME         100

/*..hui [23-5-24占쏙옙占쏙옙 2:09:49] 0.5占쏙옙 占쌍깍옙 占쏙옙占쏙옙占쏙옙占쏙옙..*/
// #define BREATH_ANIMATION_DUTY         50
// #define BREATH_ANIMATION_TIME         40

/*..hui [23-5-24占쏙옙占쏙옙 2:14:01] 0.5占쏙옙 占쌍깍옙..*/
// #define BREATH_ANIMATION_DUTY         40
// #define BREATH_ANIMATION_TIME         50

/*..hui [23-5-31占쏙옙占쏙옙 9:24:07] 0.75占쏙옙 占쌍깍옙..*/
#define BREATH_ANIMATION_DUTY 50
#define BREATH_ANIMATION_TIME 60

/*..hui [23-5-31占쏙옙占쏙옙 9:36:09] 6회.. = 0.75 * 6 = 4.5占쏙옙....*/
//////#define BREATH_FLICKER_COUNT          45

/*..hui [23-5-31占쏙옙占쏙옙 9:36:09] 4회.. = 0.75 * 4 = 3占쏙옙....*/
#define BREATH_FLICKER_COUNT 29

#define LED_SLEEP_ENTER_TIME 6000
#define LED_SLEEP_WAKEUP_TIME 100

typedef enum
{
    DEBUG__COMP_DELAY,
    DEBUG__COLD_TEMP,
    DEBUG__ROOM_TEMP,
    DEBUG__HOT_TEMP,
    DEBUG__MIXING_TEMP,
    DEBUG__OUT_DOOR_FRONT_TEMP,

    DEBUG__OUT_DOOR_SIDE_TEMP,
    DEBUG__OUT_DOOR_FINAL_TEMP,
    /*DEBUG__TRAY_TEMP,*/
    /*DEBUG__TRAY_AVERAGE_TEMP,*/

    DEBUG__EVA_ICE_TEMP,

    DEBUG__FLOW_HZ,
    DEBUG__DRAIN_HZ,

    DEBUG__ICE_FULL_AD,
    DEBUG__LEAK_AD,
    DEBUG__UV_WATER_AD,
    DEBUG__UV_ICE_TANK_AD,
    DEBUG__UV_ICE_TRAY_1_AD,
    DEBUG__UV_ICE_TRAY_2_AD,

    DEBUG__BLDC_TARGET,
    DEBUG__BLDC_OPERATION,
    DEBUG__BLDC_ERROR,
    DEBUG__BLDC_TEMP,

    DEBUG__ICE_STEP,
    DEBUG__ICE_TRAY_INPUT,
    DEBUG__ICE_TRAY_ERROR,
    DEBUG__ICE_WATER_LEVEL,
    DEBUG__ICE_DRAIN_LEVEL,
    DEBUG__FEED_NOS_DCFAN,
    DEBUG__ROOM_COLD_HOT,

    DEBUG__ROOM_FILTER_REED,
    DEBUG__ROOM_TOP_REED,
    DEBUG__COMP_ICEHEATER_HOTHEATER,

    DEBUG__FILTER_CHANGE_TYPE,
    DEBUG__NEO_RESET_DAY,
    DEBUG__RO_RESET_DAY,
    DEBUG__INO_RESET_DAY,
    DEBUG__NEO_WATER_USAGE,
    DEBUG__RO_WATER_USAGE,
    DEBUG__INO_WATER_USAGE,
    DEBUG__STER_LOW_WATER_ERR,
    DEBUG__INO_STER_DRAIN_ERR

} DEBUG_STEP;

typedef enum
{
    FLUSHING_NONE_STATE = 0,

    FLUSHING_STANDBY_STATE,

    FLUSHING_FILTER,
    FLUSHING_FILL_COLD_TANK_START_STATE,
    FLUSHING_FILL_COLD_TANK_FINISH_STATE,
    FLUSHING_COLD_TANK,
    FLUSHING_FILL_HOT_TANK_STATE,
    FLUSHING_SKIP,
    FLUSHING_FINISH_STATE,

} FLUSHING_STEP;

typedef enum
{
    ACID_CLEAN_NONE_STATE = 0,

    ACID_CLEAN_STANDBY,
    ACID_CLEAN_PREPARE,
    ACID_CLEAN_CHANGE_FILTER,
    ACID_CLEAN_WAIT_1_HOUR,
    ACID_CLEAN_RINSE,
    ACID_CLEAN_FINISH
} ACID_CLEAN_STEP;

typedef enum
{
    STER_MODE_NONE_STATE,

    STER_MODE_PREPARE,

    STER_MODE_HOT_PREHEAT,
    STER_MODE_HOT_INPUT_STATE,
    STER_MODE_HOT_WAIT_STATE,

    /* 占썲레占쏙옙占쏙옙크 占쏙옙占?? 占쏙옙占?? 占쌩곤옙 [V1.0.0.5] 250903 CH.PARK */
    STER_MODE_DRAIN_PREHEAT,
    STER_MODE_DRAIN_INPUT_STATE,
    STER_MODE_DRAIN_WAIT_STATE,

    STER_MODE_FINISH

}ICE_STER_MODE;

typedef enum
{
    STEP0_STANDBY,
    STEP1_40MIN_ON,
    STEP2_20MIN_OFF,
    STEP3_40MIN_ON,
    STEP4_120MIN_OFF

} PUMP_RETRY_STEP;

typedef enum
{
    GREEN_WEEK,
    INTENSIVE_WEEK
} POWER_SAVING_STATE;

typedef enum
{
    HOT_STER_TEMP_HIGH_MODE,
    HOT_STER_TEMP_LOW_MODE

} HOT_STER_OP_TEMP;


typedef enum
{
    DC_LOAD__NOS_VALVE,
    DC_LOAD__HOT_OUT_VALVE,
    DC_LOAD__COLD_PURE_OUT_VALVE,
    DC_LOAD__PURE_IN_VALVE,
    DC_LOAD__HOT_IN_VALVE,
    DC_LOAD__HOT_DRAIN_VALVE,
    DC_LOAD__OVERFLOW_VALVE, //cold air
    DC_LOAD__COLD_IN_VALVE,
    DC_LOAD__COLD_DRAIN_VALVE,
    DC_LOAD__ICETRAY_IN_VALVE,
    DC_LOAD__ICE_WATER_EXTRACT_VALVE,       // 2KG MAX

    DC_LOAD__BLDC_COMP,
    DC_LOAD__COLD_FAN,

    AC_LOAD_HOT_TRIAC,
    AC_LOAD_HOT_RELAY,

    DC_LOAD__FLOWVALVE_MOTOR,
    DC_LOAD__FLOW_SENSOR,

    DC_LOAD__UV_FAUCET,
    DC_LOAD__UV_ICE_FAUCET1,
    DC_LOAD__UV_ICE_FAUCET2,
    DC_LOAD__UV_ICE_TANK_1_2,
    DC_LOAD__UV_ICE_TRAY,
    DC_LOAD__UV_ICE_TANK_3,

    DC_LOAD__ICE_FULL_SENSOR,

    DC_LOAD__SWING_BAR,
    DC_LOAD__ICE_TRAY_MOTOR,
    DC_LOAD__MICRO_SWITCH,
    DC_LOAD__ICE_DOOR_MOTOR,
    DC_LOAD__GAS_SWITCH_MOTOR,
    DC_LOAD__DRAIN_PUMP,
    DC_LOAD__DRAIN_PUMP_ERROR_E60,

    DC_LOAD__ICE_DOOR_HEATER,               // 2KG MAX
    DC_LOAD__ICE_CRUSH_MOTOR,               // 2KG MAX
    DC_LOAD__ICE_SELECT_DOOR_MOTOR,         // 2KG MAX

    DC_LOAD__ICE_LACK_SENSOR,               // 2KG MAX

    DC_LOAD__MAX

}SELF_TEST_NO;

#define SELF_TEST_RESULT_DATA_LENGTH  (DC_LOAD__MAX)

typedef union
{
    U8 byte[SELF_TEST_RESULT_DATA_LENGTH * 2];
    U16 word[SELF_TEST_RESULT_DATA_LENGTH];
} TYPE_SELF_TEST_DATA;

typedef enum
{
    STEP_STATE_DEACTIVE = 0,
    STEP_STATE_ACTIVE,
} Step_State;

typedef enum
{
    STEP_DIRECTION_CW = 0,
    STEP_DIRECTION_CCW,
} Step_Direction;

typedef struct tsSTEPMOTOR
{
    U16 TargetPulse;
    U16 NowPulse;
    U16 count;
    Step_Direction Direction;
    Step_State state;
} tsSTEPMOTOR;

typedef enum
{
    ICE_TANK_LOW = 0,
    ICE_TANK_MID,
    ICE_TANK_FULL,
    ICE_TANK_ERROR,
} Ice_Amount;

/* PCH ZZANG */
typedef struct {
    U8 gu8_error_check_timer;
    U8 gu8_error_clear_timer;
    U8 gu8_uv_retry_timer;
    U8 gu8_uv_retry_count;
    U8 gu8_uv_retry_stop_flag;
    U8 gu8_Error_bit;
} UV_Check;

#define WIFI_SELF_TEST_NO_OPERATION 0
#define WIFI_SELF_TEST_START 1
#define WIFI_SELF_TEST_ING 2
#define WIFI_SELF_TEST_FINISH 3
#define WIFI_SELF_TEST_STOP 4
#define WIFI_SELF_TEST_PROHIBIT 5

#define WIFI_SELF_TEST_0_PERCENT 0
#define WIFI_SELF_TEST_10_PERCENT 10
#define WIFI_SELF_TEST_20_PERCENT 20
#define WIFI_SELF_TEST_30_PERCENT 30
#define WIFI_SELF_TEST_40_PERCENT 40
#define WIFI_SELF_TEST_50_PERCENT 50
#define WIFI_SELF_TEST_60_PERCENT 60
#define WIFI_SELF_TEST_70_PERCENT 70
#define WIFI_SELF_TEST_80_PERCENT 80
#define WIFI_SELF_TEST_90_PERCENT 90
#define WIFI_SELF_TEST_100_PERCENT 100

#define SELF_TEST_INITIAL_DATA 0xFFFF
// #define SELF_TEST_SENSOR_ERROR_DATA          130
#define SELF_TEST_SENSOR_ERROR_DATA 255

#define LowByte(data) ((U8)((data) & 0xff))
#define HighByte(data) ((U8)(((data) >> 8) & 0xff))

#define LowWord(data) ((U16)((data) & 0xFFFF))
#define HighWord(data)                  ((U16)(((data) >> 16) & 0xFFFF)

#define BitRead(value, bit) (((value) >> (bit)) & 0x01)
#define BitSet(value, bit) ((value) |= (1UL << (bit)))
#define BitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define BitWrite(value, bit, bitvalue) (bitvalue ? BitSet(value, bit) : BitClear(value, bit))

#define ON_OFF_DISPLAY_OFF 0
#define ON_OFF_DISPLAY_ICE_SET 1
#define ON_OFF_DISPLAY_EXTRA_COLD_STE 2
#define ON_OFF_DISPLAY_STEAM_OFF_SET 4

#define BUTTON_SET_DISPLAY_TIME 30
/***************************************************************************************************************/
#define UV_BOOTING_WAIT_INTERVAL_100MS            (216000)
/***************************************************************************************************************/
#define UV_CARE_WATER_FAUCET_INTERVAL_100MS       (216000)    /* 6占시곤옙 * 60占쏙옙 * 60占쏙옙 * 10 (100MS) */
#define UV_CARE_ICE_FAUCET_INTERVAL_100MS         (216000)    /* 6占시곤옙 * 60占쏙옙 * 60占쏙옙 * 10 (100MS) */
#define UV_CARE_ICE_TANK_1_2_INTERVAL_100MS       (216000)    /* 6占시곤옙 * 60占쏙옙 * 60占쏙옙 * 10 (100MS) */
#define UV_CARE_ICE_TANK_3_INTERVAL_100MS         (216000)    /* 6占시곤옙 * 60占쏙옙 * 60占쏙옙 * 10 (100MS) */
#define UV_CARE_ICE_TRAY_INTERVAL_100MS           (108000)    /* 3占시곤옙 * 60占쏙옙 * 60占쏙옙 * 10 (100MS) */
/***************************************************************************************************************/
#define UV_ON_WATER_FAUCET_TIMER_100MS            (18000)        /* 30占쏙옙 * 60占쏙옙 * 10 (100MS) */
#define UV_ON_ICE_FAUCET_TIMER_100MS              (18000)        /* 30占쏙옙 * 60占쏙옙 * 10 (100MS) */
#define UV_ON_ICE_TANK_1_2_TIMER_100MS            (72000)    /* 2占시곤옙 * 60占쏙옙 * 60占쏙옙 * 10 (100MS) */
#define UV_ON_ICE_TANK_3_TIMER_100MS              (18000)        /* 30占쏙옙 * 60占쏙옙 * 10 (100MS) */
#define UV_ON_ICE_TRAY_TIMER_100MS                (36000)        /* 30占쏙옙 * 60占쏙옙 * 10 (100MS) */
/***************************************************************************************************************/

#if 0
#define C_01_LPM 7
#define C_02_LPM 14
#define C_03_LPM 22
#define C_035_LPM 26
#define C_04_LPM 30
#define C_05_LPM 38
#define C_06_LPM 45
#define C_07_LPM 52
#define C_08_LPM 60
#define C_09_LPM 68
#define C_10_LPM 76
#define C_11_LPM 83
#define C_12_LPM 90
#define C_13_LPM 98
#define C_14_LPM 106
#define C_15_LPM 114
#endif

#if 0
#define C_02_LPM 10
#define C_025_LPM 13
#define C_03_LPM 16
#define C_035_LPM 19
#define C_04_LPM 22
#define C_05_LPM 28
#define C_055_LPM 31
#define C_057_LPM 32
#define C_06_LPM 34
#define C_07_LPM 40
#endif

/*..hui [20-10-14占쏙옙占쏙옙 4:14:19] 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占썸에 占쏙옙占쏙옙 占쏙옙占쏙옙..*/
// #define C_ICE_TRAY_FILL_200CC          1010
/*#define C_ICE_TRAY_FILL_200CC            2500*/
/*..hui [24-4-11占쏙옙占쏙옙 9:18:41] 트占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙. 占쏙옙 10cc 占쏙옙占쏙옙 占쌩곤옙 占쌉쇽옙占쌔억옙占쏙옙..*/
// #define C_ICE_TRAY_FILL_200CC            2680
/*..hui [24-4-11占쏙옙占쏙옙 9:18:41] 트占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙. 占쏙옙 10cc 占쏙옙占쏙옙 占쌩곤옙 占쌉쇽옙占쌔억옙占쏙옙..*/
// #define C_ICE_TRAY_FILL_200CC            1020
// #define C_ICE_TRAY_FILL_200CC 1080 /* 트占쏙옙占쏙옙 占쌉쇽옙 占쏙옙占쏙옙 +60 250224 CH.PARK */
// [2026-01-12] [기술과제] CH.PARK 정확한 입수용량은 약 263ml
#define C_ICE_TRAY_FILL_200CC 980 /* 트占쏙옙占쏙옙 占쌉쇽옙 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占?? -10%占쏙옙 占쏙옙占쏙옙占쏙옙 950 250414 CH.PARK */

#define ICE_MAKE_TIME 899 /* 占쌤깍옙 25'C, 占시쇽옙 占승듸옙 25'C 占쏙옙占쏙옙 */
#define PREHEAT_AMB_TEMP 25

#define HOT_GAS_NOISE_REDUCE_TIME 300

#define HEAT_TORAL_TIME_10_UNDER 5150
#define HEAT_TORAL_TIME_15_UNDER 3600
#define HEAT_TORAL_TIME_20_UNDER 3000
#define HEAT_TORAL_TIME_25_UNDER 2700
#define HEAT_TORAL_TIME_30_UNDER 2700
#define HEAT_TORAL_TIME_35_UNDER 2700
#define HEAT_TORAL_TIME_35_OVER 2700

#define HOT_GAS_TIME_9_UNDER_765S 7650
#define HOT_GAS_TIME_13_UNDER_600S 6000
#define HOT_GAS_TIME_19_UNDER_180S 1800
/*#define HOT_GAS_TIME_24_UNDER_30S           300*/
/*#define HOT_GAS_TIME_29_UNDER_20S           200*/
// #define HOT_GAS_TIME_24_UNDER_30S 350
#define HOT_GAS_TIME_24_UNDER_30S 450       /* V1.0.0.4 탈占쏙옙占시곤옙 10占쏙옙 占쏙옙占쏙옙 (20~24占쏙옙 35占쏙옙 -> 45占쏙옙) 250825 CH.PARK */
// #define HOT_GAS_TIME_29_UNDER_20S 250
#define HOT_GAS_TIME_29_UNDER_20S 350       /* V1.0.0.4 탈占쏙옙占시곤옙 10占쏙옙 占쏙옙占쏙옙 (25~29占쏙옙 25占쏙옙 -> 35占쏙옙) 250825 CH.PARK */
#define HOT_GAS_TIME_30_OVER_15S 150

#define PREHEAT_TIME_14_UNDER_600S 6000
#define PREHEAT_TIME_20_UNDER_360S 3600
#define PREHEAT_TIME_25_UNDER_360S 3600

/*#define HOT_BLOCKED_FLOW_HZ              5*/
// #define HOT_BLOCKED_FLOW_HZ 10
#define HOT_BLOCKED_FLOW_HZ 10

/*#define HOT_FIRST_BLOCKED_FLOW_HZ        14*/
#define HOT_FIRST_BLOCKED_FLOW_HZ 10

#define BUZZER_OFF 0
#define BUZZER_POWER_ON 1
#define BUZZER_EFFLUENT 2
#define BUZZER_EFFLUENT_END 3
#define BUZZER_COOL_SETUP 4
#define BUZZER_COOL_CANCEL 5
#define BUZZER_SELECT 6
#define BUZZER_ERROR 7
#define BUZZER_SETUP 8
#define BUZZER_CANCEL 9
#define BUZZER_EFFLUENT_CONTINUE 10
#define BUZZER_STERILIZE_START 11
#define BUZZER_STERILIZE_END 12
#define BUZZER_AP_CONNECT 13
#define BUZZER_SERVER_CONNECT 14
#define BUZZER_MUTE 15
#define BUZZER_MEMENTO_1 16 /* 占쌨몌옙占쏙옙 1 */
#define BUZZER_MEMENTO_2 17 /* 占쌨몌옙占쏙옙 2 */
#define BUZZER_MEMENTO_3 18 /* 占쌨몌옙占쏙옙 3 */
#define BUZZER_MEMENTO_4 19 /* 占쌨몌옙占쏙옙 4 */
#define BUZZER_MEMENTO_5 20 /* 占쌨몌옙占쏙옙 5 */
#define BUZZER_SETUP_MUTE 30
#define BUZZER_CANCEL_MUTE 31
#define BUZZER_MEMENTO_1_MUTE 32
#define BUZZER_MEMENTO_5_MUTE 33

#define USCAN1 0
#define USCAN2 1
#define USCAN3 2
#define USCAN4 3
#define USCAN5 4
#define USCAN6 5
#define USCAN7 6

#define UControl_Key_Mask 0x00

#define MODEL_CHPI 0
#define MODEL_CPI 1

#define ALTITUDE_1_MODE_HIGH 0
#define ALTITUDE_2_MODE_MID 1
#define ALTITUDE_3_MODE_LOW 2
#define ALTITUDE_4_MODE_VERY_LOW 3

/*#define SLEEP_MODE_HEATER_OFF_TEMP                          80*/
/*#define SLEEP_MODE_HEATER_ON_TEMP                           43*/

/*..hui [24-11-15占쏙옙占쏙옙 4:46:18] 占쏙옙침占쏙옙占??/占싱삼옙占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙恙∽옙占쏙옙占?? 占싻몌옙..*/
#define SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_1 89
#define SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_1 60

#define SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_2 89
#define SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_2 60

#define SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_3 86
#define SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_3 60

#define SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_4 79
#define SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_4 60

#define ALTITUDE_1_MODE_HEATER_OFF_TEMP_AMB_30_OVER 96
#define ALTITUDE_1_MODE_HEATER_ON_TEMP_AMB_30_OVER 88

#define ALTITUDE_1_MODE_HEATER_OFF_TEMP_AMB_30_UNDER 96
#define ALTITUDE_1_MODE_HEATER_ON_TEMP_AMB_30_UNDER 90

/*..hui [24-11-15占쏙옙占쏙옙 4:44:06] 占쏙옙占쏙옙占쏙옙占?? 占쏙옙占쏙옙.. 占시듸옙占쏙옙..*/
#define ALTITUDE_2_MODE_HEATER_OFF_TEMP 91
#define ALTITUDE_2_MODE_HEATER_ON_TEMP 85

#define ALTITUDE_3_MODE_HEATER_OFF_TEMP 86
#define ALTITUDE_3_MODE_HEATER_ON_TEMP 80

#define ALTITUDE_4_MODE_HEATER_OFF_TEMP 79
#define ALTITUDE_4_MODE_HEATER_ON_TEMP 73

#if 0
#define ALTITUDE_2_MODE_HEATER_OFF_TEMP 94
#define ALTITUDE_2_MODE_HEATER_ON_TEMP 86

#define ALTITUDE_3_MODE_HEATER_OFF_TEMP 91
#define ALTITUDE_3_MODE_HEATER_ON_TEMP 83

#define ALTITUDE_4_MODE_HEATER_OFF_TEMP 89
#define ALTITUDE_4_MODE_HEATER_ON_TEMP 81
#endif

/*#define DEV_ADDR_EEP                          0xA0*/ /* Device EEPROM - AT24C02C */

#define DEV_ADDR_EEP 0xAE /* Device EEPROM - ISL12026 */
#define DEV_ADDR_RTC 0xDE /* Device RTC - ISL12026 */

/***********************************************************************************************************************/
#define EEPROM_ADDR_CHECK_START 0x0040
/***********************************************************************************************************************/
/* 占쏙옙占쏙옙횝占쏙옙占?? 占쏙옙占쏙옙 EEPROM 占쏙옙占썲데占쏙옙占쏙옙 */
#define SPECIAL_SETTING_START_ADDR 0x0050
#define SPECIAL_SETTING_LENGTH 16
/***********************************************************************************************************************/
#define EEPROM_ADDR1_COLD_SETTING 0x0050
#define EEPROM_ADDR1_HOT_LOCK 0x0051
#define EEPROM_ADDR1_ALL_LOCK 0x0052
#define EEPROM_ADDR1_MUTE_SETTING 0x0053
#define EEPROM_ADDR1_COLD_LEVEL 0x0054
#define EEPROM_ADDR1_HOT_ENABLE 0x0055
#define EEPROM_ADDR1_INSTALL_FLUSHING 0x0056
#define EEPROM_ADDR1_FILTER_FLUSHING 0x0057
#define EEPROM_ADDR1_FIRST_TIME_SETTING 0x0058
#define EEPROM_ADDR1_SOUND_TYPE 0x0059
#define EEPROM_ADDR1_VOICE_VOLUME 0x005A
#define EEPROM_ADDR1_ALTITUDE 0x005B
#define EEPROM_ADDR1_LANGUAGE_TYPE 0x005C
#define EEPROM_ADDR1_CT_FORCED_FLUSHING 0x005D
#define EEPROM_ADDR1_CT_REPLACE_FILTER 0x005E
// #define EEPROM_ADDR1_COLD_POWER               0x005F
/***********************************************************************************************************************/
#define ICE_SETTING_START_ADDR 0x0060
#define ICE_SETTING_LENGTH 7
/***********************************************************************************************************************/
#define EEPROM_ADDR2_ICE_LOCK 0x0060
#define EEPROM_ADDR2_ICE_ON_OFF 0x0061
#define EEPROM_ADDR2_ICE_MAKE_PRIORITY 0x0062
#define EEPROM_ADDR2_RECOVER_FAST_ICE 0x0063
#define EEPROM_ADDR2_ACID_CLEAN 0x0064
#define EEPROM_ADD2_ICE_SIZE 0x0065  /* 占쏙옙占쏙옙 크占쏙옙 占쌩곤옙 (占쏙옙/占쏙옙) 250224 CH.PARK */
#define EEPROM_ADDR2_ICE_TYPE 0x0066 /* 占쏙옙占쏙옙 타占쏙옙 [占싹뱄옙],[占쏙옙占쏙옙] 占쌩곤옙 250317 CH.PARK */
/***********************************************************************************************************************/

/////////////////////////////////////////////////////////////////////////////
#define FUNCTION_SETTING_START_ADDR 0x0070
#define FUNCTION_SETTING_LENGTH 16

#define EEPROM_ADDR3_OWER_SAVE_SETTING 0x0070
#define EEPROM_ADDR3_CIRCULATION_DRAIN 0x0071
#define EEPROM_ADDR3_AUTO_UV_CONTROL 0x0072
#define EEPROM_ADDR3_EXTRACT_LED_ONOFF 0x0073

#define EEPROM_ADDR3_SMART_UNUSED_TIME 0x0074
#define EEPROM_ADDR3_NOT_USE 0x0075
#define EEPROM_ADDR3_NOT_USE_2 0x0076

#define EEPROM_ADDR3_STEAM_OFF 0x0077
#define EEPROM_ADDR3_PERIOD_STER_HOUR 0x0078
#define EEPROM_ADDR3_PERIOD_STER_MINUTE 0x0079

#define EEPROM_ADDR3_SLEEP_MODE_ENABLE 0x007A
#define EEPROM_ADDR3_SLEEP_START_HOUR 0x007B
#define EEPROM_ADDR3_SLEEP_START_MINUTE 0x007C
#define EEPROM_ADDR3_SLEEP_FINISH_HOUR 0x007D
#define EEPROM_ADDR3_SLEEP_FINISH_MINUTE 0x007E
#define EEPROM_ADDR3_WAIT_MODE_ENABLE   0x007F
/////////////////////////////////////////////////////////////////////////////
#define ETC_SAVE_START_ADDR 0x0080
#define ETC_SAVE_LENGTH 4

#define EEPROM_ADDR4_CUP_LEVEL 0x0080
#define EEPROM_ADDR4_WATER_SELECT_DEFAULT 0x0081
#define EEPROM_ADDR4_ICE_MAKE_ADAPTIVE_HZ_H 0x0082
#define EEPROM_ADDR4_ICE_MAKE_ADAPTIVE_HZ_L 0x0083

/////////////////////////////////////////////////////////////////////////////
#define MEMENTO_START_ADDR 0x0090
#define MEMENTO_LENGTH 5

#define EEPROM_ADDR5_MEMENTO_NUM0 0x0090
#define EEPROM_ADDR5_MEMENTO_NUM1 0x0091
#define EEPROM_ADDR5_MEMENTO_NUM2 0x0092
#define EEPROM_ADDR5_MEMENTO_NUM3 0x0093
#define EEPROM_ADDR5_MEMENTO_NUM4 0x0094
/***********************************************************************************************************************/
#define IOT_FUNCTION_ADDR               0x00A0
#define IOT_FUNCTION_LENGTH             10 // 16
/***********************************************************************************************************************/
#if 0
#define EEPROM_ADDR6_CUP_LEVEL_SELECT 0x00A0
// #define EEPROM_ADDR6_CUP_LEVEL_SELECT_B       0x00A1
#define EEPROM_ADDR6_CUP_LEVEL_ORDER 0x00A2
#define EEPROM_ADDR6_OC_OF_SELECT 0x00A3
#define EEPROM_ADDR6_OZ_ML_SELECT 0x00A4
#define EEPROM_ADDR6_HOT_TEMP_LEVEL_ORDER 0x00A5
#define EEPROM_ADDR6_HOT_TEMP_DEFAULT 0x00A6
#endif

#define EEPROM_ADDR6_HALF_CUP_AMOUNT         0x00A0
#define EEPROM_ADDR6_ONE_CUP_AMOUNT       	 0x00A2
#define EEPROM_ADDR6_TWO_CUP_AMOUNT          0x00A4
#define EEPROM_ADDR6_FOUR_CUP_AMOUNT         0x00A6
#define EEPROM_ADDR6_FOTA_START              0x00A8
#define EEPROM_ADDR6_DRAIN_TANK_STER_COUNT   0x00A9
// #define EEPROM_ADDR6_WATER_USAGE_GAL          0x00A7
// #define EEPROM_ADDR6_WATER_USAGE_GAL_B        0x00A8
// #define EEPROM_ADDR6_FILTER_RESET_DAY_NEO     0x00A9
// #define EEPROM_ADDR6_FILTER_RESET_DAY_NEO_B   0x00AA
// #define EEPROM_ADDR6_FILTER_RESET_DAY_RO      0x00AB
// #define EEPROM_ADDR6_FILTER_RESET_DAY_RO_B    0x00AC

// #define EEPROM_ADDR6_CHILD_LOCK_ENABLE 0x00AD
// #define EEPROM_ADDR6_FOTA_START 0x00AE
// #define EEPROM_ADDR6_FILTER_CHANGE_CYCLE 0x00AF

#define WATER_USAGE_ADDR                        0x00B0
#define WATER_USAGE_LENGTH                      13
#define EEPROM_ADDR7_WATER_USAGE__NEO 0x00B0
#define EEPROM_ADDR7_WATER_USAGE__NEO_B 0x00B1
#define EEPROM_ADDR7_WATER_USAGE__RO 0x00B2
#define EEPROM_ADDR7_WATER_USAGE__RO_B 0x00B3
#define EEPROM_ADDR7_WATER_USAGE__INO 0x00B4
#define EEPROM_ADDR7_WATER_USAGE__INO_B 0x00B5
#define EEPROM_ADDR7_FILTER_RESET_DAY__NEO 0x00B6
#define EEPROM_ADDR7_FILTER_RESET_DAY__NEO_B 0x00B7
#define EEPROM_ADDR7_FILTER_RESET_DAY__RO 0x00B8
#define EEPROM_ADDR7_FILTER_RESET_DAY__RO_B 0x00B9
#define EEPROM_ADDR7_FILTER_RESET_DAY__INO 0x00BA
#define EEPROM_ADDR7_FILTER_RESET_DAY__INO_B 0x00BB
#define EEPROM_ADDR7_FILTER_CHANGE_TYPE 0x00BC
#define EEPROM_ADDR8_STER_DRAIN_STOP 0x00C0
#define EEPROM_ADDR8_STER_LOW_WATER_STOP 0x00C1
#define EEPROM_ADDR_WIFI_POWER 0x00E0   // WIFI On/Off State
#define EEPROM_ADDR_FIRST_PARING 0x00E1 // WIFI First Paring Check
#define EEPROM_ADDR_FOTA_MODULE 0x00E2  // WIFI Module Fota State
#define EEPROM_ADDR_FOTA_MCU 0x00E3     // WIFI MCU Fota State

/////////////////////////////////////////////////////////////////////////////
#define MY_DATA_ADDR                        0x00F0
#define MY_DATA_LENGTH                      13

#define EEPROM_ADDR_MY1_TEMP                0x00F0
#define EEPROM_ADDR_MY1_AMOUNT              0x00F1
#define EEPROM_ADDR_MY1_USE                 0x00F3

#define EEPROM_ADDR_MY2_TEMP                0x00F4
#define EEPROM_ADDR_MY2_AMOUNT              0x00F5
#define EEPROM_ADDR_MY2_USE                 0x00F7

#define EEPROM_ADDR_MY3_TEMP                0x00F8
#define EEPROM_ADDR_MY3_AMOUNT              0x00F9
#define EEPROM_ADDR_MY3_USE                 0x00FB

#define EEPROM_ADDR_MY_DEFAULT              0x00FC

/////////////////////////////////////////////////////////////////////////////
#define HOT_TEMP_ADDR                       0x0100
#define HOT_TEMP_LENGTH                     4

#define EEPROM_ADDR_HOT_TEMP_0              0x0100
#define EEPROM_ADDR_HOT_TEMP_1              0x0101
#define EEPROM_ADDR_HOT_TEMP_2              0x0102
#define EEPROM_ADDR_HOT_TEMP_3              0x0103

/////////////////////////////////////////////////////////////////////////////
#define EEPROM_ADDR_CHECK_END 0x01EA
/***********************************************************************************************************************/
#define DEBUG_DATA_ADDR 0x00C0
#define DEBUG_DATA_LENGTH 2
/***********************************************************************************************************************/
/***********************************************************************************************************************/
#define EEPROM_ADDR_TEST 0x01EC // MAIN PBA TEST  //kdh /*48*/
/***********************************************************************************************************************/
#define WIFI_DATA_ADDR 0x00E0
#define WIFI_DATA_LENGTH 4
/***********************************************************************************************************************/
/* 키 占쌉뤄옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 */
#define KEY_MY_SELECT                       0x00040000     // MY 키
#define KEY_COLD_WATER_OFF                  0x00020000     // 占시쇽옙 OFF 키
#define KEY_ICE_EX                          0x00010000     // 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙키
#define KEY_ICE_SELECT                      0x00008000     // 占쏙옙占쏙옙 키
#define KEY_ICE_WATER_SELECT                0x00004000     // 占쏙옙占쏙옙占쏙옙 키
#define KEY_HOT_SELECT                      0x00002000     // 占승쇽옙 키
#define KEY_AMBIENT_SELECT                  0x00001000     // 占쏙옙占쏙옙 키
#define KEY_COLD_SELECT                     0x00000800     // 占시쇽옙 키
#define KEY_AMOUNT_SELECT                   0x00000400     // 占쎈량 키
#define KEY_SETTING_ICE_SIZE                0x00000200     // 占쏙옙占쏙옙 占쏙옙占?? 키
#define KEY_SETTING_ICE_OFF                 0x00000100     // 占쏙옙占쏙옙OFF 키
#define KEY_SETTING_HOT_LOCK                0x00000080     // 占승쇽옙 占쏙옙占?? 키
#define KEY_SETTING_ICE_FIRST               0x00000040     // 占쏙옙占쏙옙 占쏙옙占쏙옙 키
#define KEY_SETTING_COLD_TEMP               0x00000020     // 占시쇽옙 占쏙옙占쏙옙 키
#define KEY_SETTING_SLEEP_MODE              0x00000010     // 占쏙옙침占쏙옙占?? 키
#define KEY_SETTING_ICE_LOCK                0x00000008     // 占쏙옙占쏙옙 占쏙옙占?? 키
#define KEY_SETTING_ALL_LOCK                0x00000004     // 占쏙옙체 占쏙옙占?? 키
/***********************************************************************************************************************/
#define LONG_KEY_PCB_TEST_MODE                  (KEY_ICE_SELECT + KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT)      /* PBA 占쌓쏙옙트占쏙옙占?? : 占쏙옙占쏙옙+占승쇽옙+占쏙옙占쏙옙+占쎈량 (占쏙옙占쏙옙표占쏙옙 占쏙옙占쏙옙) */
#define LONG_KEY_VOLUME_2S                      (KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT)                                        /* 占쌀몌옙 占쏙옙占쏙옙 : 占쏙옙占쏙옙+占쎈량 (占쏙옙占쏙옙표占쏙옙 占쏙옙占쏙옙) */
#define LONG_KEY_TIME_SETTING                   (KEY_ICE_SELECT + KEY_ICE_WATER_SELECT)                                         /* 占시계설占쏙옙占쏙옙占?? : 占쏙옙占쏙옙占쏙옙+占쏙옙占쏙옙 (占쏙옙占쏙옙표占쏙옙 占쏙옙占쏙옙) */

#define LONG_KEY_MANUAL_FACTORY_TEST            (KEY_ICE_WATER_SELECT + KEY_HOT_SELECT + KEY_AMOUNT_SELECT)                     /* 占쏙옙占쏙옙 占쏙옙均챨占쏙옙占쏙옙 : 占쏙옙占쏙옙占쏙옙+占승쇽옙+占쎈량 */
#define LONG_KEY_FLUSHING_SKIP                  (KEY_ICE_SELECT + KEY_ICE_WATER_SELECT + KEY_AMOUNT_SELECT + KEY_MY_SELECT)     /* 占시뤄옙占쏙옙 占쏙옙킵키 : 占쏙옙占쏙옙+占쏙옙占쏙옙占쏙옙+占쎈량+MY (占쏙옙占쏙옙표占쏙옙 占쏙옙占쏙옙) */
#define LONG_KEY_DISPLAY_TEST_MODE_CHPI         (KEY_ICE_SELECT + KEY_COLD_SELECT)                                              /* 占쏙옙占쏙옙 占쏙옙占쏙옙트 占싯삼옙 (占쏙옙占싸띰옙占쏙옙/占쏙옙占쏙옙占쏙옙占?? 占싯삼옙) : 占쏙옙占쏙옙+占시쇽옙 (占쏙옙占쏙옙표占쏙옙 占쏙옙占쏙옙) */

/* 3占쏙옙 占싱삼옙 占쏙옙占쏙옙占?? 키占쏙옙占쏙옙 */
#define LONG_KEY_3S_BLE_FAIRING                 (KEY_AMBIENT_SELECT)                                                            /* BLE 占쏙옙占?? : 占쏙옙占쏙옙 3占쏙옙 (占쏙옙占쏙옙표占쏙옙 占쏙옙占쏙옙) */
#define LONG_KEY_3S_WIFI_FAIRING                (KEY_AMBIENT_SELECT + KEY_COLD_SELECT)                                          /* wifi 占쏙옙占?? : 占쏙옙占쏙옙+占시쇽옙 3占쏙옙 (占쏙옙占쏙옙표占쏙옙 占쏙옙占쏙옙) */
#define LONG_KEY_3S_WIFI_ONOFF                  (KEY_COLD_SELECT + KEY_AMOUNT_SELECT)                                           /* wifi on/off : 占시쇽옙+占쎈량 3占쏙옙 (占쏙옙占쏙옙표占쏙옙 占쏙옙占쏙옙) */
#define LONG_KEY_3S_MANUAL_DRAIN                (KEY_COLD_SELECT + KEY_HOT_SELECT)                                              /* 占쏙옙占쏙옙 占썲레占쏙옙 : 占시쇽옙+占승쇽옙 3占쏙옙 (占쏙옙占쏙옙표占쏙옙 占쏙옙占쏙옙) */
#define LONG_KEY_3S_TESTPROGRAM                 (KEY_ICE_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT)                       /* 占쏙옙占쏙옙占쏙옙占쌓쏙옙트 : 占쏙옙占쏙옙+占쏙옙占쏙옙+占쎈량 3占쏙옙 (占쏙옙占쏙옙표占쏙옙 占쏙옙占쏙옙) */
#define LONG_KEY_3S_HOT_STER                    (KEY_AMOUNT_SELECT + KEY_ICE_WATER_SELECT)                                      /* 占쏙옙占쏙옙 占쏙옙占승삼옙占?? : 占쏙옙占쏙옙占쏙옙+占쎈량 (占쏙옙占쏙옙표占쏙옙 占쏙옙占쏙옙) */
#define LONG_KEY_3S_MEMENTO                     (KEY_COLD_SELECT + KEY_HOT_SELECT + KEY_AMBIENT_SELECT)                         /* 占쌨몌옙占쏙옙占쏙옙 : 占시쇽옙 + 占쏙옙占쏙옙 + 占승쇽옙 (占쏙옙占쏙옙표占쏙옙 占쏙옙占쏙옙) */
#define LONG_KEY_3S_CODY_WATER_LINE             (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT)                       /* 占쌘듸옙 占쏙옙占싸삼옙辣占쏙옙 : 占승쇽옙 + 占쏙옙占쏙옙 + 占쎈량 (占쏙옙占쏙옙占쌤억옙占싱쏙옙) */
#define LONG_KEY_3S_ICE_TRAY_TEST               (KEY_ICE_SELECT + KEY_AMBIENT_SELECT)                                           /* 占쌘듸옙 트占쏙옙占쏙옙 占쌓쏙옙트占쏙옙占?? : 占쏙옙占쏙옙 + 占쏙옙占쏙옙 */
#define LONG_KEY_3S_TAKEOFF_ICE                 (KEY_ICE_SELECT + KEY_HOT_SELECT)                                               /* 占쌘듸옙 占쏙옙占쏙옙탈占쏙옙占쏙옙占?? : 占쏙옙占쏙옙 + 占승쇽옙 */
#define LONG_KEY_3S_MANAGER_INSTRUCTION_MODE    (KEY_ICE_WATER_SELECT + KEY_COLD_SELECT)                                        /* 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占?? : 占시쇽옙+占쏙옙占쏙옙占쏙옙 */
#define LONG_KEY_3S_HOT_DRAIN_COLD              (KEY_ICE_WATER_SELECT + KEY_HOT_SELECT)                                         /* 占승쇽옙 占쌓쏙옙트占쏙옙 (占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙) : 占쏙옙占쏙옙占쏙옙 + 占승쇽옙 */
// #define LONG_KEY_3S_BRIGHT_TEST                 (KEY_ICE_WATER_SELECT + KEY_ICE_SELECT + KEY_MY_SELECT)
#define LONG_KEY_3S_CANCEL_COMP_DELAY           (KEY_ICE_SELECT + KEY_AMOUNT_SELECT)                                            /* 占쏙옙占쏙옙 占쏙옙占시곤옙 占쏙옙占쏙옙(占쏙옙占쏙옙占쌘울옙) : 占쏙옙占쏙옙 + 占쎈량 */
/***********************************************************************************************************************/
#define ICE_WATER_KEY_CONTINUE 1
#define ICE_KEY_CONTINUE 2

//
#define UKey_Mask 0x00
// #define UWater_Extract_Key           0x01
// #define UIce_Extract_Key             0x02
#define UWater_Extract_Key 0x01
#define UIce_Extract_Key 0x02

#define UWater_Extract_Long_Key 0x02
#define UIce_Extract_Long_Key 0x01

/*..hui [18-1-30占쏙옙占쏙옙 5:04:07] 占썲레占쏙옙占쏙옙占쏙옙 占쏙옙占?? 占쏙옙占쏙옙 占쏙옙占썸에 占쏙옙占쏙옙 占시곤옙 占쏙옙占쏙옙..*/
/*..hui [19-12-2占쏙옙占쏙옙 2:59:15] 4占쏙옙 30占쏙옙..*/
/*#define COLD_DRAIN_TIME    2700*/

/*..hui [19-12-2占쏙옙占쏙옙 3:49:41] 占쏙옙크占쏙옙 크占싹깍옙 5占쏙옙 30占십뤄옙.....*/
/*#define COLD_DRAIN_TIME    3300*/
#define COLD_DRAIN_TIME 1200

#define NOW_USE_PHOTO 6000 // 占싱삼옙占?? 占쏙옙占쏙옙 占썬낮 확占쏙옙 占시곤옙 10(600)->1占쏙옙(60)
#define NoWaterOutTime 360 // 占싱삼옙占?? 占쏙옙占쏙옙 6占시곤옙 6 x 60(360)->30占쏙옙(30)

#define TEMPERATURE_SENSOR_OPEN 1000
#define TEMPERATURE_SENSOR_SHORT 20

#define TEMPERATURE_SENSOR_8BIT_OPEN 250
#define TEMPERATURE_SENSOR_8BIT_SHORT 5

#define TEMPERATURE_SENSOR_ERROR_CHECK_TIME 30

#define ICE_FEDDER_MIX_MAX_TIME 20
#if 0
#define PUMP_PWM_Free 1699 // Sterilization.h 占쏙옙占쏙옙 占쏙옙占쏙옙, 占썩동 占십깍옙 20V
#define PUMP_PWM 1499      // 16V(1300)->18V(1500) 占쏙옙占쏙옙 DUTY
#define PUMP_PWM_MAX 1999  // 16V(1300)->18V(1500) 占쏙옙占쏙옙 DUTY
#endif

#if 0
#define PUMP_PWM 4000     // 2ms
#define PUMP_PWM_MAX 6000 // Full(3ms)
#endif

#define PUMP_PWM 33600     // 2ms
#define PUMP_PWM_MAX 48000 // Full(3ms)

#define DRAIN_CURRENT 83 // 0.4V(82)

#define ICE_TRAY_POSITION_ICE_MAKING 0 /*..占쏙옙占쏙옙占쏙옙占쏙옙..*/
#define ICE_TRAY_POSITION_ICE_THROW 1  /*..占쏙옙占쏙옙占쏙옙占쏙옙..*/
#define ICE_TRAY_POSITION_MOVING 2     /*..占싱듸옙占쏙옙..*/
#define ICE_TRAY_POSITION_ERROR 3      /*..占쏙옙占쏙옙..*/

#define CUP_SELECT_LED_OFF_TIME 70

#define STEP_ANGLE1 2000 // Select Bar 1200->2000

/*..hui [20-3-26占쏙옙占쏙옙 7:24:07] ICE Door 1500->1000.. 占쏙옙占싱쏙옙2.0 占쏙옙占??..*/
/*#define STEP_ANGLE_DOOR 1000*/

/*..hui [20-3-26占쏙옙占쏙옙 7:24:23] 占쏙옙占싱쏙옙3.0占쏙옙 占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占??..*/
/*#define STEP_ANGLE_DOOR 670*/

/*..hui [20-3-26占쏙옙占쏙옙 7:30:12] 50占쌨쏙옙 占쏙옙占쏙옙 占쏙옙 占쌍는걸뤄옙..*/
#define STEP_ANGLE_DOOR         800 // 750
#define STEP_ANGLE_TEMP_DOOR    480     // 1회 800占쏙옙占쏙옙 60% 占쏙옙占쏙옙 (占싱니삼옙占??)
#define STEP_ANGLE_SELECT       1100
// #define STEP_ANGLE_TEMP_SELECT  600
#define STEP_ANGLE_TRAY         750

#define ICE_DOOR_CLOSE_TIME_100MS       70    // 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 3占쏙옙 -> 7占쏙옙
#define ICE_SELECT_CLOSE_TIME_100MS     30    // 占쏙옙占쏙옙 占싱너듸옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 3占쏙옙

#define ICE_OUT_BACK_1S_DELAY_TIME      90    // 占쏙옙占쏙옙 5占쏙옙 -> 9占쏙옙 占쏙옙占??
#define ICE_OUT_BACK_2S_DELAY_TIME      90    // 占쏙옙占쏙옙 5占쏙옙 -> 9占쏙옙 占쏙옙占??

#define ICE_SHAKE_DELAY_TIME            40    // 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙 占실댐옙占쏙옙占쏙옙 占쏙옙占?? 占시곤옙

// 1占쏙옙 (占쏙옙占쏙옙)
#define ICE_OUT_BACK_1S_GO_TIME         10    // 3~5.9占쏙옙 占쏙옙占쏙옙 占쏙옙 1占쏙옙 占쏙옙회占쏙옙
#define ICE_OUT_BACK_2S_GO_TIME         30    // 6占쏙옙 占싱삼옙 占쏙옙占쏙옙 占쏙옙 2占쏙옙 -> 3占쏙옙 占쏙옙회占쏙옙

#define TRIP_REST_TIME 84
#define TOTAL_MAXIMUM_REST_TIME 144

#define USE_SAVE_LEARNEND_MODE_TIME 16

#define USE_SAVE_LEARNEND_MODE_MIN_TIME 1
#define USE_SAVE_LEARNEND_MODE_MAX_TIME 100

// #define DISPLAY_SLEEP_TIME                6000
#define ONE_WEEK_TIME_HOUR 168
#define WEEK_COUNT 4

#define DIRECT_CONVERT_COUNT 100
#define ONE_WEEK_INITIAL_HOUR 0xff

#define ICE_DOOR_CLOSE_INTERVAL     9000 // 900占쏙옙 (15占쏙옙)

// 20160530 Sus EVA 占쌩곤옙 占쏙옙占쏙옙 (占쏙옙占쏙옙 占쏙옙占?? 3占쏙옙->8占쏙옙)
// #define COMP_START_TIME 480                     // COMP 占썩동 占쏙옙占?? 8占쏙옙
// #define COMP_START_TIME 4800                     // COMP 占썩동 占쏙옙占?? 8占쏙옙
/*..hui [19-9-18占쏙옙占쏙옙 1:15:38] COMP 占썩동 占쏙옙占?? 7占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙..*/
/*#define COMP_START_TIME        4200*/

/*..hui [19-11-19占쏙옙占쏙옙 4:09:12] COMP 占썩동 占쏙옙占?? 6占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙..*/
/*#define COMP_START_TIME                      3600*/
/*..hui [23-4-12占쏙옙占쏙옙 2:07:00] 占쏙옙占쏙옙占쏙옙 占쏙옙占싱쏙옙占쏙옙 占쏙옙占시곤옙 5占쏙옙..*/
#define COMP_START_TIME 3000
#define DEVELOPE_COMP_DELAY_CANCEL_TIME 300

#define ICEVV_TIME_INIT 300 // 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占시곤옙 30占쏙옙

#define COLD_TIME 50       // 占시쇽옙占쏙옙占쏙옙占쏙옙 占시곤옙 5占쏙옙
#define IceWaterDelay 1440 // 占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙 24占시곤옙 占쏙옙占쏙옙 占쏙옙占?? 24 x 60

#define ICE_INIT_ERROR_CANCEL_TIME 72000

#define STANDBY 0    // 占쏙옙占쏟스댐옙占??
#define WASH 1       // 占쏙옙척
#define WASHEND 2    // 占쏙옙척占쏙옙占쏙옙
#define NEUTRAL 3    // 占쏙옙화
#define NEUTRALEND 4 // 占쏙옙화占쏙옙占쏙옙

#if 1
#define CUP_LEVEL_HALF      1
#define CUP_LEVEL_ONE       2
#define CUP_LEVEL_TWO       4
#define CUP_LEVEL_FOUR      8
#define CUP_LEVEL_MY_CUP    16
#endif

#if 0
#define CUP_LEVEL_1_120ML 1
#define CUP_LEVEL_2_250ML 2
#define CUP_LEVEL_3_500ML 3
#define CUP_LEVEL__10_OZ__295_ML 4
#define CUP_LEVEL__12_OZ__355_ML 5
#define CUP_LEVEL__14_OZ__415_ML 6
#define CUP_LEVEL__16_OZ__475_ML 7
#define CUP_LEVEL__20_OZ__590_ML 8
#define CUP_LEVEL__32_OZ__945_ML 9
#define CUP_LEVEL_CONTINUE 10

#define CUP_LEVEL__MAX 10
#endif

/******************************************************************************/

typedef enum
{
    CUP_LEVEL_1_120ML = 1, // 120ml
    CUP_LEVEL_2_250ML = 2,  // 250ml
    CUP_LEVEL_3_500ML = 3, // 500ml
    CUP_LEVEL_4_1000ML = 4,         // 1L
    CUP_LEVEL_CONTINUE = 5,        // 占쏙옙占쏙옙
} CUP_LEVEL;

typedef enum
{
    ICE_LEVEL_1_STEP = 1,
    ICE_LEVEL_2_STEP = 2,
    ICE_LEVEL_3_STEP = 3,
    ICE_LEVEL_4_STEP = 4,
} ICE_LEVEL;

#define C_CUP_MY_TEA                          300
#define C_CUP_MY_COLD                         3.792F    // 占쏙옙 V1
#define C_CUP_MY_COLD_120ML                   4.2831F    // 占쏙옙 V2
#define C_CUP_MY_PURE                         3.625F    // 占쏙옙
#define C_CUP_MY_HOT                          3.291F    // 占쏙옙

#define C_ICE_MAKING                          1.8F    // 제빙 유량 (V1)
// #define C_ICE_MAKING                          2.35F    // 제빙 유량 (V2) - V1대비 +30%
// C_ICE_MAKING이 커질수록 얼음도 커짐

#define CUP_LEVEL__MAX CUP_LEVEL_CONTINUE
/******************************************************************************/
#define CUP_LEVEL_ORDER__UP 0
#define CUP_LEVEL_ORDER__DOWN 1
/******************************************************************************/
/*#define CUP_LEVEL_SELECT_DEFAULT_4_8_12_16_20             0xD5*/
/*#define CUP_LEVEL_SELECT_DEFAULT_4_8_12_20_CONTINUE       0x295*/
/*#define CUP_LEVEL_SELECT_DEFAULT_4_8_12_20_CONTINUE       0x195*/
#define CUP_LEVEL_SELECT_DEFAULT_4_8_12_20_CONTINUE 0x295
/******************************************************************************/
#define ROOM_TEMP_DISPLAY_MID 0
#define ROOM_TEMP_DISPLAY_LOW 1
#define ROOM_TEMP_DISPLAY_HIGH 2
/******************************************************************************/
#define Fahrenheit_oF_SELECT 0
#define Celsius_oC_SELECT 1
/******************************************************************************/
#define Oz_SELECT 0
#define mL_SELECT 1
/******************************************************************************/
#define HOT_TEMP_LEVEL_ORDER__UP 0
#define HOT_TEMP_LEVEL_ORDER__DOWN 1
/******************************************************************************/
#define HOT_TEMP_DEFAULT_TEMP 2
/******************************************************************************/
#define WIFI_ICE_MAKING_STANDBY 0
#define WIFI_ICE_TRAY_IN_START 1
#define WIFI_ICE_TRAY_IN_ING 2
#define WIFI_ICE_MAKING_START 3
#define WIFI_ICE_MAKING_ING 4
#define WIFI_ICE_TAKE_OFF_START 5
#define WIFI_ICE_TAKE_OFF_ING 6
#define WIFI_ICE_MAKING_FINISH_START 7
#define WIFI_ICE_MAKING_FINISH_ING 8
/******************************************************************************/
#define WIFI_FLUSHING_OFF 0
#define WIFI_FLUSHING_ON 1
#define WIFI_FLUSHING_GOING 2
#define WIFI_FLUSHING_DONE 3
/******************************************************************************/
#define WIFI_SMART_SAVE_GREEN_WEEK_START 0
#define WIFI_SMART_SAVE_GREEN_WEEK_ING 1
#define WIFI_SMART_SAVE_INTENSIVE_WEEK_START 2
#define WIFI_SMART_SAVE_INTENSIVE_WEEK_ING 3
/******************************************************************************/
#define WIFI_ICE_STER_OFF 0
#define WIFI_ICE_STER_ON 1
#define WIFI_ICE_STER_GOING 2
#define WIFI_ICE_STER_DONE 3
/******************************************************************************/
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
#define WIFI_ACID_CLEAN_STANDBY__0 0

#define WIFI_ACID_CLEAN_START_ACID_WATER__1 1
#define WIFI_ACID_CLEAN_ACID_WATER_ING__2 2

#define WIFI_ACID_CLEAN_START_CHANGE_FILTER__3 3
#define WIFI_ACID_CLEAN_CHANGE_FILTER_ING__4 4

#define WIFI_ACID_CLEAN_START_WAIT_1_HOUR__5 5
#define WIFI_ACID_CLEAN_WAIT_1_HOUR_ING__6 6

#define WIFI_ACID_CLEAN_START_DRAIN_ACID_WATER__7 7
#define WIFI_ACID_CLEAN_DRAIN_ACID_WATER_ING__8 8

#define WIFI_ACID_CLEAN_START_1ST_RINSE_FEED_WATER__9 9
#define WIFI_ACID_CLEAN_RINSE_1ST_FEED_WATER_ING__10 10
#define WIFI_ACID_CLEAN_START_1ST_DRAIN_RINSE_WATER__11 11
#define WIFI_ACID_CLEAN_START_1ST_DRAIN_RINSE_WATER_ING__12 12

#define WIFI_ACID_CLEAN_START_2ND_RINSE_FEED_WATER__13 13
#define WIFI_ACID_CLEAN_RINSE_2ND_FEED_WATER_ING__14 14
#define WIFI_ACID_CLEAN_START_2ND_DRAIN_RINSE_WATER__15 15
#define WIFI_ACID_CLEAN_START_2ND_DRAIN_RINSE_WATER_ING__16 16
#define WIFI_ACID_CLEAN_FINISH__17 17

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

/*..hui [23-6-26占쏙옙占쏙옙 12:25:38] 占쏙옙占쏙옙트 占쎌선 占쏙옙占쏙옙 1占쏙옙..*/
#define WIFI_PERIOD_STER_HOUR_DEFAULT 1
#define WIFI_PERIOD_STER_MINUTE_DEFAULT 0

#define WIFI_SLEEP_MODE_START_HOUR_DEFAULT 0
#define WIFI_SLEEP_MODE_START_MINUTE_DEFAULT 0

#define WIFI_SLEEP_MODE_FINISH_HOUR_DEFAULT 6
#define WIFI_SLEEP_MODE_FINISH_MINUTE_DEFAULT 0

#define WIFI_FILTER_CHANGE_CYCLE_DEFAULT 100
#define WIFI_FILTER_CHANGE_CYCLE_MIN 30
#define WIFI_FILTER_CHANGE_CYCLE_MAX 200

#define WIFI_WAIT_MODE_ENABLE_DEFAULT   0

#define PURE_WATER_SELECT   1
#define COLD_WATER_SELECT   2
#define HOT_WATER_SELECT    4
#define ICE_WATER_SELECT    8

#define COLD_POWER_HIGH 0
#define COLD_POWER_LOW 1

#define ICE_SELECT__NONE 0
#define ICE_SELECT__ICE 1
#define ICE_SELECT__ICE_WATER 2

#define ICE_SIZE_LARGE 0
#define ICE_SIZE_SMALL 1

#define COLD_FIRST_ICE_MAKE 0
#define ICE_FIRST_ICE_MAKE 1

#define NEW_FAST_ICE 0
#define RECOVER_FAST_ICE 1

#define RGB_OFF 0
#define RGB_COLOR_HOT 1
#define RGB_COLOR_COLD 2

#define TEST_MODE_RGB_OFF 0
#define TEST_MODE_RGB_COLOR_RED 1
#define TEST_MODE_RGB_COLOR_GREEN 2
#define TEST_MODE_RGB_COLOR_BLUE 3

#define SETTING_FOCUS_NONE 0
#define SETTING_FOCUS_FAST_ICE 1
#define SETTING_FOCUS_ICE_OFF 2
#define SETTING_FOCUS_COLD_OFF 3

typedef enum
{
    DRAIN_RETRY_INIT,
    DRAIN_RETRY_COLD_DRIN_ON,
    DRAIN_RETRY_PUMP_1MIN_OFF,
    DRAIN_RETRY_PUMP_2MIN_ON

} DRAIN_RETRY;

#define DRAIN_LEVEL_EMPTY 1
#define DRAIN_LEVEL_LOW 2
#define DRAIN_LEVEL_HIGH 4
#define DRAIN_LEVEL_ERROR 8

#define ROOM_LEVEL_LOW 0
#define ROOM_LEVEL_MID 1
#define ROOM_LEVEL_FULL 2
#define ROOM_LEVEL_ERROR 3

#define UV_WATER_TANK_OPERATION_TIME_MIN             120
#define UV_ICE_TANK_OPERATION_TIME_MIN               120
#define UV_ICE_OFF_OPERATION_TIME_MIN                120

#define ICE_TANK_UV_MAX_OPERATION_PER_ONE_DAY                2
#define ICE_TANK_UV_STANDBY_MAX_TIME                         6 //  6 hours
#define ICE_TANK_UV_OEPRATION_MAX_TIME                       120 // 120minutes


#define ICE_TRAY_UV_MAX_OPERATION_PER_ONE_DAY_THROW          2      // 탈占쏙옙占쏙옙치 2회
#define ICE_TRAY_UV_THROW_MAX_TIME                           60 // 60minutes

#define ICE_TRAY_UV_MAX_OPERATION_PER_ONE_DAY_MAKING         4      // 占쏙옙占쏙옙占쏙옙치 4회
#define ICE_TRAY_UV_MAKING_MAX_TIME                          18000 // 30minutes

#define UV_FAULT_TEST_1MIN_30SEC 900

#if 0
/*..hui [23-6-8占쏙옙占쏙옙 9:40:56] 占쌓울옙 占싱놂옙占?? 1占쏙옙..*/
#define FILTER_RESET_DAY__NEO_INO 365
#define FILTER_ALARM_BEFORE_30_DAYS__NEO_INO 30

/*..hui [23-6-8占쏙옙占쏙옙 9:41:19] RO占쏙옙 2占쏙옙 730占쏙옙..*/
#define FILTER_RESET_DEFAULT_24_MONTH_912_DAY_HOUR__RO 730
#endif

#if 0
#define NEO_TOTAL_USAGE_MAX_WATER 3600
#define RO_TOTAL_USAGE_MAX_WATER 7200
#define INO_TOTAL_USAGE_MAX_WATER 3600

#define FILTER_ALARM_REMAIN_240_LITER 240
#endif

#define NEO_TOTAL_USAGE_MAX_WATER 3785
#define RO_TOTAL_USAGE_MAX_WATER 7570
#define INO_TOTAL_USAGE_MAX_WATER 3785

/*#define FILTER_ALARM_REMAIN_240_LITER                240*/
#define FILTER_ALARM_REMAIN_315_LITER 315

#if 0
#define FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__NEO 456
#define FILTER_RESET_DEFAULT_24_MONTH_912_DAY_HOUR__RO 912
#define FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__INO 456
#endif

#if 0
/*..hui [24-2-23占쏙옙占쏙옙 10:04:55] 15占쏙옙占쏙옙/30占쏙옙占쏙옙..*/
#define FILTER_RESET_DEFAULT_MONTH__NEO 15
#define FILTER_RESET_DEFAULT_MONTH__RO 30
#define FILTER_RESET_DEFAULT_MONTH__INO 15

/*..hui [23-12-18占쏙옙占쏙옙 7:38:25] 1占시곤옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙..*/
#define FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__NEO 10944
#define FILTER_RESET_DEFAULT_24_MONTH_912_DAY_HOUR__RO 21888
#define FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__INO 10944

#define FILTER_RESET_MAX_HOUR__NEO 21888
#define FILTER_RESET_MAX_HOUR__RO 43776
#define FILTER_RESET_MAX_HOUR__INO 21888

#define FILTER_ALARM_REMAIN_30_DAYS 720
#endif

/*..hui [24-2-23占쏙옙占쏙옙 10:05:01] 12占쏙옙占쏙옙/24占쏙옙占쏙옙..*/
#define FILTER_RESET_DEFAULT_MONTH__NEO 12
#define FILTER_RESET_DEFAULT_MONTH__RO 24
#define FILTER_RESET_DEFAULT_MONTH__INO 12

/*..hui [23-12-18占쏙옙占쏙옙 7:38:25] 1占시곤옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙..*/
/* SSG : 30.4 * 24 * 12 = 8755.2 (占쌥올몌옙) */
#define FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__NEO 8755
#define FILTER_RESET_DEFAULT_24_MONTH_912_DAY_HOUR__RO 17510
#define FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__INO 8755

#define FILTER_RESET_MAX_HOUR__NEO 17510
#define FILTER_RESET_MAX_HOUR__RO 35020
#define FILTER_RESET_MAX_HOUR__INO 17510

#define FILTER_ALARM_REMAIN_30_DAYS 720

#define FILTER_CHANGE_TYPE__NEO_INO 0
#define FILTER_CHANGE_TYPE__NEO_RO_INO_ALL 1

/*#define FILTER_CHANGE_RESET_TIME                     18000*/
#define FILTER_CHANGE_RESET_TIME 9000

/*#define ACID_CLEAN_TANK_EMPTY_MAX_TIME               36000*/
/*#define ACID_CLEAN_TANK_EMPTY_MAX_TIME               18000*/
/*..hui [24-5-28占쏙옙占쏙옙 4:34:04] 40占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙..*/
/*#define ACID_CLEAN_TANK_EMPTY_MAX_TIME               24000*/
/*..hui [24-7-22占쏙옙占쏙옙 2:00:27] 1占시곤옙占쏙옙占쏙옙 占쏙옙占?? 占싫되몌옙 占썲레占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙..*/
#define ACID_CLEAN_TANK_EMPTY_MAX_TIME 36000

// #define SETTING_MAX_YEAR      35
// #define SETTING_MIN_YEAR      21

#define SETTING_MAX_YEAR 80
#define SETTING_MIN_YEAR 23

#if 0
/*..hui [20-1-15占쏙옙占쏙옙 7:42:07] 2020占쏙옙 1占쏙옙1占쏙옙 0占쏙옙0占쏙옙0占쏙옙..*/
#define RTC_DEFAULT_YEAR 23
#define RTC_DEFAULT_MONTH 7
#define RTC_DEFAULT_DATE 1
#define RTC_DEFAULT_HUOR 0
#define RTC_DEFAULT_MIN 0
#define RTC_DEFAULT_SEC 0
#define RTC_DEFAULT_DAYWEEK 6
#define RTC_DEFAULT_Y2K 20
#endif

#if 0
#define RTC_DEFAULT_YEAR 24
#define RTC_DEFAULT_MONTH 4
#define RTC_DEFAULT_DATE 1
#define RTC_DEFAULT_HUOR 0
#define RTC_DEFAULT_MIN 0
#define RTC_DEFAULT_SEC 0
#define RTC_DEFAULT_DAYWEEK 1
#define RTC_DEFAULT_Y2K 20
#endif

#define FILTER_FLUSHING_NONE 0
#define FILTER_FLUSHING_NEO_INO 1
#define FILTER_FLUSHING_RO 2
#define FILTER_FLUSHING_NANO_INO 3

#define STER_PUMP_STAGE_90_PERCENT 0
#define STER_PUMP_STAGE_80_PERCENT 1
// #define STER_PUMP_STAGE_18V         2

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

/*#define HOT_STER_SAFETY_TIME                          6000*/
/*..hui [24-1-25占쏙옙占쏙옙 3:30:33] 占쏙옙占쏙옙占시곤옙 15占쏙옙.....*/
#define HOT_STER_SAFETY_TIME 9000
#define ICE_TANK_STER_PREHEAT_TEMP        75
#define ICE_TANK_STER_TARGET_TEMP         75
#define HOT_STER_INPUT_HZ                 900 // 600
/*#define HOT_STER_WAIT_TIME                3000*/
#define HOT_STER_WAIT_TIME                1800
#define DRAIN_TANK_STER_PREHEAT_TEMP      72
#define DRAIN_TANK_STER_TARGET_TEMP       72
#define DRAIN_TANK_PRE_DRAIN_MAX_TIME     70
#define DRAIN_STER_WAIT_TIME              1200
#define DRAIN_STER_INPUT_HZ               300 // 530

#define ICE_TANK_STER_DELAY_TIME          5

#define ICE_TRAY_STER_PREHEAT_TEMP        82
#define ICE_TRAY_STER_TARGET_TEMP         82
#define ICE_TANK_PREHEAT_MAX_TIME         100
/*#define ICE_TRAY_PRE_DRAIN_MAX_TIME       30*/
/////#define ICE_TRAY_PRE_DRAIN_MAX_TIME       40
#define ICE_TRAY_PRE_DRAIN_MAX_TIME       70


/*#define STER_NO_OPERATION_COLD_TEMP                   35*/
/*#define STER_NO_OPERATION_COLD_TEMP                   38*/
/*#define STER_NO_OPERATION_COLD_TEMP                   15*/
/*#define STER_NO_OPERATION_COLD_TEMP                   12*/
#define STER_NO_OPERATION_COLD_TEMP 10

/*#define HOT_CIRCULATION_MAX_TIME            1800*/
/*#define HOT_CIRCULATION_MAX_TIME            1200*/

/*#define HOT_CIRCULATION_MAX_TIME            1800*/
/*..hui [24-1-31占쏙옙占쏙옙 10:10:40] 占승듸옙 占쏙옙占싱깍옙占쏙옙占쏙옙 占쏙옙환 占쌍쇽옙화..*/
/*#define HOT_CIRCULATION_MAX_TIME              100*/
/*..hui [24-1-31占쏙옙占쏙옙 2:51:55] 占승듸옙 占십뱄옙 占쏙옙占쏙옙.. 20占십뤄옙 占쏙옙占쏙옙..*/
/*#define HOT_CIRCULATION_MAX_TIME              200*/
/*..hui [24-2-1占쏙옙占쏙옙 2:05:26] 占쌕쏙옙 10占십뤄옙.. 占쏙옙占쏙옙환 占쏙옙占쏙옙占??..*/
#define HOT_CIRCULATION_MAX_TIME 100
#define MELT_ICE_HOT_CIRCULATION_MAX_TIME 200

/*#define MELT_ICE_HOT_CIRCULATION_MAX_TIME            1200*/
/*#define ICE_TRAY_HOT_CIRCULATION_MAX_TIME            1200*/

#if 0
#define SLEEP_IN 245  //  占쏙옙占쏙옙, 1.2V
#define SLEEP_OUT 450 //  占쏙옙占쏙옙, 2.2V
#endif

// #define SLEEP_IN    385
// #define SLEEP_OUT   810

// #define SLEEP_IN    100
// #define SLEEP_OUT   160

/*..hui [20-1-22占쏙옙占쏙옙 2:46:18] PCB, 占썩구占쏙옙占쏙옙 占쏙옙 占쌕울옙占쏙옙 占쌕쏙옙..*/
/*#define SLEEP_IN    345*/
/*#define SLEEP_OUT   634*/

/*..hui [20-2-18占쏙옙占쏙옙 5:17:51] 占썩구占쏙옙 占쏙옙占쏙옙 占쏙옙 占쌕쏙옙 占쏙옙占쏙옙..*/
/////#define SLEEP_IN    381
/////#define SLEEP_OUT   754

#define PUMP_NO_LOAD_MINIMUM_OPERATION_TIME 450
/*#define DRAIN_NO_WATER_FEEDBACK_AD                   190*/
/*#define DRAIN_NO_WATER_FEEDBACK_AD                   100*/
/*..hui [24-4-4占쏙옙占쏙옙 5:59:35] 70%占쏙옙 100%占쏙옙 占싼댐옙 占쏙옙占쏙옙..*/
/*..hui [24-4-4占쏙옙占쏙옙 6:00:00] 占쏙옙 占쏙옙占쏙옙占쏙옙 120占쏙옙占쏙옙 占쏙옙占쏙옙.. 占쏙옙占쏙옙占싹띰옙占쏙옙 240~390..*/
/*#define DRAIN_NO_WATER_FEEDBACK_AD                   170*/
/*#define DRAIN_NO_WATER_FEEDBACK_AD                   150*/
#define DRAIN_NO_WATER_FEEDBACK_AD 180
#define ICE_DOOR_HEATER_FB_AD 180

#define PUMP_NO_LOAD_CHECK_TIME 30

#define DRAIN_COMPLETE_FEEDBACK 180

/*#define DRAIN_VALVE_OPEN_TIME       450*/
/*..hui [23-8-14占쏙옙占쏙옙 3:21:50] 占쏙옙占쏙옙占쏙옙->占쏙옙占쏙옙占쏙옙 占쏙옙占승시곤옙 1占쏙옙.. 占쏙옙占쏙옙占쌍곤옙 1占쏙옙 30占십뤄옙..*/
/*#define DRAIN_VALVE_OPEN_TIME       900*/
/*#define DRAIN_VALVE_OPEN_TIME       1100*/
/*#define DRAIN_VALVE_OPEN_TIME       900*/
/*..hui [24-3-26占쏙옙占쏙옙 5:25:30] 占쌕쏙옙 1占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙.. 占쏙옙크 占쏙옙 占쏙옙칠占쏙옙占쏙옙占쏙옙..*/
// #define DRAIN_VALVE_OPEN_TIME 600
/* ICE 2KG MAX占쏙옙 15占쏙옙 */
#define DRAIN_VALVE_OPEN_TIME       150

#define MANUAL_DRAIN_MAX_TIME 18000

#define MANUAL_DRAIN_FINISH_CHECK_TIME 600

#define MIX_ALL_NORMAL 0
#define MIX_COLD_TEMP_ABNORMAL_HIGH 1
#define MIX_HOT_TEMP_ABNORMAL_LOW 2

#define TARGET_ROOM_27_TEMP 25
// #define HOT_MIX_START_TIME             10
#define HOT_MIX_START_TIME 5

/*#define TARGET_HOT_85_TEMP             85*/
#define TARGET_HOT_85_TEMP 87

#define TARGET_HOT_77_TEMP 77

#define TARGET_HOT_43_TEMP 43

#define COLD_MIX_START_TIME 10

/*#define PERIODIC__STER_CYCLE         7*/
/*..hui [23-11-8占쏙옙占쏙옙 2:31:08] 28占싹울옙 占싼뱄옙 占싹는걸뤄옙 占쏙옙占쏙옙..*/
/* 3占싹울옙 占싼뱄옙占쏙옙 占쏙옙占쏙옙 */
#define PERIODIC__STER_CYCLE                    3
#define FIRST_POWER_ON_PERIODIC__STER_CYCLE     3
#define DRAIN_TANK__STER_CYCLE                  9    //10

/*..hui [23-7-13占쏙옙占쏙옙 9:55:52] 占쌓쏙옙트占쏙옙..*/
/////////#define PERIODIC__STER_CYCLE         1
///////#define HOT_STER_TEMP_HIGH_MODE         0
////////#define HOT_STER_TEMP_LOW_MODE          1

/*..hui [24-4-5占쏙옙占쏙옙 9:49:29] 占쏙옙占쏙옙占쏙옙크 3 1占쏙옙짜占쏙옙 占실듸옙占?? 100..*/
#define UV_SOLO__ERROR_CHECK_UNDER_AD 41
#define UV_SOLO__ERROR_CHECK_OVER_AD 205

/*..hui [24-4-5占쏙옙占쏙옙 9:49:44] 占쏙옙占쏙옙占쏙옙크 1,2 占싸곤옙 165, 1占쏙옙..*/
/*..hui [24-4-5占쏙옙占쏙옙 9:49:55] 占쏙옙占싱쏙옙트占쏙옙占쏙옙 1,2 占싸곤옙 : 164, 1占쏙옙 : 100..*/
/*..hui [24-4-5占쏙옙占쏙옙 9:50:07] 占시쇽옙占쏙옙크 1,2 占싸곤옙 : 182, 1占쏙옙 : 100..*/
/*#define UV_COUPLE__ERROR_CHECK_UNDER_AD            82*/
#define UV_COUPLE__ERROR_CHECK_UNDER_AD         120
#define UV_COUPLE__ERROR_CHECT_OVER_AD          410

#define C_CUP_120CC_ROOM 400 // 350 // 342
#define C_CUP_250CC_ROOM 830 // 762
#define C_CUP_500CC_ROOM 1750
#define C_CUP_1000CC_ROOM (C_CUP_500CC_ROOM * 2)
#define C_CUP_2000CC_ROOM (C_CUP_1000CC_ROOM * 2)

/* 占시쇽옙 120cc 占쏙옙占쏙옙 占쏙옙占?? 10% 占쏙옙占쏙옙 */
#define C_CUP_120CC_COLD 433 // 440 // 350 // 339
#define C_CUP_250CC_COLD 830 // 774
#define C_CUP_500CC_COLD 1712
#define C_CUP_1000CC_COLD (C_CUP_500CC_COLD * 2)
#define C_CUP_2000CC_COLD (C_CUP_1000CC_COLD * 2)

#define C_CUP_120CC_HOT 415
#define C_CUP_250CC_HOT 868
#define C_CUP_500CC_HOT 1776
#define C_CUP_1000CC_HOT (C_CUP_500CC_HOT * 2)
#define C_CUP_2000CC_HOT (C_CUP_1000CC_HOT * 2)

#define C_CUP_150CC_ICE_WATER (953 * 2) // 485 // 470 // 440 // 350 // 339
#define C_CUP_250CC_ICE_WATER (1410 * 2) // 830 // 774
#define C_CUP_350CC_ICE_WATER (1562 * 2) // 1712
#define C_CUP_500CC_ICE_WATER (2288 * 2)


#define TRAY_POSITION_U16 200
#define TRAY_MOVE_MAX 1600

#define ICE_TRAY_MODE_NONE 0
#define ICE_TRAY_MODE_INIT 1
#define ICE_TRAY_MODE_UP 2
#define ICE_TRAY_MODE_DOWN 3

#define ICE_TRAY_STEP_NUM 4

#define ICE_TRAY_HOLD_STEP 0 // 10
#define ICE_TRAY_INIT_PULSE                1000
#define ICE_TRAY_UP_PULSE 1000
#define ICE_TRAY_DOWN_PULSE 1000
#define ICE_TRAY_INIT_ADJUST 0

#define ICE_TRAY_STATUS_DOWN 0
#define ICE_TRAY_STATUS_UP 1

#define C_CUP_ICETRAY_HOT_STER 800

#define C_CUP_MY_RAMEN              1780
#define C_CUP_MY_DRIPCOFFEE         500

#define C_CUP_MY1                   111
#define C_CUP_MY2                   222
#define C_CUP_MY3                   333

#define DIMMING_SET_DEFAULT 0xef

#define FLOW_VALVE_MAX_OPEN 1800        // 占싱니띰옙 占쏙옙占쏙옙占싹곤옙

// 占쏙옙2025-06-02 Phil
#define FLOW_VALVE_ADJUST              300  //2025-06-05 21:01:28   cbr     //600	// 占쏙옙2025-06-02 Phil


/*#define UV_PROGRESS_DISPLAY_TIME            70*/
/*..hui [24-7-22占쏙옙占쏙옙 11:05:39] UI 占쏙옙占쏙옙占쏙옙占쏙옙 30占십뤄옙 占쏙옙占쏙옙 占쏙옙청..*/
#define UV_PROGRESS_DISPLAY_TIME 300
#define EERROR_DISPLAY_TIME 70

#define GAS_SWITCH_COLD 0
#define GAS_SWITCH_ICE 1
#define GAS_SWITCH_HOTGAS 2

/*..hui [20-2-24占쏙옙占쏙옙 7:44:45] 占시쇽옙 ONOFF占쏙옙 占승듸옙占쏙옙占쏙옙 占쌨댐옙 占싻몌옙..*/
#define COLD_TEMP_HIGH 0
#define COLD_TEMP_LOW 1

#define WIFI_UV_OPERATION_OFF 0
#define WIFI_UV_OPERATION_ON 1
#define WIFI_UV_OPERATION_GOING 2

#define WIFI_PAIRING_START 0
#define WIFI_PAIRING_ING 1
#define WIFI_PAIRING_FAIL 2
#define WIFI_PAIRING_SUCESS 3
#define WIFI_ERROR_DENY__AP3 4
#define WIFI_NO_AP__AP4 5
#define WIFI_NO_ACK__AP2 6
#define WIFI_FAIL_PASS__AP1 7
#define WIFI_NO_SERVER__AP5 8

#define PAIRING_STEP_1 0
#define PAIRING_STEP_2 1
#define PAIRING_STEP_3 2
#define PAIRING_STEP_4 3
#define PAIRING_STEP_5 4

#if 0
#define ICE_SETTING_OFF 0
#define ICE_SETTING_ICE_FIRST 1
#define ICE_SETTING_COLD_FIRST 2
#endif

#define MAKE_STOP 0
#define MAKE_COLD 1
#define MAKE_ICE 2

/*..hui [19-10-15占쏙옙占쏙옙 5:50:08] 占쏙옙占쏙옙 占쏙옙占쏙옙 占쌍대값占쏙옙 999.9..*/
#define USER_WATER_MAX_ACC 99999
#define DISPLAY_USER_WATER_MAX_ACC 9999

#define HEATING_PASS_TIME_THREE_MIN 1800

#define SILVER_CARE_TIME_MIN 2880

// #define CODY_CARE_MAX_TIME            65535
/*..hui [21-3-5占쏙옙占쏙옙 10:04:59] 占쌍댐옙 9999占쏙옙.. 占쏙옙占쏙옙占쏙옙 占쏙옙占??..*/
#define CODY_CARE_MAX_TIME 9999

#define ROOM_OVER_HEAT_TEMP 50
#define ROOM_OVER_HEAT_CLEAR_TEMP 45

////////////////////////////////////////////////////////////////////////////////////

#if 0
#define FILTER_NO_CHANGE 0
#define NEO_INO_FILTER_CHANGE 1
#define ALL_NEO_INO_RO_FILTER_CHANGE 3
#endif

#define FILTER_NO_CHANGE 0
#define NEO_INO_FILTER_CHANGE 4
#define ALL_NEO_INO_RO_FILTER_CHANGE 7

#define BLDC_COMP_OFF_0_HZ 0

#define BLDC_COMP_37Hz 0b00100101
#define BLDC_COMP_38Hz 0b00100110
#define BLDC_COMP_39Hz 0b00100111
#define BLDC_COMP_40Hz 0b00101000
#define BLDC_COMP_41Hz 0b00101001
#define BLDC_COMP_42Hz 0b00101010
#define BLDC_COMP_43Hz 0b00101011
#define BLDC_COMP_44Hz 0b00101100
#define BLDC_COMP_45Hz 0b00101101
#define BLDC_COMP_46Hz 0b00101110
#define BLDC_COMP_47Hz 0b00101111
#define BLDC_COMP_48Hz 0b00110000
#define BLDC_COMP_49Hz 0b00110001
#define BLDC_COMP_50Hz 0b00110010
#define BLDC_COMP_51Hz 0b00110011
#define BLDC_COMP_52Hz 0b00110100
#define BLDC_COMP_53Hz 0b00110101
#define BLDC_COMP_54Hz 0b00110110
#define BLDC_COMP_55Hz 0b00110111
#define BLDC_COMP_56Hz 0b00111000
#define BLDC_COMP_57Hz 0b00111001
#define BLDC_COMP_58Hz 0b00111010
#define BLDC_COMP_59Hz 0b00111011
#define BLDC_COMP_60Hz 0b00111100
#define BLDC_COMP_61Hz 0b00111101
#define BLDC_COMP_62Hz 0b00111110
#define BLDC_COMP_63Hz 0b00111111
#define BLDC_COMP_64Hz 0b01000000
#define BLDC_COMP_65Hz 0b01000001
#define BLDC_COMP_66Hz 0b01000010
#define BLDC_COMP_67Hz 0b01000011
#define BLDC_COMP_68Hz 0b01000100
#define BLDC_COMP_69Hz 0b01000101
#define BLDC_COMP_70Hz 0b01000110
#define BLDC_COMP_71Hz 0b01000111
#define BLDC_COMP_72Hz 0b01001000
#define BLDC_COMP_73Hz 0b01001001
#define BLDC_COMP_74Hz 0b01001010
#define BLDC_COMP_75Hz 0b01001011

#define HOT_GAS_AMB_TEMP_9_DIGREE 9
#define HOT_GAS_AMB_TEMP_13_DIGREE 13
#define HOT_GAS_AMB_TEMP_19_DIGREE 19
#define HOT_GAS_AMB_TEMP_24_DIGREE 24
#define HOT_GAS_AMB_TEMP_29_DIGREE 29

#define WIFI_OFF 0
#define WIFI_CONNECT 1
#define WIFI_DISCONNECT 2
#define WIFI_BLINK 3

#define WIFI_PAIRING_STANDBY 0
#define WIFI_PAIRING_STEP0_PREPARE 1
#define WIFI_PAIRING_STEP1_25_PERCENT 2
#define WIFI_PAIRING_STEP2_50_PERCENT 3
#define WIFI_PAIRING_STEP3_75_PERCENT 4
#define WIFI_PAIRING_STEP_FINISH 5

#define PAIRING_PROGRESS_0_PERCENT 0
#define PAIRING_PROGRESS_25_PERCENT 25
#define PAIRING_PROGRESS_50_PERCENT 50
#define PAIRING_PROGRESS_75_PERCENT 75
#define PAIRING_PROGRESS_100_PERCENT 100

#define WIFI_CERTIFICATE_NONE 0
#define WIFI_CERTIFICATE_ON 1
#define WIFI_CERTIFICATE_FINISH 2

#define WIFI_HOT_LOCK_OFF 1
#define WIFI_HOT_LOCK_ON 2

#define WIFI_PAIRING_START_30_MIN 18000

#define FEEDBACK_SHOW_TIME 30
#define POPUP_SHOW_TIME 30

#define ERROR_POPUP_SHOW_TIME 30

#define TEMP_SENSOR_OPEN 970
#define TEMP_SENSOR_SHORT 50
#define GAP 30
#define AT_PCB_UART_TEST 0xF9

#define NONE_TEST_MODE 0x00
#define PCB_TEST_MODE 0x01
#define UART_TEST_MODE 0x02
#define DISPLAY_TEST_MODE 0x04

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SOUND_TYPE_VOICE 0
#define SOUND_TYPE_MELODY 1
#define SOUND_TYPE_MUTE 2

#define SOUND_VOLUME_LEVEL_1 0
#define SOUND_VOLUME_LEVEL_2 1
#define SOUND_VOLUME_LEVEL_3 2
#define SOUND_VOLUME_LEVEL_4 3
#define SOUND_VOLUME_LEVEL_5 4

#define LANGUAGE_TYPE_KOREA 0
#define LANGUAGE_TYPE_ENGLISH 1
#define LANGUAGE_TYPE_SPANISH 2
#define LANGUAGE_TYPE_CHINESE 3
#define LANGUAGE_TYPE_FRANCE 4

#define LANGUAGE_MAX 4

#define SMART_ICON_NONE 0
/*..hui [25-3-27占쏙옙占쏙옙 1:53:24] 占쏙옙 占쏙옙占쏙옙占쏙옙..*/
#define SMART_ICON_SUNNY 1
/*..hui [25-3-27占쏙옙占쏙옙 1:53:28] 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙..*/
#define SMART_ICON_CLOUDY 2
/*..hui [25-3-27占쏙옙占쏙옙 1:53:31] 占쏙옙占?? 占쏙옙占쏙옙占쏙옙..*/
#define SMART_ICON_RAINY 3
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*NXD Address*/
#define VOICE_START 0x00
//==============================================================
#define KR          0            // 占싼깍옙占쏙옙
#define US        200            // 占쏙옙占쏙옙
#define ES        400            // 占쏙옙占쏙옙占싸억옙
#define CN        600            // 占쌩깍옙占쏙옙
#define FR        800            // 占쏙옙占쏙옙占쏙옙占쏙옙
#define KR_25	  1200			 // 25占쏙옙 占쏙옙占쏙옙

/* 占쏙옙占쏙옙 占신뱄옙占쏙옙! */
/* MINI, 1KG, 2KG 占쏙옙占쏙옙占쏙옙占쏙옙 */
#define VOICE_1_STOP_ICE_ICETANK_COVER                          1     // 占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙占?? 커占쏙옙占쏙옙 占쏙옙占싫쏙옙占싹댐옙. 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌌니댐옙.
#define VOICE_2_SHUTOFF_WATER_FRONT_COVER                       2     // '占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 커占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌌니댐옙.'
#define VOICE_3_RESTART_ICE_COVER_OK                            3     // 占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙占?? 커占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占싹댐옙. 占쌕쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌌니댐옙

#define VOICE_4_CALL_AS_COLD_WATER_ERROR                        93     // '占시쇽옙 占쏙옙?占쏙옙 占싱삼옙占쏙옙 占쏙옙占쏙옙占실억옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占싶울옙 占쏙옙占쏙옙占쏙옙占쌍쇽옙占쏙옙'
#define VOICE_5_CALL_AS_HOT_WATER_ERROR                         94     // '占승쇽옙 占쏙옙?占쏙옙 占싱삼옙占쏙옙 占쏙옙占쏙옙占실억옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占싶울옙 占쏙옙占쏙옙占쏙옙占쌍쇽옙占쏙옙'
#define VOICE_6_CALL_AS_ICE_ERROR                               95     // '占쏙옙占쏙옙 占쏙옙?占쏙옙 占싱삼옙占쏙옙 占쏙옙占쏙옙占실억옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占싶울옙 占쏙옙占쏙옙占쏙옙占쌍쇽옙占쏙옙'
#define VOICE_7_CALL_AS_WATER_SUPPLY_ERROR                      96    // '占쏙옙 占쏙옙占쌨울옙 占싱삼옙占쏙옙 占쏙옙占쏙옙 占실억옙占쏙옙占쏙옙, 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占?? 확占쏙옙占쏙옙占쌍시곤옙 占쏙옙占쏙옙占쏙옙 占쌥븝옙占실몌옙 占쏙옙占쏙옙占쏙옙占싶뤄옙 占쏙옙占쏙옙占쏙옙占쌍쇽옙占쏙옙.'
#define VOICE_8_CALL_AS_WATER_LEAKAGE_ERROR                     97     // '"占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占실억옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占?? 占쏙옙占쏙옙笭챨占?? 占쏙옙占쏙옙占쏙옙 占쌥븝옙占실몌옙 占쏙옙占쏙옙占쏙옙占싶뤄옙 占쏙옙占쏙옙占쏙옙占쌍쇽옙占쏙옙."'
#define VOICE_9_PRESS_YES_OR_NO_AFTER_FILTER		            98     // 占쏙옙占싶몌옙 占쏙옙체占쌩다몌옙 占쏙옙 占쏙옙占쏙옙占싣곤옙占?? 占쏙옙占쏙옙占쌍쇽옙占쏙옙.  占쏙옙체占쏙옙占쏙옙 占십았다몌옙 '占시쇽옙' 占쏙옙튼占쏙옙 占쏙옙占쏙옙占쌍쇽옙占쏙옙.
#define VOICE_10_NO_REPLACE_WITH_COVER							10	   // 占쏙옙占싶곤옙 占시바몌옙占쏙옙 占쏙옙占쌌듸옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占실억옙占쏙옙占싹댐옙. 占쏙옙품 커占쏙옙占쏙옙 占쏙옙占쏙옙 占쌕쏙옙 占쏙옙 占쏙옙 확占쏙옙占쏙옙占쌍쇽옙占쏙옙.
#define VOICE_11_START_FILTER_FLUSHING							11 	   // 占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占싹깍옙 占쏙옙占쏙옙 占쌔븝옙 占쌩울옙 占쌍쏙옙占싹댐옙. 占쏙옙첩占?? 占쏙옙慕占쏙옙玲占쏙옙占??.
#define VOICE_12_FINISH_FILTER_FLUSHING                         12     // '占쏙옙占쏙옙 占시뤄옙占쏙옙占쏙옙 占싹뤄옙퓸占?? 占쏙옙품 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占쌌니댐옙.'
#define VOICE_13_CHECK_FILTER_FLUSHING_MANUAL                   99     // '"占쏙옙占쏙옙 占시뤄옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占?? 占십았쏙옙占싹댐옙.  占쏙옙占쏙옙 占쏙옙체占쏙옙 占쏙옙占쏙옙占싹셨다몌옙, 占신댐옙占쏙옙占쏙옙 占쏙옙占쏙옙占싹울옙 占시뤄옙占쏙옙占쏙옙 占쌕쏙옙 占쏙옙占쏙옙占쏙옙占쌍쇽옙占쏙옙."'
#define VOICE_14_NO_REPLACE_WITH_COVER							100	   // 占쏙옙占싶곤옙 占시바몌옙占쏙옙 占쏙옙占쌌듸옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占실억옙占쏙옙占싹댐옙. 占쏙옙품 커占쏙옙占쏙옙 占쏙옙占쏙옙 占쌕쏙옙 占쏙옙 占쏙옙 확占쏙옙占쏙옙占쌍쇽옙占쏙옙. // 占쌩븝옙
#define VOICE_15_PROHIBIT_DURING_SMART_TESTING_MODE             101     // 占쏙옙占쏙옙 IoCare 占시뤄옙占쏙옙 占쌜울옙占쏙옙 占쏙옙占쏙옙트 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占싱띰옙 占쏙옙품占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙 占쏙옙占쏙옙占싹댐옙. 占쌜울옙占쏙옙 占쏙옙占쏙옙트 占쏙옙占쏙옙占쏙옙 占싹뤄옙占싹쏙옙 占쏙옙 占쌕쏙옙 占시듸옙占쏙옙占쌍쇽옙占쏙옙.
#define VOICE_16_START_SMART_TESTING_MODE                       16     // 占쏙옙품 占쏙옙占승몌옙 占식억옙占싹깍옙 占쏙옙占쏙옙 占쏙옙占쏙옙트 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌌니댐옙. 占쏙옙첩占?? 占쏙옙慕占쏙옙玲占쏙옙占??
#define VOICE_17_FINISH_SMART_TESTING_MODE_NO_ERROR             102     // '占쏙옙占쏙옙트 占쏙옙占쏙옙占쏙옙 占싹뤄옙 占실억옙 占쏙옙품占쏙옙 占쏙옙占쏙옙絿占?? 占쏙옙 占쌍쏙옙占싹댐옙. '
#define VOICE_18_FINISH_SMART_TESTING_MODE_WITH_ERROR           103     // '占쏙옙占쏙옙트 占쏙옙占쏙옙占쏙옙 占싹뤄옙 占실억옙占쏙옙占싹댐옙. 占쏙옙占쏙옙트 占쏙옙占쏙옙 占쏙옙占?? 占싱삼옙占쏙옙 占쏙옙占쏙옙占실억옙占쏙옙占싹댐옙. ioCare占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙 占쏙옙占쏙옙占쏙옙 확占쏙옙占쏙옙占쌍쇽옙占쏙옙.'
#define VOICE_19_START_BLE_PAIRNG			                    104     // 占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 ioCare 占쌜울옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌌니댐옙.
#define VOICE_20_INFORM_APP_PAIRING_SUCCESS_WITH_BLE            105     // 占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 ioCare 占쏙옙 占쏙옙占쏙옙占쏙옙 占싹뤄옙퓸占쏙옙占쏙옙求占??.
#define VOICE_21_INFORM_APP_PAIRING_FAIL_WITH_BLE            	106     // 占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 ioCare 占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占싹울옙占쏙옙占싹댐옙.  占쌘듸옙占쏙옙 占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌍댐옙占쏙옙 확占쏙옙占쏙옙占쌍쇽옙占쏙옙
#define VOICE_22_START_WIFI_PAIRNG			                    107     // 占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 ioCare 占쌜울옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌌니댐옙.
#define VOICE_23_INFORM_APP_PAIRING_SUCCESS_WITH_WIFI           108     // 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占싹뤄옙퓸占쏙옙占쏙옙求占??.  占쏙옙占쏙옙占쏙옙占쏙옙 ioCare 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙트占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙 占쌍쏙옙占싹댐옙.
#define VOICE_24_INFORM_APP_PAIRING_FAIL_WITH_WIFI            	109     // 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占써에 占쏙옙占쏙옙占싹울옙占쏙옙占싹댐옙.   占쏙옙占싶놂옙 占쏙옙占쏙옙占썩를 확占쏙옙占쏙옙占쌍시곤옙,    占쏙옙占쏙옙占쏙옙 占쌥븝옙占실몌옙 占쌥쇽옙占싶울옙 占쏙옙占쏙옙占쏙옙占쌍쇽옙占쏙옙
#define	VOICE_25_INFORM_WIFI_MODE_DEACTIVATED					110	   // 占쏙옙품占쏙옙 Wi-Fi占쏙옙 占쏙옙占쏙옙占쏙옙占싹댐옙. 占쌕쏙옙 占쏙옙占쏙옙占싹뤄옙占쏙옙 占시쇽옙占쏙옙 占쎈량 占쏙옙튼占쏙옙 占쏙옙占시울옙 3占쏙옙 占쏙옙占쏙옙占쌍쇽옙占쏙옙.
#define	VOICE_26_APPLY_WIFI_AFTER_DEACTIVATING					26	   // 占쏙옙품占쏙옙 Wi-Fi占쏙옙 占쏙옙占쏙옙占쏙옙占싹댐옙.
#define VOICE_27_INFORM_WIFI_ON                                 27     // '占쏙옙품占쏙옙 Wi-Fi占쏙옙 占쏙옙占쏙옙占쏙옙占싹댐옙.'
#define VOICE_28_INFORM_WIFI_OFF                                112     // 占쏙옙품占쏙옙 Wi-Fi占쏙옙 占쏙옙占쏙옙占쏙옙占싹댐옙. 占쌕쏙옙 占쏙옙占쏙옙占싹뤄옙占쏙옙 占시쇽옙占쏙옙 占쎈량 占쏙옙튼占쏙옙 占쏙옙占시울옙 3占쏙옙 占쏙옙占쏙옙占쌍쇽옙占쏙옙.
#define	VOICE_29_APPLY_PRODUCT_CERT_OCCUPATION					29	   // 占쏙옙품 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쌉니댐옙.    占쌜울옙占쏙옙 占쏙옙占싱듸옙占싹댐옙 占쏙옙튼占쏙옙 占쏙옙占쏙옙 占쌍쇽옙占쏙옙.
#define VOICE_30_INFORM_APP_PAIRING_SUCCESS_WITH_WIFI           113     // 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占싹뤄옙퓸占쏙옙占쏙옙求占??.  占쏙옙占쏙옙占쏙옙占쏙옙 ioCare 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙트占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙 占쌍쏙옙占싹댐옙.
#define VOICE_31_INFORM_APP_PAIRING_FAIL_WITH_WIFI            	114     // 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占써에 占쏙옙占쏙옙占싹울옙占쏙옙占싹댐옙.   占쏙옙占싶놂옙 占쏙옙占쏙옙占썩를 확占쏙옙占쏙옙占쌍시곤옙,    占쏙옙占쏙옙占쏙옙 占쌥븝옙占실몌옙 占쌥쇽옙占싶울옙 占쏙옙占쏙옙占쏙옙占쌍쇽옙占쏙옙
#define VOICE_32_INFORM_APP_PAIRING_FAIL_WITH_WIFI            	32     // 占쏙옙품占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占싹울옙占쏙옙占싹댐옙.
#define	VOICE_33_INFORM_PROEDUCT_BEFORE_FLUSHING				116	   // 占싫놂옙占싹쇽옙占쏙옙. 占쏙옙占쏙옙占쏙옙 占쌘울옙占쏙옙 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙치占쏙옙 占쏙옙占싶드리占쌘쏙옙占싹댐옙. 占쏙옙 占쏙옙占쏙옙占싣곤옙占?? 占쏙옙占쏙옙占시몌옙 占쏙옙치占쏙옙 占쏙옙占쏙옙占싹겠쏙옙占싹댐옙.
#define	VOICE_34_INFORM_WIFI_BEFORE_FLUSHING					34	   // 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌌니댐옙.
#define VOICE_35_INFORM_FLUSHING_START							118		// 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占싹깍옙 占쏙옙占쏙옙 占쌔븝옙占쏙옙占쌉니댐옙. 占싹뤄옙 占쏙옙 占쏙옙占쏙옙占쏙옙玲占쏙옙占??.
#define VOICE_36_INFORM_FLUSHING_FINISH							119		// 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占싹깍옙 占쏙옙占쏙옙 占쌔븝옙 占싹뤄옙퓸占쏙옙占쏙옙求占??.
#define	VOICE_37_NO_USE_AFTER_WAKE								119		// 占쏙옙챨占?? 占싱삼옙占?? 占쏙옙 첫 占쏙옙占쏙옙 占쏙옙占쏙옙玲占쏙옙占??.
#define	VOICE_38_HOT_WATER_PREHEAT								38		//	占승쇽옙 占승듸옙占쏙옙 占쏙옙占쌩곤옙 占쌍쏙옙占싹댐옙. 占쏙옙첩占?? 占쏙옙慕占쏙옙玲占쏙옙占??.
#define VOICE_40_CAUTION_HOT_WATER                              40      // '占쏙옙 占승듸옙占쏙옙 占쌩거울옙占??, 占쏙옙占쏙옙 占싹쇽옙占쏙옙.'
#define VOICE_41_CAUTION_CONTINUOUS_HOT_WATER                   41      // 占승쇽옙占쏙옙 占쌩거울옙占?? 占쏙옙占쏙옙占싹쇽옙占쏙옙.       占쏙옙占쏙옙占쏙옙 占쏙옙占쌩시뤄옙占쏙옙 占쏙옙占쏙옙 占쏙옙튼占쏙옙 占쏙옙占쏙옙占쌍쇽옙占쏙옙.
#define VOICE_42_APPLYING_SETTING_FAIL                          123     // 占쏙옙占쏙옙 占쏙옙튼占쏙옙 3占쏙옙 占쏙옙占쏙옙占시몌옙,   占쌘울옙占쏙옙 占쏙옙占쏙옙占쏙옙占쏙옙 占쌕억옙占쏙옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占싹쏙옙 占쏙옙 占쌍쏙옙占싹댐옙.
#define VOICE_43_CLICK_3S_FOR_SETTING_MODE                      133     // 占쏙옙占쏙옙占쏙옙占?? 占쏙옙占쏙옙占쌌니댐옙. 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占?? 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌌니댐옙.
#define VOICE_39_HOT_WATER_EXTRACT                              39      // 占쏙옙占승쇽옙占쏙옙 占쏙옙占쏙옙絳求占??. 占쏙옙占쏙옙 占쏙옙占썩구占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쌍쇽옙占쏙옙.
/****************************************************************************************************************************************************/
/**
 * 占쏙옙 占싣뤄옙占싸댐옙 확占쏙옙 占싹뤄옙!
 */

 /* 占쏙옙占쏙옙 占쏙옙占쏙옙 */
#define VOICE_44_INFORM_WATER_OPEN_FILER                      	124     // 占쏙옙占쏙옙 커占쏙옙占쏙옙 占쏙옙占싫쏙옙占싹댐옙. 占쏙옙占쏙옙 커占쏙옙占쏙옙 占쌥억옙占쌍쇽옙占쏙옙.
#define VOICE_45_INFORM_HOT_LOCK_ON                             125     // 占승쇽옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占싹댐옙. 占승쇽옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占싹뤄옙占쏙옙, 占쏙옙占쏙옙占쏙옙占쏙옙 占승쇽옙 占쏙옙占?? 占쏙옙튼占쏙옙 占쏙옙占쏙옙占쌍쇽옙占쏙옙
#define VOICE_49_INFORM_ICE_LOCK_ON                             128     // 占쏙옙占쏙옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占싹댐옙. 占쏙옙占쏙옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占싹뤄옙占쏙옙, 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占?? 占쏙옙튼占쏙옙 占쏙옙占쏙옙占쌍쇽옙占쏙옙.
#define VOICE_50_PRESS_BUTTON_ICE_FUNCTION_ON                   129     // '占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙, 占쏙옙占쏙옙 占쏙옙튼占쏙옙 3占쏙옙 占쏙옙占쏙옙 ON占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占쌍쇽옙占쏙옙.
#define VOICE_51_SET_CLOCK_ECO_MODE                 		    130     // 占쏙옙침占쏙옙占?? 占쏙옙占쏙옙占?? 占쏙옙占쏙옙 wifi占쏙옙 占쏙옙占쏙옙占싹거놂옙 占쏙옙占쏙옙 占시곤옙占쏙옙 占쏙옙占쏙옙占쏙옙占쌍쇽옙占쏙옙.
#define VOICE_52_NO_GUARANTEE_ICE_ECO_MODE                      131    // 占쏙옙침占쏙옙占?? 占쏙옙占쏙옙占실억옙, 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌩쏙옙占싹댐옙. 占쏙옙占쏙옙占쏙옙 占쏙옙 占십울옙占싹몌옙, 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙침占쏙옙占?? 占쏙옙占쏙옙占쏙옙占쌍쇽옙占쏙옙.
#define VOICE_53_PRESS_SETTING_MODE_ALL_LOCK_OFF                132    // 占쏙옙占?? 占쏙옙튼占쏙옙 占쏙옙占쏙옙笭占쏙옙求占??. 占쏙옙체 占쏙옙占?? 占쏙옙튼占쏙옙 3占쏙옙 占싱삼옙 占쏙옙占쏙옙占쏙옙 占쏙옙占?? 占쏙옙占쏙옙占?? 占쌕쏙옙 占쏙옙占쏙옙占?? 占쏙옙 占쌍쏙옙占싹댐옙.
#define VOICE_133_SETTING_MODE_START                            133     // 占쏙옙占쏙옙占쏙옙占?? 占쏙옙占쏙옙占쌌니댐옙. 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占?? 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌌니댐옙.
#define VOICE_134_SETTING_MODE_START_1KG_CP                     134     // 占쏙옙占쏙옙占쏙옙占?? 占쏙옙占쏙옙占쌌니댐옙. 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占?? 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌌니댐옙.
#define VOICE_54_ACTIVATE_SETTING_HOT_LOCK		                54     // 占승쇽옙 占쏙옙튼占쏙옙 占쏙옙占쏙옙占싹댐옙.
#define VOICE_55_DEACTIVATE_SETTING_HOT_LOCK		            135     // 占승쇽옙占쏙옙 占쏙옙占쏙옙絿占?? 占쏙옙 占쌍쏙옙占싹댐옙.
#define VOICE_59_ACTIVATE_SETTING_COLD			                59     // 占시쇽옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占쏙옙占싹댐옙.    占쏙옙占쏙옙占싹쏙옙 占승듸옙占쏙옙占쏙옙 占시곤옙占쏙옙 占쌕쇽옙 占쌀울옙絳求占??.
#define VOICE_60_DEACTIVATE_SETTING_COLD			            136     // 占시쇽옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占쏙옙占싹댐옙.    占시쇽옙占쏙옙 占쏙옙占쏙옙絿占?? 占쏙옙 占쏙옙占쏙옙占싹댐옙.
#define VOICE_63_INFORM_ALL_LOCK_ON                             63     // '占쏙옙占?? 占쏙옙튼占쏙옙 占쏙옙占쏙옙占싹댐옙.
#define VOICE_64_INFORM_ALL_LOCK_OFF                            137     // '占쏙옙체 占쏙옙튼 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占실억옙占쏙옙占싹댐옙.
#define VOICE_65_VOICE_MODE                                   	65     // 占쏙옙占쏙옙占싫놂옙 占쏙옙占쏙옙都求占??.
#define VOICE_66_MELODY_MODE                                  	66     // 효占쏙옙占쏙옙 占쏙옙占쏙옙都求占??.
#define VOICE_67_MUTE_MODE                                  	67     // 占쏙옙占쏙옙 占쏙옙占쏙옙都求占??.
#define VOICE_68_MODE_SET_VOICE                                 68     // 占쏙옙占쏙옙占싫놂옙 占쏙옙占?? 占쏙옙占쏙옙占실억옙占쏙옙占싹댐옙.
#define VOICE_69_MODE_SET_MELODY                                69     // 효占쏙옙占쏙옙 占쏙옙占?? 占쏙옙占쏙옙占실억옙占쏙옙占싹댐옙.
#define VOICE_70_MODE_SET_MUTE                                  70     // 占쏙옙占쏙옙 占쏙옙占?? 占쏙옙占쏙옙占실억옙占쏙옙占싹댐옙.
#define VOICE_71_INFORM_COLD_FUNCTION_OFF                       138     // '"占시쇽옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占쏙옙占싹댐옙. 占시쇽옙占쏙옙 占쏙옙占쏙옙絿占?? 占쏙옙 占쏙옙占쏙옙占싹댐옙."
#define VOICE_72_INFORM_COLD_FUNCTION_ON                        72     // '"占시쇽옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占쏙옙占싹댐옙. 占쏙옙占쏙옙占싹쏙옙 占승듸옙占쏙옙占쏙옙 占시곤옙占쏙옙 占쌕쇽옙 占쌀울옙絳求占??."
#define VOICE_139_TRANSFER_STRONG_TO_WEAK                       139     // 占시쇽옙 占승듸옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙퓸占쏙옙占쏙옙求占??.  占쏙옙占쏙옙占싹쏙옙 占승듸옙占쏙옙占쏙옙 占시곤옙占쏙옙 占쌕쇽옙 占쌀울옙絳求占??.
#define VOICE_140_TRANSFER_WEAK_TO_STRONG                       140     // 占시쇽옙 占승듸옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙퓸占쏙옙占쏙옙求占??. 占쏙옙占쏙옙占싹쏙옙 占승듸옙占쏙옙占쏙옙 占시곤옙占쏙옙 占쌕쇽옙 占쌀울옙絳求占??.
#define VOICE_75_SETTING_MODE_CLOCK                           	75     // '占시곤옙 占쏙옙占쏙옙 占쏙옙占쏙옙都求占?? '
#define VOICE_76_MODE_SET_CLOCK                               	76     // 占시곤옙占쏙옙 占쏙옙占쏙옙占실억옙占쏙옙占싹댐옙.
#define VOICE_77_FINISH_SETTING_MODE                      		77     // 占쏙옙占쏙옙占쏙옙占?? 占쏙옙占쏙옙占쌌니댐옙.
#define VOICE_78_INFORM_ICE_LOCK_ON                             141     // 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙튼占쏙옙 占쏙옙占쏙옙占싹댐옙.
#define VOICE_79_INFORM_ICE_LOCK_OFF                            142     // 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙튼占쏙옙 占쏙옙占쏙옙占?? 占쏙옙 占쌍쏙옙占싹댐옙.
#define VOICE_143_TRANSFER_BIG_TO_SAMLL		                    143     // 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙퓸占쏙옙占쏙옙求占??. 占쏙옙占쏙옙占싹쏙옙 占쏙옙占쏙옙크占쏙옙占?? 占쏙옙占쏙옙풉占쏙옙占쏙옙占쏙옙 占시곤옙占쏙옙 占쌕쇽옙 占쌀울옙絳求占??
#define VOICE_144_TRANSFER_SMALL_TO_BIG                         144     // 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 큰 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙퓸占쏙옙占쏙옙求占??.  占쏙옙占쏙옙占싹쏙옙 占쏙옙占쏙옙크占쏙옙占?? 占쏙옙占쏙옙풉占쏙옙占쏙옙占쏙옙 占시곤옙占쏙옙 占쌕쇽옙 占쌀울옙絳求占??.
#define VOICE_80_INFORM_ICE_FUNCTION_ON                         80     // '占쏙옙占쏙옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占쏙옙占싹댐옙. 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙쨉占?? 占시곤옙占쏙옙 占쌕쇽옙 占쌀울옙絳求占??'
#define VOICE_81_INFORM_ICE_FUNCTION_OFF                      	81     //  占쏙옙占쏙옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占쏙옙占싹댐옙. 占쏙옙占쏙옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙狗占쏙옙占?? 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙OFF 占쏙옙튼占쏙옙 占쏙옙占쏙옙占쌍쇽옙占쏙옙.
#define VOICE_145_ACTIVATE_ECO_MODE            			        145    // 占쏙옙침占쏙옙占?? 占쏙옙占쏙옙占실억옙占쏙옙占싹댐옙.   占쏙옙占쏙옙占쏙옙 占쏙옙침占시곤옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쌌니댐옙.
#define VOICE_146_DEACTIVAT_ECO_MODE				            146    // 占쏙옙침占쏙옙占?? 占쏙옙占쏙옙占실억옙占쏙옙占싹댐옙.
#define VOICE_147_INFORM_RAMYEON_RECIPE			                147     // 占쏙옙占?? 占쏙옙占쏙옙占실울옙 占쏙옙占쏙옙화 占쏙옙 占승쇽옙 占쎈량占쏙옙 占쏙옙占쏙옙絳求占??.
#define VOICE_148_INFORM_RAMYEON_DRIP_COFFEE	                148     // 占썲립커占쏙옙 占쏙옙占쏙옙占실울옙 占쏙옙占쏙옙화 占쏙옙 占승쇽옙 占쎈량占쏙옙 3占쏙옙占쏙옙 占쏙옙占쏙옙占쏘서 占쏙옙占쏙옙絳求占??.  占승쇽옙 占쏙옙占쏙옙占쏙옙 占싹뤄옙占?? 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占쌍쇽옙占쏙옙.
#define VOICE_149_INFORM_TEA_RECIPE                             149     // 占쏙옙 占쏙옙占쏙옙占실울옙 占쏙옙占쏙옙화 占쏙옙 占승쇽옙 占쎈량占쏙옙 占쏙옙占쏙옙絳求占??.
#define VOICE_150_INFORM_MY1_RECIPE				                150     // MY1占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙絳求占??.
#define VOICE_151_INFORM_MY2_RECIPE				                1351     // MY2占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙絳求占??.
#define VOICE_152_INFORM_MY3_RECIPE                             152     // MY3占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙絳求占??.
#define VOICE_153_INFORM_SET_MY1_RECIPE			                153     // 占쏙옙占쏙옙占쏙옙占쏙옙 占쎈량占쏙옙 占승듸옙占쏙옙 my1占쏙옙 占쏙옙占쏙옙占쏙옙 占싹뤄옙퓸占쏙옙占쏙옙求占??.
#define VOICE_154_INFORM_SET_MY2_RECIPE			                154     // 占쏙옙占쏙옙占쏙옙占쏙옙 占쎈량占쏙옙 占승듸옙占쏙옙 my2占쏙옙 占쏙옙占쏙옙占쏙옙 占싹뤄옙퓸占쏙옙占쏙옙求占??.
#define VOICE_155_INFORM_SET_MY3_RECIPE                         155     // 占쏙옙占쏙옙占쏙옙占쏙옙 占쎈량占쏙옙 占승듸옙占쏙옙 my3占쏙옙 占쏙옙占쏙옙占쏙옙 占싹뤄옙퓸占쏙옙占쏙옙求占??.
#define VOICE_85_INFORM_ICE_TRAY_STER	                        85     // 占쏙옙占쏙옙 트占쏙옙占싱몌옙 占쏙옙占승쇽옙占쏙옙 占쏙옙척 占쏙옙占쌉니댐옙.  占쏙옙척占쏙옙 占싹뤄옙퓔占?? 占쌕쏙옙 占쏙옙占쏙옙占쏙옙 占쌍쇽옙占쏙옙.
#define VOICE_86_INFORM_ICE_TRAY_STER_NO_ICE                    86     // 占쏙옙占쏙옙 트占쏙옙占싱몌옙 占쏙옙占승쇽옙占쏙옙 占쏙옙척 占쏙옙占쌉니댐옙.  占쏙옙척占쏙옙 占싹뤄옙퓔占?? 占쌕쏙옙 占쏙옙占쏙옙占쏙옙 占쌍쇽옙占쏙옙.
#define VOICE_87_INFORM_COMPLETE_ICE_TRAY_STER	                87     // 占쏙옙占쏙옙 트占쏙옙占쏙옙 占쏙옙占승쇽옙 占쏙옙척占쏙옙 占싹뤄옙퓸占쏙옙占쏙옙求占??. 占쏙옙占쏙옙占쏙옙 占쌕쏙옙 占쏙옙占쏙옙占쌌니댐옙.
#define VOICE_91_INFORM_ICE_FULL            			        91     // 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙찼占쏙옙占싹댐옙.
#define VOICE_92_INFORM_CLICK_ICE_WATER			                92     // 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙絳求占??.  占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙求占?? 占신븝옙占쏙옙 큰 占쏙옙占쏙옙 占쏙옙占쏙옙占?? 占쌍쇽옙占쏙옙.

/* 1KG,2KG ONLY! */
#define VOICE_126_INFORM_COLD_FUNCTION_OFF_1_2KG                126     // 占시쇽옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占쌍쏙옙占싹댐옙. 占시쇽옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙狗占쏙옙占??, 占쏙옙占쏙옙占쏙옙占쏙옙 占시쇽옙OFF 占쏙옙튼占쏙옙 占쏙옙占쏙옙占쌍쇽옙占쏙옙
#define VOICE_156_ICE_30_PERCENT_UNDER                          156     // "占쏙옙占쏙옙占쏙옙占쏙옙占?? 占쏙옙 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占싹댐옙. 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 占쎌선占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙 占쌍쏙옙占싹댐옙."

/* MINI ONLY! */
#define VOICE_47_INFORM_COLD_FUNCTION_OFF                       127     // 占시쇽옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙占쌍쏙옙占싹댐옙. 占시쇽옙 占쏙옙占쏙옙占?? 占쏙옙占쏙옙狗占쏙옙占??, 占시쇽옙 占쏙옙튼占쏙옙 3占쏙옙 占싱삼옙 占쏙옙占쏙옙占쌍쇽옙占쏙옙

/* 2KG ONLY! */
#define VOICE_152_MY3_WATER_EXTRACT                             152
#define VOICE_157_BREAK_ICE_SELECTED                            157     // "占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占시되억옙占쏙옙占싹댐옙."

/* ICE MINI, MAX ONLY! */
#define VOICE_1365_ICE_STUCK_DETECTED                           165     // "얼음 토출구에 얼음이 걸려 있습니다. 추출 버튼을 한번 더 눌러 걸린 얼음을 제거해 주세요."

/* MELODY (ICE MINI, 1KG, 2KG REVISION) */
#define VOICE_151_SPECIAL_FUNCTION                             	151     // '특占쏙옙占쏙옙占쏙옙都求占??.' (占쏙옙占쏙옙/占쏙옙占쏙옙占??)

#define VOICE_191_MELODY_PLUG_IN_COWAY                         44
#define VOICE_192_MELODY_DISPENSE_CONTINUOUS                   45
#define VOICE_193_MELODY_DISPENSE_START                        46
#define VOICE_194_MELODY_DISPENSE_FINISH                       47

#define VOICE_196_MELODY_SELECT                                48
#define VOICE_197_MELODY_WARNING                               49
#define VOICE_198_MELODY_SET_ON                                50
#define VOICE_199_MELODY_SET_OFF                               51

#define VOICE_196_WIFI_SELECT                                396
#define VOICE_197_WIFI_WARNING                               397
#define VOICE_198_WIFI_SET_ON                                398
#define VOICE_199_WIFI_SET_OFF                               399
//==============================================================

typedef enum
{
    HOT_SET_TEMP____45oC = 0,
	HOT_SET_TEMP____50oC,
	HOT_SET_TEMP____55oC,
	HOT_SET_TEMP____60oC,
	HOT_SET_TEMP____65oC,
	HOT_SET_TEMP____70oC,
	HOT_SET_TEMP____75oC,
	HOT_SET_TEMP____80oC,
	HOT_SET_TEMP____85oC,
	HOT_SET_TEMP____90oC,
	HOT_SET_TEMP____95oC,
	HOT_SET_TEMP____100oC,
}HOT_TEMP_LEVEL;


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define AT_MODEL_CMD_CHP_ICON_AIS_2KG 0x47

#define AT_MODEL_CMD_NATION_KOREA 0x00
#define AT_MODEL_CMD_NATION_US 0x07

#define AT_RS232_STX 0x01
#define AT_RS232_ETX 0x04
#define AT_RS232_ACK 0x06
#define AT_RS232_NAK 0x15

#define AT_UART_No_CMD 0x0000
#define AT_UART_CMD_START 0x2000              // Start
#define AT_UART_CMD_SETTINGS 0x3000           // Settings
#define AT_UART_CMD_WIFI 0x3010               // WIFI
#define AT_UART_CMD_UV_ICE_FAUCET_1 0x3011    // ICE FAUCET UV 1
#define AT_UART_CMD_SENSOR_FLOW_FILTER 0x3012 // Filter 占쏙옙占쏙옙 占쏙옙占쏙옙
#define AT_UART_CMD_CURRENT_CALC 0x3013       // DC 占쏙옙占쏙옙
#define AT_UART_CMD_TECH_TASK_ERROR 0x6016
#define AT_UART_CMD_TECH_TASK_WARNING 0x6017
#define AT_UART_CMD_TECH_TASK_INFO 0x6018
#define AT_UART_CMD_TECH_TASK_DEBUG 0x6019
#define AT_UART_CMD_TECH_TASK_LOG 0x601A
#define AT_UART_CMD_TECH_TASK_CONFIG 0x601B
#define AT_UART_CMD_TECH_TASK_STATUS 0x601C
#define AT_UART_CMD_TECH_TASK_COMMAND 0x601D
#define AT_UART_CMD_TECH_TASK_RESPONSE 0x601E

#define AT_UART_CMD_UV_ICE_FAUCET_2 0x3014 // ICE FAUCET UV 2
#define AT_UART_CMD_UV_WATER_FAUCET 0x3015 // WATER FAUCET UV
#define AT_UART_CMD_DC_FAN 0x3016          // fan
#define AT_UART_CMD_DRAIN_PUMP 0x3017      // drain pump

#define AT_UART_CMD_TDS_IN 0x3018 // TDS IN 占쏙옙占쏙옙
#define AT_UART_CMD_UV_TANK_3 0x3019
// #define AT_UART_CMD_TDS_OUT                    0x3019              // TDS OUT 占쏙옙占쏙옙
#define AT_UART_CMD_ICE_LACK_SENSOR 0x301A
#define AT_UART_CMD_UV_ICE_TANK_1_2 0x301B // uv ice tank 1,2
#define AT_UART_CMD_UV_ICE_TRAY_1_2 0x301C // uv ice tray 1,2

#define AT_UART_CMD_ICE_FULL_SENSOR 0x301D // ice full sensor
#define AT_UART_CMD_RTC_TIME 0x301E        // rtc

// #define AT_UART_CMD_TRAY_PUMP                  0x301F              // tray pump
#define AT_UART_CMD_ICE_DOOR_HEATER 0x301F

#define AT_UART_CMD_SENSOR_TH 0x3020 // 占승듸옙 占쏙옙占쏙옙

#define AT_UART_CMD_SENSOR_WATER_LEVEL 0x3030 // 占쏙옙占쏙옙 占쏙옙占쏙옙

#define AT_UART_CMD_SENSOR_ICE 0x3040 // 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙
#define AT_UART_CMD_HEATER 0x3050     // 占승쇽옙 占쏙옙占쏙옙

#define AT_UART_CMD_NO_LOAD 0x5000        // 占쏙옙체 占쏙옙占쏙옙 OFF
#define AT_UART_CMD_HOT_HEATER_ON 0x5010  // 占승쇽옙 占쏙옙占쏙옙 ON
#define AT_UART_CMD_HOT_HEATER_OFF 0x5011 // 占승쇽옙 占쏙옙占쏙옙 OFF

#define AT_UART_CMD_ICE_HEATER_ON 0x5012  // 탈占쏙옙 占쏙옙占쏙옙 ON
#define AT_UART_CMD_ICE_HEATER_OFF 0x5013 // 탈占쏙옙 占쏙옙占쏙옙 OFF

#define AT_UART_CMD_ROOM_IN_VALVE_ON 0x5100
#define AT_UART_CMD_ROOM_IN_VALVE_OFF 0x5101

#define AT_UART_CMD_COLD_IN_VALVE_ON 0x5102
#define AT_UART_CMD_COLD_IN_VALVE_OFF 0x5103

#define AT_UART_CMD_HOT_IN_VALVE_ON 0x5104
#define AT_UART_CMD_HOT_IN_VALVE_OFF 0x5105

#define AT_UART_CMD_ROOM_COLD_EXTRACT_VALVE_ON 0x5106
#define AT_UART_CMD_ROOM_COLD_EXTRACT_VALVE_OFF 0x5107

#define AT_UART_CMD_COLD_VALVE_ON 0x5108
#define AT_UART_CMD_COLD_VALVE_OFF 0x5109
#define AT_UART_CMD_HOT_VALVE_ON 0x510A
#define AT_UART_CMD_HOT_VALVE_OFF 0x510B

/* 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占?? 占쏙옙占쏙옙 250311 CH.PARK */
#define AT_UART_CMD_ICE_WATER_VALVE_ON 0x510C
#define AT_UART_CMD_ICE_WATER_VALVE_OFF 0x510D

#define AT_UART_CMD_FEED_VALVE_ON 0x510E
#define AT_UART_CMD_FEED_VALVE_OFF 0x510F
#define AT_UART_CMD_NOS_VALVE_ON 0x5110
#define AT_UART_CMD_NOS_VALVE_OFF 0x5111

#define AT_UART_CMD_HOT_DRAIN_VALVE_ON 0x5114
#define AT_UART_CMD_HOT_DRAIN_VALVE_OFF 0x5115

#define AT_UART_CMD_TRAY_IN_VALVE_ON 0x5116
#define AT_UART_CMD_TRAY_IN_VALVE_OFF 0x5117

#define AT_UART_CMD_COLD_DRAIN_ON 0x5118
#define AT_UART_CMD_COLD_DRAIN_OFF 0x5119

#define AT_UART_CMD_FLUSHING_FEED_VALVE_ON 0x5122
#define AT_UART_CMD_FLUSHING_FEED_VALVE_OFF 0x5123

#define AT_UART_CMD_FLUSHING_NOS_VALVE_ON 0x5124
#define AT_UART_CMD_FLUSHING_NOS_VALVE_OFF 0x5125

#define AT_UART_CMD_OVERHEATING_NOS_ON 0x512A
#define AT_UART_CMD_OVERHEATING_NOS_OFF 0x512B

#define AT_UART_CMD_AIR_FEED_ON 0x5132
#define AT_UART_CMD_AIR_FEED_OFF 0x5133

#define AT_UART_CMD_HOT_IN_FEED_ON 0x5134
#define AT_UART_CMD_HOT_IN_FEED_OFF 0x5135

#define AT_UART_CMD_ICE_TANK_STER_LEFT_ON 0x513C
#define AT_UART_CMD_ICE_TANK_STER_LEFT_OFF 0x513D

#define AT_UART_CMD_ICE_TANK_STER_RIGHT_ON 0x513E
#define AT_UART_CMD_ICE_TANK_STER_RIGHT_OFF 0x513F

#define AT_UART_CMD_COOLING_FAN_ON 0x5200
#define AT_UART_CMD_COOLING_FAN_OFF 0x5201

#define AT_UART_CMD_GAS_SWITCH_ON 0x5202
#define AT_UART_CMD_GAS_SWITCH_OFF 0x5203

#define AT_UART_CMD_ICE_TRAY_MOTOR_ON 0x5206
#define AT_UART_CMD_ICE_TRAY_MOTOR_OFF 0x5207
#define AT_UART_CMD_ICE_DOOR_MOTOR_ON 0x5208
#define AT_UART_CMD_ICE_DOOR_MOTOR_OFF 0x5209
#define AT_UART_CMD_ICE_EXTRACT_MOTOR_CW_ON 0x520A
#define AT_UART_CMD_ICE_EXTRACY_MOTOR_CW_OFF 0x520B
#define AT_UART_CMD_ICE_EXTRACT_MOTOR_CCW_ON 0x520C
#define AT_UART_CMD_ICE_EXTRACY_MOTOR_CCW_OFF 0x520D

/* 占쏙옙占싱쏙옙 占쏙옙占쏙옙트占쏙옙占쏙옙 占싯삼옙 占쏙옙占쏙옙 250311 CH.PARK */
#define AT_UART_CMD_ICE_SELECT_MOTOR_ON 0x520E
#define AT_UART_CMD_ICE_SELECT_MOTOR_OFF 0x520F

#define AT_UART_CMD_SWING_BAR_ON 0x5210
#define AT_UART_CMD_SWING_BAR_OFF 0x5211

#define AT_UART_CMD_FLOW_MOTOR_OPEN 0x5212
#define AT_UART_CMD_FLOW_MOTOR_CLOSE 0x5213

#define AT_UART_CMD_FLOW_MOTOR_CONTINUE 0x5214
#define AT_UART_CMD_FLOW_MOTOR_INIT 0x5215

/* 占쏙옙占쏙옙 占싻쇽옙占쏙옙占?? 占쏙옙占쏙옙 250311 CH.PARK */
#define AT_UART_CMD_ICE_BREAK_MOTOR_ON 0x5216
#define AT_UART_CMD_ICE_BREAK_MOTOR_OFF 0x5217

#define AT_UART_CMD_DRAIN_MOTOR_OPEN 0x5218
#define AT_UART_CMD_DRAIN_MOTOR_CLOSE 0x5219

#define AT_UART_CMD_DRAIN_PUMP_ON 0x5302
#define AT_UART_CMD_DRAIN_PUMP_OFF 0x5303
#define AT_UART_CMD_TRAY_PUMP_ON 0x5304
#define AT_UART_CMD_TRAY_PUMP_OFF 0x5305

#define AT_UART_CMD_COMP_ON 0x9900
#define AT_UART_CMD_COMP_OFF 0x9901
#define AT_UART_CMD_ICE_SWITCH_ICE 0x9902
#define AT_UART_CMD_ICE_SWITCH_COLD 0x9903
#define AT_UART_CMD_ICE_SWITCH_HOTGAS 0x9904

#define AT_UART_CMD_BLDC_COMP_ERROR 0x9910

#define AT_UART_CMD_SYSTEM_COMPLETE 0xFF00 // (占싯삼옙占쏙옙占쏙옙)占쏙옙품占싹반몌옙占쏙옙 占쏙옙환

#define NON_UART_TEST 0x00
#define NOT_INCLUDE_FRONT_UART_TEST 0x01
#define INCLUDE_FRNOT_UART_TEST 0x02
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//*************\\
 /* mini 占쌩곤옙 */
//*************//

// #define HEATER_POWER_HIGH 3000
// #define HEATER_POWER_LOW 2450

//#define HEATER_POWER_HIGH           3000
#define HEATER_POWER_HIGH           3200//3150// 占쏙옙2025-06-02 Phil  //2025-07-14 cbr_test
//#define HEATER_POWER_LOW            2450
#define HEATER_POWER_LOW            2700//2650// 占쏙옙2025-06-02 Phil  //2025-07-14 cbr_test

// 12占쌤곤옙占?? 占쏙옙占쏙옙占싹면서 占쏙옙占쏙옙 占쏙옙占쏙옙
#define HOT_SET_TEMP_4__MAX__100_oC 0
#define HOT_SET_TEMP_3__COFFEE__85_oC 1
#define HOT_SET_TEMP_2__TEA__70_oC 2
#define HOT_SET_TEMP_1__MILK__43_oC 3

// 占승쇽옙 LPM
#define C_02_LPM    10
#define C_025_LPM   13
#define C_03_LPM    16
#define C_032_LPM   17
#define C_033_LPM   18
#define C_035_LPM   19
#define C_04_LPM    22
#define C_05_LPM    28
#define C_06_LPM    34
#define C_07_LPM    40
#define C_08_LPM    46

#define BUTTON_SET_DISPLAY_OFF                     0
#define BUTTON_SET_COLD_DISPLAY                    1
#define BUTTON_SET_MUTE_DISPLAY                    2
#define BUTTON_SET_ICE_OFF_DISPLAY                 4
#define BUTTON_SET_RECOVER_FAST_ICE_DISPLAY        8

typedef enum {
    FLOW_MODE_NONE,
    FLOW_MODE_INIT,
    FLOW_MODE_DECREASE,
    FLOW_MODE_INCREASE,
} FLOW_VALVE_MODE;

#define Heater_Efficiency       0.95
// #define C_Flow_Min_Q            350 // 占쌍쇽옙 占쏙옙占쏙옙占쏙옙 0.35LPM (占쏙옙占싹울옙占쏙옙 占쏙옙占쏙옙)
#define C_Flow_Min_Q            300 // 占쌍쇽옙 占쏙옙占쏙옙占쏙옙 0.30LPM

// #define HOT_TRIAC_OFF_TEMP                    99
#define HOT_TRIAC_OFF_TEMP 101
#define HOT_TRIAC_OFF_RETURN_TEMP 97

// #define HOT_RELAY_TRIAC_OFF_TEMP              100
#define HOT_RELAY_TRIAC_OFF_TEMP 106
#define HOT_RELAY_TRIAC_OFF_RETURN_TEMP 97

#define C_Heater_Power 2720
#define C_Heater_Max_Power 3650 // max 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 확占쏙옙 242 * 242 / 16.1(占쏙옙占쏙옙 占쏙옙占쏙옙치)
#define C_Heater_Min_Power 1900 // min 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 확占쏙옙 198 * 198 / 19.71(占쏙옙占쏙옙 占쏙옙占쏙옙치)

// #define STEP_TRIAC                    50        // 트占쏙옙占싱억옙 占쏙옙 占쏙옙占쏙옙 占쌤곤옙 (80占쌤곤옙占?? 占쏙옙占쏙옙)
// #define STEP_TRIAC                    86        // 트占쏙옙占싱억옙 占쏙옙 占쏙옙占쏙옙 占쌤곤옙 (80占쌤곤옙占?? 占쏙옙占쏙옙)
// #define STEP_TRIAC                    114        // 트占쏙옙占싱억옙 占쏙옙 占쏙옙占쏙옙 占쌤곤옙 (80占쌤곤옙占?? 占쏙옙占쏙옙)
#define STEP_TRIAC 110 // 트占쏙옙占싱억옙 占쏙옙 占쏙옙占쏙옙 占쌤곤옙 (80占쌤곤옙占?? 占쏙옙占쏙옙)

/* MY 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 */
#define CUP_TYPE_RAMEN 0
#define CUP_TYPE_COFFEE 1
#define CUP_TYPE_TEA 2
#define CUP_TYPE_MY1 3
#define CUP_TYPE_MY2 4
#define CUP_TYPE_MY3 5

#define SERVER_DISCONNECT 0
#define SERVER_CONNECT 1

/* 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙 占쌩곤옙 占쏙옙占쏙옙 횟占쏙옙 占쌩곤옙 : 1회 (250414) */
#define ICE_FULL_ADD_COUNT      1

#define FILTER_RESET_456_DAY    10944

/* Memento Here! */
#define MEMENTO_DISPLAY_OFF_TIME    2
#define MEMENTO_DISPLAY_ON_TIME     52

#define HOT_TEMP_SELECT_DEFAULT_45_70_85_100       0x0921

/* 占쏙옙占쏙옙占싯삼옙 */
#define FCT_FLOW_OKAY_VALUE         (0x32)

/* 占쏙옙 占쏙옙占쏙옙 占쏙옙占?? 占쏙옙占쏙옙 占쏙옙占쏙옙 */
#define DEFAULT_HALF_CUP_AMOUNT  120
#define	DEFAULT_ONE_CUP_AMOUNT   250
#define	DEFAULT_TWO_CUP_AMOUNT   500
#define	DEFAULT_FOUR_CUP_AMOUNT   1000

/* WELCOME LED 占쏙옙占쏙옙 타占싱몌옙 */
#define WELCOME_LED_ON_TIME        600      // 60占쏙옙
#define WELCOME_LED_WIFI_ON_TIME   70       // 7占쏙옙

// 2025-09-04 CH.PARK [V1.0.0.5] 탈占쏙옙 占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙 占쌤계별 占쌨쏙옙 占쏙옙 占쏙옙占쏙옙 (1~8占쌤곤옙 70, 9占쌤곤옙 600占쌨쏙옙)
/* 2025-09-04 CH.PARK [V1.0.0.5] 탈占쏙옙 占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙 占쌤계별 占쌨쏙옙 占쏙옙 占쏙옙占쏙옙 (1占쌤곤옙 210, 占쏙옙占쏙옙占쏙옙 50, 9占쌤곤옙 600占쌨쏙옙) */
#define ICE_TRAY_DOWN_PULSE_STEP_1         210
#define ICE_TRAY_DOWN_PULSE_STEP_2         50
#define ICE_TRAY_DOWN_PULSE_STEP_3         50
#define ICE_TRAY_DOWN_PULSE_STEP_4         50
#define ICE_TRAY_DOWN_PULSE_STEP_5         50
#define ICE_TRAY_DOWN_PULSE_STEP_6         50
#define ICE_TRAY_DOWN_PULSE_STEP_7         50
#define ICE_TRAY_DOWN_PULSE_STEP_8         50
#define ICE_TRAY_DOWN_PULSE_STEP_9         600

/* 2025-09-04 CH.PARK [V1.0.0.5] 탈占쏙옙 占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙 占쌤계별 占쏙옙占쏙옙占쏙옙 占시곤옙 5占십뤄옙 확占쏙옙 (占쏙옙占쏙옙占쏙옙占??)  */
#define ICE_TRAY_DOWN_DELAY_TIME           50 // 18

#define DIMMING_FND_LEFT_NORMAL_STATE               3
#define DIMMING_FND_RIGHT_NORMAL_STATE              3
#define DIMMING_SETTING_MODE_FUNCTION_STATE_EXTRA   2
#define DIMMING_FUNTION_LED_STATE                   4
#define DIMMING_SETTING_LED_STATE                   6
#define DIMMING_EXTRACT_LED_STATE                   5
#define DIMMING_ICE_EXTRACT_OUTER_LED_STATE         4
#define DIMMING_ICE_EXTRACT_INNER_LED_STATE         3
#define DIMMING_BAR_LED_STATE                       4
#define DIMMING_RECEIPE_LED_STATE                   6
#define DIMMING_BIG_STER_LED_STATE                  3
#define DIMMING_SMALL_STER_LED_STATE                3
#define DIMMING_TOP_SMALL_LED_STATE                 4
#define DIMMING_MIDDLE_SMALL_LED_STATE              4
#define DIMMING_SETTING_LED_SIDE_STATE              4
#define DIMMING_RECEIPE_LED_DRIPCOFFEE_STATE        5
#define DIMMING_COLON_SEG_DOT_STATE                 2
#define DIMMING_WELCOME_LEFT_STATE                  4
#define DIMMING_WELCOME_RIGHT_STATE                 8
#define DIMMING_ICE_TYPE_STATE                      7

#define DIMMING_SETTING_MODE_FUNCTION_STATE_MAIN    10

#define PAIRING_DISPLAY_DELAY_TIME_100MS            5

#ifdef __COLD_OPERATION_LPP__
/* LPP 占쏙옙占쏙옙 占쏙옙占쏙옙 */
/* 占시쇽옙占쏙옙占싱븝옙 占쏙옙占쏙옙 (占쌤깍옙쨉占?? 10占쏙옙 占쏙옙占쏙옙) */
#define COLD_ON_TEMP_10DE_UNDER             90      // V10 9占쏙옙
#define COLD_OFF_TEMP_10DE_UNDER            80      // V10 6占쏙옙
#define COLD_DELAY_TIME_10DE_UNDER          0       // V10 0占쏙옙

/* 占시쇽옙占쏙옙占싱븝옙 占쏙옙占쏙옙 (10 ~ 20占쏙옙) */
#define COLD_ON_TEMP_10_20DE                90      // V10 9占쏙옙
#define COLD_OFF_TEMP_10_20DE_FIRST         80      //
#define COLD_OFF_TEMP_10_20DE               80      // V10 8占쏙옙
#define COLD_DELAY_TIME_10_20DE_FIRST       0       // V10 0占쏙옙 (占십깍옙占??)
#define COLD_DELAY_TIME_10_20DE             0       // V10 0占쏙옙

/* 占시쇽옙占쏙옙占싱븝옙 占쏙옙占쏙옙 (20 ~ 30占쏙옙) */
#define COLD_ON_TEMP_20_30DE                90     // V10 9占쏙옙
#define COLD_OFF_TEMP_20_30DE               80     // V10 8占쏙옙
#define COLD_DELAY_TIME_20_30DE_FIRST       0      // V10 0占쏙옙 (占십깍옙占??)
#define COLD_DELAY_TIME_20_30DE             0      // V10 0占쏙옙

/* 占시쇽옙占쏙옙占싱븝옙 占쏙옙占쏙옙 (30占쏙옙 占싱삼옙) */
#define COLD_ON_TEMP_30DE_UPDER             90      // V10 9占쏙옙
#define COLD_OFF_TEMP_30DE_UPDER            80      // V10 8占쏙옙
#define COLD_DELAY_TIME_30DE_UPDER_FIRST    0       // V10 0占쏙옙 (占십깍옙占??)
#define COLD_DELAY_TIME_30DE_UPDER          0       // V10 0占쏙옙

#else

/* 占쏙옙占쏙옙? */
#define COLD_ON_TEMP_10DE_UNDER             75      // V18 7.5占쏙옙
#define COLD_OFF_TEMP_10DE_UNDER            60      // V18 6占쏙옙
#define COLD_DELAY_TIME_10DE_UNDER          0       // V18 0占쏙옙

/* 占시쇽옙占쏙옙占싱븝옙 占쏙옙占쏙옙 (10 ~ 20占쏙옙) */
#define COLD_ON_TEMP_10_20DE                75      // V18 7.5占쏙옙
#define COLD_OFF_TEMP_10_20DE_FIRST         55      // V19 5.5占쏙옙 (占십깍옙占??)
#define COLD_OFF_TEMP_10_20DE               58      // V18 5.8占쏙옙
#define COLD_DELAY_TIME_10_20DE_FIRST       0       // V18 0占쏙옙 (占십깍옙占??)
#define COLD_DELAY_TIME_10_20DE             0       // V18 0占쏙옙

/* 占시쇽옙占쏙옙占싱븝옙 占쏙옙占쏙옙 (20 ~ 30占쏙옙) */
#define COLD_ON_TEMP_20_30DE                75     // V18 7.5占쏙옙
#define COLD_OFF_TEMP_20_30DE               58     // V18 5.8占쏙옙
#define COLD_DELAY_TIME_20_30DE_FIRST       600   // V19 1占쏙옙 (占십깍옙占??)
#define COLD_DELAY_TIME_20_30DE             600   // V19 1占쏙옙

/* 占시쇽옙占쏙옙占싱븝옙 占쏙옙占쏙옙 (30占쏙옙 占싱삼옙) */
#define COLD_ON_TEMP_30DE_UPDER             75      // V18 7.5占쏙옙
#define COLD_OFF_TEMP_30DE_UPDER            58      // V18 5.8占쏙옙
#define COLD_DELAY_TIME_30DE_UPDER_FIRST    1800    // V18 3占쏙옙 (占십깍옙占??)
#define COLD_DELAY_TIME_30DE_UPDER          3000    // V18 5占쏙옙

#endif

#define FEEDER_MOTOR_DELAY_TIME             10      // 1占쏙옙

/* 占시곤옙占싹뤄옙 占쏙옙 표占쏙옙占쏙옙 占쏙옙占쌔온듸옙 5'C !! 250729 CH.PARK */
#define COLD_COMPLETE_DISPLAY_TEMPERATURE   5

/* MY WATER 占식띰옙占쏙옙占?? 占쏙옙占쏙옙 */
typedef struct
{
	U8 use;
	U8 temp;
	U16 amount;
}MY_RECEIPE;

typedef enum
{
	MY_INDEX_RAMEN = 0,
	MY_INDEX_DRIPCOFFEE,
	MY_INDEX_TEA,
	MY_INDEX_MY1,
	MY_INDEX_MY2,
    MY_INDEX_MY3,
	MY_INDEX_MAX
}MY_INDEX;

typedef struct {
    U8 gu8_start;           // 占쏙옙占?? 占쏙옙占쏙옙占??
    U8 gu8_step;            // 占쏙옙占?? 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙
    U16 gu16_timer;         // 占쏙옙占?? 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 타占싱몌옙 (100ms)
} special_func;

typedef struct
{
    U8 U8_iceSelect;        // 占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙
    U8 U8_waterSelect;      // 占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙 占쏙옙占쏙옙
} DISPLAY_STACK;

typedef enum
{
    MODEL_REED_NONE,
    MODEL_REED_USE,

    MODEL_NUM_MAX,
} MODEL_DATA;
typedef enum
{
    REED_NO_DETECTED,
    REED_DETECTED,

    REED_NUM_MAX,
} REED_INFO;

typedef enum
{
    PROCESS_ICE_JAM_INIT,
    PROCESS_ICE_JAM_DOOR_OPEN,
    PROCESS_ICE_JAM_FEEDER_BACK,
    PROCESS_ICE_JAM_FEEDER_CHECK,
    PROCESS_ICE_JAM_DOOR_CLOSE,
    PROCESS_ICE_JAM_DOOR_CLOSE_CHECK,
    PROCESS_ICE_JAM_DONE,                   // 정상적으로 닫혔을 때
    PROCESS_ICE_JAM_ERROR,                  // 닫히지 않았을 때
    PROCESS_ICE_JAM_VOICE_INFO_PLAY,        // 닫히지 않음을 알림
} ICE_JAM_RESV_STEP;

typedef struct _modeling_
{
    MODEL_DATA u8model;             // 모델 (리드 미사용 / 리드 사용)
    U8    u8IsModelChecked;         // 모델 판정여부 (True : 완료, False : 미완료)
    U8    u8ModelCheckTimer;        // 모델 판정시간
} MODEL;

typedef struct _icestuck_
{
    U8  u8IceJamCheck;                      // 얼음걸림 확인 플래그
    U8  u8IceJamProcessTimer;               // 얼음걸림 동작 시간
    U8  u8IceJamProcessCount;               // 얼음걸림 동작 횟수
    ICE_JAM_RESV_STEP  u8IceJamResolveStep; // 얼음걸림 동작 시퀀스
    U8  u8IceJamVoicePlayCount;              // 얼음걸림 해제 안내음성 안내 횟수 (최대 2회)
} ICE_STUCK_1;

typedef struct _ice_door_reed_
{
    U8  u8IceDoorInputTimer;       // 아이스도어 리드 판단완료 시간
    U8  u8IceDoorPreStatus;       // 아이스도어 리드 이전 상태
    U8  u8IceDoorCurStatus;       // 아이스도어 리드 현재 상태
    REED_INFO  u8IceDoorStatus;          // 아이스도어 리드 최종 상태
} ICE_DOOR_REED;

#define ICE_JAM_PROCESS_TIME_MAX                10     // 1초
#define ICE_DOOR_REED_INPUT_TIME_MAX            10     // 1초
#define ICE_JAM_VOICE_INFO_PLAY_COUNT_MAX       2      // 얼음걸림 해제 안내음성 안내 최대 횟수 (최대 2회)

#define ICE_JAM_RESV_COUNT_MAX              1

#define ICE_OUT_1_STEP_TIME      40
#define ICE_OUT_2_STEP_TIME      50
#define ICE_OUT_3_STEP_TIME      60
#define ICE_OUT_4_STEP_TIME      70

#define ACTIVE_LOW_DETECTED       0
#define ACTIVE_LOW_NO_DETECTED    1

#define ACTIVE_HIGH_DETECTED      1
#define ACTIVE_HIGH_NO_DETECTED   0

#define INVALID         0
#define SUSPECT         0.3F
#define VALID           1.0F

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#endif
