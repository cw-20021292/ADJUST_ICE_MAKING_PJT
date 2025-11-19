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
#include    "AC_motor_output.h"

void output_ac_motor(void);
void check_error_micro_sw_detect_at_once(void);
void check_error_micro_sw_movement(void);
void output_ice_feeder_motor(void);
void output_ice_tray_motor(void);
void check_error_tray_motor_up_operation(void);
void check_error_tray_motor_down_retry_operation(void);
void ice_make_system_up_move_reset(void);
void ice_make_system_down_move_reset(void);

void over_ice_making_check(void);
void over_ice_making_melt_proc(void);
void ice_system_reset(void);
void ice_stuck_reset(void);
void ice_system_stop(void);

void inverse_direction_time_check(void);
void reset_micro_sw_move_err_check_state(void);
void down_tray_motor(void);
void up_tray_motor(void);
void stop_tray_motor(void);
void check_ice_system_ok(void);

////

//----------------------------------------------------// Motor
U8 gu8DualTrayStep;
U8 gu8DualTrayCheckCNT;
U16 gu16DualCheckDelay;
U8 gu8_Err_Tray_Up_Count;
U8 gu8_Err_Tray_Down_Count;

/*..hui [19-12-13���� 7:12:16] Ʈ���� Ż�� �̵� ���� ���� ī��Ʈ..*/
U8 gu8_err_tray_down_acc_count;


U8 gu8_Tray_CW_Interval_Timer;
bit F_Tray_CW_delay_finish;




U8 gu8_Tray_CCW_Interval_Timer;
bit F_Tray_CCW_delay_finish;


U8 u8_Tray_up_moving_retry_timer;


U16 gu16_Tray_down_moving_retry_timer;

bit F_ErrTrayMotor_DualInital;
U16 gu16_Err_Tray_Motor_Down_Total_Tmr;
U16 gu16_Err_Tray_Motor_Up_Total_Tmr;



U16 gu16_Ice_Tray_Up_Reset_Delay_Tmr;

U16 gu16_Ice_Tray_Down_Reset_Delay_Tmr;

U8 gu8_Tray_Motor_Direction;

U8 gu8_Pre_Tray_Motor_Direction;
bit F_Ice_Tray_Up_Move_Reset;

bit F_Ice_Tray_Down_Move_Reset;

bit F_over_ice_check_enable;


U16 gu16_over_ice_melt_timer;

U8 gu8_over_ice_melt_proc;

U8 gu8_over_ice_melt_operation_count;


bit F_Over_Ice_Heater_State;

bit bit_ice_out_back_1s_state;
U8 gu8_ice_out_reverse_1s_timer;

bit bit_ice_out_back_state;
U8 gu8_ice_out_reverse_timer;

U8 gu8_ice_out_operation_timer;
bit bit_ice_full_state;

U8 gu8_ice_system_ok;

/* �����ɸ� �̻� ���� ���� */
bit bit_ice_stuck_back_state;
U8 gu8_ice_stuck_reverse_timer;

/* ���� ���� �� ���� ��ġ ���� ���� ���� ����  */
bit bit_ice_mix_back_state;
U8 gu8_ice_mix_reverse_timer;

U8 gu8_tray_up_contiunue_timer;

U8 gu8_ice_break_acc_count_100ms = CLEAR;
U8 gu8_ice_continue_acc_count_100ms = CLEAR;

// Endurance Here!
U8 gu8_ice_out_endurance_timer;
U32 gu32_feeder_screw_ccw_count;

bit bit_ice_shake_state;
U16 gu16_ice_full_shake_timer_100ms;
U8  gu8_ice_full_shaking_op_timer_100ms;

/* �������� ���� �յڷ� ���� ��� ���� ���� */
U8 gu8_ice_feeder_shake;
U8 gu8_ice_feeder_shake_time;

/* �Ϲݾ��� ���� ���� ���� */
U8 gu8_normal_ice_acc_cur_count_100ms = CLEAR;      // ���� ����ð�?
U8 gu8_normal_ice_acc_set_count_100ms = CLEAR;      // ���� Ÿ�ٽð�
U8 gu8_normal_ice_stay_count = CLEAR;               // �߰� ���� Ƚ��
bit bit_normal_ice_out_start;                       // �Ϲݾ��� ���� ���� �����÷���

U16 gu16_ice_extract_timer_100ms;

extern MODEL model;
extern ICE_STUCK_1 IceStuck;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_ac_motor(void)
{
    /*ac_motor_time_check();*/
    output_ice_feeder_motor();
    output_ice_tray_motor();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_ice_feeder_motor(void)
{
    if(gu8IceOutCCWInterval > 0)
    {
        gu8IceOutCCWInterval--;    // �������? ���?3->2��
    }
    else{}

    if(gu16ErrIceOut > 0)
    {
        gu16ErrIceOut--;                // �������� ���Ϳ��� 120��
    }
    else{}

/*..hui [20-4-17���� 3:04:49] �Ǵ� ��ȸ�� ������ ice_extraction_finish�� F_IR ���������?..��~~~..*/
/*..hui [20-4-17���� 3:04:59] ���� ������ 2�� ��ȸ�� �Ϸ� �� �ϵ��� �ϱ� ����..*/
    //===========================================// �������� ���� ����
    if(F_IceOutCCW == SET)                      // ����ȸ��(��ȸ��)
    {
        if( F_IceBreak == CLEAR )
        {
            /*..hui [20-4-14���� 12:42:38] 3�� �� �Ǵ� ���� ����..*/
            if(pMOTOR_ICE_OUT_CCW != SET && gu8IceOutCCWInterval == 0)
            {
                gu16ErrIceOut = 1200; 						 //�������? 120��
                bit_normal_ice_out_start = SET;
            }
            else{}

            /*..hui [20-4-14���� 12:45:16] ���� 2�� �̻� ���ӽ� ���� ����..*/
            if(pMOTOR_ICE_OUT_CCW == SET && gu16ErrIceOut == 0)
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                /* �������� �� ����Ϸ���� �ʴ� ���� ���� 250808 CH.PARK */
                ice_extraction_finish();
                F_IceOutCCW = CLEAR;
                bit_normal_ice_out_start = CLEAR;
            }
            else{}

            if( pMOTOR_ICE_OUT_CCW == SET )
            {
                /* 2025-09-18 @CH.PARK ���� �Ǵ��� ��ȸ�� �ϴ� �ð����� �Ǵ� (���� ���� ����) */
                gu16_ice_extract_timer_100ms++;

                gu8_ice_out_operation_timer++;
                if( gu8_ice_out_operation_timer >= 30 && gu8_ice_out_operation_timer < 60 )
                {
                    bit_ice_out_back_1s_state = SET;
                    bit_ice_out_back_state = CLEAR;
                }
                else if( gu8_ice_out_operation_timer >= 60 )
                {
                    gu8_ice_out_operation_timer = 60;
                    bit_ice_out_back_1s_state = CLEAR;
                    bit_ice_out_back_state = SET;
                }
                else{}
            }
            else
            {
                /*..hui [20-4-22���� 10:27:26] ���� ������ ������ ��쿡��? �����ϵ���..*/
                if( F_IceFull == SET )
                {
                    bit_ice_full_state = SET;
                }
                else
                {
                    #ifndef __AC_MOTOR_TEST_MODE__
                    bit_ice_full_state = CLEAR;
                    #endif
                }
            }

            if(bit_normal_ice_out_start != CLEAR)
            {
                gu8_normal_ice_acc_cur_count_100ms++;

                if(gu8_ice_out_continue == SET)
                {
                    /* [V1.0.0.2] �Ϲݾ��� ���� ���� �� 3�� ����, 1�� ���� �ݺ� */
                    gu8_ice_continue_acc_count_100ms++;
                    if(pMOTOR_ICE_OUT_CCW == SET)
                    {
                        if(gu8_ice_continue_acc_count_100ms >= 30)      /* 3�� ���� */
                        {
                            gu8_ice_continue_acc_count_100ms = 0;
                            pMOTOR_ICE_OUT_CCW = CLEAR;
                        }
                        else {  }
                    }
                    else
                    {
                        if(gu8_ice_continue_acc_count_100ms >= 10)      /* 1�� ���� */
                        {
                            gu8_ice_continue_acc_count_100ms = 0;
                            pMOTOR_ICE_OUT_CCW = SET;
                        }
                        else {  }
                    }
                }
                else if(gu8_ice_amount_step == ICE_LEVEL_1_STEP)            // 1�ܰ�
                {
                    gu8_normal_ice_stay_count = 0;
                    gu8_normal_ice_acc_set_count_100ms = ICE_OUT_1_STEP_TIME;
                    if(gu8_normal_ice_acc_cur_count_100ms <= gu8_normal_ice_acc_set_count_100ms)
                    {
                        pMOTOR_ICE_OUT_CCW = SET;
                    }
                    else
                    {
                        gu8_normal_ice_acc_cur_count_100ms = 0;
                    }
                }
                else if(gu8_ice_amount_step == ICE_LEVEL_2_STEP)
                {
                    if(gu8_normal_ice_stay_count >= 1)
                    {
                        gu8_normal_ice_acc_set_count_100ms = 30;
                        if(gu8_normal_ice_acc_cur_count_100ms <= (gu8_normal_ice_acc_set_count_100ms - 10))      // 2�� ����
                        {
                            pMOTOR_ICE_OUT_CCW = SET;
                        }
                        else if(gu8_normal_ice_acc_cur_count_100ms <= (gu8_normal_ice_acc_set_count_100ms + 1))  // 1�� ����
                        {
                            pMOTOR_ICE_OUT_CCW = CLEAR;
                        }
                        else
                        {
                            gu8_normal_ice_acc_cur_count_100ms = 0;
                        }
                    }
                    else
                    {
                        gu8_normal_ice_acc_set_count_100ms = 50;
                        if(gu8_normal_ice_acc_cur_count_100ms <= (gu8_normal_ice_acc_set_count_100ms - 10))      // 4�� ����
                        {
                            pMOTOR_ICE_OUT_CCW = SET;
                        }
                        else if(gu8_normal_ice_acc_cur_count_100ms <= gu8_normal_ice_acc_set_count_100ms)        // 1�� ����
                        {
                            pMOTOR_ICE_OUT_CCW = CLEAR;
                        }
                        else
                        {
                            gu8_normal_ice_acc_cur_count_100ms = 0;
                            gu8_normal_ice_stay_count++;
                        }
                    }
                }
                else if(gu8_ice_amount_step == ICE_LEVEL_3_STEP)
                {
                    if(gu8_normal_ice_stay_count >= 1)
                    {
                        gu8_normal_ice_acc_set_count_100ms = 30;
                        if(gu8_normal_ice_acc_cur_count_100ms <= (gu8_normal_ice_acc_set_count_100ms - 10))      // 2�� ����
                        {
                            pMOTOR_ICE_OUT_CCW = SET;
                        }
                        else if(gu8_normal_ice_acc_cur_count_100ms <= (gu8_normal_ice_acc_set_count_100ms))      // 1�� ����
                        {
                            pMOTOR_ICE_OUT_CCW = CLEAR;
                        }
                        else
                        {
                            gu8_normal_ice_acc_cur_count_100ms = 0;
                        }
                    }
                    else
                    {
                        gu8_normal_ice_acc_set_count_100ms = 50;
                        if(gu8_normal_ice_acc_cur_count_100ms <= (gu8_normal_ice_acc_set_count_100ms - 10))      // 4�� ����
                        {
                            pMOTOR_ICE_OUT_CCW = SET;
                        }
                        else if(gu8_normal_ice_acc_cur_count_100ms <= gu8_normal_ice_acc_set_count_100ms)        // 1�� ����
                        {
                            pMOTOR_ICE_OUT_CCW = CLEAR;
                        }
                        else
                        {
                            gu8_normal_ice_acc_cur_count_100ms = 0;
                            gu8_normal_ice_stay_count++;
                        }
                    }
                }
                else if(gu8_ice_amount_step == ICE_LEVEL_4_STEP)
                {
                    gu8_normal_ice_acc_set_count_100ms = 50;
                    if(gu8_normal_ice_acc_cur_count_100ms <= (gu8_normal_ice_acc_set_count_100ms - 10))      // 4�� ����
                    {
                        pMOTOR_ICE_OUT_CCW = SET;
                    }
                    else if(gu8_normal_ice_acc_cur_count_100ms <= gu8_normal_ice_acc_set_count_100ms)        // 1�� ����
                    {
                        pMOTOR_ICE_OUT_CCW = CLEAR;
                    }
                    else
                    {
                        gu8_normal_ice_acc_cur_count_100ms = 0;
                    }
                }
                else {  }
            }
            else
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
            }
        }
        else
        {
            bit_normal_ice_out_start = SET;

            /* ���������� 6�� �̻� �����ϸ� ���� */
            gu8_ice_out_operation_timer++;
            if( gu8_ice_out_operation_timer >= 30 && gu8_ice_out_operation_timer < 60 )
            {
                bit_ice_out_back_1s_state = SET;
                bit_ice_out_back_state = CLEAR;
            }
            else if( gu8_ice_out_operation_timer >= 60 )
            {
                gu8_ice_out_operation_timer = 60;
                bit_ice_out_back_1s_state = CLEAR;
                bit_ice_out_back_state = SET;
            }
            else{}

            /* �������� �� 2�� ����, 1�� ���� �ݺ� (�ֽ�) ��ä���? naverworks ��û 250704 ch.park */
            gu8_ice_break_acc_count_100ms++;
            if(pMOTOR_ICE_OUT_CCW == SET)
            {
                /* 2025-09-18 @CH.PARK ���� �Ǵ��� ��ȸ�� �ϴ� �ð����� �Ǵ� (���� ���� ����) */
                gu16_ice_extract_timer_100ms++;

                if(gu8_ice_break_acc_count_100ms >= 20)     /* 2�ʵ��� */
                {
                    gu8_ice_break_acc_count_100ms = 0;
                    pMOTOR_ICE_OUT_CCW = CLEAR;
                }
                else {  }
            }
            else
            {
                if(gu8_ice_break_acc_count_100ms >= 10)     /* 1������ */
                {
                    gu8_ice_break_acc_count_100ms = 0;
                    pMOTOR_ICE_OUT_CCW = SET;
                }
                else {  }
            }
        }

        /*..hui [20-4-14���� 1:09:53] �����? ��ȸ�� ����..*/
        pMOTOR_ICE_OUT_CW = CLEAR;
        gu8_ice_out_reverse_timer = 0;
        gu8_ice_stuck_reverse_timer = 0;
    }
    else
    {
        gu8_normal_ice_acc_cur_count_100ms = CLEAR;
        gu8_normal_ice_acc_set_count_100ms = CLEAR;
        gu8_normal_ice_stay_count = CLEAR;
        bit_normal_ice_out_start = CLEAR;

        #ifdef __AC_MOTOR_TEST_MODE__
        #ifdef __SCREW_ACC_ENDURANCE__  /* ��ȸ�� ������ */
        /*..hui [20-4-22���� 10:27:26] ���� ������ ������ ��쿡��? �����ϵ���..*/
        if( F_IceFull == SET )
        {
            bit_ice_full_state = SET;
        }
        else
        {
            // bit_ice_full_state = CLEAR;
        }

        /* pMOTOR_ICE_OUT_CCW = CLEAR; */

        gu8_ice_out_operation_timer = 0;

        // Endurance Here!
        /*..hui [20-4-14���� 12:38:42] �Ǵ���ũ���� ���� �������� ������ ������..*/
        if(bit_ice_full_state == SET)
        {
            gu8_ice_out_endurance_timer++;
            if(gu8_ice_out_endurance_timer >= 30)            // 3�� ����
            {
                // LPP ���������?
                if( gu8_ice_out_endurance_timer >= 50 )      // 2�� ��ȸ��
                {
                    gu8_ice_out_endurance_timer = 0;

                    pMOTOR_ICE_OUT_CCW = CLEAR;
                    pMOTOR_ICE_OUT_CW = CLEAR;

                    gu32_feeder_screw_ccw_count++;
                    if(gu32_feeder_screw_ccw_count >= 999999)
                    {
                        gu32_feeder_screw_ccw_count = 999999;
                    }
                }
                else
                {
                    pMOTOR_ICE_OUT_CCW = CLEAR;
                    pMOTOR_ICE_OUT_CW = SET;
                }
            }
            else
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
        }
        else
        {
            pMOTOR_ICE_OUT_CCW = CLEAR;
            pMOTOR_ICE_OUT_CW = CLEAR;
            gu8_ice_out_reverse_timer = 0;
            gu8_ice_stuck_reverse_timer = 0;
            gu8_ice_mix_reverse_timer = 0;
        }
        #endif

        #ifdef __SCREW_AC_ENDURANCE__   /* ��ȸ�� ������ */
        gu8_ice_out_operation_timer = 0;
        gu8_ice_break_acc_count_100ms = 0;

        if( F_IceFull == SET )
        {
            bit_ice_full_state = SET;
        }
        else
        {
            // bit_ice_full_state = CLEAR;
        }

        // Endurance Here!
        if(bit_ice_full_state == SET)
        {
            gu8_ice_out_endurance_timer++;
            if(gu8_ice_out_endurance_timer >= 30)       // 3�� ����
            {
                if(gu8_ice_out_endurance_timer >= 50)   // 2�� ��ȸ��
                {
                    gu8_ice_out_endurance_timer = 0;
                    pMOTOR_ICE_OUT_CCW = CLEAR;
                    pMOTOR_ICE_OUT_CW = CLEAR;

                    gu32_feeder_screw_ccw_count++;
                    if(gu32_feeder_screw_ccw_count >= 999999)
                    {
                        gu32_feeder_screw_ccw_count = 999999;
                    }
                }
                else
                {
                    pMOTOR_ICE_OUT_CCW = SET;
                    pMOTOR_ICE_OUT_CW = CLEAR;
                }
            }
            else
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
        }
        else
        {
            pMOTOR_ICE_OUT_CCW = CLEAR;
            pMOTOR_ICE_OUT_CW = CLEAR;
            gu8_ice_out_reverse_timer = 0;
            gu8_ice_stuck_reverse_timer = 0;
            gu8_ice_mix_reverse_timer = 0;
        }
        #endif

        #else
        /* ������α׷�? */
        /* pMOTOR_ICE_OUT_CCW = CLEAR; */
        bit_ice_full_state = CLEAR;
        gu8_ice_out_operation_timer = 0;
        gu8_ice_break_acc_count_100ms = 0;
        gu8_ice_continue_acc_count_100ms = 0;

        /*..hui [20-4-14���� 12:38:42] �Ǵ���ũ���� ���� �������� ������ ������..*/
        if(bit_ice_out_back_1s_state == SET)
        {
            /* ���彺��ġ ����ϴ�? ���̰� ���� �ɸ� Ȯ�����̰ų� �������� ���� ���� ��ȸ�������� ���? */
            if(model.u8model == MODEL_REED_USE)
            {
                if((IceStuck.u8IceJamCheck == SET)
                || (IceStuck.u8IceJamResolveStep > 0)
                )
                {
                    pMOTOR_ICE_OUT_CCW = CLEAR;
                    pMOTOR_ICE_OUT_CW = CLEAR;
                    return;
                }
            }

            pMOTOR_ICE_OUT_CCW = CLEAR;

            gu8_ice_out_reverse_1s_timer++;

            /* 3�� �̻� ����Ϸ�? �� 5�� ���? (����) �� 1�� ���� */
            if( gu8_ice_out_reverse_1s_timer < ICE_OUT_BACK_1S_DELAY_TIME )
            {
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            else if( gu8_ice_out_reverse_1s_timer < (U8)(ICE_OUT_BACK_1S_DELAY_TIME + ICE_OUT_BACK_1S_GO_TIME))
            {
                pMOTOR_ICE_OUT_CW = SET;
            }
            else
            {
                bit_ice_out_back_1s_state = CLEAR;
                gu8_ice_out_reverse_1s_timer = 0;
                /*..hui [20-4-22���� 10:35:40] ��ȸ�� �Ϸ� �� ��������..*/
                F_IR = SET;
                F_Low_IR = SET;
            }

            gu8_ice_out_reverse_timer = 0;
            gu8_ice_stuck_reverse_timer = 0;
            gu8_ice_mix_reverse_timer = 0;
        }
        else if( bit_ice_out_back_state == SET )
        {
            /* ���彺��ġ ����ϴ�? ���̰� ���� �ɸ� Ȯ�����̰ų� �������� ���� ���� ��ȸ�������� ���? */
            if(model.u8model == MODEL_REED_USE)
            {
                if((IceStuck.u8IceJamCheck == SET)
                || (IceStuck.u8IceJamResolveStep > 0)
                )
                {
                    pMOTOR_ICE_OUT_CCW = CLEAR;
                    pMOTOR_ICE_OUT_CW = CLEAR;
                    return;
                }
            }

            pMOTOR_ICE_OUT_CCW = CLEAR;

            gu8_ice_out_reverse_timer++;

            /* 6�� �̻� ����Ϸ�? �� 5�� ���? (����) �� 3�� ���� */
            if( gu8_ice_out_reverse_timer < ICE_OUT_BACK_2S_DELAY_TIME )
            {
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            else if( gu8_ice_out_reverse_timer < (U8)(ICE_OUT_BACK_2S_DELAY_TIME + ICE_OUT_BACK_2S_GO_TIME))
            {
                pMOTOR_ICE_OUT_CW = SET;
            }
            else
            {
                bit_ice_out_back_state = CLEAR;
                gu8_ice_out_reverse_timer = 0;
                /*..hui [20-4-22���� 10:35:40] ��ȸ�� �Ϸ� �� ��������..*/
                F_IR = SET;
                F_Low_IR = SET;

                /* 2025-09-18 CH.PARK 3�� ��ȸ�� ���� �ݵ��? 1�� ���? �� ��ȸ���ǵ��� ��.
                �ٷ� ȸ�� ������ ������ �ȵ� */
                gu8IceOutCCWInterval = 10;
            }

            gu8_ice_stuck_reverse_timer = 0;
            gu8_ice_mix_reverse_timer = 0;
            gu8_ice_out_reverse_1s_timer = 0;
        }
        else if(gu8_ice_feeder_shake == SET)
        {
            /* 2025-10-13 CH.PARK �������� ���� ���� �� 100% �� ���� �Ͻ������� ���� ���� */
            if(F_IceSelectClose == SET)
            {
                return;
            }

            gu8_ice_feeder_shake_time++;
            if(gu8_ice_feeder_shake_time <= ICE_SHAKE_DELAY_TIME)             // 4�� ���?
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            else if(gu8_ice_feeder_shake_time <= (ICE_SHAKE_DELAY_TIME + 10))        // 1�� ����
            {
                pMOTOR_ICE_OUT_CCW = SET;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            else if(gu8_ice_feeder_shake_time <= (ICE_SHAKE_DELAY_TIME + 15))        // 0.5�� ���?
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            else if(gu8_ice_feeder_shake_time <= (ICE_SHAKE_DELAY_TIME + 25))        // 1�� ����
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = SET;
            }
            else
            {
                gu8_ice_feeder_shake = CLEAR;
                gu8_ice_feeder_shake_time = 0;
            }
        }
        else if( bit_ice_stuck_back_state == SET )
        {
            pMOTOR_ICE_OUT_CCW = CLEAR;

            gu8_ice_stuck_reverse_timer++;

            /*..hui [25-3-17���� 4:16:14] ���� �ɸ� ���� ���� 2��..*/
            if( gu8_ice_stuck_reverse_timer >= 20 )
            {
                gu8_ice_stuck_reverse_timer = 0;
                bit_ice_stuck_back_state = CLEAR;
            }
            else
            {
                pMOTOR_ICE_OUT_CW = SET;
            }

            gu8_ice_mix_reverse_timer = 0;
            gu8_ice_out_reverse_1s_timer = 0;
            gu8_ice_out_reverse_timer = 0;
        }
        else if( bit_ice_mix_back_state == SET )              /* �����Ϸ� �� �ڼ��� ���� */
        {
            /* ���彺��ġ ����ϴ�? ���̰� ���� �ɸ� Ȯ�����̰ų� �������� ���� ���� ��ȸ�������� ���? */
            if(model.u8model == MODEL_REED_USE)
            {
                if((IceStuck.u8IceJamCheck == SET)
                || (IceStuck.u8IceJamResolveStep > 0)
                )
                {
                    pMOTOR_ICE_OUT_CCW = CLEAR;
                    pMOTOR_ICE_OUT_CW = CLEAR;
                    return;
                }
            }

            gu8_ice_mix_reverse_timer++;
            // if( gu8_ice_mix_reverse_timer <= 2 )           /* 0.2�� ���� */
            if( gu8_ice_mix_reverse_timer <= 5 )              /* 0.5�� ���� (����) 250828 CH.PARK */
            {
                pMOTOR_ICE_OUT_CCW = SET;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            // else if( gu8_ice_mix_reverse_timer <= 12 )      /* 1�� ���? */
            else if( gu8_ice_mix_reverse_timer <= 15 )         /* 1�� ���? */
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            // else if( gu8_ice_mix_reverse_timer <= 15 )      /* 0.3�� ���� */
            else if( gu8_ice_mix_reverse_timer <= 20 )         /* 0.5�� ���� (����) 250828 CH.PARK */
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = SET;
            }
            else
            {
                bit_ice_mix_back_state = CLEAR;
                gu8_ice_mix_reverse_timer = 0;
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }

            gu8_ice_stuck_reverse_timer = 0;
            gu8_ice_out_reverse_1s_timer = 0;
            gu8_ice_out_reverse_timer = 0;
        }
        else if(bit_ice_shake_state == SET)
        {
            /* ���彺��ġ ����ϴ�? ���̰� ���� �ɸ� Ȯ�����̰ų� �������� ���� ���� ��ȸ�������� ���? */
            if(model.u8model == MODEL_REED_USE)
            {
                if((IceStuck.u8IceJamCheck == SET)
                || (IceStuck.u8IceJamResolveStep > 0)
                )
                {
                    pMOTOR_ICE_OUT_CCW = CLEAR;
                    pMOTOR_ICE_OUT_CW = CLEAR;
                    return;
                }
            }

            gu8_ice_full_shaking_op_timer_100ms++;

            if( gu8_ice_full_shaking_op_timer_100ms <= 5 )              /* 0.5�� ���� */
            {
                pMOTOR_ICE_OUT_CCW = SET;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            else if( gu8_ice_full_shaking_op_timer_100ms <= 15 )         /* 1�� ���? */
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
            else if( gu8_ice_full_shaking_op_timer_100ms <= 20 )         /* 0.5�� ���� */
            {
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = SET;
            }
            else
            {
                bit_ice_shake_state = CLEAR;
                gu16_ice_full_shake_timer_100ms = 0;
                gu8_ice_full_shaking_op_timer_100ms = 0;
                pMOTOR_ICE_OUT_CCW = CLEAR;
                pMOTOR_ICE_OUT_CW = CLEAR;
            }
        }
        else
        {
            pMOTOR_ICE_OUT_CCW = CLEAR;
            pMOTOR_ICE_OUT_CW = CLEAR;

            gu8_ice_out_reverse_1s_timer = 0;
            gu8_ice_out_reverse_timer = 0;
            gu8_ice_stuck_reverse_timer = 0;
            gu8_ice_mix_reverse_timer = 0;

            if( F_IceFull == SET )
            {
                gu16_ice_full_shake_timer_100ms++;
                if(gu16_ice_full_shake_timer_100ms >= 18000)
                {
                    gu16_ice_full_shake_timer_100ms = 0;
                    gu8_ice_full_shaking_op_timer_100ms = 0;
                    bit_ice_shake_state = SET;
                }
                else {  }
            }
            else
            {
                gu16_ice_full_shake_timer_100ms = 0;
                gu8_ice_full_shaking_op_timer_100ms = 0;
                bit_ice_shake_state = CLEAR;
            }
        }
        #endif
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_ice_tray_motor(void)
{
    /*..hui [18-2-9���� 1:09:49] CW CCW ���� ���� �� 5�� ���? �� ��ȯ..*/
    inverse_direction_time_check();

    if( Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET
        || Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET
        || Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET )
    {
        /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
        /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
        run_stop_ice_tray();
    }
    else if(F_ErrTrayMotor_DualInital == SET)
    {
        check_error_micro_sw_detect_at_once();
        /*..hui [18-2-13���� 3:16:13] move ���� Ȯ�� �� ���ð��� ���� üũ�� ��ȯ�� ���? Ŭ����..*/
        /*..hui [18-2-13���� 3:16:29] �ٽ� move�����̵Ǹ� ó������ �����ϵ���....*/
        reset_micro_sw_move_err_check_state();
    }
    else
    {
        check_error_micro_sw_movement();
        gu8DualTrayStep = 0;
    }

    check_ice_system_ok();

    if( Bit18_Tray_Micro_SW_Up_Move_Error__E62 == CLEAR
        && Bit19_Tray_Micro_SW_Down_Move_Error__E63 == CLEAR
        && Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == CLEAR )
    {
        /*..hui [25-3-17���� 3:16:46] ���̽�Ʈ���� ���� ���?..*/
        /*..hui [25-3-17���� 3:17:56] ���� �ƴҶ��� ��µǵ���?..*/
        control_ice_tray();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void reset_micro_sw_move_err_check_state(void)
{
    F_Ice_Tray_Up_Move_Reset = 0;
    F_Ice_Tray_Down_Move_Reset = 0;
    F_Safety_Routine = 0;
    gu16_Err_Tray_Motor_Up_Total_Tmr = 0;
    gu16_Err_Tray_Motor_Down_Total_Tmr = 0;
    u8_Tray_up_moving_retry_timer = 0;
    gu16_Tray_down_moving_retry_timer = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void inverse_direction_time_check(void)
{
    /*if( pMOTOR_ICE_TRAY_CW == SET )*/
    if( gu8_ice_tray_mode == ICE_TRAY_MODE_UP )
    {
        gu8_Tray_CW_Interval_Timer = 0;
        F_Tray_CW_delay_finish = CLEAR;
    }
    else
    {
        gu8_Tray_CW_Interval_Timer++;

        if(gu8_Tray_CW_Interval_Timer >= 50)
        {
            gu8_Tray_CW_Interval_Timer = 50;
            F_Tray_CW_delay_finish = SET;
        }
        else{}
    }

    /*if(pMOTOR_ICE_TRAY_CCW == SET)*/
    if( gu8_ice_tray_mode == ICE_TRAY_MODE_DOWN )
    {
        gu8_Tray_CCW_Interval_Timer = 0;
        F_Tray_CCW_delay_finish = CLEAR;
    }
    else
    {
        gu8_Tray_CCW_Interval_Timer++;

        if(gu8_Tray_CCW_Interval_Timer >= 50)
        {
            gu8_Tray_CCW_Interval_Timer = 50;
            F_Tray_CCW_delay_finish = SET;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_micro_sw_detect_at_once(void)
{
    /*..hui [18-2-1���� 10:43:34] Ʈ���� ���� ������ ��õ�? ..*/
    if(gu16DualCheckDelay > 0)
    {
        gu16DualCheckDelay--;
    }
    else{}


    if(F_TrayMotorPreUP == SET)
    {
        gu8DualTrayStep = 1;
        F_TrayMotorPreUP = 0;
    }
    else{}

    switch(gu8DualTrayStep)
    {
        case 0 :

            /*..hui [18-2-1���� 11:19:07] Ʈ���� ���� ���� �̵�..*/
            /*pMOTOR_ICE_TRAY_CW = 1;*/
            /*pMOTOR_ICE_TRAY_CCW = 0;*/
            run_up_ice_tray();

            /*gu16DualCheckDelay = 150;*/     // ���� 15�� �̵�
            gu16DualCheckDelay = 100;     // ���� 15�� �̵�
            gu8DualTrayStep++;     // 1.CW
            break;

        case 1 :

            if(gu16DualCheckDelay == 0)
            {
                /*pMOTOR_ICE_TRAY_CW = 0;*/
                /*pMOTOR_ICE_TRAY_CCW = 0;*/
                run_stop_ice_tray();
                gu16DualCheckDelay = 20;    // 2�� ����
                gu8DualTrayStep++;     // 2.������ġ���� ����
            }
            /*else if(gu16DualCheckDelay <= 130 && gu16DualCheckDelay >= 50)*/
            /*else if(gu16DualCheckDelay <= 130 && gu16DualCheckDelay >= 50)*/
            else if(gu16DualCheckDelay <= 90 && gu16DualCheckDelay >= 70)
            {
                if(gu8IceLEV == 2)              // �̵��� Dual Open ����
                {
                    gu8DualTrayStep = 0;
                    gu16DualCheckDelay = 0;
                    gu8DualTrayCheckCNT = 0;
                    F_ErrTrayMotor_DualInital = 0;    // Tray �ν� �̵����̸� Tray M/S Error �ʱ�߻�? ����
                    gu8IceStep = STATE_0_STANDBY;
                    gu8InitStep = 0;
                    F_IceInit = 1;
                }
                else{}
            }

            break;

        case 2 :

            if(gu16DualCheckDelay == 0)
            {
                /*..hui [18-2-1���� 11:19:15] Ʈ���� Ż�� ���� �̵�..*/
                /*pMOTOR_ICE_TRAY_CW = 0;*/
                /*pMOTOR_ICE_TRAY_CCW = 1;*/
                run_down_ice_tray();
                /*gu16DualCheckDelay = 150;*/   // Ż�� 15�� �̵�
                gu16DualCheckDelay = 250;   // Ż�� 15�� �̵�
                gu8DualTrayStep++;          // 3.CCW
            }
            else{}

            break;

        case 3 :

            if(gu16DualCheckDelay == 0)
            {
                /*pMOTOR_ICE_TRAY_CW = 0;*/
                /*pMOTOR_ICE_TRAY_CCW = 0;*/
                run_stop_ice_tray();
                gu16DualCheckDelay = 3000;     // 5�� ����
                gu8DualTrayStep++;              // 4.Ż����ġ���� ����
            }
            /*else if(gu16DualCheckDelay <= 130 && gu16DualCheckDelay >= 50)*/
            else if(gu16DualCheckDelay <= 220 && gu16DualCheckDelay >= 80)
            {
                if(gu8IceLEV == 2)              // �̵��� Dual Open ����
                {
                    gu8DualTrayStep = 0;
                    gu16DualCheckDelay = 0;
                    gu8DualTrayCheckCNT = 0;
                    F_ErrTrayMotor_DualInital = 0;  // Tray �ν� �̵����̸� Tray M/S Error �ʱ�߻�? ����
                    gu8IceStep = STATE_0_STANDBY;
                    gu8InitStep = 0;
                    F_IceInit = 1;
                }
            }
            else{}

            break;

        case 4 :

            if(gu16DualCheckDelay == 0)
            {
                gu8DualTrayStep = 0;
                if(++gu8DualTrayCheckCNT >= 3)
                {
                    Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 = SET;          // 3ȸ �õ��� Error
                    F_ErrTrayMotor_DualInital = 0;
                }
                else{}
            }
            else{}

            break;

        default :

            /*pMOTOR_ICE_TRAY_CW = 0;*/
            /*pMOTOR_ICE_TRAY_CCW = 0;*/
            run_stop_ice_tray();

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_micro_sw_movement(void)
{
    //------------------------------------------------- �������� ȸ��
    /*..hui [18-1-26���� 8:22:52] F_TrayMotorUP �� ���� F_TrayMotorCCW�� Ż����ġ.. ..*/
    /*..hui [18-1-26���� 8:23:08] F_TrayMotorUP �� �����δ� CCW�� ����..*/
    gu8_Tray_Motor_Direction = (U8)(((F_TrayMotorDOWN << 1) & 0x02) |
                                     (F_TrayMotorUP));

    switch(gu8_Tray_Motor_Direction)
    {
        case TRAY_MOTOR_STOP:

            /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
            /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
            run_stop_ice_tray();
            gu16_Err_Tray_Motor_Up_Total_Tmr = 0;
            gu16_Err_Tray_Motor_Down_Total_Tmr = 0;
            u8_Tray_up_moving_retry_timer = 0;
            gu16_Tray_down_moving_retry_timer = 0;

            break;

        case TRAY_MOTOR_CW_DIRECTION:

            /*..hui [18-2-6���� 1:32:40] CCW�� ���� 5�ʰ� ���� ������ ���¸� ���?..*/
            if(F_Tray_CCW_delay_finish == SET)
            {
                /*..hui [18-2-2���� 3:11:59] �������� �̵��� ���� ����..*/
                /*..hui [18-2-6���� 7:02:16] CW�� SET�Ǵ� ������ gu8IceStep�� 1�϶��ۿ� ����, ���� �����Ҷ�..*/
                check_error_tray_motor_up_operation();
            }
            else
            {
                /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
                /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
                run_stop_ice_tray();
            }

            break;

        case TRAY_MOTOR_CCW_DIRECTION:

            /*..hui [18-2-6���� 1:32:40] CCW�� ���� 5�ʰ� ���� ������ ���¸� ���?..*/
            /*..hui [18-2-6���� 8:18:30] CCW�� SET�Ǵ� ������ ����Ż��/����Ż����....*/
            if(F_Tray_CW_delay_finish == SET)
            {
                /*..hui [18-2-2���� 3:12:05] Ż�� ���� �̵��� ���� ����..*/
                check_error_tray_motor_down_retry_operation();
            }
            else
            {
                /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
                /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
                run_stop_ice_tray();
            }

            break;


        default:

            /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
            /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
            run_stop_ice_tray();

            break;
    }

    ice_make_system_up_move_reset();        // �������� �غ�����
    ice_make_system_down_move_reset();      // Ż������ �غ�����

    /*..hui [18-2-9���� 1:55:07] SW������ ���ÿ� SET�� ���? ����..*/
    if(F_TrayMotorUP == SET && F_TrayMotorDOWN == SET)
    {
        Bit18_Tray_Micro_SW_Up_Move_Error__E62 = SET;
    }
    else{}

    /*..hui [19-12-13���� 7:25:08] Ʈ���� ���� �� ���������� Ż�� ������ ���� �� ���� ī��Ʈ �ʱ�ȭ..*/
    if( gu8IceStep >= STATE_45_ICE_TAKE_OFF )
    {
        gu8_err_tray_down_acc_count = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_tray_motor_up_operation(void)
{
    /*..hui [18-2-6���� 5:25:47] Ż������ ���� �������� �̵� �� ��������..*/
    switch( gu8IceTrayLEV )
    {
        case ICE_TRAY_POSITION_ICE_MAKING:

            /*..hui [18-2-6���� 2:14:43] ���� �������� ������ ����..*/
            /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
            run_stop_ice_tray();

            F_TrayMotorUP = CLEAR;
            gu16_Err_Tray_Motor_Up_Total_Tmr = 0;
            gu8_Err_Tray_Up_Count = 0;
            u8_Tray_up_moving_retry_timer = 0;
            gu8_tray_up_contiunue_timer = 0;

            break;

        case ICE_TRAY_POSITION_MOVING:

            u8_Tray_up_moving_retry_timer = 0;
            /*pMOTOR_ICE_TRAY_CW = SET;*/
            if( gu8_ice_tray_mode == ICE_TRAY_MODE_NONE )
            {
                gu8_tray_up_contiunue_timer++;

                if( gu8_tray_up_contiunue_timer >= 10 )
                {
                    gu8_tray_up_contiunue_timer = 0;
                    run_up_ice_tray();
                }
                else{}
            }
            else
            {
                gu8_tray_up_contiunue_timer = 0;
            }

            break;

        case ICE_TRAY_POSITION_ICE_THROW:

            u8_Tray_up_moving_retry_timer++;

            if( u8_Tray_up_moving_retry_timer <= 50 )
            {
                /*pMOTOR_ICE_TRAY_CW = SET;*/
                run_up_ice_tray();
            }
            else if((u8_Tray_up_moving_retry_timer > 50) && (u8_Tray_up_moving_retry_timer <= 100))
            {
                /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
                run_stop_ice_tray();
            }
            else if((u8_Tray_up_moving_retry_timer > 100) && (u8_Tray_up_moving_retry_timer <= 150))
            {
                /*pMOTOR_ICE_TRAY_CW = SET;*/
                run_up_ice_tray();
            }
            /*else if((u8_Tray_up_moving_retry_timer > 150) && (u8_Tray_up_moving_retry_timer <= 200))
            {
                pMOTOR_ICE_TRAY_CW = CLEAR;
            }
            else if((u8_Tray_up_moving_retry_timer > 200) && (u8_Tray_up_moving_retry_timer <= 250))
            {
                pMOTOR_ICE_TRAY_CW = SET;
            }*/
            else
            {
                /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
                run_stop_ice_tray();

                F_TrayMotorUP = CLEAR;
                u8_Tray_up_moving_retry_timer = 0;
                gu8_tray_up_contiunue_timer = 0;

                gu8_Err_Tray_Up_Count++;

                /*if(gu8_Err_Tray_Up_Count >= 3)*/
                if(gu8_Err_Tray_Up_Count >= TRAY_UP_RETRY_COUNT)
                {
                    Bit18_Tray_Micro_SW_Up_Move_Error__E62 = SET;
                }
                else
                {
                    /*gu8_Err_Tray_Up_Count++;*/
                    F_Ice_Tray_Up_Move_Reset = SET;
                    ice_system_stop();

                    if( gu8_Err_Tray_Up_Count <= TRAY_UP_ICE_STUCK_COUNT )
                    {
                        /*..hui [25-3-17���� 4:18:38] ù 2ȸ�� �����ɸ� ��ȸ�� ���� �߰�..*/
                        bit_ice_stuck_back_state = SET;
                    }
                    else{}
                }
            }

            break;

        case ICE_TRAY_POSITION_ERROR:

            /*..hui [18-2-6���� 4:49:15] Ʈ���� ���� ������ ���? ����..*/
            /*..hui [18-2-6���� 4:51:07] �������� �������� ���� ���κ� ���ð��� ���� �κп��� ó��..*/
            /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
            run_stop_ice_tray();
            F_TrayMotorUP = CLEAR;
            u8_Tray_up_moving_retry_timer = 0;
            gu8_tray_up_contiunue_timer = 0;

            break;


        default:

            /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
            run_stop_ice_tray();
            F_TrayMotorUP = CLEAR;
            u8_Tray_up_moving_retry_timer = 0;
            gu8_tray_up_contiunue_timer = 0;

            break;
    }


    /*if( pMOTOR_ICE_TRAY_CW == SET )*/
    if( gu8_ice_tray_mode == ICE_TRAY_MODE_UP )
    {
        gu16_Err_Tray_Motor_Up_Total_Tmr++;

        if( gu16_Err_Tray_Motor_Up_Total_Tmr >= ICETRAY_CW_TIME )
        {
            /*pMOTOR_ICE_TRAY_CW = CLEAR;*/
            run_stop_ice_tray();

            F_TrayMotorUP = CLEAR;
            gu16_Err_Tray_Motor_Up_Total_Tmr = 0;

            gu8_Err_Tray_Up_Count++;

            /*if(gu8_Err_Tray_Up_Count >= 3)*/
            if(gu8_Err_Tray_Up_Count >= TRAY_UP_RETRY_COUNT)
            {
                Bit18_Tray_Micro_SW_Up_Move_Error__E62 = SET;
            }
            else
            {
                /*gu8_Err_Tray_Up_Count++;*/
                F_Ice_Tray_Up_Move_Reset = SET;
                ice_system_stop();

                if( gu8_Err_Tray_Up_Count <= TRAY_UP_ICE_STUCK_COUNT )
                {
                    /*..hui [25-3-17���� 4:18:38] ù 2ȸ�� �����ɸ� ��ȸ�� ���� �߰�..*/
                    bit_ice_stuck_back_state = SET;
                }
                else{}
            }
        }
        else{}
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_tray_motor_down_retry_operation(void)
{
    /*..hui [18-2-6���� 8:26:55] �������� Ż������ �̵� �� ��������....*/
    switch(gu8IceTrayLEV)
    {
        case ICE_TRAY_POSITION_ICE_MAKING:


            /*..hui [18-2-6���� 8:27:13] 5�� �̻� ���� ������ �� �õ� ���? ����..*/
            gu16_Tray_down_moving_retry_timer++;

            if(gu16_Tray_down_moving_retry_timer <= 250)
            {
                run_down_ice_tray();
            }
            else if((gu16_Tray_down_moving_retry_timer > 250) && (gu16_Tray_down_moving_retry_timer <= 300))
            {
                /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
                run_stop_ice_tray();
            }
            else if((gu16_Tray_down_moving_retry_timer > 300) && (gu16_Tray_down_moving_retry_timer <= 550))
            {
                /*pMOTOR_ICE_TRAY_CCW = SET;*/
                run_down_ice_tray();
            }
            else
            {
                /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
                run_stop_ice_tray();
                F_TrayMotorDOWN = CLEAR;
                gu16_Tray_down_moving_retry_timer = 0;

                gu8_Err_Tray_Down_Count++;
                gu8_err_tray_down_acc_count++;

                if(gu8_Err_Tray_Down_Count >= 3 || gu8_err_tray_down_acc_count >= 10)
                {
                    /*Bit18_Tray_Micro_SW_Up_Move_Error__E62 = SET;*/
                    Bit19_Tray_Micro_SW_Down_Move_Error__E63 = SET;
                }
                else
                {
                    /*gu8_Err_Tray_Down_Count++;*/
                    F_Ice_Tray_Down_Move_Reset = SET;
                    ice_system_stop();
                }
            }

            break;

        case ICE_TRAY_POSITION_MOVING:

            gu16_Tray_down_moving_retry_timer = 0;
            /*pMOTOR_ICE_TRAY_CCW = SET;*/
            run_down_ice_tray();

            break;

        case ICE_TRAY_POSITION_ICE_THROW:

            /*..hui [18-2-6���� 2:14:43] ���� �������� ������ ����..*/
            /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
            run_stop_ice_tray();
            F_TrayMotorDOWN = CLEAR;
            gu16_Err_Tray_Motor_Down_Total_Tmr = 0;
            gu8_Err_Tray_Down_Count = 0;
            gu16_Tray_down_moving_retry_timer = 0;

            break;

        case ICE_TRAY_POSITION_ERROR:

            /*..hui [18-2-6���� 4:49:15] Ʈ���� ���� ������ ���? ����..*/
            /*..hui [18-2-6���� 4:51:07] �������� �������� ���� ���κ� ���ð��� ���� �κп��� ó��..*/
            /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
            run_stop_ice_tray();
            F_TrayMotorDOWN = CLEAR;
            gu16_Tray_down_moving_retry_timer = 0;

            break;


        default:

            /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
            run_stop_ice_tray();
            F_TrayMotorDOWN = CLEAR;
            gu16_Tray_down_moving_retry_timer = 0;

            break;
    }


    /*if(pMOTOR_ICE_TRAY_CCW == SET)*/
    if( gu8_ice_tray_mode == ICE_TRAY_MODE_DOWN )
    {
        gu16_Err_Tray_Motor_Down_Total_Tmr++;

        if(gu16_Err_Tray_Motor_Down_Total_Tmr >= ICETRAY_CCW_TIME)
        {
            /*pMOTOR_ICE_TRAY_CCW = CLEAR;*/
            run_stop_ice_tray();
            F_TrayMotorDOWN = CLEAR;
            gu16_Err_Tray_Motor_Down_Total_Tmr = 0;

            gu8_Err_Tray_Down_Count++;
            gu8_err_tray_down_acc_count++;

            if(gu8_Err_Tray_Down_Count >= 3 || gu8_err_tray_down_acc_count >= 10)
            {
                /*Bit18_Tray_Micro_SW_Up_Move_Error__E62 = SET;*/
                Bit19_Tray_Micro_SW_Down_Move_Error__E63 = SET;
            }
            else
            {
                /*gu8_Err_Tray_Down_Count++;*/
                F_Ice_Tray_Down_Move_Reset = SET;
                ice_system_stop();
            }
        }
        else{}
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_make_system_up_move_reset(void)
{
    U16 mu16_delay_time = 0;

    if( gu8_Err_Tray_Up_Count <= TRAY_UP_ICE_STUCK_COUNT )
    {
        /*..hui [25-3-17���� 3:59:26] ù 5ȸ�� 1������..*/
        mu16_delay_time = TRAY_UP_ICE_STUCK_DELAY_TIME;     // 1�� ���?
    }
    else
    {
        mu16_delay_time = TRAY_UP_RESET_DELAY_TIME;         // 90��
    }

    if(F_Ice_Tray_Up_Move_Reset == SET)
    {
        gu16_Ice_Tray_Up_Reset_Delay_Tmr++;

        /*if(gu16_Ice_Tray_Up_Reset_Delay_Tmr >= TRAY_UP_RESET_DELAY_TIME)*/
        if(gu16_Ice_Tray_Up_Reset_Delay_Tmr >= mu16_delay_time)
        {
            if( gu8_Err_Tray_Up_Count <= 2 )
            {
                ice_stuck_reset();
                F_Ice_Tray_Up_Move_Reset = CLEAR;
                /*..hui [25-3-17���� 4:20:05] Ʈ���� ������ �ٽ� ����..*/
                /*run_down_ice_tray();*/
                down_tray_motor();
            }
            else
            {
                ice_system_reset();
                F_Ice_Tray_Up_Move_Reset = CLEAR;
            }
        }
        else
        {
            /*..hui [18-2-13���� 3:24:13] 10�� ����߿�? ���� ���ͽ� �ϴ��� ����....*/
            if(gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING)
            {
                ice_system_reset();
                F_Ice_Tray_Up_Move_Reset = CLEAR;
            }
            else{}
        }
    }
    else
    {
        gu16_Ice_Tray_Up_Reset_Delay_Tmr = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_make_system_down_move_reset(void)
{
    over_ice_making_check();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void over_ice_making_check(void)
{
    F_over_ice_check_enable = F_Ice_Tray_Down_Move_Reset;

    if(F_over_ice_check_enable != SET || Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET || Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET)
    {
        gu16_Ice_Tray_Down_Reset_Delay_Tmr = 0;
        gu16_over_ice_melt_timer = 0;
        gu8_over_ice_melt_proc = 0;
        gu8_over_ice_melt_operation_count = 0;
        //F_over_ice_melt_mode_cold_water_valve_out = CLEAR;
        F_Over_Ice_Heater_State = CLEAR;
    }
    else
    {
        gu16_Ice_Tray_Down_Reset_Delay_Tmr++;

        if(gu16_Ice_Tray_Down_Reset_Delay_Tmr >= TRAY_ERROR_STANDBY_TIME)   //10min
        {
            gu16_Ice_Tray_Down_Reset_Delay_Tmr = TRAY_ERROR_STANDBY_TIME;

            over_ice_making_melt_proc();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void over_ice_making_melt_proc(void)
{
    /*..hui [18-2-6���� 9:42:36] �������Ȱ� ���̴��߿� ������ Ʈ���� ���� ���͵Ǹ� �ϴ��� ����..*/
    if(gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW)
    {
        ice_system_reset();
        F_Ice_Tray_Down_Move_Reset = CLEAR;
    }
    else{}


    switch(gu8_over_ice_melt_proc)
    {
        case 0:

            gu16_over_ice_melt_timer = 0;
            gu8_over_ice_melt_proc++;

            break;

        case 1:

            /*..hui [18-2-6���� 9:16:17] ���� 10�ʵ��� �ü� �޼����? ON�Ѵ�..*/
            gu16_over_ice_melt_timer++;

            /*if(gu16_over_ice_melt_timer >= 100)*/
            /*..hui [23-9-22���� 11:26:29] 15�ʷ� �ø�.. �����ܾ��̽� ���?..*/
            if(gu16_over_ice_melt_timer >= 150)
            {
                F_IceVV = CLEAR;
                gu16_over_ice_melt_timer = 0;
                gu8_over_ice_melt_proc++;
            }
            else
            {
                F_IceVV = SET;
            }

            F_Over_Ice_Heater_State = CLEAR;

            break;

        case 2:

            /*..hui [18-2-6���� 9:21:25] �ü� �Լ��ϰ� 20�ʵ��� Ż�����͸� �����Ѵ�..*/
            gu16_over_ice_melt_timer++;

            /*..hui [20-4-21���� 7:15:57] ������ ���� 10�ʷ� ����..*/
            /*..hui [20-4-21���� 7:22:24] AIS30�� Ż���� �ʱ� OFF ���� �����ϹǷ� �ٽ� 15�ʷ�....*/
            /*if(gu16_over_ice_melt_timer >= 150)*/
            /*if(gu16_over_ice_melt_timer >= 6000)*/
            /*..hui [23-9-22���� 11:26:49] Ż������ ���� ����.. 20�е��� ���?..*/
            if(gu16_over_ice_melt_timer >= 12000)
            {
                F_Over_Ice_Heater_State = CLEAR;
                gu16_over_ice_melt_timer = 0;
                gu8_over_ice_melt_proc++;
            }
            else
            {
                F_Over_Ice_Heater_State = SET;
            }

            break;


        case 3:

            gu16_over_ice_melt_timer = 0;
            gu8_over_ice_melt_proc++;

            F_Over_Ice_Heater_State = CLEAR;

            break;

        case 4:

            /*..hui [18-2-6���� 9:23:11] 5�ʵ��� �ü� �޼����? ON..*/
            gu16_over_ice_melt_timer++;

            if(gu16_over_ice_melt_timer >= 50)
            {
                F_IceVV = CLEAR;
                gu16_over_ice_melt_timer = 0;
                gu8_over_ice_melt_proc++;
            }
            else
            {
                F_IceVV = SET;
            }

            F_Over_Ice_Heater_State = CLEAR;

            break;

        case 5:

            /*..hui [18-2-6���� 9:23:58] 10�е��� ���?..*/
            gu16_over_ice_melt_timer++;

            if(gu16_over_ice_melt_timer >= 6000)
            {
                /*..hui [18-2-6���� 9:25:47] 10�е��� ����Ŀ�? �ٽ� �޼����? 5�� ON�Ѵ�..*/
                gu16_over_ice_melt_timer = 0;
                gu8_over_ice_melt_proc = 3;

                /*..hui [18-2-6���� 9:29:04] �� 9�� �뷫 90�е��� ����..*/
                gu8_over_ice_melt_operation_count++;

                /*..hui [18-2-6���� 9:30:30] 90�� ���� ���� �� CCW ���� �ѹ� �� ����..*/
                if(gu8_over_ice_melt_operation_count >= 10)
                {
                    ice_system_reset();
                    F_Ice_Tray_Down_Move_Reset = CLEAR;

                    if(gu8IceTrayLEV != ICE_TRAY_POSITION_ICE_THROW)
                    {
                        F_TrayMotorUP = CLEAR;
                        F_TrayMotorDOWN = SET;
                    }
                    else{}
                }
                else{}
            }
            else{}

            F_Over_Ice_Heater_State = CLEAR;

            break;

        default:

            gu8_over_ice_melt_proc = 0;
            gu8_over_ice_melt_operation_count = 0;
            gu16_over_ice_melt_timer = 0;

            break;

    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_system_reset(void)
{
    F_Safety_Routine = CLEAR;
    gu8IceStep = STATE_0_STANDBY;
    gu8InitStep = 0;

    F_IceHeater = CLEAR;
    F_IceVV = CLEAR;

    /*..hui [18-3-22���� 10:04:37] CCW ���� �̵��߿��� ������ ����������.. ����Ż�� ����..������ ª�Ҵ�....*/
    F_IceInit = SET;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_stuck_reset(void)
{
    F_Safety_Routine = CLEAR;
    gu8IceStep = STATE_0_STANDBY;
    gu8InitStep = 0;

    F_IceHeater = CLEAR;
    F_IceVV = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_system_stop(void)
{
    F_Safety_Routine = SET;
    //F_IceMakeGo = CLEAR;
    //F_IceInit = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void down_tray_motor(void)
{
    F_TrayMotorUP = CLEAR;
    F_TrayMotorPreUP = CLEAR;
    F_TrayMotorDOWN = SET;
    F_TrayMotorPreDOWN = SET;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void up_tray_motor(void)
{
    F_TrayMotorUP = SET;
    F_TrayMotorPreUP = SET;
    F_TrayMotorDOWN = CLEAR;
    F_TrayMotorPreDOWN = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_ice_system_ok(void)
{
    if( Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == CLEAR
        && Bit18_Tray_Micro_SW_Up_Move_Error__E62 == CLEAR
        && Bit19_Tray_Micro_SW_Down_Move_Error__E63 == CLEAR
        && F_Ice_Tray_Up_Move_Reset == CLEAR
        && F_Ice_Tray_Down_Move_Reset == CLEAR
        && F_Safety_Routine == CLEAR
        && gu8_Err_Tray_Down_Count == 0
        && gu8_Err_Tray_Up_Count == 0 )
    {
        gu8_ice_system_ok = SET;
    }
    else
    {
        gu8_ice_system_ok = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_tray_motor(void)
{
    F_TrayMotorUP = CLEAR;
    F_TrayMotorPreUP = CLEAR;
    F_TrayMotorDOWN = CLEAR;
    F_TrayMotorPreDOWN = CLEAR;
}





