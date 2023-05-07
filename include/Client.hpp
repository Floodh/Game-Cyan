#pragma once

#include "SafeQue.hpp"
#include <iostream>
#include <winsock2.h>

#define SERVER "213.204.195.24"  // or "localhost" - ip address of UDP server
#define BUFLEN 512  // max length of answer
#define PORT 8888  // the port on which to listen for incoming data

#define PKGSIZE ((1 + 1 +  1 + 1 + 20 * 3) * 8)
#define CLIENTNUMBER 1

struct Message
{
    const char* message;
    Message(const char* message)
        : message{message}
    {}
};


inline SafeQueue<Message> eventQueue{};
inline SafeQueue<Message> sendMessageQue{};


int clientThread();

