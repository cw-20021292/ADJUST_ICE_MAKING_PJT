/**
 * File : App_Comm.c
 *
 * User Application
 * Depend on API
*/

#include "App_Comm.h"
#include "api_uart.h"           // UART API prototypes
#include "App_Comm_Protocol.h"
#include "App_Comm_CLI.h"


U16 DebugTotalLength = 0;

tsCommInfo CommInfo = {0, };

void SetCommState(teCommState state)
{
    CommInfo.comm_state = state;
}

teCommState GetCommState(void)
{
    return CommInfo.comm_state;
}

void SetCommRxIndex(U8 index)
{
    CommInfo.comm_rx_index = index;
}

U8 GetCommRxIndex(void)
{
    return CommInfo.comm_rx_index;
}

void SetRxPacketLength(U16 length)
{
    CommInfo.RxPacketLength = length;
}

U16 GetRxPacketLength(void)
{
    return CommInfo.RxPacketLength;
}


static void Comm_Send_Packet_Handler(void)
{
    if(CommInfo.comm_state == COMM_STATE_TRANSMIT)
    {
        Uart_Send_Buffer(UART_CHANNEL_3, (const char *)CommInfo.comm_tx_buffer, CommInfo.comm_tx_index);
        CommInfo.comm_state = COMM_STATE_IDLE;
    }
}

static void Comm_Rcv_Packet_Handler(void)
{
    U8 data = 0;

    while(Uart_Read_Data(UART_CHANNEL_3, &data) == TRUE)
    {
        switch(CommInfo.comm_state)
        {
            case COMM_STATE_IDLE :
                if( data == COMM_PROTOCOL_STX )
                {
                    _MEMSET_(CommInfo.comm_rx_buffer, 0, UART3_RX_BUFFER_SIZE);
                    SetCommState(COMM_STATE_RECEIVING);
                    SetCommRxIndex(0);
                    SetRxPacketLength(0);

                    CommInfo.comm_rx_buffer[CommInfo.comm_rx_index++] = data;
                }
                break;

            case COMM_STATE_RECEIVING :
                CommInfo.comm_rx_buffer[CommInfo.comm_rx_index++] = data;

                // LENGTH 필드를 읽은 후 예상 패킷 길이 계산
                if(CommInfo.comm_rx_index == (PROTOCOL_IDX_LENGTH + 1))
                {
                    // 전체 패킷 길이 = 4(헤더) + LENGTH(데이터) + 3(CRC+ETX)
                    SetRxPacketLength(((PROTOCOL_IDX_LENGTH + 1) + CommInfo.comm_rx_buffer[PROTOCOL_IDX_LENGTH] + 3));

                    // 패킷 길이 유효성 사전 검사
                    if((GetRxPacketLength() < COMM_PROTOCOL_PACKET_BASIC_LENGTH)
                    || (GetRxPacketLength() > UART3_RX_BUFFER_SIZE)
                    )
                    {
                        SetCommState(COMM_STATE_IDLE);
                        SetCommRxIndex(0);
                        SetRxPacketLength(0);
                        break;
                    }
                }

                // 예상 길이만큼 수신 완료 시 검증
                if((CommInfo.comm_rx_index >= PROTOCOL_IDX_LENGTH + 1)
                && (CommInfo.comm_rx_index >= GetRxPacketLength())
                )
                {
                    // 계산된 위치에 ETX가 있는지 확인
                    if(CommInfo.comm_rx_buffer[GetRxPacketLength() - 1] == COMM_PROTOCOL_ETX)
                    {
#ifdef USE_COMM_CLI
                        if(CLI_isValidPacket(CommInfo.comm_rx_buffer) == TRUE)
                        {
                            SetCommState(COMM_STATE_CLI);
                            SetCommRxIndex(0);
                            break;
                        }
#else
                        if(Protocol_isValidPacket(CommInfo.comm_rx_buffer) == TRUE)
                        {
                            CommInfo.comm_tx_index = Protocol_Make_Ack_Packet(CommInfo.comm_rx_buffer, CommInfo.comm_tx_buffer);

                            SetCommState(COMM_STATE_TRANSMIT);
                            SetCommRxIndex(0);
                        }
                        else
                        {
                            SetCommState(COMM_STATE_IDLE);
                            SetCommRxIndex(0);
                            SetRxPacketLength(0);
                        }
#endif
                    }
                    else
                    {
                        // ETX가 예상 위치에 없음 - 잘못된 패킷
                        SetCommState(COMM_STATE_IDLE);
                        SetCommRxIndex(0);
                        SetRxPacketLength(0);
                    }
                }
                // 버퍼 오버플로우 방지
                else if(CommInfo.comm_rx_index > UART3_RX_BUFFER_SIZE)
                {
                    SetCommState(COMM_STATE_IDLE);
                    SetCommRxIndex(0);
                    SetRxPacketLength(0);
                }
                break;

            case COMM_STATE_CLI :
                CLI_Packet_Handler(data);
                break;

            default :
                break;
        }

    }
}

/*********************************************************************************/
/**
 * @brief 패킷 처리
 * @details 수신 패킷 처리 및 송신 패킷 처리
 * @note @TODO : while문에 적용
 */
void Comm_Packet_Handler(void)
{
    Comm_Rcv_Packet_Handler();
    Comm_Send_Packet_Handler();
}

