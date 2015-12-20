//
// Created by biziw on 20.12.2015.
//

#ifndef TIC_TAC_TOE_SERVER_H
#define TIC_TAC_TOE_SERVER_H

#include <boost/asio.hpp>
#include "Room.h"
#include "Session.h"
#include "Player.h"

using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_service &io_service, const tcp::endpoint &endpoint)
            : acceptor_(io_service, endpoint), socket_(io_service) {
        do_accept();
    }

private:
    void do_accept();

    tcp::acceptor acceptor_;
    tcp::socket socket_;
    Room room_;
};


#endif //TIC_TAC_TOE_SERVER_H
