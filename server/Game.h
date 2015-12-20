//
// Created by biziw on 20.12.2015.
//

#ifndef TIC_TAC_TOE_GAME_H
#define TIC_TAC_TOE_GAME_H

#include <iostream>
#include "../shared/GameBoard.h"
#include "Pointers.h"
#include "Player.h"

class Game :
        public std::enable_shared_from_this<Game> {
public:
    Game(Room &room, player_ptr player1, player_ptr player2)
            : room_(room), player1_(player1), player2_(player2) {
    }

    void start();
    void stop();
    void parse_msg(player_ptr player, const Message &msg);
    void leave(player_ptr player);

private:
    bool finished_ = false;
    player_ptr player1_;
    player_ptr player2_;
    GameBoard board_;
    Room &room_;
};

#endif //TIC_TAC_TOE_GAME_H
