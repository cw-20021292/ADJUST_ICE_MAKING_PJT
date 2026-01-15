/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "extract_control.h"
#include    "api_debug.h"
/**********************************************************************************************************************/
void water_extract_control(void);
void start_effluent_water(void);
void stop_effluent_water(void);
void ice_extract_control(void);
void start_extract_ice(void);
void stop_effluent_dripcoffee(void);
void dripcoffee_timer(void);
void start_effluent_coffee_drip(void);
/**********************************************************************************************************************/
U8 gu8_effluent_control_timer;
bit F_Effluent_OK;
/**********************************************************************************************************************/
U16 gu16_user_water_out_count;
U16 gu16_feed_timer;
U16 gu16_compensation_time;
/**********************************************************************************************************************/
U16 gu16_ice_water_out_start_timer;
/**********************************************************************************************************************/
WATER_OUT_STEP gu8_Water_Out_Step;
U8 gu8_effluent_timer;
/**********************************************************************************************************************/
U8 gu8_buffer_drain_timer;
U8 gu8_air_vent_timer;
/**********************************************************************************************************************/
ICE_OUT_STEP gu8_Ice_Out_Step;
U16 gu16_ice_out_timer;
U16 gu16_temp_ice_out_timer;
U8 gu8_Drain_water_timer;
U8 gu8TestRemoveAirTimer = 10;      //2025-07-17 cbr �̴ϵ��ϻ��
/**********************************************************************************************************************/
U16 drip_timer;
/**********************************************************************************************************************/
extern bit bit_ice_out_back_state;
extern bit F_IR;
extern bit F_IceOutCCW;
extern U8 gu8IceClose;
/**********************************************************************************************************************/
// [25-02-20 18:09:11] yspark
extern U16 gu16_moving_pulse;
extern U16 gu16_extract_display_hz;
extern U8 gu8_durable_test_start;
extern bit bit_ice_water_extract;
extern U8  gu8_ice_water_ext_start_timer_100ms;
extern bit F_IceFull;
extern bit F_IceLack;
extern bit bit_filter_cover;
extern MY_INDEX my_recipe_select;
extern bit bit_myWater_setting_start;
/***********************************************************************************************************************/
// [25-05-09] ù��/��°�� ���� timer �з�
U16 gu16_firstEffluent_hotwater_timer;
bit F_firstEffluent_hotWater;
/***********************************************************************************************************************/
// [25-07-07] sean ù��/��°�� ���� heating ���� �߰�
bit F_firstEffluent_hotWaterHeat;
U16 gu16_drip_standby_timer;
bit F_first_Drip_standby;
bit F_second_Drip_standby;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_extract_control(void)
{
	if(F_firstEffluent_hotWater == SET)
	{   // [25-05-27 12:57:14] yspark, ù�� ī��Ʈ ����
        if(F_WaterOut == SET && u8WaterOutState == HOT_WATER_SELECT)
        {  // �¼� ���� ���� ��� Ÿ�̸� �ʱ�ȭ
            gu16_firstEffluent_hotwater_timer = 0;
            //2025-07-08 cbr_test
            if((gu8Pre_hot_setting_temperature != gu8_hot_setting_temperature))
            {
                F_firstEffluent_hotWater = CLEAR;
            }
            else{}  //2025-07-08 cbr_test
            if(F_hot_flow_error == SET)
            {
                F_firstEffluent_hotWater = CLEAR;
            }//cbr_test
            else{}
        }
        else
        {
            if(gu16_firstEffluent_hotwater_timer <= 300)
            {
                gu16_firstEffluent_hotwater_timer++;
            }
            else
            {
                gu16_firstEffluent_hotwater_timer = 0;
                F_firstEffluent_hotWater = CLEAR;
				F_firstEffluent_hotWaterHeat = CLEAR;
            }
        }
	}
	else
	{
		gu16_firstEffluent_hotwater_timer = 0;
	}

    if(bit_filter_cover == CLEAR)
    {
        F_WaterOut = CLEAR;
        stop_effluent_water();
        gu8_Preheat_Step = STATE_0_PREHEAT_PREPARE_STATE ;
        return;
    }
    else
    {
        if((bit_myWater_setting_start == SET)
        && (my_recipe_select == MY_INDEX_DRIPCOFFEE)
        )
        {
            if(F_WaterOut == SET)
			{
                dripcoffee_timer();
                start_effluent_coffee_drip();
			}
			else
			{
                stop_effluent_dripcoffee();
                gu8_Preheat_Step = STATE_0_PREHEAT_PREPARE_STATE ;
			}
        }
        else
        {
            if(F_WaterOut == SET)
			{
                start_effluent_water();
			}
			else
			{
			    stop_effluent_water();
			    gu8_Preheat_Step = STATE_0_PREHEAT_PREPARE_STATE ;
			}
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_effluent_water(void)
{
    U8 mu8_finish = 0;
    U8 mu8_time = 0;

    switch( gu8_Water_Out_Step )
    {
        case STATE_0_STANDBY_STATE :
            if( u8WaterOutState == COLD_WATER_SELECT )
            {
                if(bit_cooling_complete_5degree == SET)
	            {
	               bit_cooling_complete_5degree = CLEAR;
	            }
            }

            if(u8IceOutState == ICE_SELECT__ICE_WATER )
            {
                mu8_time = VALVE_ICE_WATER_OUT_TIME;  // 3�� �� ���� ����
            }
            else
            {
                mu8_time = VALVE_CONTROL_TIME_FOR_DEBUG;
            }

            /*..hui [18-8-27���� 6:35:25] ������..*/
            gu8_effluent_timer++;

            if( gu8_effluent_timer >= mu8_time )
            {
                gu8_Water_Out_Step = STATE_10_WATER_IN_FEED_ON_STATE;
                gu8_effluent_timer = 0;
                gu16_ice_water_out_start_timer = 0;
            }
            else{}

            break;

        case STATE_10_WATER_IN_FEED_ON_STATE :

            /*..hui [25-1-9���� 1:43:13] �ü�/���� �Լ� ��� OPEN, �ü� ����ħ ��� CLOSE..*/
            /*..hui [25-1-9���� 1:46:49] �¼��� ���⼭ �����÷ο� NOS ��� CLOSE �س���..*/
            gu8_effluent_timer++;

            if(gu8_effluent_timer >= VALVE_CONTROL_TIME_FOR_DEBUG)
            {
                /* �������� �ݵ�� ����� */
                if(u8IceOutState == ICE_SELECT__ICE_WATER )
                {
                    gu8_Water_Out_Step = STATE_11_COLD_WATER_PRESSURE_PREVENT_STATE;
                    gu8_effluent_timer = 0;
                    return;
                }
                else {  }

                if( u8WaterOutState == HOT_WATER_SELECT )
                {
                    gu8_Water_Out_Step = STATE_20_HOT_PRE_HEATING_STATE;
                    gu8_Drain_water_timer = 0;
                    gu8_effluent_timer = 0;
                }
                else if( u8WaterOutState == COLD_WATER_SELECT )
                {
                    gu8_Water_Out_Step = STATE_11_COLD_WATER_PRESSURE_PREVENT_STATE;
                    gu8_effluent_timer = 0;
                }
                else
                {
                    gu8_Water_Out_Step = STATE_30_EXTRACT_VALVE_ON_STATE;
                    gu8_effluent_timer = 0;
                }
            }
            else{}

            break;

        case STATE_11_COLD_WATER_PRESSURE_PREVENT_STATE:        /* �ü��� ���� */
            gu8_effluent_timer++;
            if(gu8_effluent_timer >= VALVE_PRESSURE_PREVENT_TIME)
            {
                gu8_Water_Out_Step = STATE_30_EXTRACT_VALVE_ON_STATE;
                gu8_effluent_timer = 0;
            }
            else {  }
        break;

        case STATE_20_HOT_PRE_HEATING_STATE :

            //mu8_finish = preheat_water();
			if(gu8_Test_dbg_drain_Mode == CLEAR)
			{
            	mu8_finish = preheat_water();
			}
			else
			{
            	mu8_finish = SET;
			}

			/*.. sean [25-01-16] ���� ��, �¼� Drain���� ������ ����..*/
            if(mu8_finish == SET)
            {
                gu8_Water_Out_Step = STATE_21_HOT_PRE_HEATING_BUFFER_DRAIN_STATE;
                gu8_effluent_timer = 0;
				// gu8_buffer_drain_timer = BUFFER_DRAIN_TIME;
				//gu8_buffer_drain_timer = 5;
            }
            else{}

            break;

        case STATE_21_HOT_PRE_HEATING_BUFFER_DRAIN_STATE :

            gu8_effluent_timer++;

            // [25-05-27 14:40:03] yspark, ù�ܸ� ������ũ ��ä�� ���� ����
            if (F_firstEffluent_hotWater)
            {  // ��° �� �̻�
                if(gu8_effluent_timer >= 0)
                {
                    gu8_Water_Out_Step = STATE_22_HOT_PRE_HEATING_BUFFER_DRAIN_COMPLETE_STATE;
                    gu8_effluent_timer = 0;
                }
                else{}
            }
            else
            {
                // ��2025-06-11 Phil
                if (( ( gu8_hot_setting_temperature == HOT_SET_TEMP____100oC )
                || ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
                || ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )
                //|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____85oC ) )
                || ( gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )			// ��2025-06-11 Phil after PM
                || ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC )			//2025-07-28 cbr
                || ( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC ) )		// ��2025-06-11 Phil after PM
                && (bit_Hot_InLowTemp_SetHighTemp == 1))
                {
                    if(gu8_effluent_timer >= BUFFER_DRAIN_TIME_FOR_HIGH_TEMP)
                    {
                        gu8_Water_Out_Step = STATE_22_HOT_PRE_HEATING_BUFFER_DRAIN_COMPLETE_STATE;
                        gu8_effluent_timer = 0;
                    }
                    else{}
                }
                else
                {
                    if(gu8_effluent_timer >= BUFFER_DRAIN_TIME)
                    {
                        gu8_Water_Out_Step = STATE_22_HOT_PRE_HEATING_BUFFER_DRAIN_COMPLETE_STATE;
                        gu8_effluent_timer = 0;
                    }
                    else{}

                }
            }

#if 0
            if(gu8_effluent_timer >= BUFFER_DRAIN_TIME)
            {
                gu8_Water_Out_Step = STATE_22_HOT_PRE_HEATING_BUFFER_DRAIN_COMPLETE_STATE;
                gu8_effluent_timer = 0;
            }
            else{}
#endif
            break;
        case STATE_22_HOT_PRE_HEATING_BUFFER_DRAIN_COMPLETE_STATE :

            //�߰� process�߰��ϱ� ���� State Add
            // [25-02-20 18:10:54] yspark, ��� ����
            // ���� ������ �̵�
            /*
            if (gu16_moving_pulse == 0)
            {
                gu8_Water_Out_Step = STATE_30_EXTRACT_VALVE_ON_STATE;
            }
			*/
			gu8_Water_Out_Step = STATE_30_EXTRACT_VALVE_ON_STATE;
            break;

        case STATE_23_HOT_PRE_HEATING_PRESS_DOWN_STATE:
            gu8_Water_Out_Step = STATE_30_EXTRACT_VALVE_ON_STATE;
        break;

        case STATE_30_EXTRACT_VALVE_ON_STATE :

            /*..hui [25-1-9���� 1:45:20] ���� ���� ��� ON..*/
            /*..hui [25-1-9���� 1:45:28] �¼��� �¼� ���� ��� ON..*/
            gu8_effluent_timer++;
            if(gu8_effluent_timer >= VALVE_CONTROL_TIME_FOR_DEBUG)
            {
                gu8_Water_Out_Step = STATE_31_WATER_EXTRACT_STATE;
                gu8_effluent_timer = 0;
            }
            else{}

            break;

/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/

        case STATE_31_WATER_EXTRACT_STATE :
			/*.. sean [25-01-16].. 100ml���� ���� �÷ο� ��� 500ms �����༭ Air ������������ �� */
            // yspark [25-02-18 18:54:38] ���� �÷ο� ��� �ð� ����
            /* ���� �������� �� ������ �� */
            if( u8WaterOutState == HOT_WATER_SELECT )
            {
                /* �̴Ͽ� �����ϰ� */
                if((gu16Extracted_Hz / 210) == 1)
                {
                    gu16Extracted_Hz = 0;
                    gu8_air_vent_timer = BUFFER_AIR_VENT_TIME;
                    gu8_Water_Out_Step = STATE_32_WATER_AIR_VENT_STATE;
                }
                else {  }
                // if ( (  gu16Extracted_Hz % 280 == 0 ) && ( gu8_hot_setting_temperature != HOT_SET_TEMP____45oC  ) )
                // {
                //     gu8_air_vent_timer = BUFFER_AIR_VENT_TIME;
                //     gu8_Water_Out_Step = STATE_32_WATER_AIR_VENT_STATE;
                // }
            }
            else {  }

            /*..hui [18-11-14���� 3:33:23] �� ���� ����..*/
            /* ����Ϸ� */
            if(F_Effluent_OK == SET)
            {
				gu8TestRemoveAirTimer = BUFFER_REMOVE_AIR_TIME;          // ���� ���� ���� Overflow Valve �����ð� �Ҵ�
                F_WaterOut = CLEAR;
                /*gu8_Water_Out_Step = STATE_40_EXTRACT_VALVE_OFF_STATE;*/
                gu8_Water_Out_Step = STATE_33_REMOVE_AIR_STATE;
                gu8_effluent_timer = 0;
                play_melody_extract_complete_194();

                u8Extract_Continue = CLEAR;
                bit_tray_in_error_temporary = CLEAR;
                Extract_Stack.U8_waterSelect = CLEAR;
			}
            else{}

            break;

        case STATE_32_WATER_AIR_VENT_STATE :
			gu8_air_vent_timer--;
            /*..hui [18-11-14���� 3:33:23] �� ���� ����..*/
            if(gu8_air_vent_timer == 0)
            {
                gu8_Water_Out_Step = STATE_31_WATER_EXTRACT_STATE;
				gu16Extracted_Hz = 0;
            }
            else{}

            break;
			case STATE_33_REMOVE_AIR_STATE :
            if (gu8TestRemoveAirTimer == 0)
            {
                gu8_Water_Out_Step = STATE_40_EXTRACT_VALVE_OFF_STATE;
            }
            else
            {
                gu8TestRemoveAirTimer--;
            }
            break;
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
        default:

            gu8_Water_Out_Step = STATE_0_STANDBY_STATE;
            gu8_effluent_timer = 0;

            break;
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_effluent_water(void)
{
	//�¼� �� ���� Ȯ���ϱ����ؼ� �߰�
    if( ( u8WaterOutState == HOT_WATER_SELECT)
		&& (gu8_Water_Out_Step >= STATE_30_EXTRACT_VALVE_ON_STATE )
		&& (gu8Pre_hot_setting_temperature == gu8_hot_setting_temperature ) )
    {
		// [25-05-09] ù��/��°�� ���� �ʱ�ȭ
		F_firstEffluent_hotWater = SET;
		if(gu16Effluent_Hz < 10)
		{
			F_firstEffluent_hotWaterHeat = SET;
		}
		else {}
    }
    else {}

    bit_Hot_InLowTemp_SetHighTemp = 0;		// �� 2025-06-11 Phil  // �����ð� ���� �ʱ�

    switch(gu8_Water_Out_Step)
    {
        case STATE_0_STANDBY_STATE :

            //
            gu8_effluent_timer = 0;

            break;

        case STATE_10_WATER_IN_FEED_ON_STATE :
        case STATE_20_HOT_PRE_HEATING_STATE :
        case STATE_30_EXTRACT_VALVE_ON_STATE :
        case STATE_31_WATER_EXTRACT_STATE :

            gu8_effluent_timer++;

            if(gu8_effluent_timer >= VALVE_CONTROL_TIME_FOR_DEBUG)
            {
                gu8_Water_Out_Step = STATE_40_EXTRACT_VALVE_OFF_STATE;
                gu8_effluent_timer = 0;
            }
            else{}

            break;

        case STATE_40_EXTRACT_VALVE_OFF_STATE :

            gu8_effluent_timer++;

            if(gu8_effluent_timer >= VALVE_CONTROL_TIME_FOR_DEBUG)
            {
                gu8_Water_Out_Step = STATE_0_STANDBY_STATE;
                gu8_effluent_timer = 0;
            }
            else{}

            break;

        default :

            gu8_Water_Out_Step = STATE_0_STANDBY_STATE;
            gu8_effluent_timer = 0;

            break;
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_extract_control(void)
{
    if( (F_IceOut == SET)
    // && (gu8_ice_out_continue == CLEAR)
    )
    {
        start_extract_ice();
    }
    else
    {
        // if(F_IceOut == CLEAR)
  		// {
	    	ice_extraction_finish();
  		// }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_extract_ice(void)
{
    U16 ice_extract_timer;
    U16 action_time_unit;
    U16 idle_time_unit;
    U16 cycle_time_unit;
    U16 num_cycles;
    U16 remaining_time_unit;
    U16 total_action_time_unit;

    switch(gu8_Ice_Out_Step)
    {
        case STATE_0_ICE_STANDBY_STATE :
            /*..hui [25-1-10���� 9:56:00] ���̽� ���� ���� �� ������..*/
            /* �Ǵ� ��ȸ�� ��� �Ϸ�Ǹ� �׶����� ����� ���� ���� [V1.0.0.2] 250818 CH.PARK */
            if((F_IceOpen == SET)
            && (gu16_Ice_Door_StepMotor == STEP_ANGLE_DOOR)
            && (bit_ice_out_back_1s_state != SET)
            && (bit_ice_out_back_state != SET)
            && (gu8_ice_feeder_shake != SET)
            && (F_IceSelectClose != SET)
            )
            {
                if(F_IceBreak == CLEAR)
                {
                    F_IceOutCCW = SET;
                    gu16_ice_out_timer = 0;
                    gu16_ice_extract_timer_100ms = 0;
                    gu8_Ice_Out_Step = STATE_10_ICE_EXTRACT_STATE;

                    // CLI 디버깅 출력
                    dlog(SYSMOD, INFO, ("CLI - IceExtractStart \r\n"));

                }
                else
                {
                    /* ���������� ��ġ������ ���� ������ ������
                    ���� �����ϵ��� ���� 250825 CH.PARK */
                    if(gu16_IceSelect_StepMotor <= 150)
                    {
                        F_IceOutCCW = SET;
                        gu16_ice_out_timer = 0;
                        gu16_ice_extract_timer_100ms = 0;
                        gu8_Ice_Out_Step = STATE_10_ICE_EXTRACT_STATE;
                    }
                    else {  }
                }

                /* 250929 CH.PARK ��ȸ�� �� �ϰ� ���� �� ������ 1�� �� ���� ���� ����  */
                gu8IceOutCCWInterval = FEEDER_MOTOR_DELAY_TIME;

                if(u8IceOutState == ICE_SELECT__ICE_WATER)
                {
                    F_WaterOut = SET;
                    F_Effluent_OK = CLEAR;
                    effluent_hz_decision();
                }
                else {  }
            }
            else {  }
            break;

        case STATE_10_ICE_EXTRACT_STATE :
            if( F_IceBreak == CLEAR )
            {
                /* �Ϲݾ��� */
                F_IceBreak_Motor_Out = CLEAR;

                /* 2025-09-18 @CH.PARK �ܰ躰 ���� ���� �ð���
                ���� �Ǵ� ��ȸ�� �ð����� �Ǵ��ϵ��� ���� (����ð� ���� ����) */
                if(gu8_ice_out_continue == SET)
                {
                    // (�Ϲݾ���) 3��ON/1��OFF �� �� ���� ���� �ð��� 90��
                    ice_extract_timer = 900;
                }
                else
                {
                    if(gu8_ice_amount_step == ICE_LEVEL_1_STEP)
                    {
                        ice_extract_timer = ICE_OUT_1_STEP_TIME;
                    }
                    else if(gu8_ice_amount_step == ICE_LEVEL_2_STEP)
                    {
                        ice_extract_timer = ICE_OUT_2_STEP_TIME;
                    }
                    else if(gu8_ice_amount_step == ICE_LEVEL_3_STEP)
                    {
                        ice_extract_timer = ICE_OUT_3_STEP_TIME;
                    }
                    else if(gu8_ice_amount_step == ICE_LEVEL_4_STEP)
                    {
                        ice_extract_timer = ICE_OUT_4_STEP_TIME;
                    }
                    else
                    {
                        ice_extract_timer = 30;
                    }
                }
            }
            else
            {
                /* �������� */
                F_IceBreak_Motor_Out = SET;

                /* ���� ������ ���� ���� �ð� �ο� 250317 CH.PARK */
                if(gu8_ice_amount_step == ICE_LEVEL_1_STEP)
                {
                    ice_extract_timer = 250;    /* 25�� */
                }
                else if(gu8_ice_amount_step == ICE_LEVEL_2_STEP)
                {
                    ice_extract_timer = 390;        /* 39�� */
                }
                else if(gu8_ice_amount_step == ICE_LEVEL_3_STEP)
                {
                    ice_extract_timer = 530;        /* 53�� */
                }
                else if(gu8_ice_amount_step == ICE_LEVEL_4_STEP)
                {
                    ice_extract_timer = 760;        /* ��ä��� 4��37�� ���ϻ� ��纯�� ��û���� ���� : [76��] 250730 CH.PARK */
                }
                else
                {
                    ice_extract_timer = 250;
                }

                action_time_unit = 20;  // �������� �� �Ǵ� ���� �ð�: 20 * 100ms = 2��
                idle_time_unit = 10;    // �������� �� �Ǵ� ���� �ð�: 10 * 100ms = 1��

                // ���� ����
                cycle_time_unit = (action_time_unit + idle_time_unit);       // 1����Ŭ 3��
                num_cycles = (ice_extract_timer / cycle_time_unit);          // ��ü ����Ŭ Ƚ��
                remaining_time_unit = (ice_extract_timer % cycle_time_unit); // ����Ŭ�� ���۽ð� ������

                /* 2025-09-18 CH.PARK �Ǵ� ���۽ð� ���� ���� �������� ����ð� ���� (���� ����ð��� 25�� ����) */
                if(gu8_ice_out_continue == SET)
                {
                    // (��������) 2��ON/1��OFF �� �� ���� ���� �ð��� 80��
                    ice_extract_timer = 800;
                }
                else
                {
                    ice_extract_timer = (num_cycles * action_time_unit) + (remaining_time_unit > action_time_unit ? action_time_unit : remaining_time_unit);
                }
            }

            /* 2025-09-18 CH.PARK �Ǵ� ���۽ð� ���� ���� �������� ����ð� ���� (���� ����ð��� 25�� ����) */
            gu16_ice_out_timer = gu16_ice_extract_timer_100ms;
            if( gu16_ice_out_timer >= ice_extract_timer )
            {
                gu8_Ice_Out_Step = STATE_50_ICEWATER_EXTRACT_FINISH_STATE;
                gu16_ice_out_timer = 0;
            }
            else{}
            break;

        /* �������� �Ϸ� �� 1�� �� ������ �� ���� ����� */
        case STATE_11_ICE_DELAY_1S_STATE :
            gu16_ice_out_timer++;
            if( gu16_ice_out_timer >= 10 )
            {
                gu16_ice_out_timer = 0;
                gu8_Ice_Out_Step = STATE_20_ICEWATER_COLD_FFED_ON_STATE;
                /*..hui [25-1-10���� 1:42:45] ���� ���� Ȯ��..*/
                cold_effluent_hz();
            }
            else{}

            break;


        case STATE_20_ICEWATER_COLD_FFED_ON_STATE :
            gu16_ice_out_timer++;

            /* ���⼭ �ü� ������ ON */
            if( gu16_ice_out_timer >= 10 ) // VALVE_CONTROL_TIME_FOR_DEBUG
            {
                gu16_ice_out_timer = 0;
                gu8_Ice_Out_Step = STATE_30_ICEWATER_EXTRACT_VALVE_ON_STATE;
            }
            else{}
            break;

        /* �������� ���� �ü� ���� ���� */
        case STATE_30_ICEWATER_EXTRACT_VALVE_ON_STATE :
            gu16_ice_out_timer++;

            /* ���⼭ �ü� �Լ���� ON */
            /* ���� mini,1kg�� �ٸ��� 2kg�� �ü����� ������ ������ ON���� ���� */
            if( gu16_ice_out_timer >= 10 )
            {
                gu16_ice_out_timer = 0;
                gu8_Ice_Out_Step = STATE_31_ICEWATER_EXTRACT_STATE;
            }
            else{}

            break;

/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
        case STATE_31_ICEWATER_EXTRACT_STATE :
            /* ����Ϸ�!! */
            if( F_Effluent_OK == SET )
            {
                gu16_ice_out_timer = 0;
                gu8_Ice_Out_Step = STATE_40_ICEWATER_EXTRACT_VALVE_OFF_STATE;

                gu8_clock_hide_state = SET;
                gu8_clock_hide_timer = 0;
                F_Effluent_OK = CLEAR;
                Extract_Stack.U8_waterSelect = CLEAR;
            }
            else{}
            break;
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
        case STATE_40_ICEWATER_EXTRACT_VALVE_OFF_STATE :
            gu16_ice_out_timer++;

            if( gu16_ice_out_timer >= 10 )
            {
                gu16_ice_out_timer = 0;
                gu8_Ice_Out_Step = STATE_41_ICEWATER_COLD_FEED_OFF_STATE;
            }
            else{}

            break;

        case STATE_41_ICEWATER_COLD_FEED_OFF_STATE :
            gu16_ice_out_timer++;

            /*..���⼭ �ü� �Լ� ��� CLOSE.. (����) */
            if( gu16_ice_out_timer >= 10 )
            {
                gu16_ice_out_timer = 0;
                gu8_Ice_Out_Step = STATE_50_ICEWATER_EXTRACT_FINISH_STATE;
            }
            else{}

            break;

        case STATE_50_ICEWATER_EXTRACT_FINISH_STATE :
            /* ���⼭ ������ �ü� ���� ��� CLOSE */
            ice_extraction_finish();
            gu8_Ice_Out_Step = 0;
            gu16_ice_out_timer = 0;

            break;



        default :

            gu8_Ice_Out_Step = 0;
            gu16_ice_out_timer = 0;

            break;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void continued_extract_control(void)
{
    if( F_WaterOut == SET && u8Extract_Continue == SET )
    {
        gu16Water_Extract_Timer++;

        if(gu16Water_Extract_Timer >= u16Efluent_Time)
        {
            F_WaterOut = CLEAR;
            gu16Water_Extract_Timer = 0;
            u16Efluent_Time = 0;

            /*..hui [18-1-11i?��i?? 11:12:11] i?��i�Ӎi�ҡ�i�ҩ� i??i�ע�..*/
            u8Extract_Continue = CLEAR;

            /*..hui [18-3-14i?��i?? 3:50:40] i??e?��i�ҡ�i�ҩ� i�ˡ�e�̨�..*/
            F_WaterOut_Disable_State = SET;
            gu16_extract_display_hz = 0;
            play_melody_extract_complete_194();
            gu8_clock_hide_state = SET;
            gu8_clock_hide_timer = 0;
        }
        else{}
    }
    else
    {
        gu16Water_Extract_Timer = 0;
    }
}

void start_effluent_coffee_drip(void)
{
    U8 mu8_finish = 0;
    U8 mu8_time = 0;

	// [25-06-04] MY������ �������� �ÿ�, ���� ���� ���� �� �ֵ��� ����
	if(bit_myWater_setting_start == SET)
	{
		gu16_water_select_return_time = 0;
	}
	else {}

    switch( gu8_Water_Out_Step )
    {
        case STATE_0_STANDBY_STATE :

            /*..hui [18-8-27���� 6:35:25] ������..*/
            gu8_effluent_timer++;

            if( gu8_effluent_timer >= VALVE_CONTROL_TIME_FOR_DEBUG )
            {
                gu8_Water_Out_Step = STATE_10_WATER_IN_FEED_ON_STATE;
                gu8_effluent_timer = 0;
            }
            else{}

            break;

        case STATE_10_WATER_IN_FEED_ON_STATE :

            /*..hui [25-1-9���� 1:43:13] �ü�/���� �Լ� ��� OPEN, �ü� ����ħ ��� CLOSE..*/
            /*..hui [25-1-9���� 1:46:49] �¼��� ���⼭ �����÷ο� NOS ��� CLOSE �س���..*/
            gu8_effluent_timer++;

            if(gu8_effluent_timer >= VALVE_CONTROL_TIME_FOR_DEBUG)
            {
                if( u8WaterOutState == HOT_WATER_SELECT )
                {
                    /*gu8_Water_Out_Step = STATE_11_DRAIN_REMAIN_WATER_STATE;*/
                    gu8_Water_Out_Step = STATE_20_HOT_PRE_HEATING_STATE;
                    gu8_Drain_water_timer = 0;
                    gu8_effluent_timer = 0;
                }
                else
                {
                    gu8_Water_Out_Step = STATE_30_EXTRACT_VALVE_ON_STATE;
                    gu8_effluent_timer = 0;
                }
            }
            else{}

            break;

        case STATE_20_HOT_PRE_HEATING_STATE :

            mu8_finish = preheat_water();
#if 0
			if(gu8_Test_dbg_drain_Mode == CLEAR)
			{
            	mu8_finish = preheat_water();
			}
			else
			{
            	mu8_finish = SET;
			}
#endif
            /*.. sean [25-01-16] ���� ��, �¼� Drain���� ������ ����..*/
            if(mu8_finish == SET)
            {
				if(drip_timer < 120)
					drip_timer = 120;
				else{}

                //gu8_Water_Out_Step = STATE_30_EXTRACT_VALVE_ON_STATE;
                gu8_Water_Out_Step = STATE_21_HOT_PRE_HEATING_BUFFER_DRAIN_STATE;
                gu8_effluent_timer = 0;
                //gu8_buffer_drain_timer = BUFFER_DRAIN_TIME;
                //gu8_buffer_drain_timer = 5;
            }
            else{}

            break;

        case STATE_21_HOT_PRE_HEATING_BUFFER_DRAIN_STATE :

            gu8_effluent_timer++;

            // [25-05-27 14:40:03] yspark, ù�ܸ� ������ũ ��ä�� ���� ����
            if (F_firstEffluent_hotWater)
            {  // ��° �� �̻�
                if(gu8_effluent_timer >= 0)
                {
                    gu8_Water_Out_Step = STATE_22_HOT_PRE_HEATING_BUFFER_DRAIN_COMPLETE_STATE;
                    gu8_effluent_timer = 0;
                }
                else{}
            }
            else
            {  // ù��
            	 if(u8Target_Hz_Hot > gu8_hot_filling_max_hz) {gu8_effluent_timer = 30;}

            	  // ��2025-06-11 Phil
            	  	if (( ( gu8_hot_setting_temperature == HOT_SET_TEMP____100oC )
								|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
								|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )
								|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____85oC ) )
								&& (bit_Hot_InLowTemp_SetHighTemp == 1))
								{
                    if(gu8_effluent_timer >= BUFFER_DRAIN_TIME_FOR_HIGH_TEMP)
                    {
                        gu8_Water_Out_Step = STATE_22_HOT_PRE_HEATING_BUFFER_DRAIN_COMPLETE_STATE;
                        gu8_effluent_timer = 0;
                    }
                    else{}
                }
                else
                {
                    if(gu8_effluent_timer >= BUFFER_DRAIN_TIME)
                    {
                        gu8_Water_Out_Step = STATE_22_HOT_PRE_HEATING_BUFFER_DRAIN_COMPLETE_STATE;
                        gu8_effluent_timer = 0;
                    }
                    else{}

                }
            }

            break;

        case STATE_22_HOT_PRE_HEATING_BUFFER_DRAIN_COMPLETE_STATE :

			gu8_Water_Out_Step = STATE_30_EXTRACT_VALVE_ON_STATE;
            break;

        case STATE_30_EXTRACT_VALVE_ON_STATE :

            /*..hui [25-1-9���� 1:45:20] ���� ���� ��� ON..*/
            /*..hui [25-1-9���� 1:45:28] �¼��� �¼� ���� ��� ON..*/
            gu8_effluent_timer++;

            if(gu8_effluent_timer >= VALVE_CONTROL_TIME_FOR_DEBUG)
            {
                gu8_Water_Out_Step = STATE_31_WATER_EXTRACT_STATE;
                gu8_effluent_timer = 0;
            }
            else{}

            break;

/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
        case STATE_31_WATER_EXTRACT_STATE :
            /*..hui [18-11-14���� 3:33:23] �� ���� ����..*/
            if(F_Effluent_OK == SET)
            {
                F_WaterOut = CLEAR;
                gu8_Water_Out_Step = STATE_40_EXTRACT_VALVE_OFF_STATE;
                //gu8_Water_Out_Step = STATE_33_REMOVE_AIR_STATE;
                gu8_effluent_timer = 0;
                play_melody_extract_complete_194();

                u8Extract_Continue = CLEAR;

				F_first_Drip_standby = CLEAR;
				F_second_Drip_standby = CLEAR;
                Extract_Stack.U8_waterSelect = CLEAR;
            }
            else{}

			if( ( gu16Extracted_Hz / 170 == 1 ) && (F_first_Drip_standby == CLEAR ) )
			{
                gu8_Water_Out_Step = STATE_50_FIRST_STANDBY_STATE;
				F_first_Drip_standby = SET;
				//sync ���߱� ���ؼ� timer ���� 20%
				if(drip_timer < 240)
					drip_timer = 240;
				else{}
				gu16_drip_standby_timer = 400;
			}
			else if( ( gu16Extracted_Hz / 340 == 1 ) && (F_second_Drip_standby == CLEAR ))
			{
                gu8_Water_Out_Step = STATE_51_SECOND_STANDBY_STATE;
				F_second_Drip_standby = SET;
				//sync ���߱� ���ؼ� timer ���� 60%
					if(drip_timer < 720)
						drip_timer = 720;
					else {}
				gu16_drip_standby_timer = 400;
			}
			else {}

            break;

        case STATE_32_WATER_AIR_VENT_STATE :
            gu8_air_vent_timer--;
            /*..hui [18-11-14���� 3:33:23] �� ���� ����..*/
            if(gu8_air_vent_timer == 0)
            {
                gu8_Water_Out_Step = STATE_31_WATER_EXTRACT_STATE;
                gu16Extracted_Hz = 0;
            }
            else{}

            break;

        case STATE_33_REMOVE_AIR_STATE :
            if (gu8TestRemoveAirTimer == 0)
            {
                gu8_Water_Out_Step = STATE_40_EXTRACT_VALVE_OFF_STATE;
            }
            else
            {
                gu8TestRemoveAirTimer--;
            }
            break;

        case STATE_50_FIRST_STANDBY_STATE :
            /*..hui [18-11-14���� 3:33:23] �� ���� ����..*/
            if( gu16_drip_standby_timer > 0 )
            {
            	gu16_drip_standby_timer--;
            }
			else
            {
            	gu8_Water_Out_Step = STATE_10_WATER_IN_FEED_ON_STATE;
            }

            break;


        case STATE_51_SECOND_STANDBY_STATE :
            /*..hui [18-11-14���� 3:33:23] �� ���� ����..*/
            if( gu16_drip_standby_timer > 0 )
            {
            	gu16_drip_standby_timer--;
#if 0
				if( (F_first_Drip_standby  == SET) && (F_second_Drip_standby  == SET))
				{
					//sync ���߱� ���ؼ� timer ���� 90%
					if(drip_timer < 1080)
						drip_timer = 1080;
					else {}
				}
#endif
            }
			else
            {
				if( (F_first_Drip_standby  == SET) && (F_second_Drip_standby  == SET))
				{
					//sync ���߱� ���ؼ� timer ���� 90%
					if(drip_timer < 1080)
						drip_timer = 1080;
					else {}
				}
            	gu8_Water_Out_Step = STATE_10_WATER_IN_FEED_ON_STATE;
            }

            break;

        default:

            gu8_Water_Out_Step = STATE_0_STANDBY_STATE;
            gu8_effluent_timer = 0;

            break;
    }
}

void stop_effluent_dripcoffee(void)
{
	if( ( u8WaterOutState == HOT_WATER_SELECT)
	&& (gu8_Water_Out_Step >= STATE_20_HOT_PRE_HEATING_STATE )
    && (gu8Pre_hot_setting_temperature == gu8_hot_setting_temperature)
    )
	{
		F_firstEffluent_hotWater = SET;
	}
	else {}

    /*..sean [25-06-12] �ʱ�ȭ �ؾ��� ��쿡�� �帳Ŀ�ǵ� ������ �ʱ�ȭ..*/
	F_first_Drip_standby = CLEAR;
	F_second_Drip_standby = CLEAR;
	drip_timer = 0;

	switch(gu8_Water_Out_Step)
	{
			case STATE_0_STANDBY_STATE :
					gu8_effluent_timer = 0;
					break;

			case STATE_10_WATER_IN_FEED_ON_STATE :
			case STATE_20_HOT_PRE_HEATING_STATE :
			case STATE_30_EXTRACT_VALVE_ON_STATE :
			case STATE_31_WATER_EXTRACT_STATE :

					gu16_firstEffluent_hotwater_timer = 0;
					gu8_effluent_timer++;

					if(gu8_effluent_timer >= VALVE_CONTROL_TIME_FOR_DEBUG)
					{
                        gu8_Water_Out_Step = STATE_40_EXTRACT_VALVE_OFF_STATE;
                        gu8_effluent_timer = 0;
					}
					else{}
					break;

			case STATE_40_EXTRACT_VALVE_OFF_STATE :
					gu8_effluent_timer++;

					if(gu8_effluent_timer >= VALVE_CONTROL_TIME_FOR_DEBUG)
					{
                        gu8_Water_Out_Step = STATE_0_STANDBY_STATE;
                        gu8_effluent_timer = 0;
					}
					else{}

                    /* sean [25-06-06] ��ư�� �̿��� ���ᵵ ���°����� */
                    F_WaterOut_Disable_State = SET;
                    /*..sean [25-06-10] drip timer�� �ʱ�ȭ ..*/
                    drip_timer = 0;
                    gu8_dripcoffee_percent = 0;
					break;

			default :
					gu8_Water_Out_Step = STATE_0_STANDBY_STATE;
					gu8_effluent_timer = 0;
					break;
	}

}

void dripcoffee_timer(void)
{
	if(F_WaterOut == CLEAR)
	{
		drip_timer = 0;
		gu8_dripcoffee_percent = 0;
	}
	else
	{
		drip_timer++;

		if( (gu16_drip_standby_timer == 0) && (F_first_Drip_standby  == SET) && (F_second_Drip_standby  == SET) )
		{
			if(drip_timer % 4 == 0)
			drip_timer++;
			else {}
		}
		else {}

		gu8_dripcoffee_percent = (U8)(drip_timer/12);
	}

}

void cup_select_init(void)
{
	gu8_cup_led_select = SET;
    gu8_cup_led_off_time = 0;
}
