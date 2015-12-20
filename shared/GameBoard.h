//
// Created by biziw on 20.12.2015.
//

#ifndef TIC_TAC_TOE_GAMEBOARD_H
#define TIC_TAC_TOE_GAMEBOARD_H

#include <array>

typedef enum { B_EMPTY, B_TIC, B_TAC} cell_type;

class GameBoard {
public:
    GameBoard() {
    }
    void print();
    void flush() {
        for (auto it = board_.begin(); it != board_.end(); ++it) {
            *it = B_EMPTY;
        }
    }
    bool setcell(char index, cell_type e);
    int status();
private:
    char symbol(cell_type c);
    std::array<cell_type, 9> board_ {};
};


#endif //TIC_TAC_TOE_GAMEBOARD_H
