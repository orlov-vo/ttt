//
// Created by biziw on 20.12.2015.
//

#include <iostream>
#include "GameBoard.h"

void GameBoard::print() {
    std::cout << symbol(board_[6]) << " | " << symbol(board_[7]) << " | " << symbol(board_[8]) << std::endl;
    std::cout << std::string(9, '-') << std::endl;
    std::cout << symbol(board_[3]) << " | " << symbol(board_[4]) << " | " << symbol(board_[5]) << std::endl;
    std::cout << std::string(9, '-') << std::endl;
    std::cout << symbol(board_[0]) << " | " << symbol(board_[1]) << " | " << symbol(board_[2]) << std::endl;
}

char GameBoard::symbol(cell_type c) {
    switch (c) {
        case B_EMPTY:
            return ' ';
        case B_TIC:
            return 'X';
        case B_TAC:
            return 'O';
    }
    return '%';
}

bool GameBoard::setcell(char index, cell_type e) {
    static bool tic = true;
    if (e != B_EMPTY && index >= 0 && index < board_.size() && board_[index] == B_EMPTY) {
        board_[index] = e;
        return true;
    }
    return false;
}

// return 0 - if played, 1 - won 1plr, 2 - won 2plr, 3 - no won
int GameBoard::status() {
    if (board_[0] != B_EMPTY && board_[0] == board_[1] && board_[0] == board_[2]) // check first line
        if (board_[0] == B_TIC) return 1; else return 2;
    if (board_[3] != B_EMPTY && board_[3] == board_[4] && board_[3] == board_[5]) // check second line
        if (board_[3] == B_TIC) return 1; else return 2;
    if (board_[6] != B_EMPTY && board_[6] == board_[7] && board_[6] == board_[8]) // check last line
        if (board_[6] == B_TIC) return 1; else return 2;
    if (board_[0] != B_EMPTY && board_[0] == board_[3] && board_[0] == board_[6]) // check first row
        if (board_[0] == B_TIC) return 1; else return 2;
    if (board_[1] != B_EMPTY && board_[1] == board_[4] && board_[1] == board_[7]) // check second row
        if (board_[1] == B_TIC) return 1; else return 2;
    if (board_[2] != B_EMPTY && board_[2] == board_[5] && board_[2] == board_[8]) // check last row
        if (board_[2] == B_TIC) return 1; else return 2;
    if (board_[0] != B_EMPTY && board_[0] == board_[4] && board_[0] == board_[8]) // check diag 1
        if (board_[0] == B_TIC) return 1; else return 2;
    if (board_[2] != B_EMPTY && board_[2] == board_[4] && board_[2] == board_[6]) // check diag 2
        if (board_[2] == B_TIC) return 1; else return 2;
    bool no_empty = true;
    for (auto it: board_) {
        if (it == B_EMPTY) {
            no_empty = false;
            break;
        }
    }
    return (no_empty) ? 3 : 0;
}
