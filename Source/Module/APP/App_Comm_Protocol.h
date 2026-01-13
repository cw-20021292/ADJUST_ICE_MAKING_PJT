/**
 * File : App_Comm_Protocol.h
 *
 * Application Programming Interface
 * Depend on API
*/

#ifndef __APP_COMM_PROTOCOL_H__
#define __APP_COMM_PROTOCOL_H__

#include "api_uart.h"

#define COMM_PROTOCOL_STX        0x02
#define COMM_PROTOCOL_ETX        0x03
#define COMM_PROTOCOL_ID_PC      0x01
#define COMM_PROTOCOL_ID_MAIN    0x02
#define COMM_PROTOCOL_ID_FRONT   0x03
#define COMM_PROTOCOL_CMD_CLI     0xFF

#define COMM_PROTOCOL_PACKET_BASIC_LENGTH          7

#define GET_16_HIGH_BYTE(val)       (U8)(((val)&0xFF00) >> 8)
#define GET_16_LOW_BYTE(val)        (U8)((val)&0x00FF)

typedef enum
{
    PROTOCOL_IDX_STX = 0,
    PROTOCOL_IDX_ID = 1,
    PROTOCOL_IDX_CMD = 2,
    PROTOCOL_IDX_LENGTH = 3,
    PROTOCOL_IDX_DATA = 4,
} PROTOCOL_INDEX;


U8 Protocol_isValidPacket(U8 *buf);
U8 Protocol_Make_Ack_Packet(U8 *buf, U8 *tx_buf);



#endif /*__APP_COMM_PROTOCOL_H__*/

