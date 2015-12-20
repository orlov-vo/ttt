#include <iostream>
#include <boost/asio.hpp>
#include "Server.h"

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: ttt_server <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        std::list<Server> servers;
        tcp::endpoint endpoint(tcp::v4(), (unsigned short) std::atoi(argv[1]));
        servers.emplace_back(io_service, endpoint);

        io_service.run();
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}