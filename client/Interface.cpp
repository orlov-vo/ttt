//
// Created by biziw on 20.12.2015.
//

#include <iostream>
#include "Interface.h"

void Interface::display() {
    std::cout << "\Ec";
    std::cout << "STATUS: ";
    switch (status_) {
        case WAIT:
            std::cout << "wait player..." << std::endl;
            break;
        case STARTED:
            std::cout << "play game..." << std::endl;
            board_.print();

            if (can_move_) {
                std::cout << std::endl;
                int cell = 0;
                do {
                    do {
                        std::cout << "\E[1A\E[0J";
                        std::cout << "Enter cell (1-9): ";
                        std::cin >> cell;
                    } while (cell < 1 && cell > 9);
                } while (!board_.setcell((char) (cell - 1), B_TIC));
                Message msg(CMSG_SETCELL, (unsigned int) (cell - 1));
                client_.write(msg);
                can_move_ = false;
                display();
            }
            break;
        case FINISHED:
            std::cout << "finished..." << std::endl;
            if (win_) {
                std::cout << "Congratulations! You won opponent!" << std::endl;
            } else {
                std::cout << "You lose!" << std::endl;
            }
            // TODO: retry or exit?
            break;
    }
}

void Interface::start(unsigned int data) {
    can_move_ = data == 1;
    status_ = STARTED;
    display();
}

void Interface::stop(unsigned int data) {
    win_ = data == 1;
    status_ = FINISHED;
    board_.flush();
    display();
}

void Interface::parse_msg(message_type t, char *body) {
    unsigned int data = *((unsigned int*) body);
    switch (t) {
        case SMSG_START_GAME:
            start(data);
            break;
        case SMSG_STOP_GAME:
            stop(data);
            break;
        case SMSG_SETCELL:
            setcell(data);
            break;
        default:
            std::cerr << "Wrong opcode: " << (int) t << std::endl;
    }
}

bool Interface::work() {
    while (!read_msgs_.empty()) {
        auto msg = read_msgs_.front();
        parse_msg(msg.type(), msg.body());
        read_msgs_.pop_front();
    }
    return true;
}

void Interface::incomming_msg(const Message &msg) {
    read_msgs_.push_back(msg);
}

void Interface::setcell(unsigned int data) {
    board_.setcell((char) data, B_TAC);
    can_move_ = true;
    display();
}