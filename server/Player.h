//
// Created by biziw on 20.12.2015.
//

#ifndef TIC_TAC_TOE_PLAYER_H
#define TIC_TAC_TOE_PLAYER_H

#include <memory>
#include <deque>
#include "../shared/Message.h"
#include "Pointers.h"

typedef std::deque<Message> message_queue;

class Player {
public:
    virtual ~Player() { }

    virtual void deliver(const Message &msg) = 0;

    virtual void start_game(game_ptr game) = 0;
    virtual void stop_game() = 0;

    virtual void kick() = 0;
};

#endif //TIC_TAC_TOE_PLAYER_H
