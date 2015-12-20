//
// Created by biziw on 20.12.2015.
//

#ifndef TIC_TAC_TOE_POINTERS_H
#define TIC_TAC_TOE_POINTERS_H

#include <memory>

class Room;
typedef std::shared_ptr<Room> room_ptr;

class Game;
typedef std::shared_ptr<Game> game_ptr;

class Player;
typedef std::shared_ptr<Player> player_ptr;

#endif //TIC_TAC_TOE_POINTERS_H
