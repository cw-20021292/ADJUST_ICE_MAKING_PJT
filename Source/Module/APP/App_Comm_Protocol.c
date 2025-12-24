/**
 * File : App_Comm_Protocol.c
 *
 * Application Programming Interface
 * Depend on API
*/

#include "App_Comm_Protocol.h"

#include    "Macrodriver.h"
#include    "Packet_Match.h"
#include    "M8_Ice_Making.h"
U16 Debuglength = 0;

static U8 Protocol_Make_Ack_Data(U8* buf, U8* Txbuf)
{
    U8 u8cmd = buf[PROTOCOL_IDX_CMD];
    U8 u8DataIndex = 0;
    U8 data_length = 0;

    switch( u8cmd )
    {
        case PROTOCOL_F0_CMD:                    // 0xF0
            // F0 구조체에 데이터 채우기
            Parse_F0_Protocol();
            data_length = PROTOCOL_F0_LENGTH;

            // F0 구조체를 바이트 배열로 변환하여 TxData에 복사
            Get_F0_Data_Bytes(Txbuf, data_length);
            break;

        case PROTOCOL_F1_CMD:                    // 0xF1
            // F1 구조체에 데이터 채우기
            Parse_F1_Protocol();
            data_length = PROTOCOL_F1_LENGTH;

            // F1 구조체를 바이트 배열로 변환하여 TxData에 복사
            Get_F1_Data_Bytes(Txbuf, data_length);
        break;

        case PROTOCOL_B3_CMD:                    // 0xB3
            SetFreezingTable(&buf[5]);
            SetUsedFreezingTable(SET);

            // F1 구조체에 데이터 채우기
            Parse_F1_Protocol();
            data_length = PROTOCOL_F1_LENGTH;

            // F1 구조체를 바이트 배열로 변환하여 TxData에 복사
            Get_F1_Data_Bytes(Txbuf, data_length);

            break;

        case PROTOCOL_B1_CMD:                    // 0xB1
            /* ECO */
            Parse_B1_Protocol(buf);

            data_length = buf[PROTOCOL_IDX_LENGTH];
            for(u8DataIndex = 0; u8DataIndex < data_length; u8DataIndex++)
            {
                Txbuf[u8DataIndex] = ((U8*)&buf)[u8DataIndex + 4];
            }
            break;

        case PROTOCOL_B2_CMD:                    // 0xB2
            /* ECO */
            Parse_B2_Protocol(buf);
            data_length = buf[PROTOCOL_IDX_LENGTH];
            for(u8DataIndex = 0; u8DataIndex < data_length; u8DataIndex++)
            {
                Txbuf[u8DataIndex] = ((U8*)&buf)[u8DataIndex + 4];
            }
            break;

        case PROTOCOL_B4_CMD:                    // 0xB4
            /* ECO */
            Parse_B4_Protocol(buf);
            data_length = buf[PROTOCOL_IDX_LENGTH];
            for(u8DataIndex = 0; u8DataIndex < data_length; u8DataIndex++)
            {
                Txbuf[u8DataIndex] = ((U8*)&buf)[u8DataIndex + 4];
            }
            break;

        default:
            break;
    }

    return data_length;

}

static U8 Protocol_Make_Cmd(U8 *buf)
{
    U8 u8cmd = buf[PROTOCOL_IDX_CMD];
    U8 u8Txcmd = 0;

    /* 제품은 F0, F1으로만 응답 */
    switch( u8cmd )
    {
        case PROTOCOL_F0_CMD:                    // 0xF0
            u8Txcmd = PROTOCOL_F0_CMD;
            break;

        case PROTOCOL_F1_CMD:                    // 0xF1
        case PROTOCOL_B3_CMD:                    // 0xB3
            u8Txcmd = PROTOCOL_F1_CMD;
        break;

        case PROTOCOL_B1_CMD:                    // 0xB1
            u8Txcmd = PROTOCOL_B1_CMD;
        break;

        case PROTOCOL_B2_CMD:                    // 0xB2
            u8Txcmd = PROTOCOL_B2_CMD;
        break;

        case PROTOCOL_B4_CMD:                    // 0xB4
            u8Txcmd = PROTOCOL_B4_CMD;
        break;

        default:
            u8Txcmd = 0;
            break;
    }

    return u8Txcmd;
}

static U16 Protocol_CRC_Cal(U8 *puchMsg, U16 usDataLen)
{
    U8 i = 0;
    U16 wCRCin = 0x0000;
    U16 wCPoly = 0x1021;
    U8 wChar = 0;

    while(usDataLen--)
    {
        wChar = *(puchMsg++);
        wCRCin ^= ((U16)wChar << 8);
        for(i = 0; i < 8; i++)
        {
            if (wCRCin & 0x8000)
            {
                wCRCin = (wCRCin << 1) ^ wCPoly;
            }
            else
            {
                wCRCin = wCRCin << 1;
            }
        }
    }

    return (wCRCin);
}

U8 Protocol_isValidPacket(U8 *buf)
{
    U16 calculated_crc = 0;
    U16 received_crc = 0;
    U16 packet_length = 0;

    if(buf[0] != COMM_PROTOCOL_STX)
    {
        return FALSE;
    }

    if(buf[1] != COMM_PROTOCOL_ID_PC)
    {
        return FALSE;
    }

    packet_length = (PROTOCOL_IDX_LENGTH+1) + buf[PROTOCOL_IDX_LENGTH] + 3;
    Debuglength = packet_length;

    if(packet_length < COMM_PROTOCOL_PACKET_BASIC_LENGTH || packet_length > UART3_RX_BUFFER_SIZE)
    {
        return FALSE;
    }

    if(buf[packet_length - 1] != COMM_PROTOCOL_ETX)
    {
        return FALSE;
    }

    calculated_crc = Protocol_CRC_Cal(buf, (U16)(packet_length - 3));

    if( buf[packet_length-3] != GET_16_HIGH_BYTE(calculated_crc) || buf[packet_length-2] != GET_16_LOW_BYTE(calculated_crc) )
    {
        return FALSE;
    }

    return TRUE;
}

U8 Protocol_Make_Ack_Packet(U8 *buf, U8 *tx_buf)
{
    U8 data_length = 0;
    U16 packet_length = 0;
    U16 calculated_crc = 0;

    tx_buf[PROTOCOL_IDX_STX] = COMM_PROTOCOL_STX;
    tx_buf[PROTOCOL_IDX_ID] = COMM_PROTOCOL_ID_MAIN;
    tx_buf[PROTOCOL_IDX_CMD] = Protocol_Make_Cmd(buf);

    data_length = Protocol_Make_Ack_Data(buf, &tx_buf[PROTOCOL_IDX_DATA]);
    tx_buf[PROTOCOL_IDX_LENGTH] = data_length;

    calculated_crc = Protocol_CRC_Cal(tx_buf, (U8)(4 + data_length));
    tx_buf[4 + data_length] = GET_16_HIGH_BYTE(calculated_crc);
    tx_buf[4 + data_length + 1] = GET_16_LOW_BYTE(calculated_crc);
    tx_buf[4 + data_length + 2] = COMM_PROTOCOL_ETX;

    packet_length = 4 + data_length + 2 + 1;

    return packet_length;
}

