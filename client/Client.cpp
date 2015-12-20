//
// Created by biziw on 20.12.2015.
//

#include "Client.h"
#include "Interface.h"

Interface *Client::make_interface() {
    Interface *i = new Interface(*this);
    interface_ = i;
    return i;
}

void Client::do_connect(tcp::resolver::iterator endpoint_iterator) {
    boost::asio::async_connect(socket_, endpoint_iterator,
                               [this](boost::system::error_code ec, tcp::resolver::iterator) {
                                   if (!ec) {
                                       do_read();
                                   }
                               });
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
void Client::do_read() {
    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_msg_.data(), Message::length()),
                            [this](boost::system::error_code ec, std::size_t /*length*/) {
                                if (!ec) {
                                    interface_->incomming_msg(read_msg_);
                                    do_read();
                                }
                                else {
                                    socket_.close();
                                }
                            });
}

void Client::do_write() {
    boost::asio::async_write(socket_,
                             boost::asio::buffer(write_msgs_.front().data(),
                                                 write_msgs_.front().length()),
                             [this](boost::system::error_code ec, std::size_t /*length*/) {
                                 if (!ec) {
                                     write_msgs_.pop_front();
                                     if (!write_msgs_.empty()) {
                                         do_write();
                                     }
                                 }
                                 else {
                                     socket_.close();
                                 }
                             });
}
#pragma clang diagnostic pop