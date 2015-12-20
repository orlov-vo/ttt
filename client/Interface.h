//
// Created by biziw on 20.12.2015.
//

#ifndef TIC_TAC_TOE_INTERFACE_H
#define TIC_TAC_TOE_INTERFACE_H

#include "../shared/GameBoard.h"
#include "Client.h"

class Interface {
public:
    Interface(Client &c)
            : client_(c) {
    }

    void display();
    void start(unsigned int data);
    void stop(unsigned int data);
    void setcell(unsigned int data);
    void incomming_msg(const Message &msg);
    bool work();

private:
    void parse_msg(message_type t, char *body);

    message_queue read_msgs_;
    Client &client_;
    GameBoard board_;
    enum { WAIT, STARTED, FINISHED} status_ = WAIT;
    bool can_move_ = false;
    bool win_ = false;
};


#endif //TIC_TAC_TOE_INTERFACE_H
