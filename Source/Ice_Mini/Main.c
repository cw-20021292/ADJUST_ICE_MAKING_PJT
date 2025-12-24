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
#include    "Main.h"
#include    "App_Comm.h"

void main(void);
void Sync_50MS(void);
void Sync_100MS(void);
void wifi(void);
void check_adc(void);

extern void eeprom_initial();
extern void diplay_test_start();
extern void Display_test_step_Handler();

extern void Main_PBA_Test_Mode_Start();
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void main(void)
{
    System_ini();
    Uart_Init();

    while(1)
    {
        WDTE = (U8)0xAC;

        if(u8FactoryTestMode > 0)
        {
            Sync_100MS();

            if(u8FactoryTestMode == PCB_TEST_MODE)
            {
                Front_Communication();
                Pcb_Test_Main();
                ProcessVoice_Main();
                wifi();
            }
            else if(u8FactoryTestMode == DISPLAY_TEST_MODE)
            {
                Front_Communication();
                /* 메인프론트, 서브프론트 검사 다시 구분 250718 CH.PARK */
                #ifdef _DISPLAY_FCT_SUB_LINE_
                Display_test_step_Handler();
                #else
                Display_Test_Main();
                #endif
                ProcessVoice_Main();
            }
            else /*if(u8FactoryTestMode == UART_TEST_MODE)*/
            {
                if( gu8_uart_test_mode == INCLUDE_FRNOT_UART_TEST
                || gu8_uart_test_mode == NOT_INCLUDE_FRONT_UART_TEST )
                {
                    Front_Communication();
                }
                else{}

                Uart_Test_Main();
                ProcessVoice_Main();
                wifi();
            }
        }
        else
        {
            Sync_50MS();
            Front_Communication();

            Sync_100MS();
            Input();
            Mode_Control();
            Ice_Make_Process();
            Make_Mode_Decision();
            Heating_Control();
            flushing_main();
            Output();
            Error_Control();
            Display_Control();
            Front_Communication();
            ProcessVoice_Main();
            self_test();

            Comm_Packet_Handler();

            Save_Eeprom_Data();
            wifi();

            #if CONFIG_MMI
                Pc_Communication();
            #endif
        }
    }

}/* --- End of main() --- */

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Sync_50MS(void)
{
    while(u8CountSync < 50)
    {
        check_adc();
        WifiControlProcess(WIFI_TIME_WHILE);
    }

    /*u8CountSync = CLEAR;*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Sync_100MS(void)
{
    while(u8CountSync < 100)
    {
        check_adc();
        WifiControlProcess(WIFI_TIME_WHILE);
    }

    u8CountSync = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi(void)
{
    WifiControlProcess(WIFI_TIME_100MS);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_adc(void)
{
    if( F_ADC_Check == SET )
    {
        F_ADC_Check = CLEAR;
        AD_Conversion();
        /*..hui [23-9-19占쏙옙占쏙옙 11:27:38] 占쌤깍옙 占쏙옙占쏙옙 1占쏙옙 占쌩곤옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙 占쏙옙占쏙옙..*/
        get_final_small_amb_temp();
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




