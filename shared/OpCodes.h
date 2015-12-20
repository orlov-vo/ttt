//
// Created by biziw on 20.12.2015.
//

#ifndef TIC_TAC_TOE_PROTOCOL_H
#define TIC_TAC_TOE_PROTOCOL_H

typedef enum {
    AMSG_ERROR,
    CMSG_SETCELL,
    SMSG_SETCELL,
    SMSG_START_GAME,
    SMSG_STOP_GAME,
} message_type;

#endif //TIC_TAC_TOE_PROTOCOL_H
