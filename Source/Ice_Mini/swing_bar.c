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
#include    "swing_bar.h"
#include    "Packet_Match.h"
void output_swing_bar(void);


//===================================== ��������
bit F_CristalIce;
bit F_Cristal;
U8 gu8_cristal_timer;


U8 onon;
U8 offoff;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_swing_bar(void)
{
    if(gu8_cristal_timer > 0)
    {
        gu8_cristal_timer--;
    }
    else{}

    if(Bit2_Ice_Operation_Disable_State == SET
    || F_ErrTrayMotor_DualInital == SET
    || F_Safety_Routine == SET)
    {
        F_CristalIce = 0;
        pSWING_BAR = 0;
        return;
    }
    else{}


    if(F_CristalIce != SET)
    {
        gu8_cristal_timer = 0;
        pSWING_BAR = 0;                              // ����������
        return;
    }
    else{}

    #if 0
    if( gu8IceStep >= STATE_11_WAIT_ROOM_WATER_FULL && gu8IceStep < STATE_31_MAIN_ICE_MAKING )
    {
        gu8_cristal_timer = 0;
        pSWING_BAR = 1;                              // ����������
        return;
    }
    else{}
    #endif

    if(gu16IceMakeTime <= 5)
    {
        gu8_cristal_timer = 0;
        pSWING_BAR = 0;                              // ����������
        return;
    }
    else{}

    if(gu8_cristal_timer == 0 && gu8IceStep == STATE_31_MAIN_ICE_MAKING)          // �������� ������ ����
    {
        F_Cristal = !F_Cristal;

        if(F_Cristal == SET)
        {
            // gu8_cristal_timer = CRISTAL_ON;
            if(GetB2SwingbarOn() > 0)
            {
                gu8_cristal_timer = GetB2SwingbarOn();
            }
            else
            {
                gu8_cristal_timer = CRISTAL_ON;
            }

            pSWING_BAR = 1;
        }
        else
        {
            // gu8_cristal_timer = CRISTAL_OFF;
            if(GetB2SwingbarOff() > 0)
            {
                gu8_cristal_timer = GetB2SwingbarOff();
            }
            else
            {
                gu8_cristal_timer = CRISTAL_OFF;
            }
            pSWING_BAR = 0;
        }
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


