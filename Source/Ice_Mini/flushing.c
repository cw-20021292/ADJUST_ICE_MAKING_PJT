/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : AT+CONNECT=74F07DB01010
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "flushing.h"
#include    "work_flow.h"

void flushing_main(void);
void check_flushing_enable(void);
void Flushing_Standby(void);
void Flushing_Filter(void);

void flushing_pairing_start(void);
void control_fill_cold_tank(void);
U8 cold_tank_fill_proc(void);
void Cold_Tank_Flushing(void);
void flushing_finish(void);
void flushing_percent_display(void);

extern void start_hot_water_filling(void);
extern void operation_hot_water_filling(void);
extern void hot_water_filling_control(void);

TYPE_BYTE          U8InstallFlushingEnableB;
#define            u8InstallFlushingEnable                 U8InstallFlushingEnableB.byte
#define            Bit0_First_Turn_On_State                U8InstallFlushingEnableB.Bit.b0
#define            Bit1_Filter_Flushing_Ing_State          U8InstallFlushingEnableB.Bit.b1


TYPE_BYTE          U8FlushingStopB;
#define            u8FlushingStop                          U8FlushingStopB.byte
#define            Bit0_Flushing_Error_Stop_State          U8FlushingStopB.Bit.b0
#define            Bit1_Flushing_Cover_Open_Stop_State     U8FlushingStopB.Bit.b1


extern TYPE_BYTE          U8HotFillingStateB;
#define            u8HotFillingState                              U8HotFillingStateB.byte
#define            Bit0_Hot_Filling_Room_Full_State               U8HotFillingStateB.Bit.b0
#define            Bit1_Hot_Filling_Error_State                   U8HotFillingStateB.Bit.b1
#define            Bit2_Hot_Filling_Water_Out_State               U8HotFillingStateB.Bit.b2
#define            Bit3_Hot_Filling_First_Op_State                U8HotFillingStateB.Bit.b3
#define            Bit4_Hot_Filling_Delay_State                   U8HotFillingStateB.Bit.b4
#define            Bit5_Hot_Filling_Flushing_State                U8HotFillingStateB.Bit.b5
#define            Bit6_Hot_Filling_Filter_Open_State             U8HotFillingStateB.Bit.b6
#define            Bit7_Hot_Filling_Manual_State                  U8HotFillingStateB.Bit.b7

#define COLD_TANK_FILL_CC 		3500 // 1L
#define COLD_FILLING_MAX_TIME 	1800 // 3minute

#define COLD_TANK_FLUSH_CC 		10500 // 2L
#define COLD_FLUSHING_MAX_TIME 	3000 // 5minute

bit bit_install_flushing_state;
U8 gu8_filter_flushing_state;

FLUSHING_STEP gu8_flushing_mode;
FLUSHING_STEP gu8_flushing_mode_saved;

bit bit_flushing_check_finish;
bit bit_flushing_start;
U8 gu8_flushing_step;
U16 gu16_flushing_timer;
U8 gu8_flushing_operation_timer_min;

U8 gu8_display_flushing_reamin_minute;
U8 gu8_display_flushing_elapsed_percent;

U8 gu8_display_flushing_total_percent;

U8 gu8_flushing_okay_key_indicator;
bit bit_flushing_halt;
bit bit_tank_flushing_halt;

bit bit_filter_flushing_no_cancel;


bit bit_flushing_tank_start;
U8 gu8_flushing_tank_step;
U8 gu8_return_flushing_tank_step;


U16 gu16_flushing_tank_timer;
U16 gu16_tank_flushing_max_timer;
U32 gu32_tank_flushing_operation_timer;

bit bit_tank_drain_pump_output;
bit bit_tank_drain_valve_output;
U8 gu8_before_tank_drain_level;
U16 gu16_tank_drain_op_timer;

U8 gu8_tank_drain_no_water_timer;

U16 gu16_tank_drain_finish_timer;

bit bit_ro_drain_finish;


bit bit_install_voice_start;
U8 gu8_install_voice_timer;

U8 gu8_filter_flushing_step;
U16 gu16_filter_flushing_timer;
U16 gu16_filter_flushing_timer_saved;
U16 gu16_filter_flushing_HZ;
bit bit_fill_cold_start;
COLD_TANK_FILL_STEP gu8_cold_tank_fill_step;
U16 gu16_cold_tank_timer;
U16 gu16_cold_tank__max_timer;
U16 gu16_Cold_Tank_Fill_Hz;
U16 gu16_Cold_Tank_Flush_Hz;
bit bit_cold_air_remove_state;
bit bit_first_full_water;

COLDTANK_FLUSHING_STEP gu8_cold_tank_flushing_step;
U16 gu16_cold_tank_flushing_timer;		/* �ü���ũ �÷��� �� �ܰ� Ÿ�̸� */
U16 gu16_cold_tank_flushing_max_timer;	/* �ü���ũ �÷��� �ִ� �ð� Ÿ�̸� */

U16 gu16_flushing_finish_delay_timer;


extern bit F_FW_Version_Display_Mode;
extern bit F_WaterOut;
extern U8 gu8_Flow_1sec;
extern bit F_First_Hot_Effluent;
extern U8 gu8_hot_filling_max_hz;
extern U16 gu16_first_delay_timer;
extern U16 gu16_Filling_Hz;
extern bit F_Hot_Filling_Finish;
extern U16 gu16_hot_filling_control_timer;
extern bit bit_hot_filling_manual;
extern bit bit_hot_filling_start;
extern U8 gu8_Hot_Filling_Step;
extern bit bit_instruction_mode_start;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
typedef enum
{
	FLUSHING_FILTER_OPEN_VALVE,
	FLUSHING_FILTER_CHECK_OUTAGE,
	FLUSHING_FILTER_FILLING,
	FLUSHING_FILTER_DONE
}FLUSHING_FILTER_STATE;

typedef enum
{
	FLUSHING_INSTALL = 0,
	FLUSHING_FILTER_REPLACE,
	FLUSHING_POWER_RESET,
}FLUSHING_MODE;

U8 u8Flushing_Filter_Step;
void flushing_main(void)
{
	if(F_FW_Version_Display_Mode == CLEAR)
    {
        return;
    }
    else{}

	if(gu8_flushing_mode != FLUSHING_NONE_STATE)
	{
		if( //bit_filter_all == CLEAR
		Bit3_Leakage_Sensor_Error__E01 == SET
		|| Bit6_Main_Water_Flow_Block_Error__E09 == SET
		|| Bit16_Drain_Pump_Error__E60 == SET
		|| Bit0_Hot_Water_Flow_Block_Error__E08 == SET )
		{
			gu8_flushing_mode_saved = FLUSHING_NONE_STATE;
			gu8_flushing_mode = FLUSHING_STANDBY_STATE;
			bit_flushing_halt = SET;
			gu8_Hot_Filling_Step = 0;
		}
	}
	else {  }

    switch( gu8_flushing_mode )
    {
        /*..hui [23-6-2���� 11:08:29] �÷��� ���� ���� Ȯ��..*/
        case FLUSHING_NONE_STATE:
            check_flushing_enable();
        break;

		/*..hui [23-6-2���� 11:08:29] �÷��� ���� ���� Ȯ��..*/
		case FLUSHING_STANDBY_STATE:
			Flushing_Standby();
			break;

		case FLUSHING_FILTER:
			Flushing_Filter();
			break;

		case FLUSHING_FILL_COLD_TANK_START_STATE:
			control_fill_cold_tank();
			break;

		case FLUSHING_FILL_COLD_TANK_FINISH_STATE:
		case FLUSHING_COLD_TANK:
			Cold_Tank_Flushing();
			break;

		case FLUSHING_FILL_HOT_TANK_STATE:
		case FLUSHING_SKIP:
			hot_water_filling_control();
			break;

        case FLUSHING_WORK_ICE_MAKE_FLOW_DATA_GET_STATE:
            if(IceMakeFlowDataStack() == SET)
            {
                gu8_flushing_mode = FLUSHING_FINISH_STATE;
            }
            break;

        case FLUSHING_FINISH_STATE:
            /*..hui [23-6-2���� 11:08:42] �÷��� ����..*/
            flushing_finish();
        break;

		default:
		break;
    }

    gu8_flushing_okay_key_indicator = 0;
	flushing_percent_display();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_flushing_enable(void)
{
	//bit_flushing_check_finish = SET; // �ӽ÷� SET�ص�

	if( bit_flushing_check_finish == SET )
	{
		return;
	}
	else{}

	if( bit_install_flushing_state == SET )
	{
		gu8_flushing_mode = FLUSHING_STANDBY_STATE;
		gu8_filter_flushing_state = FILTER_FLUSHING_NONE;

		bit_install_voice_start = SET;
	}
	else if(gu8_filter_flushing_state == SET )
	{
		gu8_flushing_mode = FLUSHING_STANDBY_STATE;
		//gu8_filter_flushing_state = FILTER_FLUSHING_NONE;
		//bit_filter_flushing_start = CLEAR;
		//bit_install_voice_start = SET;
	}
	else if( F_First_Hot_Effluent == SET )
	{
		gu8_flushing_mode = FLUSHING_FILL_COLD_TANK_START_STATE;
		gu16_flushing_finish_delay_timer = 0;
	}

	gu8_display_flushing_total_percent = 0;
	bit_flushing_check_finish = SET;


}


void Flushing_Standby(void)
{
	if(gu8_flushing_okay_key_indicator == SET)
	{
		/* ���͸��彺��ġ, ����Ŀ�� �� �ϳ��� ���������� �÷��� ���� ���� */
		if(bit_filter_cover == CLEAR)
		{
			play_voice_filter_cover_opened_44();
			return;
		}
		else if(bit_filter_reed == CLEAR)
		{
			play_voice_filter_not_detected_14();
			return;
		}
		else {  }

		if( Bit3_Leakage_Sensor_Error__E01 == SET
		|| Bit6_Main_Water_Flow_Block_Error__E09 == SET
		|| Bit16_Drain_Pump_Error__E60 == SET
		|| Bit0_Hot_Water_Flow_Block_Error__E08 == SET )
		{
			play_melody_warning_197();
			return;
		}

		/*..hui [24-1-17���� 4:55:43] yes, no �˾� �� ���¿��� ���� ��ư ���� ���....*/
		/*..hui [24-1-17���� 4:55:52] RO ��ü�ص� ��� �����ϵ��� �ٲ�..*/
		if( bit_yes_no_popup == SET )
		{
			bit_yes_no_popup = CLEAR;
			bit_filter_reset_yes = SET;		// ���͸���!
			bit_filter_reset_no = CLEAR;

			#ifdef __DUMMY_PROGRAM__
			gu8_filter_flushing_state = FILTER_FLUSHING_NONE;
			gu8_flushing_mode = FLUSHING_NONE_STATE;
			#else
			gu8_flushing_mode_saved = FLUSHING_NONE_STATE;
			bit_flushing_halt = CLEAR;
			gu8_filter_flushing_state = SET;
			F_First_Hot_Effluent = SET;
			#endif
		}
		else{}

		if(gu8_flushing_mode_saved > FLUSHING_STANDBY_STATE)
		{
			gu8_flushing_mode = gu8_flushing_mode_saved;
			gu8_flushing_mode_saved = FLUSHING_NONE_STATE;
			bit_flushing_halt = CLEAR;

			if(gu8_flushing_mode < FLUSHING_COLD_TANK)
			{
				bit_fill_cold_start = SET;
			}

			if(gu8_filter_flushing_state == SET)
			{
				gu16_filter_flushing_timer = gu16_filter_flushing_timer_saved;
			}
			play_melody_setting_on_198();
		}
		else
		{
			if( bit_install_flushing_state == SET || gu8_filter_flushing_state == SET )
			{
				gu8_flushing_mode = FLUSHING_FILTER;
				//bit_install_voice_start = SET;
			}
			else if( F_First_Hot_Effluent == SET )
			{
				gu8_flushing_mode = FLUSHING_FILL_COLD_TANK_START_STATE;
			}

			gu16_filter_flushing_timer = 0;
			bit_flushing_halt = CLEAR;
			play_voice_filter_flushing_start_23();
		}

		gu8_flushing_step = 0;
		bit_install_voice_start = CLEAR;

		bit_fill_cold_start = SET;
		flushing_pairing_start();

		gu8_filter_flushing_step = 0;
		gu16_filter_flushing_timer = 0;

		gu8_flushing_step = 0;
		gu16_flushing_timer = 0;

		gu8_cold_tank_fill_step = 0;
		gu16_cold_tank_timer = 0;

		gu8_cold_tank_flushing_step = 0;
		gu16_cold_tank_flushing_timer = 0;
	}
	else
	{
        SetFlowInitStep(FLOW_STACK_STEP_INIT);

		if( bit_install_voice_start == SET )
		{
			gu8_install_voice_timer++;

			if( gu8_install_voice_timer >= 70 )
			{
				// �����ȳ� �ʼ�
				play_voice_install_guide_75();

				gu8_install_voice_timer = 0;
				bit_install_voice_start = CLEAR;
			}
			else{}
		}
		else{}
	}
}

void flushing_pairing_start(void)
{
    U8 mu8_ble_ap_mode = 0;

    /*..hui [21-8-10���� 9:04:14] ���� �÷��� �ʱ�ȭ ��� ��� �߰���..*/
    /*..hui [21-8-10���� 9:04:33] ����ߴٰ� �ٽ� �����ϸ� ���� �������ϱ� Ȯ�� �Ŀ�~~..*/
    mu8_ble_ap_mode  = GetWifiStatusValue( WIFI_STATUS_AP_BLE );


    if( bit_install_flushing_state == SET
        && mu8_ble_ap_mode == CLEAR
        && gu8_wifi_ap_first_temporary == CLEAR )
    {
        WifiKey(WIFI_KEY_BLE);

        /*..hui [24-1-10���� 2:13:36] �ڵ����� �����մϴ� ���� ��� ����..*/
        /*play_voice_pairing_auto_start_76();*/
    }
    else{}
}


void Flushing_Filter(void)
{
	switch(gu8_filter_flushing_step)
	{
		case 0:
			gu16_filter_flushing_timer++;
			if(gu16_filter_flushing_timer > 5) //500ms
			{
				gu16_filter_flushing_HZ = 10500; // 3L

				gu16_filter_flushing_timer = 0;
				gu8_filter_flushing_step++;
			}
			break;

		case 1://hot drain on
			gu16_filter_flushing_timer++;
			if(gu16_filter_flushing_timer > 5) //500ms
			{
				gu16_filter_flushing_timer = 0;
				gu8_filter_flushing_step++;
			}
			break;

		case 2://hot in on
			gu16_filter_flushing_timer++;
			if(gu16_filter_flushing_timer > 1) //100ms
			{
				gu16_filter_flushing_timer = 0;
				gu8_filter_flushing_step++;
			}
			break;

		case 3:
			gu16_filter_flushing_timer ++;
			if(gu16_filter_flushing_HZ == 0)
			{
				gu16_filter_flushing_timer = 0;
				gu8_filter_flushing_step ++;
				return;
			}

			if(gu16_filter_flushing_timer > 3000)//5minute
			{
				gu16_filter_flushing_timer = 0;
				gu8_filter_flushing_step ++;
			}

			break;

		case 4://finish
			gu8_flushing_mode = FLUSHING_FILL_COLD_TANK_START_STATE;// FLUSHING_FILL_HOT_TANK_STATE;
			gu8_filter_flushing_step = 0;
			gu16_filter_flushing_timer = 0;
			gu16_filter_flushing_HZ = 0;
			break;
	}
}

/************************************************************************************************/
/**
 * @brief �ü���ũ ä��� ����
 *
 */
void control_fill_cold_tank(void)
{
    U8 mu8_finish = 0;

    /*..hui [21-6-21���� 8:44:43] �ü���ũ �� ä��� ���� �ɷ������� ���..?..*/
    /*..hui [21-6-28���� 3:28:43] �ü���ũ ä��� �� ���� �߻��� �� �ֱ� ������ ..*/
    /*if( gu8_flushing_mode == FLUSHING_AIR_REMOVE_FINISH_STATE
        || gu8_flushing_mode == FLUSHING_FILL_COLD_TANK_START_STATE )*/

	bit_fill_cold_start = SET;
    if( bit_fill_cold_start == SET )
    {
        mu8_finish = cold_tank_fill_proc();

        if( mu8_finish == SET )
        {
            bit_fill_cold_start = CLEAR;

			if(bit_install_flushing_state == SET)
			{
				gu8_flushing_mode = FLUSHING_COLD_TANK;
			}
			else if(gu8_filter_flushing_state == SET)
			{
				gu8_flushing_mode = FLUSHING_FILL_HOT_TANK_STATE;
			}
			else
			{
				gu8_flushing_mode = FLUSHING_FILL_HOT_TANK_STATE;
			}
        }
        else{}
    }
    else
    {
        gu8_cold_tank_fill_step = 0;
        gu16_cold_tank_timer = 0;
    }
}

U8 cold_tank_fill_proc(void)
{
    U8 mu8_filling_enable_check = 0;
    U8 mu8_return = 0;

    switch( gu8_cold_tank_fill_step )
    {
        case COLD_TANK_FILL_HZ_SET:		// �ü���ũ ä��� ���� ���� Ȯ��

            gu16_cold_tank_timer++;

            if( gu16_cold_tank_timer >= 20 )
            {
                gu16_cold_tank_timer = 0;
                gu16_cold_tank__max_timer = 0;
                gu16_Cold_Tank_Fill_Hz = COLD_TANK_FILL_CC;		// �ü���ũ ä��� �ִ� �뷮 : [1L]
                gu8_cold_tank_fill_step++;
            }
            else
			{

			}
			break;

        case COLD_TANK_FILL_DRAIN:		// �ü���ũ ä��� ���� �����ũ ���� ������ ����
			if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
			{
				gu16_cold_tank_timer = 0;
				gu16_cold_tank__max_timer = 0;
				gu8_cold_tank_fill_step++;
			}
			else
			{
				gu16_cold_tank__max_timer++;
				if( gu16_cold_tank__max_timer >= 9000 ) // ���� 15���ε� Ȯ�� �ʿ���;;
				{
					gu16_cold_tank_timer = 0;
					gu16_cold_tank__max_timer = 0;
					gu8_cold_tank_fill_step++;
				}
				else{}
			}
#if 0
            /*..hui [21-6-21���� 11:01:45] FEED3   ON..*/
            gu16_cold_tank_timer++;
            if( gu16_cold_tank_timer >= 20 )
            {
                gu16_cold_tank_timer = 0;
                gu8_cold_tank_fill_step++;

				if(gu8_filter_flushing_state == SET)
				{
					gu8_display_flushing_total_percent = 30;
				}
				else{}
            }
            else
			{
				if(gu8_filter_flushing_state == SET)
				{
					gu8_display_flushing_total_percent = 20;
				}
				else {  }
			}
#endif
            break;

        case COLD_TANK_FILL_OVERFLOW_OPEN: // �����÷ο� ��� OPEN

            /*..hui [21-7-5���� 5:08:31] 2�� ���..*/
            /*..hui [21-11-10���� 2:40:19] �з�����, ����� ���� ��� ����..FEED4 ON, FEED3 OFF, FEED5 OFF �� 2�� ���..*/
            gu16_cold_tank_timer++;
            if( gu16_cold_tank_timer >= 20 )
            {
                gu16_cold_tank_timer = 0;
                gu8_cold_tank_fill_step++;
            }
            else{}

            break;

        case COLD_TANK_FILL_COLD_OPEN:		// �ü��Լ� ��� OPEN
			/* ����ũ ������ ��ȭ�� ����� (���� �����̶� ����) ��� ���� �������� �̵� */
			if(u8DrainWaterLevel >= DRAIN_LEVEL_LOW)
			{
				gu16_cold_tank__max_timer = 0;
				gu8_cold_tank_fill_step++;
				return;
			}

            /*..hui [21-6-21���� 11:01:45] FEED5 ON..*/
            /*..hui [21-11-10���� 2:40:44] FEED4 OFF, FEED3 ON, FEED5 ON..*/
            if( gu16_Cold_Tank_Fill_Hz <= 0 )
            {
                gu16_cold_tank_timer = 0;
                gu8_cold_tank_fill_step++;
            }
            else
            {
				/* �ü���ũ ä��� �ð� �ִ� [3��] */
                gu16_cold_tank__max_timer++;
                if( gu16_cold_tank__max_timer >= COLD_FILLING_MAX_TIME )
                {
                    gu16_cold_tank__max_timer = 0;
                    gu8_cold_tank_fill_step++;
                }
                else{}
            }

            break;

        case COLD_TANK_FILL_COLD_CLOSE: // �ü� �Լ���� CLOSE
			gu16_cold_tank_timer++;
			if(gu16_cold_tank_timer > 10)
			{
				gu16_cold_tank_timer = 0;
				gu8_cold_tank_fill_step++;
			}

			break;

       case COLD_TANK_FILL_OVERFLOW_CLOSE: // �����÷ο� ��� CLOSE
			gu16_cold_tank_timer++;
			if(gu16_cold_tank_timer > 10)
			{
				gu16_cold_tank_timer = 0;
				gu8_cold_tank_fill_step = 0;

				mu8_return = SET;
			}
            break;


        default:
            gu16_cold_tank_timer = 0;
            gu8_cold_tank_fill_step = 0;
            break;
    }

    return mu8_return;
}


void Cold_Tank_Flushing(void)
{
	switch(gu8_cold_tank_flushing_step)
	{
		case COLDTANK_FLUSHING_NONE:		// �ü���ũ �÷��� ����
			gu8_flushing_mode = FLUSHING_COLD_TANK;
			gu8_cold_tank_flushing_step++;

			break;

		case COLDTANK_FLUSHING_INIT:		// �ü���ũ �÷����� ���� ���� Ȯ��
			gu16_cold_tank_flushing_timer++;
			if(gu16_cold_tank_flushing_timer > 10) //1s init
			{
				gu8_cold_tank_flushing_step++;

				gu16_cold_tank_flushing_timer = 0;

				gu16_Cold_Tank_Flush_Hz = COLD_TANK_FLUSH_CC;		// �÷��� �ִ� ���� : [2L]
			}
			break;

		case COLDTANK_FLUSHING_5MINUTE:		// �ü���ũ �̹��� �о��
			gu16_cold_tank_flushing_timer++;

			if(u8DrainWaterLevel >= DRAIN_LEVEL_HIGH)
			{
				gu8_cold_tank_flushing_step = COLDTANK_FLUSHING_DRAIN_READY;
				return;
			}

			if( gu16_Cold_Tank_Flush_Hz <= 0 )
			{
				gu8_cold_tank_flushing_step = COLDTANK_FLUSHING_FINISH;
				gu16_cold_tank_flushing_timer = 0;
			}
			else {  }

			/* �ü���ũ �÷��� �ִ� �ð� : [5��] */
			gu16_cold_tank_flushing_max_timer++;
			if(gu16_cold_tank_flushing_max_timer >= COLD_FLUSHING_MAX_TIME)
			{
				gu8_cold_tank_flushing_step = COLDTANK_FLUSHING_FINISH;
				gu16_cold_tank_flushing_max_timer = 0;
				gu16_cold_tank_flushing_timer = 0;
			}
			else {  }
		break;

		case COLDTANK_FLUSHING_DRAIN_READY:		// �����ũ ���� ���� �Լ� ���
			gu16_cold_tank_flushing_timer++;
			if(gu16_cold_tank_flushing_timer > 10) //1s ready
			{
				gu8_cold_tank_flushing_step = COLDTANK_FLUSHING_DRAIN;
				gu16_cold_tank_flushing_timer = 0;
			}
			break;

		case COLDTANK_FLUSHING_DRAIN:			// �����ũ ����
			gu16_cold_tank_flushing_timer++;

			if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
			{
				gu8_cold_tank_flushing_step = COLDTANK_FLUSHING_5MINUTE;
				return;
			}

			if(gu16_cold_tank_flushing_timer > 3000 || gu16_Cold_Tank_Flush_Hz<=0) //5m flushing
			{
				gu8_cold_tank_flushing_step = COLDTANK_FLUSHING_FINISH;
				gu16_cold_tank_flushing_timer = 0;
			}
			break;

		case COLDTANK_FLUSHING_FINISH:			// �ü���ũ �÷��� �Ϸ�
			gu16_cold_tank_flushing_timer++;
			if(gu16_cold_tank_flushing_timer > 20) //2s wait
			{
				gu8_flushing_mode = FLUSHING_FILL_HOT_TANK_STATE;
				if(gu8_flushing_mode != FLUSHING_SKIP)
				{
					gu8_display_flushing_total_percent = 70;
				}
				else {  }

				gu8_cold_tank_flushing_step = COLDTANK_FLUSHING_NONE;
				gu16_cold_tank_flushing_timer = 0;
			}
			break;

		default:
			break;

	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


void flushing_finish(void)
{
	gu16_flushing_finish_delay_timer++;
	if(gu16_flushing_finish_delay_timer >= 5)		// 500ms �� finish ó��
	{
		/*..hui [23-12-18���� 7:04:18] �÷��� �� ��뷮 ���..*/
		calc_flushing_water();
		gu8_display_flushing_total_percent = 100;

		if(bit_install_flushing_state == SET )
		{
			play_voice_filter_flushing_finish_24();
		}
		else if(gu8_filter_flushing_state == SET)
		{
			Play_Voice(VOICE_12_FINISH_FILTER_FLUSHING);
		}

		//convert_filter_change_type();

		bit_install_flushing_state = CLEAR;
		gu8_filter_flushing_state = FILTER_FLUSHING_NONE;

		gu8_flushing_mode = FLUSHING_NONE_STATE;
		gu8_flushing_operation_timer_min = 0;

		//init_tank_flushing();

		/*..hui [23-8-16���� 3:35:12] ������ �ٽ� �÷��� �ϰԵɶ� ro �巹�κ��� �ϱ�����..*/
		bit_ro_drain_finish = CLEAR;

		/*..hui [24-1-11���� 10:43:17] ��ġ �÷��� �Ϸ� -> �ٷ� �����÷��� ����.. 100%���� ������..*/
		gu8_display_flushing_total_percent = 0;

		/*..hui [24-1-18���� 9:14:00] ���� ���� ���µ� �ʱ�ȭ..*/
		u8FilterResetState = FILTER_NO_CHANGE;

		/*..hui [24-2-21���� 4:11:06] CT ���� �÷��� ����..*/
		//finish_ct_forced_flushing();

		bit_instruction_mode_start = CLEAR;
	}
	else {  }
}

void flushing_percent_display(void)
{
	if((bit_install_flushing_state == SET)
	&& (gu8_filter_flushing_state == CLEAR)
	)	// ��ġ�÷����� ��!
	{
		if(gu8_flushing_mode == FLUSHING_FILTER)
		{
			if(gu8_filter_flushing_step == 3)
			{
				if(gu16_filter_flushing_timer > 3000)//5minute
				{
					//gu8_display_flushing_total_percent = 30;
				}
				else if(gu16_filter_flushing_timer > 2000)
				{
					gu8_display_flushing_total_percent = 30;
				}
				else if(gu16_filter_flushing_timer > 1000)
				{
					gu8_display_flushing_total_percent = 20;
				}
				else
				{
					gu8_display_flushing_total_percent = 10;
				}
			}
		}
		else if(gu8_flushing_mode == FLUSHING_FILL_COLD_TANK_START_STATE)
		{
			if(gu8_cold_tank_fill_step == COLD_TANK_FILL_DRAIN)
			{
				gu8_display_flushing_total_percent = 40;
			}
			else if(gu8_cold_tank_fill_step == COLD_TANK_FILL_COLD_CLOSE)
			{
				gu8_display_flushing_total_percent = 50;
			}
		}
		else if(gu8_flushing_mode == FLUSHING_COLD_TANK)
		{
			if(gu8_cold_tank_flushing_step == COLDTANK_FLUSHING_5MINUTE)
			{
				if(gu16_cold_tank_flushing_timer > 1800 || gu16_Cold_Tank_Flush_Hz <= (COLD_TANK_FLUSH_CC/2)) //3minute
				{
					gu8_display_flushing_total_percent = 60;
				}
			}
			else if(gu8_cold_tank_flushing_step == COLDTANK_FLUSHING_FINISH)
			{
				gu8_display_flushing_total_percent = 70;
			}
		}
		else if(gu8_flushing_mode == FLUSHING_FILL_HOT_TANK_STATE)
		{
			if(gu8_Hot_Filling_Step == 0)
			{
				gu8_display_flushing_total_percent = 80;
			}
			else if(gu8_Hot_Filling_Step == 5)
			{
				gu8_display_flushing_total_percent = 90;
			}
			else if(gu8_Hot_Filling_Step == 6)
			{
				gu8_display_flushing_total_percent = 100;
			}
		}
	}
	else if((bit_install_flushing_state == CLEAR)
	&& (gu8_filter_flushing_state == SET)
	)	// ���ͱ�ü �÷����� �� !!
	{
		if(gu8_flushing_mode == FLUSHING_FILTER)
		{
			if(gu8_filter_flushing_step == 3)
			{
				if(gu16_filter_flushing_timer > 3000)//5minute
				{
					gu8_display_flushing_total_percent = 70;
				}
				else if(gu16_filter_flushing_timer > 2800)
				{
					gu8_display_flushing_total_percent = 70;
				}
				else if(gu16_filter_flushing_timer > 2400)
				{
					gu8_display_flushing_total_percent = 60;
				}
				else if(gu16_filter_flushing_timer > 2000)
				{
					gu8_display_flushing_total_percent = 60;
				}
				else if(gu16_filter_flushing_timer > 1600)
				{
					gu8_display_flushing_total_percent = 50;
				}
				else if(gu16_filter_flushing_timer > 1200)
				{
					gu8_display_flushing_total_percent = 50;
				}
				else if(gu16_filter_flushing_timer > 800)
				{
					gu8_display_flushing_total_percent = 40;
				}
				else if(gu16_filter_flushing_timer > 400)
				{
					gu8_display_flushing_total_percent = 30;
				}
				else if(gu16_filter_flushing_timer > 200)
				{
					gu8_display_flushing_total_percent = 20;
				}
				else
				{
					gu8_display_flushing_total_percent = 10;
				}
			}
		}
		else if(gu8_flushing_mode == FLUSHING_FILL_COLD_TANK_START_STATE)
		{
			gu8_display_flushing_total_percent = 80;
		}
		else if(gu8_flushing_mode == FLUSHING_FILL_HOT_TANK_STATE)
		{
			gu8_display_flushing_total_percent = 90;
		}
	}
	else
	{
		// ���� �÷����� �� !!
		if(gu8_flushing_mode == FLUSHING_FILL_COLD_TANK_START_STATE)
		{
			if(gu8_cold_tank_fill_step == COLD_TANK_FILL_HZ_SET)
			{
				gu8_display_flushing_total_percent = 10;
			}
			else if(gu8_cold_tank_fill_step == COLD_TANK_FILL_DRAIN)
			{
				gu8_display_flushing_total_percent = 20;
			}
			else if(gu8_cold_tank_fill_step == COLD_TANK_FILL_COLD_OPEN)
			{
				gu8_display_flushing_total_percent = 30;
			}
			else if(gu8_cold_tank_fill_step == COLD_TANK_FILL_COLD_CLOSE)
			{
				gu8_display_flushing_total_percent = 40;
			}
			else if(gu8_cold_tank_fill_step == COLD_TANK_FILL_OVERFLOW_CLOSE)
			{
				gu8_display_flushing_total_percent = 50;
			}
		}
		else if(gu8_flushing_mode == FLUSHING_FILL_HOT_TANK_STATE)
		{
			if(gu8_Hot_Filling_Step == 0)
			{
				gu8_display_flushing_total_percent = 60;
			}
			else if(gu8_Hot_Filling_Step == 2)
			{
				gu8_display_flushing_total_percent = 70;
			}
			else if(gu8_Hot_Filling_Step == 3)
			{
				gu8_display_flushing_total_percent = 80;
			}
			else if(gu8_Hot_Filling_Step == 5)
			{
				gu8_display_flushing_total_percent = 90;
			}
			else if(gu8_Hot_Filling_Step == 6)
			{
				gu8_display_flushing_total_percent = 100;
			}
		}
	}

	if(gu8_flushing_mode == FLUSHING_FINISH_STATE)
	{
		gu8_display_flushing_total_percent = 100;
	}
}

