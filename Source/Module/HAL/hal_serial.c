/******************************************************************/
/**
 * File : hal_serial.c
 * BaudRate : 9600bps
 * Hardware Abstraction Layer
 * Depend on Renesas MCU Chip
*/
/******************************************************************/

#include "hal_serial.h"

#ifdef USE_UART0_MODULE
static void (*uart0_rx_callback_func)(uint8_t) = NULL;
static void (*uart0_tx_callback_func)(void) = NULL;
#endif /* USE_UART0_MODULE */

#ifdef USE_UART2_MODULE
static void (*uart2_rx_callback_func)(U8) = NULL;
static void (*uart2_tx_callback_func)(void) = NULL;
#endif /* USE_UART2_MODULE */

#ifdef USE_UART3_MODULE
static void (*uart3_rx_callback_func)(uint8_t) = NULL;
static void (*uart3_tx_callback_func)(void) = NULL;
#endif /* USE_UART3_MODULE */

void HAL_Uart_Init(teUART_CHANNEL channel, void (*recv_callback_func)(uint8_t), void (*send_callback_func)(void))
{
#ifdef USE_UART0_MODULE
    if(channel == UART_CHANNEL_0)
    {
        uart0_rx_callback_func = recv_callback_func;
        uart0_tx_callback_func = send_callback_func;
        UART0_START();
    }
#endif

#ifdef USE_UART2_MODULE
    if(channel == UART_CHANNEL_2)
    {
        uart2_rx_callback_func = recv_callback_func;
        uart2_tx_callback_func = send_callback_func;
        UART2_START();
    }
#endif

#ifdef USE_UART3_MODULE
    if(channel == UART_CHANNEL_3)
    {
        uart3_rx_callback_func = recv_callback_func;
        uart3_tx_callback_func = send_callback_func;
        UART3_START();
    }
#endif
}

void HAL_Uart_Deinit(uint8_t channel)
{
#ifdef USE_UART0_MODULE
    if(channel == UART_CHANNEL_0)
    {
        UART0_STOP();
        uart0_rx_callback_func = NULL;
        uart0_tx_callback_func = NULL;
    }
#endif

#ifdef USE_UART2_MODULE
    if(channel == UART_CHANNEL_2)
    {
        UART2_STOP();
        uart2_rx_callback_func = NULL;
        uart2_tx_callback_func = NULL;
    }
#endif

#ifdef USE_UART3_MODULE
    if(channel == UART_CHANNEL_3)
    {
        UART3_STOP();
        uart3_rx_callback_func = NULL;
        uart3_tx_callback_func = NULL;
    }
#endif
}

// @How to use : 사용할 UART 채널을 선택하고,
// 해당 채널의 interrupt 선언을 프로젝트에서 사용중인 인터럽트 서비스에 해당하는 함수를 호출시킨다
#ifdef USE_UART0_MODULE
/**********************************************************************************************************************/
/**
 * @brief UART0 송신 인터럽트 핸들러
 * @details UART0 송신 인터럽트 핸들러
 * @param void
 * @return void
 */
void HAL_Uart0_Interrupt_Send(void)
{
    if (uart0_tx_callback_func != NULL)
    {
        uart0_tx_callback_func();
    }
}

/**********************************************************************************************************************/
/**
 * @brief UART0 수신 인터럽트 핸들러
 * @details UART0 수신 인터럽트 핸들러
 * @param void
 * @return void
 */
void HAL_Uart0_Interrupt_Receive(void)
{
    volatile uint8_t rx_data = 0;
    volatile uint8_t errType = 0;

    errType = UART0_GET_SERIAL_STATUS();
    UART0_CLEAR_ERROR_FLAG(errType);

    if (errType != 0U)
    {
        //ERROR
    }

    rx_data = UART0_GET_RX_DATA();

    if (uart0_rx_callback_func != NULL)
    {
        uart0_rx_callback_func(rx_data);
    }
}
#endif /* USE_UART0_MODULE */

#ifdef USE_UART2_MODULE
/**********************************************************************************************************************/
/**
 * @brief UART2 송신 인터럽트 핸들러
 * @details UART2 송신 인터럽트 핸들러
 * @param void
 * @return void
 */
void HAL_Uart2_Interrupt_Send(void)
{
    if (uart2_tx_callback_func != NULL)
    {
        uart2_tx_callback_func();
    }
}

void HAL_Uart2_Interrupt_Receive(void)
{
    volatile uint8_t rx_data = 0;
    volatile uint8_t errType = 0;

    errType = UART2_GET_SERIAL_STATUS();
    UART2_CLEAR_ERROR_FLAG(errType);

    if (errType != 0U)
    {
        //ERROR
    }

    rx_data = UART2_GET_RX_DATA();

    if (uart2_rx_callback_func != NULL)
    {
        uart2_rx_callback_func(rx_data);
    }
}
#endif /* USE_UART2_MODULE */

#ifdef USE_UART3_MODULE
/**********************************************************************************************************************/
/**
 * @brief UART3 송신 인터럽트 핸들러
 * @details UART3 송신 인터럽트 핸들러
 * @param void
 * @return void
 */
void HAL_Uart3_Interrupt_Send(void)
{
    if (uart3_tx_callback_func != NULL)
    {
        uart3_tx_callback_func();
    }
}

/**********************************************************************************************************************/
/**
 * @brief UART3 수신 인터럽트 핸들러
 * @details UART3 수신 인터럽트 핸들러
 * @param void
 * @return void
 */
void HAL_Uart3_Interrupt_Receive(void)
{
    volatile uint8_t rx_data = 0;
    volatile uint8_t errType = 0;

    errType = UART3_GET_SERIAL_STATUS();
    UART3_CLEAR_ERROR_FLAG(errType);

    if (errType != 0U)
    {
        //ERROR
    }

    rx_data = UART3_GET_RX_DATA();

    if (uart3_rx_callback_func != NULL)
    {
        uart3_rx_callback_func(rx_data);
    }
}
#endif /* USE_UART3_MODULE */

