//
// Created by biziw on 20.12.2015.
//

#include "Game.h"
#include "Room.h"

void Game::start() {
    Message msg1(SMSG_START_GAME, 1);
    Message msg2(SMSG_START_GAME, 0);
    player1_->start_game(shared_from_this());
    player1_->deliver(msg1);
    player2_->start_game(shared_from_this());
    player2_->deliver(msg2);
}

void Game::stop() {
    finished_ = true;
    room_.join(player1_);
    room_.join(player2_);
}

void Game::parse_msg(player_ptr player, const Message &msg) {
    std::cout << "Recv from plr " << player.get() << " msg t" << msg.type() << " " << *((unsigned int*)msg.body()) << std::endl;
    auto t = msg.type();
    player_ptr other_plr;
    unsigned int idx;
    int status;
    switch (t) {
        case CMSG_SETCELL:
            idx = *((unsigned int *) msg.body());
            if (player1_ == player) {
                if (board_.setcell((char) idx, B_TIC)) {
                    other_plr = player2_;

                }
            } else if (player2_ == player) {
                if (board_.setcell((char) idx, B_TAC)) {
                    other_plr = player1_;
                }
            }
            status = board_.status();
            if (status == 1) {
                Message msg_w1(SMSG_STOP_GAME, 1);
                player1_->deliver(msg_w1);
                Message msg_w2(SMSG_STOP_GAME, 0);
                player2_->deliver(msg_w2);
                stop();
            } else if (status == 2) {
                Message msg_w1(SMSG_STOP_GAME, 0);
                player1_->deliver(msg_w1);
                Message msg_w2(SMSG_STOP_GAME, 1);
                player2_->deliver(msg_w2);
                stop();
            } else if (status == 3) {
                Message msg_w1(SMSG_STOP_GAME, 0);
                player1_->deliver(msg_w1);
                Message msg_w2(SMSG_STOP_GAME, 0);
                player2_->deliver(msg_w2);
                stop();
            } else {
                Message msg_sc(SMSG_SETCELL, idx);
                other_plr->deliver(msg_sc);
            }
            break;
        default:
            std::cerr << "Wrong OpCode: " << (int) t << std::endl;
    }
}

void Game::leave(player_ptr player) {
    finished_ = true;
    Message msg(SMSG_STOP_GAME, 1);
    player1_->deliver(msg);
    player2_->deliver(msg);
}