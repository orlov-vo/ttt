//
// Created by biziw on 20.12.2015.
//

#include "Server.h"

void Server::do_accept() {
    acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
        if (!ec) {
            std::make_shared<Session>(std::move(socket_), room_)->start();
        }
        do_accept();
    });
}