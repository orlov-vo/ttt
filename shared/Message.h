//
// Created by biziw on 20.12.2015.
//

#ifndef TIC_TAC_TOE_MESSAGE_H
#define TIC_TAC_TOE_MESSAGE_H

#include <cstring>
#include "OpCodes.h"

class Message {
public:
    enum { header_length = 2 };
    enum { body_length = 4 };

    Message() {
        std::memset(data_, 0, Message::length());
    }
    Message(message_type type, unsigned int body) {
        std::memcpy(data_, &type, header_length);
        std::memcpy(data_ + header_length, &body, body_length);
    }

    const char *data() const {
        return data_;
    }

    char *data() {
        return data_;
    }

    static std::size_t length() {
        return header_length + body_length;
    }

    message_type type() const {
        message_type t = AMSG_ERROR;
        std::memcpy(&t, data(), header_length);
        return t;
    }

    const char *body() const {
        return data_ + header_length;
    }

    char *body() {
        return data_ + header_length;
    }

private:
    char data_[header_length + body_length];
};

#endif //TIC_TAC_TOE_MESSAGE_H
