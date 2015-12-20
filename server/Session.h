//
// Created by biziw on 20.12.2015.
//

#ifndef TIC_TAC_TOE_SESSION_H
#define TIC_TAC_TOE_SESSION_H

#include <boost/asio.hpp>
#include "../shared/Message.h"
#include "Room.h"
#include "Player.h"

using boost::asio::ip::tcp;

class Session
        : public Player,
          public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket, Room &room)
            : socket_(std::move(socket)), room_(room), game_(NULL) {
    }

    void start() {
        room_.join(shared_from_this());
    }

    void start_game(game_ptr game) {
        game_ = game;
        do_read();
    }

    void stop_game() {
        game_.reset();
    }

    void kick() {
//        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
//        socket_.close();
    }

    void deliver(const Message &msg) {
        bool write_in_progress = !write_msgs_.empty();
        std::cout << "Send for plr " << this << " msg t" << msg.type() << (write_in_progress ? 'w' : 'n') << " " <<
        *((unsigned int *) msg.body()) << std::endl;
        write_msgs_.push_back(msg);
        if (!write_in_progress) {
            do_write();
        }
    }

    void leave() {
        if (game_.get() != NULL) game_->leave(shared_from_this());
        room_.leave(shared_from_this());
    }

private:
    void do_read() {
        auto self(shared_from_this());
        boost::asio::async_read(socket_,
                                boost::asio::buffer(read_msg_.data(), Message::length()),
                                [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                                    if (!ec) {
                                        game_->parse_msg(shared_from_this(), read_msg_);
                                        do_read();
                                    } else {
                                        std::cout << boost::system::system_error(ec).what() << std::endl;
                                        leave();
                                    }
                                });
    }

    void do_write() {
        auto self(shared_from_this());
        boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
                                 [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                                     if (!ec) {
                                         write_msgs_.pop_front();
                                         if (!write_msgs_.empty()) {
                                             do_write();
                                         }
                                     } else {
                                         std::cout << boost::system::system_error(ec).what() << std::endl;
                                         leave();
                                     }
                                 });
    }

    tcp::socket socket_;
    Room &room_;
    game_ptr game_;
    Message read_msg_;
    message_queue write_msgs_;
};


#endif //TIC_TAC_TOE_SESSION_H
