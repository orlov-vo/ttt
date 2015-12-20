//
// Created by biziw on 20.12.2015.
//

#ifndef TIC_TAC_TOE_CLIENT_H
#define TIC_TAC_TOE_CLIENT_H

#include <iostream>
#include <deque>
#include <boost/asio.hpp>
#include "../shared/Message.h"

using boost::asio::ip::tcp;

typedef std::deque<Message> message_queue;

class Interface;

class Client {
public:
    Client(boost::asio::io_service & io_service, tcp::resolver::iterator endpoint_iterator )
    : io_service_(io_service), socket_(io_service) {
        do_connect(endpoint_iterator);
    }

    void write(const Message &msg) {
        io_service_.post(
                [this, msg]() {
                    bool write_in_progress = !write_msgs_.empty();
                    write_msgs_.push_back(msg);
                    if (!write_in_progress) {
                        do_write();
                    }
                });
    }

    void close() {
        io_service_.post([this]() { socket_.close(); });
    }

    Interface *make_interface();


private:
    void do_connect(tcp::resolver::iterator endpoint_iterator);
    void do_read();
    void do_write();


private:
    boost::asio::io_service &io_service_;
    tcp::socket socket_;
    Message read_msg_;
    Interface *interface_;
    message_queue write_msgs_;
};

#endif //TIC_TAC_TOE_CLIENT_H
