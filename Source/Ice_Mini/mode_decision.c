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
#include    "mode_decision.h"
#include    "Packet_Match.h"

void Make_Mode_Decision(void);
void cold_mode_decision(void);
void ice_mode_decision(void);
U8 cold_mode_comp_control(void);
void final_mode_decision(void);
U8 cold_comp_test(void);
void cold_priority_decision(void);
void ice_priority_decision(void);
//void check_dual_mode(void);
void count_ice_make(void);




TYPE_WORD          U16ColdOperationW;
#define            u16ColdOperation                            U16ColdOperationW.word
#define            u8ColdOperation_L                           U16ColdOperationW.byte[0]
#define            u8ColdOperation_H                           U16ColdOperationW.byte[1]
#define            Bit0_Cold_Setting                           U16ColdOperationW.Bit.b0         /* (�ð�) �ü� ON/OFF �������� */
#define            Bit1_Cold_Temp_Protect                      U16ColdOperationW.Bit.b1         /* (�ð�) �ð� �� ��ȣ ���� */
#define            Bit2_Cold_Temp_Control                      U16ColdOperationW.Bit.b2         /* (�ð�) �ü� �µ����� */
#define            Bit3_Ice_Init_Cold_Stop                     U16ColdOperationW.Bit.b3         /* (�ð�) ���� ���� �ʱ�ȭ ���� */
#define            Bit4_Cold_Error                             U16ColdOperationW.Bit.b4         /* (�ð�) �ð� ���� ���� ���� */
#define            Bit5_Cold_Flushing_Stop                     U16ColdOperationW.Bit.b5         /* (�ð�) �÷����߿� �ð� ���� */
#define            Bit6_Cold_Ice_Ster_Stop                     U16ColdOperationW.Bit.b6         /* (�ð�) ����Ʈ���� ���»���� �ð� ���� */
#define            Bit7_Cody_Service_Cold_Off                  U16ColdOperationW.Bit.b7         /* (�ð�) �ڵ� �����߿��� �ð� ���� */


TYPE_WORD          U16IceOperationW;
#define            u16IceOperation                            U16IceOperationW.word
#define            u8IceOperation_L                           U16IceOperationW.byte[0]
#define            u8IceOperation_H                           U16IceOperationW.byte[1]
#define            Bit0_Ice_Setting                           U16IceOperationW.Bit.b0           /* (����) ���� ON/OFF �������� */
#define            Bit1_Ice_Temp_Protect                      U16IceOperationW.Bit.b1           /* (����) Ʈ���� �Լ� ���󿩺� */
#define            Bit2_Ice_Full                              U16IceOperationW.Bit.b2           /* (����) ������ũ �������� (�����̸� CLEAR) */
#define            Bit3_Ice_Stop_Six_Hour                     U16IceOperationW.Bit.b3           /* (����) ������� ��뿩�� : ��� ���� */
#define            Bit4_Ice_Init_Ice_Stop                     U16IceOperationW.Bit.b4           /* (����) ���� ���� �ʱ�ȭ ���� */
#define            Bit5_Ice_Stop_Safty_Routine                U16IceOperationW.Bit.b5           /* (����) ���� ���� ���� : ����Ʈ���� �ɸ� */
#define            Bit6_Ice_Error                             U16IceOperationW.Bit.b6           /* (����) �������� ���� �߻����� */
#define            Bit7_Cody_Service_Ice_Off                  U16IceOperationW.Bit.b7           /* (����) �ڵ� ���� ���� - ��ũĿ�� ���� */
#define            Bit8_Ice_Stop_Flushing                     U16IceOperationW.Bit.b8           /* (����) �÷����߿��� ���� ���� */
#define            Bit9_Ice_Stop_Ice_Ster                     U16IceOperationW.Bit.b9           /* (����) ����Ʈ���� ���»���� ���� ���� */
#define            Bit10_Fast_Ice_Make_Limit                  U16IceOperationW.Bit.b10          /* (����) �������� ����Ƚ�� ī���� ���� */


TYPE_BYTE          U8ColdTempControlB;
#define            gu8_Cold_Temp_Control                     U8ColdTempControlB.byte
#define            Bit0_Temp_Control                         U8ColdTempControlB.Bit.b0
#define            Bit1_Temp_Add_Control                     U8ColdTempControlB.Bit.b1



TYPE_BYTE          U8MakeModeB;
#define            gu8_Make_Mode                             U8MakeModeB.byte
#define            Bit0_Cold_Make_Go                         U8MakeModeB.Bit.b0
#define            Bit1_Ice_Make_Go                          U8MakeModeB.Bit.b1





bit F_Cold_Make_Mode;
bit F_Ice_Make_Mode;

bit F_cold_add_op;
U16 gu16_cold_add_op_timer;

U8 gu8_dual_temp_check_timer;
bit F_Dual_Mode_Disable;

/*..hui [20-1-29���� 1:42:16] �ü� ���� ON/OFF �߰��� ���� Ÿ�̸� �߰�.. Ȥ�ø���..*/
U8 gu8_cold_on_timer;
U16 gu16_cold_off_timer;
U8 gu8_cold_protect_timer;

bit bit_cold_first_op;

bit bit_ice_one_more;


bit bit_drain_full_ice_stop;
U16 gu16_drain_full_timer;


U16 gu16_fast_ice_make_timer;
U8 gu8_fast_ice_make_count;
bit bit_count_ice_make;
U16 gu16_fast_ice_cold_max_timer;

U16 gu16_test_cold_on_temp;
U16 gu16_test_cold_off_temp;
U16 gu16_test_cold_delay_time;

bit bit_set_temp_change;
U8 gu8_recover_org_fast_ice;

bit bit_cold_first_op;
U16 mu16_cold_off_temp;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Make_Mode_Decision(void)
{
    /*..hui [19-10-23���� 10:17:47] ó�� ���� ON�� �����˻� �Ϸ� �� �����ϱ� ����..*/
    if(F_FW_Version_Display_Mode == CLEAR)
    {
        return;
    }
    else{}

    cold_mode_decision();
    ice_mode_decision();

    final_mode_decision();

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_mode_decision(void)
{
    //F_Cold_Enable=0;
    Bit0_Cold_Setting = F_Cold_Enable;

    if(gu16_Cold_Temperature > PROTECT_COLD_TEMP)
    {
        Bit1_Cold_Temp_Protect = SET;
    }
    else
    {
        /*Bit2_Cold_Temp_Protect = CLEAR;*/
        /*..hui [20-1-29���� 2:02:15] cold_comp_test �Լ����� ó��..*/
        Bit1_Cold_Temp_Protect = SET;
    }

    Bit2_Cold_Temp_Control = cold_comp_test();


    /*..hui [23-9-4���� 4:17:26] Ʈ���� ���� �ɷ����� �ð��� ���� �����ϱ�����..*/
    /*..hui [23-9-4���� 4:17:42] Ʈ���� ���� �ɷ����� F_IceInit�� SET�� ���·� ����������..*/
    if( Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET
        || Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET
        || Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET )
    {
        Bit3_Ice_Init_Cold_Stop = SET;
    }
    else
    {
        Bit3_Ice_Init_Cold_Stop = ~F_IceInit;
    }

    /*..hui [19-8-2���� 7:28:42] �ü� ���� ���� �߻� �� �ü��� �ð� ����..*/
    /*..hui [19-8-2���� 7:28:56] �ü� ���� �߻��ص� �������� ���� �����ؾ��ϱ� ������ �������� �̵�..*/
    Bit4_Cold_Error = ~Bit0_Cold_Operation_Disable_State;

    /* �÷����߿��� �ð� ���� */
    if( bit_install_flushing_state == CLEAR && gu8_flushing_mode == FLUSHING_NONE_STATE )
    {
        Bit5_Cold_Flushing_Stop = SET;
    }
    else
    {
        Bit5_Cold_Flushing_Stop = CLEAR;
    }

    /* Ʈ���� ���»���߿��� �ð� ���� */
    if( bit_ice_tank_ster_start == CLEAR )
    {
        Bit6_Cold_Ice_Ster_Stop = SET;
    }
    else
    {
        Bit6_Cold_Ice_Ster_Stop = CLEAR;
    }

    /*..hui [24-7-29���� 2:57:56] ������ ��ô �� �ð� ����..*/
    if( bit_self_test_start == CLEAR )
    {
        Bit7_Cody_Service_Cold_Off = SET;
    }
    else
    {
        Bit7_Cody_Service_Cold_Off = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_mode_decision(void)
{
    Bit0_Ice_Setting = F_IceOn;

    #if 0
	/*..sean [25-01-20] 2�� �̻��϶����� ���� �����ϵ��� ����..*/
    if(gu16_Cold_Temperature > PROTECT_COLD_TEMP)
    {
        Bit1_Ice_Temp_Protect = SET;
    }
    else
    {
        /*Bit2_Ice_Temp_Protect = CLEAR;*/
        /*..hui [19-11-7���� 3:36:57] ������ ����..*/
        Bit1_Ice_Temp_Protect = SET;
    }
    #endif

    if( bit_tray_in_error_temporary == CLEAR )
    {
        Bit1_Ice_Temp_Protect = SET;
    }
    else
    {
        Bit1_Ice_Temp_Protect = CLEAR;
    }


    /*Bit3_Ice_Full = ~F_IceFull;*/

    if( F_IceFull == SET )
    {
        Bit2_Ice_Full = CLEAR;
    }
    else
    {
        Bit2_Ice_Full = SET;
    }

    /*Bit4_Ice_Stop_Six_Hour = ~F_IceStop;*/
    /*..hui [23-6-29���� 5:20:21] �̻���������� �����ϰ��� �������..*/
    /*..hui [23-6-29���� 5:20:47] ��ħ���� �������� ä�����ʰ� ���� ��� �ϴ��ű����� �ϰ� ���� ����.. ���ν�..*/
    Bit3_Ice_Stop_Six_Hour = ~bit_sleep_mode_start;

    Bit4_Ice_Init_Ice_Stop = ~F_IceInit;


    /*..hui [19-12-18���� 1:49:10] Ʈ���� �̵����� ��õ� �����߿��� ���� ���� �� �ð� ��ȯ..*/
    Bit5_Ice_Stop_Safty_Routine = ~F_Safety_Routine;

    /*..hui [19-12-18���� 8:03:47] ���� �Ұ� ����..*/
    Bit6_Ice_Error = ~Bit2_Ice_Operation_Disable_State;

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [24-4-2���� 7:42:15] �巹�� ��ũ ������ ���°� 5�� �̻� ���ӽ� ���� ���� ����..*/
    /*..hui [24-4-2���� 7:42:31] ��� ������ ���� ��ũ �� ��ĥ������..*/
    if( u8DrainWaterLevel == DRAIN_LEVEL_HIGH )
    {
        gu16_drain_full_timer++;

        /*..hui [24-4-5���� 4:09:04] 5�� -> 10������ ����..*/
        if( gu16_drain_full_timer >= DRAIN_FULL_ICE_STOP_TIME )
        {
            gu16_drain_full_timer = DRAIN_FULL_ICE_STOP_TIME;
            bit_drain_full_ice_stop = SET;
        }
        else
        {
            bit_drain_full_ice_stop = CLEAR;
        }
    }
    else
    {
        gu16_drain_full_timer = 0;
        bit_drain_full_ice_stop = CLEAR;
    }

    /*..hui [20-1-20���� 10:26:55] �ڵ� ���� ��� ���� �� ���� ����..*/
    /*..hui [23-12-20���� 5:14:23] �����������϶��� ����..*/
	/*.. sean [25-01-20] ���� �����߿��� ����..*/
    if( u8CodyInspectOperation == 0 && bit_drain_full_ice_stop == CLEAR && bit_self_test_start == CLEAR )
    {
        Bit7_Cody_Service_Ice_Off = SET;
    }
    else
    {
        Bit7_Cody_Service_Ice_Off = CLEAR;
    }

    /* �÷����߿��� ���� ���� */
    if( bit_install_flushing_state == CLEAR && gu8_flushing_mode == FLUSHING_NONE_STATE )
    {
        Bit8_Ice_Stop_Flushing = SET;
    }
    else
    {
        Bit8_Ice_Stop_Flushing = CLEAR;
    }

    /* Ʈ���� ���»�� �߿��� ���� ���� */
    if( bit_ice_tank_ster_start == CLEAR )
    {
        Bit9_Ice_Stop_Ice_Ster = SET;
    }
    else
    {
        Bit9_Ice_Stop_Ice_Ster = CLEAR;
    }

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [24-4-11���� 7:08:35] Ȥ�ø���.. ���� ��� ���� Ư����� �߰�..*/
    if( gu8_recover_org_fast_ice == NEW_FAST_ICE )
    {
        /*..hui [24-4-11���� 3:53:13] �����켱�϶�.. ���� Ƚ�� üũ..*/
        count_ice_make();

        if( bit_fast_ice_make == ICE_FIRST_ICE_MAKE )
        {
            if( F_IceOn == CLEAR )
            {
                /*..hui [24-4-11���� 3:57:33] ���� OFF -> ON �� Ƚ�� �ʱ�ȭ..*/
                gu8_fast_ice_make_count = 0;
            }
            else{}

            if( bit_sleep_mode_start == SET )
            {
                /*..hui [24-4-12���� 12:14:40] ��ħ��� ���Խ� Ƚ�� �ʱ�ȭ..*/
                gu8_fast_ice_make_count = 0;
            }
            else{}

            /*..hui [24-4-11���� 3:11:27] �����켱 / ���� 4ȸ �ϰ� ����..*/
            if( gu8_fast_ice_make_count >= FAST_ICE_MAKE_COUNT )
            {
                /*..hui [24-4-11���� 3:11:34] �ð� ���� �����̸� �ð����� �̵�..*/
                if( u16ColdOperation == COLD_MAKE_GOGOGO )
                {
                    Bit10_Fast_Ice_Make_Limit = CLEAR;

                    /*..hui [24-4-11���� 4:04:28] �ð� ���� �������� ���ǿ��� Ȯ��..*/
                    if( Bit0_Cold_Mode_On_State == SET && F_Comp_Output == SET )
                    {
                        gu16_fast_ice_cold_max_timer++;

                        /*..hui [24-4-11���� 4:02:20] �ð� �����ð� �ִ� 1�ð� ����� �ٽ� �����ؾ���..*/
                        if( gu16_fast_ice_cold_max_timer >= FAST_ICE_COLD_MAX_OP_TIME )
                        {
                            gu16_fast_ice_cold_max_timer = 0;
                            gu8_fast_ice_make_count = 0;
                        }
                        else{}
                    }
                    else{}
                }
                else
                {
                    Bit10_Fast_Ice_Make_Limit = SET;
                    gu16_fast_ice_cold_max_timer = 0;
                    /*..hui [24-4-11���� 3:15:38] �ð� �̰��� �����ϰ�� ī��Ʈ �ʱ�ȭ�ϰ� �ٽ� 4ȸ ����..*/
                    /*..hui [24-4-11���� 7:39:40] ���⼭�� �ʱ�ȭ�ϸ�ȵ�..*/
                    /*..hui [24-4-11���� 7:39:53] 4������ �ѹ� �����ϰ� ��� �ð����� Ȯ���ؾ��ϱ� ����..*/
                    /*gu8_fast_ice_make_count = 0;*/
                }
            }
            else
            {
                Bit10_Fast_Ice_Make_Limit = SET;
                gu16_fast_ice_cold_max_timer = 0;
            }
        }
        else
        {
            Bit10_Fast_Ice_Make_Limit = SET;
            gu16_fast_ice_cold_max_timer = 0;
            /*..hui [24-4-11���� 3:15:38] �ð� �̰��� �����ϰ�� ī��Ʈ �ʱ�ȭ�ϰ� �ٽ� 4ȸ ����..*/
            gu8_fast_ice_make_count = 0;
        }
    }
    else
    {
        bit_count_ice_make = CLEAR;

        Bit10_Fast_Ice_Make_Limit = SET;
        gu16_fast_ice_cold_max_timer = 0;
        /*..hui [24-4-11���� 3:15:38] �ð� �̰��� �����ϰ�� ī��Ʈ �ʱ�ȭ�ϰ� �ٽ� 4ȸ ����..*/
        gu8_fast_ice_make_count = 0;
    }
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void count_ice_make(void)
{
    if( bit_fast_ice_make == ICE_FIRST_ICE_MAKE )
    {
        if( gu8IceStep == STATE_45_ICE_TAKE_OFF )
        {
            if( bit_count_ice_make == CLEAR )
            {
                bit_count_ice_make = SET;

                gu8_fast_ice_make_count++;

                if( gu8_fast_ice_make_count >= FAST_ICE_MAKE_COUNT )
                {
                    gu8_fast_ice_make_count = FAST_ICE_MAKE_COUNT;
                }
                else{}
            }
            else{}
        }
        else
        {
            bit_count_ice_make = CLEAR;
        }

    }
    else
    {
        bit_count_ice_make = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 cold_mode_comp_control(void)
{

/*..hui [20-1-29���� 2:00:42] �ð� �����ð� �ִ� ����.. Ȥ�� ���߿� ����ɼ������� ���ܵδ°ɷ�..*/
#if 0
    U16 mu16_cold_on_temp = 0;
    U16 mu16_cold_off_temp = 0;

    if(F_Sleep == SET)
    {
        mu16_cold_on_temp = COLD_ON_TEMP_SAVING;
    }
    else
    {
        mu16_cold_on_temp = COLD_ON_TEMP_NORMAL;
    }
    //gu16_Amb_Front_Temperature=333;

    /*..hui [19-7-25���� 8:45:00] 30�� �̻��̾��ٰ� 30�� �߰� �ð��� 30�� �̸����� �ٽ� ��������..??????..*/
    if(gu16_Amb_Front_Temperature < COLD_OFF_REF_TEMP_AMB)
    {
        mu16_cold_off_temp = COLD_OFF_TEMP_4_DEGREE;
    }
    else
    {
        mu16_cold_off_temp = COLD_OFF_TEMP_5_DEGREE;
    }

    if(gu16_Cold_Temperature >= mu16_cold_on_temp)
    {
        Bit0_Temp_Control = SET;

        /*..hui [19-7-25���� 5:37:11] 30�� �߰� �⵿ �� �ٽ� �������� ������ �ʱ�ȭ..*/
        Bit1_Temp_Add_Control = CLEAR;
        F_cold_add_op = CLEAR;
        gu16_cold_add_op_timer = 0;
    }
    else
    {
        if(Bit0_Temp_Control == SET)
        {
            if(gu16_Cold_Temperature <= mu16_cold_off_temp)
            {
                if(mu16_cold_off_temp == COLD_OFF_TEMP_5_DEGREE)
                {
                    Bit0_Temp_Control = CLEAR;
                    Bit1_Temp_Add_Control = SET;
                    gu16_cold_add_op_timer = 0;
                }
                else
                {
                    Bit0_Temp_Control = CLEAR;
                }
            }
            else{}
        }
        else{}
    }


    if(Bit1_Temp_Add_Control == SET)
    {
        /*..hui [19-7-26���� 7:32:20] ���ҳð�..*/
        if(gu8_GasSwitch_Status == GAS_SWITCH_COLD)
        {
            gu16_cold_add_op_timer++;
        }
        else{}

        /*..hui [19-7-25���� 5:33:28] 30�� �߰� �⵿ �� ����..*/
        if(gu16_cold_add_op_timer >= COLD_ADD_OPERATION_TIME)
        {
            Bit1_Temp_Add_Control = CLEAR;
        }
        else
        {
            Bit1_Temp_Add_Control = SET;
        }
    }
    else
    {
        Bit1_Temp_Add_Control = CLEAR;
        gu16_cold_add_op_timer = 0;
    }

    /*..hui [19-7-25���� 5:40:39] 2�� ���� ������Ʈ OFF ��ġ�̵�..*/
    if(gu16_Cold_Temperature <= PROTECT_COLD_TEMP)
    {
        gu8_Cold_Temp_Control = 0;
    }
    else{}

    if(gu8_Cold_Temp_Control > 0)
    {
        return SET;
    }
    else
    {
        return CLEAR;
    }
#endif

    return CLEAR;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : �ð� �µ����� (�ð����̺�)
***********************************************************************************************************************/
U8 cold_comp_test(void)
{
    U16 mu16_cold_on_temp = 0;
    U16 mu16_cold_delay_time = 0;

    U16 mu16_fast_ice_cold_on_temp;
	U16 mu16_fast_ice_cold_off_temp;

    if( ( gu8_recover_org_fast_ice == NEW_FAST_ICE
    && bit_fast_ice_make == ICE_FIRST_ICE_MAKE
    && u16IceOperation == FAST_ICE_MAKE_ENABLE )    // �������� + �ð� ���������� ��
    || ( gu8_recover_org_fast_ice == NEW_FAST_ICE
    && bit_fast_ice_make == ICE_FIRST_ICE_MAKE
    && u16IceOperation == ICE_MAKE_GOGOGO )         // �������� + �����ƴ�, �ð� ���������� �ƴ� ��
    )
    {
        /*..hui [24-4-11���� 2:37:22] ���� �켱 ������������.. �ð� �µ� 15��, 7.5��..*/
        mu16_cold_on_temp = 150;
        mu16_cold_off_temp = 75;
        mu16_cold_delay_time = 20;

        /*..hui [25-7-8���� 4:59:39] ����LEDǥ�� �µ� ���� ������..*/
        gu16_display_cold_on_temp = 75;
        gu16_display_cold_off_temp = 58;

        /*..hui [24-4-11���� 5:08:34] �����켱 ���� ���� �ƴ� ��� -> ���� �������� ����ɶ�..*/
        /*..hui [24-4-11���� 5:08:39] �ð� ���� ���� �ٽ� Ȯ���ϱ� ����..*/
        /*..hui [24-4-11���� 5:09:15] ����Ż�� -> �ð� �������� 8�� -> �ð� �������� set -> ����Ż�� ����..*/
        /*..hui [24-4-11���� 5:09:39] ���� -> 4ȸ ���� -> �������� set���ֱ� ������ �ð� �������� �Ѿ..*/
        /*..hui [24-4-11���� 5:10:00] ���� ���� ���ǵǸ� �ð� ������ �ٽ� 15���� Ȯ���ϵ���..*/
        if( bit_set_temp_change == CLEAR )
        {
            bit_set_temp_change = SET;
            Bit0_Temp_Control = CLEAR;
        }
        else{}
    }
    else
    {
        bit_set_temp_change = CLEAR;

        if( gu8_cold_setting_level == COLD_TEMP_HIGH )
        {
            if( gu8_Amb_Temperature_One_Degree <= 10 )  /* ~ 10'C */
            {
                if( bit_sleep_mode_start  == SET )
                {
                    /*..hui [23-4-7���� 11:15:58] 10�� ����..*/
                    mu16_cold_on_temp = 100;
                    mu16_cold_off_temp = 65;
                    mu16_cold_delay_time = 20;
                }
                else
                {
                    mu16_cold_on_temp = COLD_ON_TEMP_10DE_UNDER;
                    mu16_cold_off_temp = COLD_OFF_TEMP_10DE_UNDER;
                    mu16_cold_delay_time = COLD_DELAY_TIME_10DE_UNDER;
                }

                /*..hui [25-7-8���� 4:59:39] ����LEDǥ�� �µ� ���� ������..*/
                gu16_display_cold_on_temp = COLD_ON_TEMP_10DE_UNDER;
                gu16_display_cold_off_temp = COLD_OFF_TEMP_10DE_UNDER;
            }
            else if( gu8_Amb_Temperature_One_Degree <= 20 ) /* 10~20'C */
            {
                if( bit_sleep_mode_start  == SET )
                {
                    /*..hui [23-4-7���� 11:16:02] 20�� ����..*/
                    mu16_cold_on_temp = 100;
                    mu16_cold_off_temp = 58;
                    mu16_cold_delay_time = 20;
                }
                else
                {
                    mu16_cold_on_temp = COLD_ON_TEMP_10_20DE;

                    if( bit_cold_first_op == SET )
                    {
                        mu16_cold_off_temp = COLD_OFF_TEMP_10_20DE_FIRST;
                    }
                    else
                    {
                        mu16_cold_off_temp = COLD_OFF_TEMP_10_20DE;
                    }

                    if( bit_cold_first_op == SET )
                    {
                        mu16_cold_delay_time = COLD_DELAY_TIME_10_20DE_FIRST;
                    }
                    else
                    {
                        mu16_cold_delay_time = COLD_DELAY_TIME_10_20DE;
                    }
                }

                /*..hui [25-7-8���� 4:59:39] ����LEDǥ�� �µ� ���� ������..*/
                if( bit_cold_first_op == SET )
                {
                    gu16_display_cold_on_temp = COLD_ON_TEMP_10_20DE;
                    gu16_display_cold_off_temp = COLD_OFF_TEMP_10_20DE_FIRST;
                }
                else
                {
                    gu16_display_cold_on_temp = COLD_ON_TEMP_10_20DE;
                    gu16_display_cold_off_temp = COLD_OFF_TEMP_10_20DE;
                }
            }
            else if( gu8_Amb_Temperature_One_Degree <= 30 ) /* 20~30'C */
            {
                if( bit_sleep_mode_start  == SET )
                {
                    /*..hui [23-4-7���� 11:16:10] 30�� ����..*/
                    mu16_cold_on_temp = 100;
                    mu16_cold_off_temp = 58;
                    mu16_cold_delay_time = 20;
                }
                else
                {
                    mu16_cold_on_temp = COLD_ON_TEMP_20_30DE;
                    mu16_cold_off_temp = COLD_OFF_TEMP_20_30DE;

                    if( bit_cold_first_op == SET )
                    {
                        mu16_cold_delay_time = COLD_DELAY_TIME_20_30DE_FIRST;
                    }
                    else
                    {
                        mu16_cold_delay_time = COLD_DELAY_TIME_20_30DE;
                    }
                }

                /*..hui [25-7-8���� 4:59:39] ����LEDǥ�� �µ� ���� ������..*/
                gu16_display_cold_on_temp = COLD_ON_TEMP_20_30DE;
                gu16_display_cold_off_temp = COLD_OFF_TEMP_20_30DE;
            }
            else
            {
                if( bit_sleep_mode_start  == SET )
                {
                    /*..hui [23-4-7���� 11:16:14] 30�� �ʰ�..*/
                    mu16_cold_on_temp = 100;
                    mu16_cold_off_temp = 58;
                    mu16_cold_delay_time = 3000;
                }
                else
                {
                    /* 30'C~ */
                    mu16_cold_on_temp   = COLD_ON_TEMP_30DE_UPDER;
                    mu16_cold_off_temp  = COLD_OFF_TEMP_30DE_UPDER;

                    if( bit_cold_first_op == SET )
                    {
                        mu16_cold_delay_time = COLD_DELAY_TIME_30DE_UPDER_FIRST;
                    }
                    else
                    {
                        mu16_cold_delay_time = COLD_DELAY_TIME_30DE_UPDER;
                    }

                    /*..hui [25-7-8���� 4:59:39] ����LEDǥ�� �µ� ���� ������..*/
                    if( bit_cold_first_op == SET )
                    {
                        gu16_display_cold_on_temp = COLD_ON_TEMP_30DE_UPDER;
                        gu16_display_cold_off_temp = COLD_OFF_TEMP_30DE_UPDER;
                    }
                    else
                    {
                        gu16_display_cold_on_temp = COLD_ON_TEMP_30DE_UPDER;
                        gu16_display_cold_off_temp = COLD_OFF_TEMP_30DE_UPDER;
                    }
                }
            }
        }
        else /*if( gu8_cold_setting_level == COLD_TEMP_LOW )*/
        {
            /*..hui [25-3-19���� 2:22:52] �켱 �ü� �༳���� 14�� 10����..*/
            mu16_cold_on_temp = 110;        // �ü� [��] ���̺� �ݿ� 250728 CH.PARK
            mu16_cold_off_temp = 70;        // �ü� [��] ���̺� �ݿ� 250728 CH.PARK
            mu16_cold_delay_time = 20;      // �ü� [��] ���̺� �ݿ� 250728 CH.PARK

            /*..hui [25-7-8���� 4:59:39] ����LEDǥ�� �µ� ���� ������..*/
            gu16_display_cold_on_temp = 110;
            gu16_display_cold_off_temp = 70;
        }
    }


    /* CH.PARK 냉각 테이블 데이터 반영 */
    if(GetB1ColdOnTemp() > 0)
    {
        SetB1ColdOnTemp((U8*)&mu16_cold_on_temp);
    }

    if(GetB1ColdOffTemp() > 0)
    {
        SetB1ColdOffTemp((U8*)&mu16_cold_off_temp);
    }

    if(GetB1ColdDelayTime() > 0)
    {
        SetB1ColdDelayTime(&mu16_cold_delay_time);
    }

    /*..hui [24-4-11���� 4:22:44] �����.. Ȯ�ο�..*/
    gu16_test_cold_on_temp = mu16_cold_on_temp;
    gu16_test_cold_off_temp = mu16_cold_off_temp;
    gu16_test_cold_delay_time = mu16_cold_delay_time;

    if(gu16_Cold_Temperature >= mu16_cold_on_temp)
    {
        gu8_cold_on_timer++;

        if( gu8_cold_on_timer >= 20 )
        {
            gu8_cold_on_timer = 20;
            /*Bit0_Temp_Control = SET;*/

            if( Bit0_Temp_Control == CLEAR )
            {
                Bit0_Temp_Control = SET;

                if( gu16_Cold_Temperature >= COLD_FIRST_OPERATION_20_DEGREE )
                {
                    bit_cold_first_op = SET;
                }
                else
                {
                    bit_cold_first_op = CLEAR;
                }
            }
            else{}
        }
        else{}

        gu16_cold_off_timer = 0;
    }
    else
    {
        gu8_cold_on_timer = 0;

        if(Bit0_Temp_Control == SET)
        {
            if(gu16_Cold_Temperature <= mu16_cold_off_temp)
            {
                gu16_cold_off_timer++;

                if( gu16_cold_off_timer >= mu16_cold_delay_time )
                {
                    gu16_cold_off_timer = 0;
                    Bit0_Temp_Control = CLEAR;

                    /*..hui [24-4-12���� 11:43:45] �ð� �Ϸ�� ���� Ƚ�� �ʱ�ȭ ���ʿ���..*/
                    gu8_fast_ice_make_count = 0;
                }
                else{}
            }
            else
            {
                gu16_cold_off_timer = 0;
            }
        }
        else
        {
            gu16_cold_off_timer = 0;
        }
    }

    /*..hui [19-7-25���� 5:40:39] 2�� ���� ������Ʈ OFF ��ġ�̵�..*/
    if(gu16_Cold_Temperature <= PROTECT_COLD_TEMP)
    {
        gu8_cold_protect_timer++;

        if( gu8_cold_protect_timer >= 20 )
        {
            gu8_cold_protect_timer = 20;
            gu8_Cold_Temp_Control = 0;
        }
        else{}
    }
    else
    {
        gu8_cold_protect_timer = 0;
    }

    if(gu8_Cold_Temp_Control > 0)
    {
        return SET;
    }
    else
    {
        return CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void final_mode_decision(void)
{
    if(bit_fast_ice_make == COLD_FIRST_ICE_MAKE)
    {
        cold_priority_decision();
    }
    else
    {
        ice_priority_decision();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_priority_decision(void)
{
    switch(gu8_Make_Mode)
    {
        case MAKE_STOP:

            if(u16ColdOperation == COLD_MAKE_GOGOGO)
            {
                gu8_Make_Mode = MAKE_COLD;
            }
            else
            {
                if(u16IceOperation == ICE_MAKE_GOGOGO)
                {
                    gu8_Make_Mode = MAKE_ICE;
                }
                else
                {
                    gu8_Make_Mode = MAKE_STOP;
                }
            }

        break;

        case MAKE_COLD:

            /*..hui [19-7-25���� 4:21:53] �ð� �� �ð� ���� ���� �� ����/�ð� ���� �� Ȯ��..*/
            if(u16ColdOperation != COLD_MAKE_GOGOGO)
            {
                gu8_Make_Mode = MAKE_STOP;
            }
            else{}

        break;

        case MAKE_ICE:

            /*..hui [19-7-25���� 4:22:10] ���� �� ���� �Ϸ� �� ����/�ð� ���� �� Ȯ��..*/
            /*if(gu8IceStep == STATE_51_FINISH_ICE_MAKE)*/
            if(gu8IceStep == STATE_0_STANDBY)
            {
                /*..hui [20-1-21���� 11:15:35] ���� ��� �� ��� ���¿��� �ð� ���� �߻� ��..*/
                if(u16ColdOperation == COLD_MAKE_GOGOGO)
                {
                    gu8_Make_Mode = MAKE_STOP;
                }
                else if(u16IceOperation != ICE_MAKE_GOGOGO)
                {
                    gu8_Make_Mode = MAKE_STOP;
                }
                else{}
            }
            else{}

        break;

        default:

            gu8_Make_Mode = MAKE_STOP;

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_priority_decision(void)
{
    switch(gu8_Make_Mode)
    {
        case MAKE_STOP:

            /*..hui [19-7-26���� 8:09:21] ���� �켱�̹Ƿ� �����ɶ����� ���� ����..*/
            if(u16IceOperation == ICE_MAKE_GOGOGO)
            {
                gu8_Make_Mode = MAKE_ICE;
            }
            else
            {
                /*..hui [19-7-26���� 8:09:34] ���� ���� �ƴҶ��� �ð� ����..*/
                if(u16ColdOperation == COLD_MAKE_GOGOGO)
                {
                    gu8_Make_Mode = MAKE_COLD;
                }
                else
                {
                    gu8_Make_Mode = MAKE_STOP;
                }
            }

        break;

        case MAKE_COLD:

            if(u16IceOperation == ICE_MAKE_GOGOGO)
            {
                /*..hui [19-11-6���� 1:57:36] �ð� �� ���� ���� �߻� ��..*/
                gu8_Make_Mode = MAKE_STOP;
            }
            else if(u16ColdOperation != COLD_MAKE_GOGOGO)
            {
                /*..hui [19-11-6���� 1:57:57] �ð� �� �ð� ���� ���� ��..*/
                gu8_Make_Mode = MAKE_STOP;
            }
            else{}

        break;

        case MAKE_ICE:

            /*..hui [19-11-6���� 1:59:36] ���� �� ���� �Ϸ� �� ����/�ð� ���� �� Ȯ��..*/
            /*if(gu8IceStep == STATE_51_FINISH_ICE_MAKE)*/
            if(gu8IceStep == STATE_0_STANDBY)
            {
                /*..hui [19-12-18���� 4:06:39] ���� ����� ��� ���¿��� ���� ��� �������� �߻� ��..*/
                if(u16IceOperation != ICE_MAKE_GOGOGO)
                {
                    gu8_Make_Mode = MAKE_STOP;
                }
                else{}
            }
            else{}


        break;

        default:

            gu8_Make_Mode = MAKE_STOP;

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



