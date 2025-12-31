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
#include    "display_led_icon.h"
#include    "work_ice_make.h"

/**********************************************************************************************************************/
void icon_led_output(void);
/**********************************************************************************************************************/
/* ����Ʈ ���� ������ LED ���� */
void right_icon_led_output(void);
void wifi_pairing_display(void);
void sunny_icon_out(void);
void cloud_icon_out(void);
void rain_icon_out(void);
void percent_icon_out(void);
void liter_L_icon_out(void);
void ml_icon_out(void);
void RIGHT_SEG_DOT_OUTPUT(void);
void filter_clean_txt_out (void);
/**********************************************************************************************************************/
/* ����Ʈ �»�� ������ LED ���� */
void left_icon_led_output(void);
void ice_full_text_out(void);
void uv_ster_text_out(void);
void hot_ster_text_out(void);
void sleep_icon_out(void);
void step_text_out(void);
void clock_colon_icon_out(void);
void celcius_oC_icon_out(void);
/**********************************************************************************************************************/
/* ����Ʈ �ϴܺ� ������ LED ���� */
void under_icon_led_output(void);
void UNDER_ICON_ICE_TYPE_OUTPUT(void);
void UNDER_ICON_COLD_OFF_OUTPUT(void);
void ice_lock_icon_output(void);
void hot_lock_icon_output(void);
void comp_operation_dot_output(void);
/**********************************************************************************************************************/
/* ����Ʈ �ϴܺ� �ؽ�Ʈ LED ���� */
void under_text_led_output(void);
void ice_size_text_out(void);
void cold_temp_text_out(void);
void whether_icon_out(void);
/* Cody Water Line Clean Service */
void cody_service_water_icon(void);
/**********************************************************************************************************************/
extern bit F_Ice_Lock;
extern bit F_Hot_Lock;
extern bit bit_ice_size;
extern bit bit_setting_mode_start;
extern bit bit_time_setting_start;
extern U8 gu8_cup_led_select;
extern U16 gu16_water_select_return_time;
extern bit bit_myWater_setting_start ;
extern bit bit_first_time_setting;
extern U8 gu8_clock_hide_state;
extern U16 gu16_cold_off_flick_timer;
extern U8 gu8_indicator_flick_timer;
extern U16 gu16_cold_off_flick_timer;
extern U16 gu16_hot_off_flick_timer;
extern U16 gu16_all_lock_flick_timer;
extern U16 gu16_low_water_flick_timer;
extern U16 gu16_ice_off_flick_timer;
extern U16 gu16_icewater_off_flick_timer;
extern U16 gu16_water_extract_flick_timer;
extern U8 gu8_indicator_flick_timer;
extern WATER_OUT_STEP gu8_Water_Out_Step;
extern U16 gu16_WaterQuantity_half;
extern U16 gu16_WaterQuantity_one;
extern U16 gu16_WaterQuantity_two;
extern U16 gu16_WaterQuantity_four;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void icon_led_output(void)
{
    left_icon_led_output();		// ['C], [���], [:], [�ܰ�]
    right_icon_led_output();	// [WIFI], [����], [DOT], [ml], [L]
    under_text_led_output();	// [�������], [�ü�����], [�Ϲ�/����], [�ü�OFF]
    under_icon_led_output();	// [COMP LED], [�ڹ���]
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void left_icon_led_output(void)
{
    ice_full_text_out();
    uv_ster_text_out();			/* UV��� */
    hot_ster_text_out();		/* ���»�� */
    sleep_icon_out();			/* ��ħ��� ǥ�� */
    step_text_out();			/* (����) �ܰ� ǥ�� */
    clock_colon_icon_out();		/* : �ð� �ݷ� ǥ�� */
    celcius_oC_icon_out();		/* �µ� 'C ǥ�� */
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_full_text_out(void)
{
	if(bit_display_sleep_start == SET)
	{
		Bit0_Front_Left_Led_Ice_Full_Text = CLEAR;
		Bit1_Front_Left_Led_Ice_Shortae_Text = CLEAR;
	}
	else if(bit_setting_mode_start == CLEAR)
	{
		if(F_IceFull == SET)
		{
			Bit0_Front_Left_Led_Ice_Full_Text = SET;
		}
		else
		{
			Bit0_Front_Left_Led_Ice_Full_Text = CLEAR;
		}

		if(F_IceLack == SET && F_IceOn == SET && F_IceFull == CLEAR)
		{
			Bit1_Front_Left_Led_Ice_Shortae_Text = SET;
		}
		else
		{
			Bit1_Front_Left_Led_Ice_Shortae_Text = CLEAR;
		}
	}
	else
	{
		/* �������� ���� ������ �� 250224 CH.PARK */
		Bit0_Front_Left_Led_Ice_Full_Text = CLEAR;
		Bit1_Front_Left_Led_Ice_Shortae_Text = CLEAR;
	}

	if( gu8_Led_Display_Step == LED_Display__SLEEP )
	{
		set_duty_percent( DIMMING__PERCENT_ICE_SHORTAGE_TEXT, SLEEP_MODE_DIMMING_PERCENT );
		set_duty_percent( DIMMING__PERCENT_ICE_FULL_TEXT, SLEEP_MODE_DIMMING_PERCENT );
	}
	else
	{
		set_duty_percent( DIMMING__PERCENT_ICE_SHORTAGE_TEXT, top_small_led_percent );
		set_duty_percent( DIMMING__PERCENT_ICE_FULL_TEXT, top_small_led_percent );
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uv_ster_text_out(void)
{
	if(bit_display_sleep_start == SET)
	{
		Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;
		Bit0_Front_Left_Led_Eff_Faucet_Text = CLEAR;
		Bit1_Front_Left_Led_Ice_Faucet_Text = CLEAR;
		Bit2_Front_Left_Led_Ice_Tray_Text = CLEAR;
		Bit3_Front_Left_Led_Ice_Storage_Box_Text = CLEAR;
	}
	else if(bit_display_sleep_start == SET)
	{
		Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;
	}
	else if(bit_setting_mode_start == CLEAR)
	{
		if((bit_uv_ice_tray_out == SET)
		|| (bit_uv_ice_tank_out == SET)
		|| (bit_uv_ice_faucet_out == SET)
		|| (bit_uv_extract_faucet_out == SET)		/* UV�� �ϳ��� �����ִٸ� [UV���] LED ����. 250225 CH.PARK */
		)
		{
			Bit2_Front_Left_Led_UV_Ster_Text = SET;
		}
		else
		{
			Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;
		}

		Bit0_Front_Left_Led_Eff_Faucet_Text = bit_uv_extract_faucet_out;
		Bit1_Front_Left_Led_Ice_Faucet_Text = bit_uv_ice_faucet_out;
		Bit2_Front_Left_Led_Ice_Tray_Text = bit_uv_ice_tray_out;
		Bit3_Front_Left_Led_Ice_Storage_Box_Text = bit_uv_ice_tank_out;
	}
	else
	{
		Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;
		Bit0_Front_Left_Led_Eff_Faucet_Text = CLEAR;
		Bit1_Front_Left_Led_Ice_Faucet_Text = CLEAR;
		Bit2_Front_Left_Led_Ice_Tray_Text = CLEAR;
		Bit3_Front_Left_Led_Ice_Storage_Box_Text = CLEAR;
	}

	if( gu8_Led_Display_Step == LED_Display__SLEEP )
	{
		set_duty_percent( DIMMING__PERCENT_UV_STER_TEXT, SLEEP_MODE_DIMMING_PERCENT );
		set_duty_percent( DIMMING__PERCENT_EXT_FAUCET_TEXT, SLEEP_MODE_DIMMING_PERCENT );
		set_duty_percent( DIMMING__PERCENT_ICE_FAUCET_TEXT, SLEEP_MODE_DIMMING_PERCENT );
		set_duty_percent( DIMMING__PERCENT_ICE_TRAY_TEXT, SLEEP_MODE_DIMMING_PERCENT );
		set_duty_percent( DIMMING__PERCENT_ICE_STORAGE_BOX_TEXT, SLEEP_MODE_DIMMING_PERCENT );
	}
	else
	{
		set_duty_percent( DIMMING__PERCENT_UV_STER_TEXT, big_ster_led_percent );
		set_duty_percent( DIMMING__PERCENT_EXT_FAUCET_TEXT, small_ster_led_percent );
		set_duty_percent( DIMMING__PERCENT_ICE_FAUCET_TEXT, small_ster_led_percent );
		set_duty_percent( DIMMING__PERCENT_ICE_TRAY_TEXT, small_ster_led_percent );
		set_duty_percent( DIMMING__PERCENT_ICE_STORAGE_BOX_TEXT, small_ster_led_percent );
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_ster_text_out(void)
{
	if(bit_display_sleep_start == SET)
	{
		Bit3_Front_Left_Led_Hot_Ster_Text = CLEAR;
	}
    else if( gu8_Led_Display_Step == LED_Display__TRAY_CLEAN )
    {
        if( bit_ice_tank_ster_start == SET )
        {
            Bit3_Front_Left_Led_Hot_Ster_Text = SET;
        }
        else
        {
            Bit3_Front_Left_Led_Hot_Ster_Text = CLEAR;
        }
    }
    else
    {
        Bit3_Front_Left_Led_Hot_Ster_Text = CLEAR;
    }

	if( gu8_Led_Display_Step == LED_Display__SLEEP )
	{
		set_duty_percent( DIMMING__PERCENT_HOT_STER_TEXT, DIIMMING__10_PERCENT );
	}
	else
	{
		set_duty_percent( DIMMING__PERCENT_HOT_STER_TEXT, big_ster_led_percent );
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void sleep_icon_out(void)
{
	if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
		if(bit_display_sleep_start == SET)
		{
			set_duty_percent( DIMMING__PERCENT_SLEEP_ICON, top_small_led_percent );
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_SLEEP_ICON, SLEEP_MODE_DIMMING_PERCENT );
		}
    }
    else
    {
        set_duty_percent( DIMMING__PERCENT_SLEEP_ICON, top_small_led_percent );
    }

	if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
		if(bit_display_sleep_start == SET)				/* ��ħ����� ���� �Ѿߵ� (��ħ��� �켱���� ����) 250827 CH.PARK */
		{
			Bit4_Front_Left_Led_Sleep_Icon = SET;
		}
    	else if(bit_30_min_no_use_start == SET)
	    {
	        Bit4_Front_Left_Led_Sleep_Icon = CLEAR;		/* ������ ��ֵ� ������ ���� ��ħ��� ������ OFF 250807 */
	    }
		else
		{
        	Bit4_Front_Left_Led_Sleep_Icon = SET;
		}
		return;
    }
	else {}

	if( bit_sleep_mode_enable == SET )
	{
		Bit4_Front_Left_Led_Sleep_Icon = SET;
	}
	else
	{
		Bit4_Front_Left_Led_Sleep_Icon = CLEAR;
	}

#if 0
	if(bit_setting_mode_start == SET)
	{
		/* ������� ���� ǥ�� �߰�. 250224 CH.PARK */
		if(bit_sleep_mode_enable == SET)
		{
			Bit4_Front_Left_Led_Sleep_Icon = SET;
		}
		else
		{
			Bit4_Front_Left_Led_Sleep_Icon = CLEAR;
		}
	}
	else
	{
		if(bit_display_sleep_start == SET)
		{
			Bit4_Front_Left_Led_Sleep_Icon = SET;
		}
		else
		{
			Bit4_Front_Left_Led_Sleep_Icon = CLEAR;
		}
	}

	if( gu8_Led_Display_Step == LED_Display__SLEEP)
	{
		if(bit_display_sleep_start == SET)
		{
			set_duty_percent( DIMMING__PERCENT_SLEEP_ICON, top_small_led_percent );
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_SLEEP_ICON, SLEEP_MODE_DIMMING_PERCENT );
		}
	 }
	 else
	 {
		set_duty_percent( DIMMING__PERCENT_SLEEP_ICON, top_small_led_percent );
	 }
#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void step_text_out(void)
{
    if(GetErrorCount() >= 10)
    {
        Bit5_Front_Left_Led_Step_Text = SET;
    }
    else
    {
        Bit5_Front_Left_Led_Step_Text = CLEAR;
    }
	// Bit5_Front_Left_Led_Step_Text = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void clock_colon_icon_out(void)
{
	if(bit_display_sleep_start == SET)
	{
		Bit6_Front_Left_Led_Clock_Colon_Icon = CLEAR;
	}
	else if(bit_time_setting_start == SET)
	{
		Bit6_Front_Left_Led_Clock_Colon_Icon = SET;
	}
	else if(bit_setting_mode_start == SET)
	{
		Bit6_Front_Left_Led_Clock_Colon_Icon = CLEAR;
	}
	else if( bit_first_time_setting == SET
	&& ( gu8_cup_led_select == CLEAR )
	&& ( gu16_water_select_return_time == 0 )
	&& (bit_myWater_setting_start == 0)
	&& gu8_clock_hide_state == CLEAR
	&& F_WaterOut == CLEAR
	&& F_IceOut == CLEAR)
	{
		Bit6_Front_Left_Led_Clock_Colon_Icon = SET;
	}
	else
	{
		Bit6_Front_Left_Led_Clock_Colon_Icon = CLEAR;
	}

	if( gu8_Led_Display_Step == LED_Display__SLEEP )
	{
		set_duty_percent( DIMMING__PERCENT_CLOCK_COLON_ICON, SLEEP_MODE_DIMMING_PERCENT );
	}
	else
	{
		set_duty_percent( DIMMING__PERCENT_CLOCK_COLON_ICON, colon_dot_led_percent );
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void celcius_oC_icon_out(void)
{
	if( gu8_Led_Display_Step == LED_Display__SLEEP )
	{
		set_duty_percent( DIMMING__PERCENT_oC_ICON, SLEEP_MODE_DIMMING_PERCENT );
	}
	else
	{
		set_duty_percent( DIMMING__PERCENT_oC_ICON, middle_small_led_percent );
	}

	if(bit_display_sleep_start == SET)
	{
		Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
	}
	else if( bit_setting_mode_start == SET )
	{
		Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
	}
	else if((bit_first_time_setting == SET)
	&& ( gu8_cup_led_select == CLEAR )
	&& ( gu16_water_select_return_time == 0 )
	&& (bit_myWater_setting_start == 0)
	&& (gu8_clock_hide_state == CLEAR)
	&& (F_WaterOut == CLEAR)
	&& (F_IceOut == CLEAR)
	)
	{
		Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
	}
	else
	{
		if( u8IceOutState != ICE_SELECT__NONE )
		{
			Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
		}
		else
		{
			/* �ü�OFF ���� ǥ���� ���� 'C �� */
			if((Bit2_Cold_Off_Indicator != 0)
			|| (Bit0_Ice_Lock_Indicator != 0)
			|| (Bit6_Icewater_Off_Indicator != 0)
			)
			{
				Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
			}
			else
			{
				if(( bit_myWater_setting_start == SET )
				|| ( u8WaterOutState == HOT_WATER_SELECT )
				)
				{
					if(gu8_Water_Out_Step == STATE_20_HOT_PRE_HEATING_STATE)
					{
						Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
					}
					else if(gu8_Water_Out_Step == STATE_21_HOT_PRE_HEATING_BUFFER_DRAIN_STATE)
					{
						Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
					}
					else if(gu8_Water_Out_Step == STATE_22_HOT_PRE_HEATING_BUFFER_DRAIN_COMPLETE_STATE)
					{
						Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
					}
					else
					{
						if(my_recipe_select == MY_INDEX_MY1)
						{
							if(my_setting[RECIPE_MY1].temp == 6)
							{
								if(F_Cold_Enable == CLEAR)
								{
									Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
									return;
								}
								else {  }
							}
							else {  }
						}
						else if(my_recipe_select == MY_INDEX_MY2)
						{
							if(my_setting[RECIPE_MY2].temp == 6)
							{
								if(F_Cold_Enable == CLEAR)
								{
									Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
									return;
								}
								else {  }
							}
							else {  }
						}
						else if(my_recipe_select == MY_INDEX_MY3)
						{
							if(my_setting[RECIPE_MY3].temp == 6)
							{
								if(F_Cold_Enable == CLEAR)
								{
									Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
									return;
								}
								else {  }
							}
							else {  }
						}

						Bit7_Front_Left_Led_Celcius_oC_Icon = SET;
					}
				}
				else
				{
					if(u8WaterOutState == COLD_WATER_SELECT)
    				{
						if(F_Cold_Enable == SET)
						{
							Bit7_Front_Left_Led_Celcius_oC_Icon = SET;
						}
						else
						{
							Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
						}
					}
					else
					{
						Bit7_Front_Left_Led_Celcius_oC_Icon = SET;
					}
				}
			}
		}
	}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void right_icon_led_output(void)
{
    wifi_icon_output();

	whether_icon_out();
    percent_icon_out();
    liter_L_icon_out();
    ml_icon_out();
	RIGHT_SEG_DOT_OUTPUT();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_pairing_display(void)
{
    /*..hui [23-6-14���� 9:34:53] BLE�� ��� BLUE..*/
    if( gu8_ble_ap_mode == SET )
    {
        /*Bit1_Front_Right_Led_Wifi_Icon_White = CLEAR;*/

        if( gu8_wifi_disp_timer == 0 )
        {
            /*..hui [24-3-27���� 7:31:20] ���� �Ӌ� ȭ��Ʈ 10%�� ���� ����..���ڤӤ�..*/
            //Bit4_Led_Wifi_Icon_Blue = SET;
            Bit0_Front_Right_Led_Wifi_Icon_White = SET;
        }
        else if( gu8_wifi_disp_timer == 1 )
        {
            //Bit4_Led_Wifi_Icon_Blue = CLEAR;
            Bit0_Front_Right_Led_Wifi_Icon_White = CLEAR;
        }
        else if( gu8_wifi_disp_timer == 2 )
        {
            /*..hui [24-3-27���� 7:31:20] ���� �Ӌ� ȭ��Ʈ 10%�� ���� ����..���ڤӤ�..*/
            ///Bit4_Led_Wifi_Icon_Blue = SET;
            Bit0_Front_Right_Led_Wifi_Icon_White = SET;
        }
        else
        {
            //Bit4_Led_Wifi_Icon_Blue = CLEAR;
            Bit0_Front_Right_Led_Wifi_Icon_White = CLEAR;
        }
    }
    else
    {
        //Bit4_Led_Wifi_Icon_Blue = CLEAR;

        if( gu8_wifi_disp_timer == 0 )
        {
            Bit0_Front_Right_Led_Wifi_Icon_White = SET;
        }
        else if( gu8_wifi_disp_timer == 1 )
        {
            Bit0_Front_Right_Led_Wifi_Icon_White = CLEAR;
        }
        else if( gu8_wifi_disp_timer == 2 )
        {
            Bit0_Front_Right_Led_Wifi_Icon_White = SET;
        }
        else
        {
            Bit0_Front_Right_Led_Wifi_Icon_White = CLEAR;
        }
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void whether_icon_out(void)
{
	if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
        set_duty_percent( DIMMING__PERCENT_SUNNY_ICON, SLEEP_MODE_DIMMING_PERCENT );
        set_duty_percent( DIMMING__PERCENT_CLOUD_ICON, SLEEP_MODE_DIMMING_PERCENT );
        set_duty_percent( DIMMING__PERCENT_RAIN_ICON, SLEEP_MODE_DIMMING_PERCENT);
    }
    else
    {
        set_duty_percent( DIMMING__PERCENT_SUNNY_ICON, top_small_led_percent );
        set_duty_percent( DIMMING__PERCENT_CLOUD_ICON, top_small_led_percent );
        set_duty_percent( DIMMING__PERCENT_RAIN_ICON, top_small_led_percent);
    }

    /*..hui [25-3-28���� 11:38:13] ���� ������°� �ƴ� WiFi ������ ���·� ǥ������ ����..*/
    /*..hui [25-3-28���� 11:38:46] fota ���������� ��������ǰ� ������ɋ� ǥ�� ����..*/
    if( gu8_Wifi_Connect_State != WIFI_CONNECT )
    {
        Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
        Bit3_Front_Right_Led_Cloud_Icon = CLEAR;
        Bit4_Front_Right_Led_Rain_Icon = CLEAR;
        return;
    }
    else{}

    if( gu8_smart_image == SMART_ICON_NONE )
    {
        Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
        Bit3_Front_Right_Led_Cloud_Icon = CLEAR;
        Bit4_Front_Right_Led_Rain_Icon = CLEAR;
        return;
    }
    else{}

	if(bit_display_sleep_start == SET)
	{
		Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
        Bit3_Front_Right_Led_Cloud_Icon = CLEAR;
        Bit4_Front_Right_Led_Rain_Icon = CLEAR;
        return;
	}
	else {  }

    //sunny_icon_out();
    //cloud_icon_out();
    //rain_icon_out();

    if( gu8_smart_image == SMART_ICON_SUNNY )
    {
        Bit2_Front_Right_Led_Sunny_Icon = SET;
        Bit3_Front_Right_Led_Cloud_Icon = CLEAR;
        Bit4_Front_Right_Led_Rain_Icon = CLEAR;
    }
    else if( gu8_smart_image == SMART_ICON_CLOUDY )
    {
        Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
        Bit3_Front_Right_Led_Cloud_Icon = SET;
        Bit4_Front_Right_Led_Rain_Icon = CLEAR;
    }
    else /*if( gu8_smart_image == SMART_IMAGE_RAINY )*/
    {
        Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
        Bit3_Front_Right_Led_Cloud_Icon = CLEAR;
        Bit4_Front_Right_Led_Rain_Icon = SET;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void sunny_icon_out(void)
{
    Bit2_Front_Right_Led_Sunny_Icon = CLEAR;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cloud_icon_out(void)
{
    Bit3_Front_Right_Led_Cloud_Icon = CLEAR;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void rain_icon_out(void)
{
    Bit4_Front_Right_Led_Rain_Icon = CLEAR;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void percent_icon_out(void)
{

	set_duty_percent( DIMMING__PERCENT_PERCENT_ICON, middle_small_led_percent );

    if( gu8_Led_Display_Step == LED_Display__TRAY_CLEAN )
    {
        Bit5_Front_Right_Led_Percent_Icon = SET;
    }
    else if(gu8_Led_Display_Step == LED_Display__FLUSHING)
	{
		if(gu8_flushing_mode > FLUSHING_STANDBY_STATE)
		{
			Bit5_Front_Right_Led_Percent_Icon = SET;
		}
		else
		{
			Bit5_Front_Right_Led_Percent_Icon = CLEAR;
		}
	}
	else if( bit_self_test_start == SET )
	{
		Bit5_Front_Right_Led_Percent_Icon = SET;
	}
	else if(gu8_Led_Display_Step == LED_Display__WIFI_PAIRING)
	{
		 if( bit_display_wifi_error == SET || bit_display_last_error == SET )
		 {
			Bit5_Front_Right_Led_Percent_Icon = CLEAR;
		 }
		 else
		 {
			if(gu8_pairing_delay_timer >= PAIRING_DISPLAY_DELAY_TIME_100MS)
			{
				/*..hui [23-12-4?�후 2:14:01] ???��? ?��? ?????�면?��???? ?�센?��?? ????..*/
				Bit5_Front_Right_Led_Percent_Icon = SET;
			}
			else { Bit5_Front_Right_Led_Percent_Icon = CLEAR; }
		 }
	}
	else
	{
		if(F_WaterOut == SET)
		{
			if(my_recipe_select == MY_INDEX_DRIPCOFFEE && bit_myWater_setting_start == SET )
			{
				Bit5_Front_Right_Led_Percent_Icon = SET;
			}
			else
			{
				Bit5_Front_Right_Led_Percent_Icon = CLEAR;
			}
		}
		else
		{
			Bit5_Front_Right_Led_Percent_Icon = CLEAR;
		}
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void liter_L_icon_out(void)
{
	U16 mu16_amount = 0;

	if(bit_display_sleep_start == SET)
	{
		Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
	}
	else if(bit_setting_mode_start == SET)
	{
		Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
	}
	else if( ( gu8_cup_led_select == CLEAR )
	&& ( gu16_water_select_return_time == 0 )
	&& (bit_myWater_setting_start == 0)
	&& (gu8_clock_hide_state == CLEAR)
	&& (bit_first_time_setting == SET)
	&& (F_WaterOut == CLEAR)
	&& (F_IceOut == CLEAR)
	)
	{
		Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
	}
	else if((Bit2_Cold_Off_Indicator != 0) 			/* OFF �˸� ǥ�����̸� L ǥ�� ���� */
	|| (Bit0_Ice_Lock_Indicator != 0)
	|| (Bit6_Icewater_Off_Indicator != 0)
	)
	{
		Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
	}
	else
	{
		if(u8IceOutState == ICE_SELECT__ICE)
		{
			Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
		}
		else
		{
			if( F_WaterOut == SET )
			{
				/* �帳Ŀ�Ǵ� %�� ǥ�� */
				if(my_recipe_select == MY_INDEX_DRIPCOFFEE && bit_myWater_setting_start == SET )
				{
					Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
				}
				else
				{
					/* �������̸� ���� ���ⷮ�� �°� ml, L ǥ�� 250218 CH.PARK */
					mu16_amount = (U16)((U16)gu16_extract_display_cnt * 10);
					if(u8Extract_Continue == CLEAR)
					{
						if(mu16_amount < 1000)
						{
							Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
						}
						else
						{
							Bit6_Front_Right_Led_Liter_L_Icon = SET;
						}
					}
					else
					{
						if(mu16_amount < 1000)
						{
							Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
						}
						else
						{
							Bit6_Front_Right_Led_Liter_L_Icon = SET;
						}
					}
				}
			}
			else
			{
				//LSH zzang
				if(bit_myWater_setting_start == SET)
				{
					if( my_setting[my_recipe_select].use == SET
					&& my_setting[my_recipe_select].amount >= 1000)
					{
						Bit6_Front_Right_Led_Liter_L_Icon = SET;
					}
					else
					{
						Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
					}
				}
				else
				{
					/* 1L �̻���ʹ� 1.1, 1.2 ... �̷������� ǥ���ؾߵ� */
					if((gu8Cup_level == CUP_LEVEL_1_120ML && gu16_WaterQuantity_half >= 1000)
					|| (gu8Cup_level == CUP_LEVEL_2_250ML && gu16_WaterQuantity_one >= 1000)
					|| (gu8Cup_level == CUP_LEVEL_3_500ML && gu16_WaterQuantity_two >= 1000)
					|| (gu8Cup_level == CUP_LEVEL_4_1000ML && gu16_WaterQuantity_four >= 1000)
					)
					{
						if(u8IceOutState == ICE_SELECT__ICE_WATER)
						{
							Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
						}
						else
						{
							Bit6_Front_Right_Led_Liter_L_Icon = SET;
						}
					}
					else
					{
						Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
					}
				}
			}
		}
	}

	if( gu8_Led_Display_Step == LED_Display__SLEEP )
	{
		set_duty_percent( DIMMING__PERCENT_LITER_TEXT, SLEEP_MODE_DIMMING_PERCENT );
	}
	else
	{
		set_duty_percent( DIMMING__PERCENT_LITER_TEXT, middle_small_led_percent );
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ml_icon_out(void)
{
	U16 gu16_ml_display_cnt = 0;
	gu16_ml_display_cnt = (U16)(gu16_extract_display_cnt * 10);

	if(bit_display_sleep_start == SET)
	{
		Bit7_Front_Right_Led_ml_Icon = CLEAR;
	}
	else if(bit_setting_mode_start == CLEAR)
	{
		if( ( gu8_cup_led_select == CLEAR )
		&& ( gu16_water_select_return_time == 0 )
		&& (bit_myWater_setting_start == 0)
		&& (gu8_clock_hide_state == CLEAR)
		&& (bit_first_time_setting == SET)
		&& (F_WaterOut == CLEAR)
		&& (F_IceOut == CLEAR)
		)
		{
			Bit7_Front_Right_Led_ml_Icon = CLEAR;
		}
		else if((Bit2_Cold_Off_Indicator != 0)
		|| (Bit0_Ice_Lock_Indicator != 0)
		|| (Bit6_Icewater_Off_Indicator != 0)
		)
		{
			Bit7_Front_Right_Led_ml_Icon = CLEAR;
		}
		else
		{
			if(u8IceOutState == ICE_SELECT__ICE)
			{
				Bit7_Front_Right_Led_ml_Icon = CLEAR;
			}
			else
			{
				if(F_WaterOut == SET)
				{
					/* �帳Ŀ�Ǵ� %�� ǥ�� */
					if(my_recipe_select == MY_INDEX_DRIPCOFFEE && bit_myWater_setting_start == SET )
					{
						Bit7_Front_Right_Led_ml_Icon = CLEAR;
					}
					else
					{
						if(u8Extract_Continue == CLEAR)
						{
							if(gu16_ml_display_cnt >= 1000)
							{
								Bit7_Front_Right_Led_ml_Icon = CLEAR;
							}
							else
							{
								Bit7_Front_Right_Led_ml_Icon = SET;
							}
						}
						else
						{
							if(gu16_ml_display_cnt >= 1000)
							{
								Bit7_Front_Right_Led_ml_Icon = CLEAR;
							}
							else
							{
								Bit7_Front_Right_Led_ml_Icon = SET;
							}
						}
					}
				}
				else
				{
					//LSH zzang
					if(bit_myWater_setting_start == SET)
					{
						if( my_setting[my_recipe_select].use == SET
						&& my_setting[my_recipe_select].amount == 1000)
						{
							Bit7_Front_Right_Led_ml_Icon = CLEAR;
						}
						else
						{
							Bit7_Front_Right_Led_ml_Icon = SET;
						}
					}
					else
					{
						if((gu8Cup_level == CUP_LEVEL_1_120ML && gu16_WaterQuantity_half >= 1000)
						|| (gu8Cup_level == CUP_LEVEL_2_250ML && gu16_WaterQuantity_one >= 1000)
						|| (gu8Cup_level == CUP_LEVEL_3_500ML && gu16_WaterQuantity_two >= 1000)
						|| (gu8Cup_level == CUP_LEVEL_4_1000ML && gu16_WaterQuantity_four >= 1000)
						)
						{
							if(u8IceOutState == ICE_SELECT__ICE_WATER)
							{
								Bit7_Front_Right_Led_ml_Icon = SET;
							}
							else
							{
								if(bit_myWater_setting_start == SET)
								{
									Bit7_Front_Right_Led_ml_Icon = SET;
								}
								else
								{
									Bit7_Front_Right_Led_ml_Icon = CLEAR;
								}
							}
						}
						else
						{
							/* ���� ������ ���� ml. L �� 250630 CH.PARK */
							if(gu8Cup_level == CUP_LEVEL_CONTINUE)
							{
								Bit7_Front_Right_Led_ml_Icon = CLEAR;
							}
							else
							{
								Bit7_Front_Right_Led_ml_Icon = SET;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		Bit7_Front_Right_Led_ml_Icon = CLEAR;
	}

	if( gu8_Led_Display_Step == LED_Display__SLEEP )
	{
		set_duty_percent( DIMMING__PERCENT_ml_TEXT, SLEEP_MODE_DIMMING_PERCENT );
	}
	else
	{
		set_duty_percent( DIMMING__PERCENT_ml_TEXT, middle_small_led_percent );
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void under_text_led_output(void)
{
    ice_size_text_out();
    cold_temp_text_out();
	UNDER_ICON_ICE_TYPE_OUTPUT();		/* ����Ÿ�� LED ǥ�� �߰� 250217 CH.PARK */
	UNDER_ICON_COLD_OFF_OUTPUT();		/* �ü�OFF ǥ�� �߰� 250317 CH.PARK */
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_size_text_out(void)
{
	if( bit_setting_mode_start == SET )
	{
		Bit0_Front_Under_Txt_Led_Ice_Large = SET;
		Bit1_Front_Under_Txt_Led_Ice_Center_bar = SET;
		Bit2_Front_Under_Txt_Led_Ice_Small = SET;

		if(bit_ice_size == ICE_SIZE_LARGE)
		{
		    set_duty_percent( DIMMING__PERCENT_ICE_LARGE_TEXT, setting_led_percent );
			set_duty_percent( DIMMING__PERCENT_ICE_CENTER_BAR, setting_led_percent );
			set_duty_percent( DIMMING__PERCENT_ICE_SMALL_TEXT, DIIMMING__10_PERCENT );
		}
		else
		{
		    set_duty_percent( DIMMING__PERCENT_ICE_LARGE_TEXT, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_ICE_CENTER_BAR, setting_led_percent );
			set_duty_percent( DIMMING__PERCENT_ICE_SMALL_TEXT, setting_led_percent );
		}
	}
	else
	{
		Bit0_Front_Under_Txt_Led_Ice_Large = CLEAR;
		Bit1_Front_Under_Txt_Led_Ice_Center_bar = CLEAR;
		Bit2_Front_Under_Txt_Led_Ice_Small = CLEAR;
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_temp_text_out(void)
{
	if( bit_setting_mode_start == SET )
	{
		Bit3_Front_Under_Txt_Led_Cold_High = SET;
		Bit4_Front_Under_Txt_Led_Cold_Center_Bar = SET;
		Bit5_Front_Under_Txt_Led_Cold_Low = SET;

		if(gu8_cold_setting_level == COLD_POWER_HIGH)
		{
			set_duty_percent( DIMMING__PERCENT_COLD_HIGH_TEXT, setting_led_percent );
			set_duty_percent( DIMMING__PERCENT_COLD_CENTER_BAR, setting_led_percent );
			set_duty_percent( DIMMING__PERCENT_COLD_LOW_TEXT, DIIMMING__10_PERCENT );
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_COLD_HIGH_TEXT, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_COLD_CENTER_BAR, setting_led_percent );
			set_duty_percent( DIMMING__PERCENT_COLD_LOW_TEXT, setting_led_percent );
		}
	}
	else
	{
		Bit3_Front_Under_Txt_Led_Cold_High = CLEAR;
		Bit4_Front_Under_Txt_Led_Cold_Center_Bar = CLEAR;
		Bit5_Front_Under_Txt_Led_Cold_Low = CLEAR;
	}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void UNDER_ICON_ICE_TYPE_OUTPUT(void)
{
	if(bit_display_sleep_start == SET)
	{
		Bit7_Front_Under_Txt_Led_Ice_Piece = CLEAR;
		Bit6_Front_Under_Txt_Led_Ice_Normal = CLEAR;
	}
	else if( bit_setting_mode_start == CLEAR )
	{
		Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
		Bit6_Front_Under_Txt_Led_Ice_Normal = SET;

		if(F_IceBreak == SET)		/* [����] */
		{
			set_duty_percent( DIMMING__PERCENT_ICE_NORMAL, SLEEP_MODE_DIMMING_PERCENT );
			if( gu8_Led_Display_Step == LED_Display__SLEEP )
			{
				set_duty_percent( DIMMING__PERCENT_ICE_PIECE, DIIMMING__20_PERCENT );
			}
			else
			{
				set_duty_percent( DIMMING__PERCENT_ICE_PIECE, ice_type_led_percent );
			}
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_ICE_PIECE, SLEEP_MODE_DIMMING_PERCENT );
			if( gu8_Led_Display_Step == LED_Display__SLEEP )
			{
				set_duty_percent( DIMMING__PERCENT_ICE_NORMAL, DIIMMING__20_PERCENT );
			}
			else
			{
				set_duty_percent( DIMMING__PERCENT_ICE_NORMAL, ice_type_led_percent );
			}
		}
	}
	else
	{
		/* ���� ���� �� ������� ���� �� ����Ÿ�� ǥ�õǴ°� ���� 250228 CH.PARK */
		Bit6_Front_Under_Txt_Led_Ice_Normal = CLEAR;
		Bit7_Front_Under_Txt_Led_Ice_Piece = CLEAR;
	}
}

/**
 * @brief �ü� OFF ǥ��
 *
 */
void UNDER_ICON_COLD_OFF_OUTPUT(void)
{
	if( bit_setting_mode_start == SET )
	{
		Bit6_Front_Led_Cold_Off = SET;
	}
	else
	{
		if(Bit2_Cold_Off_Indicator == CLEAR)
		{
			Bit6_Front_Led_Cold_Off = CLEAR;
		}
		else
		{

		}

	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void under_icon_led_output(void)
{
    ice_lock_icon_output();
    hot_lock_icon_output();
    comp_operation_dot_output();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_lock_icon_output(void)
{
	if(bit_display_sleep_start == SET)
	{
		Bit2_Front_Led_Icon_Led_Ice_Locker = CLEAR;
	}
	else
	{
		if(F_Ice_Lock == SET)
		{
			Bit2_Front_Led_Icon_Led_Ice_Locker = SET;
		}
		else
		{
			Bit2_Front_Led_Icon_Led_Ice_Locker = CLEAR;
		}
	}

	if( gu8_Led_Display_Step == LED_Display__SLEEP )
	{
		set_duty_percent( DIMMING__PERCENT_ICE_LOCK_ICON, SLEEP_MODE_DIMMING_PERCENT );
	}
	else
	{
		set_duty_percent( DIMMING__PERCENT_ICE_LOCK_ICON, setting_led_percent );
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_lock_icon_output(void)
{
	if(bit_display_sleep_start == SET)
	{
		Bit3_Front_Led_Icon_Led_Hot_Locker = CLEAR;
	}
	else
	{
		if(F_Hot_Lock == SET)
		{
			Bit3_Front_Led_Icon_Led_Hot_Locker = SET;
		}
		else
		{
			Bit3_Front_Led_Icon_Led_Hot_Locker = CLEAR;
		}
	}

	if( gu8_Led_Display_Step == LED_Display__SLEEP )
	{
		set_duty_percent( DIMMING__PERCENT_HOT_LOCK_ICON, SLEEP_MODE_DIMMING_PERCENT );
	}
	else
	{
		set_duty_percent( DIMMING__PERCENT_HOT_LOCK_ICON, setting_led_percent );
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void comp_operation_dot_output(void)
{
#if 0
	if(bit_display_sleep_start == SET)
    {
		// ��ħ��� �� WHITE, BLUE �ҵ�
		Bit6_Front_Led_Icon_Comp_White = CLEAR;
		Bit5_Front_Led_Icon_Comp_Blue = CLEAR;
	}
	else if( bit_setting_mode_start == SET )
	{
		Bit6_Front_Led_Icon_Comp_White = CLEAR;
	}
	else
	{
		if((u8WaterOutState == COLD_WATER_SELECT)	/* �ü� ���� */
		&& (u8IceOutState == ICE_SELECT__NONE)		/* ���� �̼��� */
		&& (bit_myWater_setting_start == 0)		/* MY �̼��� */
		)
		{
			if(F_Cold_Enable == SET)
			{
				if(gu16_Cold_Temperature < gu16_test_cold_on_temp)
				{
					// ��ǥ�µ� ���� �� WHITE ����
					Bit5_Front_Led_Icon_Comp_Blue = CLEAR;
					Bit6_Front_Led_Icon_Comp_White = SET;
				}
				else
				{
					// ��ǥ�µ� ���� �� BLUE ����
					Bit5_Front_Led_Icon_Comp_Blue = SET;
					Bit6_Front_Led_Icon_Comp_White = CLEAR; // blue on
				}
			}
			else
			{
				// �ü�OFF �� WHITE, BLUE �ҵ�
				Bit6_Front_Led_Icon_Comp_White = CLEAR;
				Bit5_Front_Led_Icon_Comp_Blue = CLEAR;
			}
		}
		else
		{
			// �ü� �̼��� �� WHITE, BLUE �ҵ�
			Bit6_Front_Led_Icon_Comp_White = CLEAR;
			Bit5_Front_Led_Icon_Comp_Blue = CLEAR;
		}
	}
#endif
	if(bit_display_sleep_start == SET)
    {
		Bit5_Front_Led_Icon_Comp_Blue = CLEAR;
		Bit6_Front_Led_Icon_Comp_White = CLEAR;
	}
	else
	{
		if( gu8_cooling_display_mode == COOLING_DISPLAY_1_OPERATION )
		{
			Bit6_Front_Led_Icon_Comp_White = SET;
			Bit5_Front_Led_Icon_Comp_Blue = CLEAR;
		}
		else if( gu8_cooling_display_mode == COOLING_DISPLAY_2_COMPLETE )
		{
			Bit6_Front_Led_Icon_Comp_White = CLEAR;
			Bit5_Front_Led_Icon_Comp_Blue = SET;
		}
		else /*if( gu8_cooling_display_mode == COOLING_DISPLAY_0_OFF )*/
		{
			Bit6_Front_Led_Icon_Comp_White = CLEAR;
			Bit5_Front_Led_Icon_Comp_Blue = CLEAR;
		}

	}


	if( gu8_Led_Display_Step == LED_Display__SLEEP )
	{
		// 10%�� �ʹ� �Ⱥ����� 20%��
		set_duty_percent( DIMMING__PERCENT_COMP_WHITE_DOT, DIIMMING__20_PERCENT );
		set_duty_percent( DIMMING__PERCENT_COMP_BLUE_DOT, DIIMMING__20_PERCENT );
	}
	else
	{
		set_duty_percent( DIMMING__PERCENT_COMP_WHITE_DOT, setting_led_percent );
		set_duty_percent( DIMMING__PERCENT_COMP_BLUE_DOT, setting_led_percent );
	}
}

/**********************************************************************************************************************/
/**
 * @brief ������ ���� ���׸�Ʈ �� DOT LED ����
 *
 */
void RIGHT_SEG_DOT_OUTPUT(void)
{
	U16 mu16_amount = 0;

	if( gu8_Led_Display_Step == LED_Display__SLEEP )
	{
		set_duty_percent( DIMMING__PERCENT_RIGHT_SEG_DOT, SLEEP_MODE_DIMMING_PERCENT );
	}
	else
	{
		set_duty_percent( DIMMING__PERCENT_RIGHT_SEG_DOT, colon_dot_led_percent );
	}

	if(bit_display_sleep_start == SET)
	{
		Bit5_Front_Right_Seg_Dot_Text = CLEAR;
	}
	else if( bit_setting_mode_start == SET )
	{
		Bit5_Front_Right_Seg_Dot_Text = CLEAR;
	}
	else if( ( gu8_cup_led_select == CLEAR )
	&& ( gu16_water_select_return_time == 0 )
	&& (bit_myWater_setting_start == 0)
	&& (gu8_clock_hide_state == CLEAR)
	&& (bit_first_time_setting == SET)
	&& (F_WaterOut == CLEAR)
	&& (F_IceOut == CLEAR)
	)
	{
		Bit5_Front_Right_Seg_Dot_Text = CLEAR;
	}
	else
	{
		if((Bit2_Cold_Off_Indicator != 0)
		|| (Bit0_Ice_Lock_Indicator != 0)
		|| (Bit6_Icewater_Off_Indicator != 0)
		|| (Bit5_Ice_Off_Indicator != 0)
		)
		{
			Bit5_Front_Right_Seg_Dot_Text = CLEAR;
		}
		else
		{
			/* ���� ���� �� Seg Dot OFF */
			if(u8IceOutState == ICE_SELECT__ICE)
			{
				Bit5_Front_Right_Seg_Dot_Text = CLEAR;
			}
			else
			{
				if( F_WaterOut == SET )
				{
					/* �������̸� ���� ���ⷮ�� �°� ml, L ǥ�� 250218 CH.PARK */
					mu16_amount = (U16)((U16)gu16_extract_display_cnt * 10);

					if(mu16_amount < 1000)
					{
						Bit5_Front_Right_Seg_Dot_Text = CLEAR;
					}
					else
					{
						Bit5_Front_Right_Seg_Dot_Text = SET;
					}
				}
				else if((u8IceOutState == ICE_SELECT__ICE_WATER)
				&& (F_IceOut == SET)
				)
				{
					/* �������̸� ���� ���ⷮ�� �°� ml, L ǥ�� 250218 CH.PARK */
					mu16_amount = (U16)((U16)gu16_extract_display_cnt * 10);

					if(mu16_amount < 1000)
					{
						Bit5_Front_Right_Seg_Dot_Text = CLEAR;
					}
					else
					{
						Bit5_Front_Right_Seg_Dot_Text = SET;
					}
				}
				else
				{
					//LSH zzang
					if(bit_myWater_setting_start == SET)
					{
						if( my_setting[my_recipe_select].use == SET
						&& my_setting[my_recipe_select].amount >= 1000)
						{
							Bit5_Front_Right_Seg_Dot_Text = SET;
						}
						else
						{
							Bit5_Front_Right_Seg_Dot_Text = CLEAR;
						}
					}
					else
					{
						/* 1L �̻��� ������ DOT LED ON */
						if((gu8Cup_level == CUP_LEVEL_1_120ML && gu16_WaterQuantity_half >= 1000)
						|| (gu8Cup_level == CUP_LEVEL_2_250ML && gu16_WaterQuantity_one >= 1000)
						|| (gu8Cup_level == CUP_LEVEL_3_500ML && gu16_WaterQuantity_two >= 1000)
						|| (gu8Cup_level == CUP_LEVEL_4_1000ML && gu16_WaterQuantity_four >= 1000)
						)
						{
							if(u8IceOutState == ICE_SELECT__ICE_WATER)
							{
								Bit5_Front_Right_Seg_Dot_Text = CLEAR;
							}
							else
							{
								Bit5_Front_Right_Seg_Dot_Text = SET;
							}
						}
						else
						{
							Bit5_Front_Right_Seg_Dot_Text = CLEAR;
						}
					}
				}
			}
		}
	}
}

/**
 * @brief [���ͼ�ô] ǥ�� ��� �߰� 250225
 *
 */
void	filter_clean_txt_out (void)
{
	if(gu8_flushing_mode == FLUSHING_FILTER)
	{
		Bit4_Front_Right_Led_Filter_Clean_Text = SET;
	}
	else
	{
		Bit4_Front_Right_Led_Filter_Clean_Text = CLEAR;
	}

	if( gu8_Led_Display_Step == LED_Display__SLEEP )
	{
		set_duty_percent( DIMMING__PERCENT_FILTER_CLEAN, SLEEP_MODE_DIMMING_PERCENT );
	}
	else
	{
		set_duty_percent( DIMMING__PERCENT_FILTER_CLEAN, top_small_led_percent );
	}
}

/**
 * @brief �Ҹ�������� LED ǥ��
 *
 */
void led_volume_setting_state(void)
{
	Bit2_Front_Led_Hot_Select = CLEAR;
	Bit3_Front_Led_Ambient_Select = SET;
	Bit4_Front_Led_Cold_Select = SET;
	Bit5_Front_Led_Amount_Select = SET;

	set_duty_percent( DIMMING__PERCENT_AMBIENT_SELECT, funtion_led_percent );
	set_duty_percent( DIMMING__PERCENT_COLD_SELECT, (funtion_led_percent / 2) );
	set_duty_percent( DIMMING__PERCENT_AMOUNT_SELECT, funtion_led_percent );

	Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
	Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
	Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
	Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
	Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;

	if(gu8Sound_Type != SOUND_TYPE_MUTE)
	{
		if(gu8VoiceVolumeLevel == SOUND_VOLUME_LEVEL_1)
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, bar_led_percent );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
		}
		else if(gu8VoiceVolumeLevel == SOUND_VOLUME_LEVEL_2)
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, bar_led_percent );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
		}
		else if(gu8VoiceVolumeLevel == SOUND_VOLUME_LEVEL_3)
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, bar_led_percent );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
		}
		else if(gu8VoiceVolumeLevel == SOUND_VOLUME_LEVEL_4)
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, bar_led_percent );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
		}
		else if(gu8VoiceVolumeLevel == SOUND_VOLUME_LEVEL_5)
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, bar_led_percent );
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, bar_led_percent );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
		}
	}
	else
	{
		/* �������� �����Ǹ� �뷮�ٴ� ������ OFF (UI���) */
		Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
		Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
		Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
		Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
		Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : Cody Water Line Clean Service
***********************************************************************************************************************/
void cody_service_water_icon(void)
{
	if(cody_water_line.gu8_start == SET)
	{
		if((cody_water_line.gu8_step == 0)
		|| (cody_water_line.gu8_step == 4)
		)
		{
			Bit3_Front_Led_Ambient_Select = SET;
			Bit3_Animation_Dimming_Ambient_Select_State = SET;
		}
		else if(cody_water_line.gu8_step == 2)
		{
			Bit4_Front_Led_Cold_Select = SET;
			Bit4_Animation_Dimming_Cold_Select_State = SET;
		}
		else
		{
			Bit3_Front_Led_Ambient_Select = CLEAR;
			Bit4_Front_Led_Cold_Select = CLEAR;
			Bit3_Animation_Dimming_Ambient_Select_State = CLEAR;
			Bit4_Animation_Dimming_Cold_Select_State = CLEAR;
		}
	}
	else {  }

	/* ����Ű ���� */
	Bit4_Front_Under_Water_White_Extract = SET;
	Bit3_Front_Under_Ice_Outer_White_Extract = SET;
	Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
	Bit2_Front_Under_Ice_Outer_Blue_Extract = CLEAR;
	Bit1_Front_Under_Ice_Inner_Blue_Extract = CLEAR;

	set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, water_extract_led_percent );
    set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, ice_extract_outer_led_percent );
    set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, ice_extract_inner_led_percent );

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_self_test_state(void)
{
    /////extract_led_out();
    percent_icon_out();
    wifi_icon_output();
}

void ice_level_led_out(void)
{
	if(gu8_ice_amount_step == ICE_LEVEL_1_STEP)
	{
		if( gu8_Led_Display_Step == LED_Display__SLEEP )
		{
			set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, SLEEP_MODE_DIMMING_PERCENT );
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, bar_led_percent );
		}
		set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
		set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
		set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
	}
	else if(gu8_ice_amount_step == ICE_LEVEL_2_STEP)
	{
		set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
		if( gu8_Led_Display_Step == LED_Display__SLEEP )
		{
			set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, SLEEP_MODE_DIMMING_PERCENT );
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, bar_led_percent );
		}
		set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
		set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
	}
	else if(gu8_ice_amount_step == ICE_LEVEL_3_STEP)
	{
		set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
		set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );

		if( gu8_Led_Display_Step == LED_Display__SLEEP )
		{
			set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, SLEEP_MODE_DIMMING_PERCENT );
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, bar_led_percent );
		}
		set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
	}
	else if(gu8_ice_amount_step == ICE_LEVEL_4_STEP)
	{
		set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
		set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
		set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );

		if( gu8_Led_Display_Step == LED_Display__SLEEP )
		{
			set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, SLEEP_MODE_DIMMING_PERCENT );
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, bar_led_percent );
		}
	}

	/* ���� �������� �� �����뷮 �����ٴ� OFF */
	if(gu8_ice_out_continue == SET)
	{
		Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
		Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
		Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
		Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
		Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
	}
	else
	{
		Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
		Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
		Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
		Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
		Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
	}
}

void water_level_led_out(void)
{
	if( gu8Cup_level == CUP_LEVEL_1_120ML )
	{
		Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;

		if( gu8_Led_Display_Step == LED_Display__SLEEP )
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, SLEEP_MODE_DIMMING_PERCENT );
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, bar_led_percent );
		}

		Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

		Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

		Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

		// ������ �������̸� �������� ��
		if(u8IceOutState == ICE_SELECT__ICE_WATER)
		{
			Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
		}
		else
		{
			Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
		}
	}
	else if( gu8Cup_level == CUP_LEVEL_2_250ML )
	{
		Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );

		Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
		if( gu8_Led_Display_Step == LED_Display__SLEEP )
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, SLEEP_MODE_DIMMING_PERCENT );
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, bar_led_percent );
		}

		Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

		Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

		// ������ �������̸� �������� ��
		if(u8IceOutState == ICE_SELECT__ICE_WATER)
		{
			Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
		}
		else
		{
			Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
		}
	}
	else if( gu8Cup_level == CUP_LEVEL_3_500ML )
	{
		Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );

		Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

		Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
		if( gu8_Led_Display_Step == LED_Display__SLEEP )
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, SLEEP_MODE_DIMMING_PERCENT );
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, bar_led_percent );
		}

		Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

		// ������ �������̸� �������� ��
		if(u8IceOutState == ICE_SELECT__ICE_WATER)
		{
			Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
		}
		else
		{
			Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
		}
	}
	else if( gu8Cup_level == CUP_LEVEL_4_1000ML )
	{
		Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );

		Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

		Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

		Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
		if( gu8_Led_Display_Step == LED_Display__SLEEP )
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, SLEEP_MODE_DIMMING_PERCENT );
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, bar_led_percent );
		}

		// ������ �������̸� �������� ��
		if(u8IceOutState == ICE_SELECT__ICE_WATER)
		{
			Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
		}
		else
		{
			Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
		}

		if( gu8_Led_Display_Step == LED_Display__SLEEP )
		{
			set_duty_percent( DIMMING__PERCENT_RIGHT_SEG_DOT, SLEEP_MODE_DIMMING_PERCENT );
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_RIGHT_SEG_DOT, colon_dot_led_percent );
		}
	}
	else
	{
		Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );

		Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

		Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

		Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
		set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

		Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;

		if( gu8_Led_Display_Step == LED_Display__SLEEP )
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, SLEEP_MODE_DIMMING_PERCENT );
		}
		else
		{
			set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, bar_led_percent );
		}
	}
}

void water_hot_level_led_out(void)
{
	if( u8WaterOutState == PURE_WATER_SELECT )
    {
        Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
        Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
        Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
        Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
    }
    else if( u8WaterOutState == COLD_WATER_SELECT )
    {
        Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
        Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
        Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
        Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
    }
    else /*if( u8WaterOutState == HOT_WATER_SELECT )*/
    {
		if( gu8_hot_setting_temperature == selected_hot_temp[0] )
		{
			Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
			Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
			Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
			Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
			Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

			if( gu8_Led_Display_Step == LED_Display__SLEEP )
			{
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, SLEEP_MODE_DIMMING_PERCENT );
			}
			else
			{
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, bar_led_percent );
			}
		}
		else if( gu8_hot_setting_temperature == selected_hot_temp[1])
		{
			Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
			Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
			Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
			Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
			Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

			if( gu8_Led_Display_Step == LED_Display__SLEEP )
			{
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, SLEEP_MODE_DIMMING_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
			}
			else
			{
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, bar_led_percent );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
			}
		}
		else if( gu8_hot_setting_temperature == selected_hot_temp[2] )
		{
			Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
			Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
			Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
			Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
			Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

			if( gu8_Led_Display_Step == LED_Display__SLEEP )
			{
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, SLEEP_MODE_DIMMING_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
			}
			else
			{
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, bar_led_percent );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
			}
		}
		else if (gu8_hot_setting_temperature == selected_hot_temp[3] )
		{
			Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
			Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
			Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
			Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
			Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

			if( gu8_Led_Display_Step == LED_Display__SLEEP )
			{
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, SLEEP_MODE_DIMMING_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
			}
			else
			{
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, bar_led_percent );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
			}
		}
		else
		{
			Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
			Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
			Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
			Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
			Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

			if( gu8_Led_Display_Step == LED_Display__SLEEP )
			{
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, SLEEP_MODE_DIMMING_PERCENT );
			}
			else
			{
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
				set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, bar_led_percent );
			}
		}
	}
}

/**
 * @brief �� ������ ���� ICON ǥ��
 *
 */
void water_extract_led_output(void)
{
	water_level_led_out();
	water_hot_level_led_out();
	icon_led_output();

	funcition_led_output();
	setting_led_output();
	extract_led_output();
	recipe_led_output();
}

/**
 * @brief ���� ������ ���� ICON ǥ��
 *
 */
void ice_extract_led_output(void)
{
	cup_level_extract_out();
	ice_level_led_out();

	funcition_led_output();
	setting_led_output();
	extract_led_output();
	recipe_led_output();

	ice_full_text_out();
    uv_ster_text_out();			/* UV��� */
    hot_ster_text_out();		/* ���»�� */
    sleep_icon_out();			/* ��ħ��� ǥ�� */
    step_text_out();			/* (����) �ܰ� ǥ�� */
    clock_colon_icon_out();		/* : �ð� �ݷ� ǥ�� */

	wifi_icon_output();

	whether_icon_out();
    percent_icon_out();

	Bit5_Front_Right_Seg_Dot_Text = CLEAR;
	Bit7_Front_Right_Led_ml_Icon = CLEAR;
	Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
	Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;

	// // celcius_oC_icon_out();		/* �µ� 'C ǥ�� */
    // // liter_L_icon_out();
    // // ml_icon_out();
	// // RIGHT_SEG_DOT_OUTPUT();

	under_text_led_output();	// [�������], [�ü�����], [�Ϲ�/����], [�ü�OFF]
	under_icon_led_output();	// [COMP LED], [�ڹ���]
}
