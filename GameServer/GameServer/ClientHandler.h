#pragma once
#include "pch.h"
#include <winsock2.h>
#include <string>

#define BUFFER_SIZE 1024

struct ClientContext {
    OVERLAPPED overlapped;
    WSABUF wsabuf;
    char buffer[BUFFER_SIZE];
    SOCKET socket;
    DWORD bytesReceived;
    std::string clientId;
};

void RemoveClient(const std::string& username);
void HandleClientMessage(ClientContext* context, const std::string& message);
void StopListening();
