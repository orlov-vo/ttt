#include <iostream>
#include <thread>

#include <boost/asio.hpp>
#include "../shared/Message.h"
#include "Client.h"
#include "Interface.h"

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: ttt_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);
        auto endpoint_iterator = resolver.resolve({argv[1], argv[2]});
        Client c(io_service, endpoint_iterator);
        Interface *i = c.make_interface();

        std::thread t([&io_service]() { io_service.run(); });

        while (i->work()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        c.close();
        t.join();
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}