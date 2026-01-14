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
#include    "work_flow.h"
#include    "hot_water_filling.h"

void hot_water_filling_control(void);
void start_hot_water_filling(void);
void operation_hot_water_filling(void);


/***********************************************************************************************************************/
TYPE_BYTE          U8HotFillingStateB;
#define            u8HotFillingState                              U8HotFillingStateB.byte
#define            Bit0_Hot_Filling_Room_Full_State               U8HotFillingStateB.Bit.b0
#define            Bit1_Hot_Filling_Error_State                   U8HotFillingStateB.Bit.b1
#define            Bit2_Hot_Filling_Water_Out_State               U8HotFillingStateB.Bit.b2
#define            Bit3_Hot_Filling_First_Op_State                U8HotFillingStateB.Bit.b3
#define            Bit4_Hot_Filling_Delay_State                   U8HotFillingStateB.Bit.b4
#define            Bit5_Hot_Filling_Flushing_State                U8HotFillingStateB.Bit.b5
#define            Bit6_Hot_Filling_Filter_Open_State             U8HotFillingStateB.Bit.b6
#define            Bit7_Hot_Filling_Manual_State                  U8HotFillingStateB.Bit.b7

extern TYPE_WORD          U16HotInFeed9ValveONB;
#define            u16HotInFeed9ValveONs                        U16HotInFeed9ValveONB.word
#define            u8HotInFeed9ValveONs_L                       U16HotInFeed9ValveONB.byte[0]
#define            u8HotInFeed9ValveONs_H                       U16HotInFeed9ValveONB.byte[1]
#define            Bit0_HIF9_Water_Filling_State                U16HotInFeed9ValveONB.Bit.b0
#define            Bit1_HIF9_Hot_Out_State                      U16HotInFeed9ValveONB.Bit.b1
#define            Bit2_HIF9_Ice_Tray_Ster_State                U16HotInFeed9ValveONB.Bit.b2
/***********************************************************************************************************************/
bit F_First_Hot_Effluent;
U8 gu8_Hot_Filling_Step;
U16 gu16_hot_filling_max_timer;
U8 gu8_flow_motor_check_step;

bit bit_hot_filling_start;
bit bit_hot_filling_manual;

U16 gu16_hot_filling_control_timer;
bit F_Hot_Filling_Finish;

U16 gu16_Filling_Hz;

bit F_ColdTank_Filling_Finish;

U16 gu16_Flushing_ColdTank_Hz;
U16 gu16_first_delay_timer;


U8 gu8_hot_filling_max_hz;
U8 gu8_hot_filling_restart_timer;

extern U8 gu8_display_flushing_total_percent;
extern U8 gu8_filter_flushing_state;
extern U8 gu8_flushing_operation_timer_min;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_water_filling_control(void)
{
    /*..hui [20-3-6���� 9:42:05] �� ���� �Ϸ�Ǳ� ������ ����..*/
    if( F_FW_Version_Display_Mode == CLEAR )
    {
        return;
    }
    else{}

	//flow �ʿ� �߰� �� ���� ���� ****
	if(1)
	//if( bit_first_full_water == SET )
    {
        Bit0_Hot_Filling_Room_Full_State = SET;
    }
    else
    {
        Bit0_Hot_Filling_Room_Full_State = CLEAR;
    }

    Bit1_Hot_Filling_Error_State = ~Bit1_Hot_Operation_Disable_State;

    Bit2_Hot_Filling_Water_Out_State = SET;

    Bit3_Hot_Filling_First_Op_State = SET;

    gu16_first_delay_timer++;

    if( gu16_first_delay_timer >= HOT_FILLING_START_DELAY_TIME )
    {
        gu16_first_delay_timer = HOT_FILLING_START_DELAY_TIME;
        Bit4_Hot_Filling_Delay_State = SET;
    }
    else
    {
        Bit4_Hot_Filling_Delay_State = CLEAR;
    }

	// flushing ���� �� ���� ����  ****
    if( gu8_flushing_mode == FLUSHING_FILL_HOT_TANK_STATE )
    {
        Bit5_Hot_Filling_Flushing_State = SET;//~bit_install_flushing_state;
    }
    else
    {
        Bit5_Hot_Filling_Flushing_State = CLEAR;
    }

    /*Bit6_Hot_Filling_Filter_Open_State = bit_filter_reed;*/

    if( bit_filter_all == SET )
    {
        gu8_hot_filling_restart_timer++;

        if( gu8_hot_filling_restart_timer >= 10 )
        {
            gu8_hot_filling_restart_timer = 10;
            Bit6_Hot_Filling_Filter_Open_State = SET;
        }
        else{}
    }
    else
    {
        gu8_hot_filling_restart_timer = 0;
        Bit6_Hot_Filling_Filter_Open_State = CLEAR;
    }

    // if((bit_hot_filling_manual == CLEAR)
    // && (bit_self_test_start == CLEAR)
    // )
    // {
    //     Bit7_Hot_Filling_Manual_State = SET;
    // }
    // else
    // {
    //     Bit7_Hot_Filling_Manual_State = CLEAR;
    // }

    if( bit_flushing_halt == CLEAR )
    {
        Bit7_Hot_Filling_Manual_State = SET;
    }
    else
    {
        Bit7_Hot_Filling_Manual_State = CLEAR;
    }

    /***********************************************************************************************************************/
    /*..hui [21-6-28���� 3:56:56] ���� �� SET �� ���..*/
    if( u8HotFillingState == HOT_FILLING_START_STATE )
    {
        start_hot_water_filling();
    }
    else{}

    if( bit_hot_filling_start == SET )
    {
        operation_hot_water_filling();
    }
    else
    {
        gu8_Hot_Filling_Step = 0;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_hot_water_filling(void)
{
    if( Bit1_Hot_Filling_Error_State == SET
    && Bit2_Hot_Filling_Water_Out_State == SET
    && Bit6_Hot_Filling_Filter_Open_State == SET )
    {
        if( bit_hot_filling_start == CLEAR )
        {
            bit_hot_filling_start = SET;
            Bit0_HIF9_Water_Filling_State = SET;
            /*..hui [20-3-6���� 9:22:33] �¼� ����� �򰥸��� �ʰ� �и�..*/
			// flushing ���� �� ���� ����  ****
            // gu16_Filling_Hz = C_CUP_120CC_ROOM; //100cc
            // gu16_Filling_Hz = C_CUP_120CC_ROOM; //100cc
            gu16_Filling_Hz = C_CUP_500CC_ROOM;      //2025-07-10 cbr 1kg �������

            /*Bit1_Prepare_Hot_Water_Popup_State = SET;*/
			// flushing ���� �� ���� ����  ****
            //gu8_flushing_mode = FLUSHING_FILL_HOT_TANK_STATE;

        }
        else{}
    }
    else
    {

    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void operation_hot_water_filling(void)
{
    /*..hui [19-11-7���� 9:21:24] �ʱ� �¼� �巹���߿��� ������ �����Ǹ� ��� ����..*/
    /*..hui [20-3-17���� 11:24:32] �¼� ���� ���� �߻��ÿ��� ���� �߰�..*/
    if( Bit1_Hot_Operation_Disable_State == SET )
        /*|| gu8_Tank_Water_Level == ROOM_LEVEL_ERROR )*/
    {
        bit_hot_filling_start = CLEAR;
        gu8_Hot_Filling_Step = 0;
        gu16_hot_filling_max_timer = 0;

        gu8_flushing_mode_saved = gu8_flushing_mode;
        gu8_flushing_mode = FLUSHING_STANDBY_STATE;
        bit_flushing_halt = SET;

        /*..hui [20-3-17���� 1:40:03] �巹���� �¼� ���� �Ұ� ���� �߻��ÿ��� �����巹������ ��ȯ..*/
        /*..hui [20-3-17���� 1:40:13] ������ �߻��ÿ��� �ٽ� ���������� ä��� �ڵ����� ����..*/
        //if( Bit1_Hot_Operation_Disable_State == SET )
        //{
            bit_hot_filling_manual = SET;
        //}
        //else{}

        return;
    }
    else{}

    /*if( bit_filter_reed == CLEAR )*/
    /*..hui [21-11-10���� 4:34:16] �������ܽ� ���� �߰�..*/
    if( bit_filter_all == CLEAR
    || bit_self_test_start == SET )
    {
        bit_hot_filling_start = CLEAR;
        gu8_Hot_Filling_Step = 0;
        gu16_hot_filling_max_timer = 0;

		gu8_flushing_mode_saved = gu8_flushing_mode;
        gu8_flushing_mode = FLUSHING_STANDBY_STATE;
        bit_flushing_halt = SET;
        return;
    }
    else{}

    if(gu8_Hot_Filling_Step >= 1 && gu8_Hot_Filling_Step <= 6)
    {
        gu16_hot_filling_max_timer++;

        if(gu16_hot_filling_max_timer >= 2400)      // 3�� -> 4�� (�¼� �������)
        {
            gu16_hot_filling_max_timer = 2400;
            bit_hot_filling_start = CLEAR;
            gu8_Hot_Filling_Step = 0;

			gu8_flushing_mode_saved = gu8_flushing_mode;
            gu8_flushing_mode = FLUSHING_STANDBY_STATE;
            bit_flushing_halt = SET;

            /*..hui [20-3-17���� 1:03:04] �ڵ����� �巹���ϴٰ� ���� �ɷ������� ���� ���� ǥ���ϵ���..*/
            bit_hot_filling_manual = SET;
            Bit0_Hot_Water_Flow_Block_Error__E08 = SET;
            return;
        }
        else{}
    }
    else{}


    if( gu8_Hot_Filling_Step >= 4 && gu8_Hot_Filling_Step <= 6 )
    {
        if( gu8_hot_filling_max_hz < gu8_Flow_1sec )
        {
           gu8_hot_filling_max_hz = gu8_Flow_1sec;
        }
        else{}
    }
    else{}

    switch( gu8_Hot_Filling_Step )
    {
        case 0:

            gu8_Hot_Filling_Step++;
            gu16_hot_filling_control_timer = 0;
            gu16_hot_filling_max_timer = 0;
            F_Hot_Filling_Finish = CLEAR;

			// flushing ���� �� ���� ����  ****
            //gu8_flushing_mode = FLUSHING_FILL_HOT_TANK_STATE;

            break;

        case 1:

            gu16_hot_filling_control_timer++;

            /*..hui [21-6-22���� 12:37:28] FEED9 ON..*/
            if(gu16_hot_filling_control_timer >= 3)
            {
                gu8_Hot_Filling_Step++;
                gu16_hot_filling_control_timer = 0;
                gu8_flow_motor_check_step = 0;          /* ����������� ����¡ ���� 250730 CH.PARK */
            }
            else{}

            break;

        case 2:

            gu16_hot_filling_control_timer++;

            /* ��ġ�÷����� ������ 1�� �� ����������� OPEN/CLOSE ����¡ ���� 250730 CH.PARK */
            if(bit_install_flushing_state == SET)
            {
                if(gu16_hot_filling_control_timer >= 600) // 1�� ���� ����������� ����¡
	            {
	                gu8_Hot_Filling_Step++;
	                gu16_hot_filling_control_timer = 0;
	            }
	            else
                {
                    switch(gu8_flow_motor_check_step)
                    {
                        case 0:
                            run_decrease_flow(1800);
                            gu8_flow_motor_check_step++;
                        break;

                        case 1:
                            if(gu8_hot_flow_mode == FLOW_MODE_NONE)
                            {
                                gu8_flow_motor_check_step++;
                            }
                        break;

                        case 2:
                            run_increase_flow(1800);
                            gu8_flow_motor_check_step++;
                        break;

                            case 3:
                            if(gu8_hot_flow_mode == FLOW_MODE_NONE)
                            {
                                gu8_flow_motor_check_step++;
                            }
                        break;

                        case 4:
                            run_decrease_flow(1800);
                            gu8_flow_motor_check_step++;
                        break;

                        case 5:
                            if(gu8_hot_flow_mode == FLOW_MODE_NONE)
                            {
                                gu8_flow_motor_check_step++;
                            }
                        break;

                        case 6:
                            run_increase_flow(1800);
                            gu8_flow_motor_check_step++;
                        break;

                        case 7:
                            if(gu8_hot_flow_mode == FLOW_MODE_NONE)
                            {
                                gu8_flow_motor_check_step++;
                            }
                        break;

                        case 8:
                            run_decrease_flow(1800);
                            gu8_flow_motor_check_step++;
                        break;

                        case 9:
                            if(gu8_hot_flow_mode == FLOW_MODE_NONE)
                            {
                                gu8_flow_motor_check_step++;
                            }
                        break;

                        case 10:
                            run_init_flow();
                            gu8_flow_motor_check_step++;
                        break;

                        case 11:
                            if(gu8_hot_flow_mode == FLOW_MODE_NONE)
                            {
                                gu8_flow_motor_check_step = 0;
                                gu8_Hot_Filling_Step++;
                                gu16_hot_filling_control_timer = 0;
                            }
                        break;
                    }
                }
            }
            else
            {
                /*..hui [21-2-8���� 9:33:33] FEED3 ON..*/
                /*..hui [21-6-22���� 5:01:46] ���� ����ȭ�ɶ����� 1�� ���..*/
                if(gu16_hot_filling_control_timer >= 10)
                {
                    gu8_Hot_Filling_Step++;
                    gu16_hot_filling_control_timer = 0;
                }
                else {  }
            }
            break;

        case 3:

            /*..hui [19-7-22���� 1:54:25] 3�� ��� �� ���� ���� Ȯ��..*/
            /*if(gu8_Flow_1sec > HOT_BLOCKED_FLOW_HZ)*/
            /*..hui [20-2-13���� 1:46:12] ù�� �巹���� ���� Full �����̹Ƿ� 15Hz�� ����..*/
            /*..hui [20-2-13���� 1:46:42] �巹�� �����ִµ� ���������� ������ ������������� �ƴ� ���������� �������..*/
            /*..hui [20-2-13���� 1:50:51] 15Hz �� 0.2���� �̻�..*/
            if(gu8_Flow_1sec > HOT_FIRST_BLOCKED_FLOW_HZ)
            {
                gu16_hot_filling_control_timer++;

                if(gu16_hot_filling_control_timer >= 10)
                {
                    gu8_Hot_Filling_Step++;
                    gu16_hot_filling_control_timer = 0;
                }
                else{}
            }
            else
            {
                gu16_hot_filling_control_timer = 0;
            }

            break;

        case 4:

            /*..hui [20-2-13���� 2:08:23] 250CC�� ���� 125CC ���� ���� ����üũ����..*/
            /*if( gu16Effluent_Hz <= (U16)(C_CUP_250CC_HOT / 2) )*/
			// flushing ���� �� ���� ����  ****

            // if( gu16_Filling_Hz <= (U16)(C_CUP_120CC_ROOM ) )
            if( gu16_Filling_Hz <= (U16)(C_CUP_250CC_ROOM ) )       //2025-07-10 cbr 1kg �������
            {
                gu8_Hot_Filling_Step++;
                gu16_hot_filling_control_timer = 0;
                gu8_hot_setting_temperature = HOT_SET_TEMP____85oC;		// ��2025-06-20 phil    //2025-07-11 cbr
                u8Target_Hz_Hot = 30;									// ��2025-06-20 phil    //2025-07-11 cbr
            }
            else{}

            break;

        case 5:

            gu16_hot_filling_control_timer++;


            /*..hui [19-1-24���� 1:42:56] 1.5�� ���� ���� üũ�Ѵ�..*/
            if(gu16_hot_filling_control_timer >= 15)
            {
                gu16_hot_filling_control_timer = 0;
                gu8_Hot_Filling_Step++;
            }
            else
            {
                /*..hui [19-1-24���� 2:00:47] Ǯ ��� �Ϸ�� �� ���..*/
                if( pHEATER_HOT_H_RELAY == SET
                   && pHEATER_HOT_TRIAC_L == SET
                   && gu8TriacLevelMax == STEP_TRIAC )
                {
                    Cal_HeaterWatt();

                }
                else{}
            }

            break;

        case 6:

            if(F_Hot_Filling_Finish == SET)
            {
                gu8_Hot_Filling_Step = 0;
                gu16_hot_filling_control_timer = 0;
                F_First_Hot_Effluent = CLEAR;
                bit_hot_filling_start = CLEAR;

                gu8_flushing_mode = FLUSHING_FINISH_STATE;

            }
            else{}

            break;

        default :

             gu8_Hot_Filling_Step = 0;
             gu16_hot_filling_control_timer = 0;

             break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


