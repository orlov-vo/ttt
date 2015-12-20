//
// Created by biziw on 20.12.2015.
//

#ifndef TIC_TAC_TOE_ROOM_H
#define TIC_TAC_TOE_ROOM_H

#include <set>
#include <iostream>
#include <vector>
#include "../shared/Message.h"
#include "../shared/GameBoard.h"
#include "Player.h"
#include "Game.h"

class Room {
public:
    void join(player_ptr player) {
        players_.push_back(player);
        std::cout << "Join player to lobby: " << player.get() << std::endl;
        if (players_.size() >= 2) {
            auto plr1 = players_.back();
            players_.pop_back();
            auto plr2 = players_.back();
            players_.pop_back();
            game_ptr g(new Game(*this, plr1, plr2));
            std::cout << "Create game " << g.get() << " for : " << plr1.get() << " and " << plr2.get() << std::endl;
            g->start();
            games_.push_back(g);
            while (games_.size() > max_recent_games)
                games_.pop_front();
        }
    }

    void leave(player_ptr player) {
        player->kick();
        for (auto it = players_.begin(); it != players_.end(); ++it)
            if (*it == player)
                players_.erase(it);
    }

private:
    std::vector<player_ptr> players_;
    enum { max_recent_games = 10 };
    std::deque<game_ptr> games_;
};


#endif //TIC_TAC_TOE_ROOM_H
