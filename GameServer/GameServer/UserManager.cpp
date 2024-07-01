<<<<<<< Updated upstream
#include "pch.h"
#include "UserManager.h"
#include "Server.h"
#include <mutex>
#include <iostream>

std::unordered_map<std::string, User> users;

void SendMessageToUser(const std::string& username, const std::string& message) {
    auto it = users.find(username);
    if (it != users.end()) {
        const User& user = it->second;
        send(user.socket, message.c_str(), message.size(), 0);
    }
    else {
        std::cout << "User " << username << " not found." << std::endl;
    }
}void SendMessageToScope(const std::string& senderId, const std::string& message, ChatScope scope) {
    std::lock_guard<std::mutex> lock(clientsMutex);

    string completeMessage = "";
    
    for (const auto& pair : users) {
        const std::string& id = pair.first;
        const User& user = pair.second;
        bool sendMessage = false;

        switch (scope) {
        case GENERAL:
            sendMessage = true;
            completeMessage = "[일반] " + senderId + " : " + message;
            break;
        case WHISPER:
            sendMessage = (id == senderId);
            completeMessage = "[귓속말] " + senderId + " : " + message;
            break;
        case NEARBY:
            sendMessage = (user.location == users[senderId].location);
            completeMessage = "[동료] " + senderId + " : " + message;
            break;
        case PARTY:
            sendMessage = (user.party == users[senderId].party);
            completeMessage = "[파티] " + senderId + " : " + message;
            break;
        case GUILD:
            sendMessage = (user.guild == users[senderId].guild);
            completeMessage = "[길드] " + senderId + " : " + message;
            break;
        case RAID:
            sendMessage = (user.raid == users[senderId].raid);
            completeMessage = "[레이드] " + senderId + " : " + message;
            break;
        case COUNTRY:
            sendMessage = (user.country == users[senderId].country);
            completeMessage = "[국가] " + senderId + " : " + message;
            break;
        case CONTINENT:
            completeMessage = "[대륙] " + senderId + " : " + message;
            sendMessage = (user.continent == users[senderId].continent);
            break;
        }

        if (sendMessage) {
            send(user.socket, completeMessage.c_str(), completeMessage.size(), 0);
        }
    }
}



void BroadcastMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (const auto& client : clients) {
        SendToClient(client.second, message);
    }
}

void SendToClient(SOCKET clientSocket, const std::string& message) {
    WSABUF wsabuf;
    wsabuf.buf = const_cast<char*>(message.c_str());
    wsabuf.len = static_cast<ULONG>(message.size());

    DWORD bytesSent = 0;
    int result = WSASend(clientSocket, &wsabuf, 1, &bytesSent, 0, NULL, NULL);
    if (result == SOCKET_ERROR) {
        int error = WSAGetLastError();
        if (error != WSAEWOULDBLOCK) {
            // 에러 처리
            std::cerr << "Failed to send message to client. Error code: " << error << std::endl;
        }
    }
}
=======
#include "pch.h"
#include "UserManager.h"
#include "Server.h"
#include <mutex>
#include <iostream>

std::unordered_map<std::string, User> users;

void SendMessageToUser(const std::string& username, const std::string& message) {
    auto it = users.find(username);
    if (it != users.end()) {
        const User& user = it->second;
        send(user.socket, message.c_str(), message.size(), 0);
    }
    else {
        std::cout << "User " << username << " not found." << std::endl;
    }
}void SendMessageToScope(const std::string& senderId, const std::string& message, ChatScope scope) {
    std::lock_guard<std::mutex> lock(clientsMutex);

    string completeMessage = "";
    
    for (const auto& pair : users) {
        const std::string& id = pair.first;
        const User& user = pair.second;
        bool sendMessage = false;

        switch (scope) {
        case GENERAL:
            sendMessage = true;
            completeMessage = "[일반] " + senderId + " : " + message;
            break;
        case WHISPER:
            sendMessage = (id == senderId);
            completeMessage = "[귓속말] " + senderId + " : " + message;
            break;
        case NEARBY:
            sendMessage = (user.location == users[senderId].location);
            completeMessage = "[동료] " + senderId + " : " + message;
            break;
        case PARTY:
            sendMessage = (user.party == users[senderId].party);
            completeMessage = "[파티] " + senderId + " : " + message;
            break;
        case GUILD:
            sendMessage = (user.guild == users[senderId].guild);
            completeMessage = "[길드] " + senderId + " : " + message;
            break;
        case RAID:
            sendMessage = (user.raid == users[senderId].raid);
            completeMessage = "[레이드] " + senderId + " : " + message;
            break;
        case COUNTRY:
            sendMessage = (user.country == users[senderId].country);
            completeMessage = "[국가] " + senderId + " : " + message;
            break;
        case CONTINENT:
            completeMessage = "[대륙] " + senderId + " : " + message;
            sendMessage = (user.continent == users[senderId].continent);
            break;
        }

        if (sendMessage) {
            send(user.socket, completeMessage.c_str(), completeMessage.size(), 0);
        }
    }
}



void BroadcastMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (const auto& client : clients) {
        SendToClient(client.second, message);
    }
}

void SendToClient(SOCKET clientSocket, const std::string& message) {
    WSABUF wsabuf;
    wsabuf.buf = const_cast<char*>(message.c_str());
    wsabuf.len = static_cast<ULONG>(message.size());

    DWORD bytesSent = 0;
    int result = WSASend(clientSocket, &wsabuf, 1, &bytesSent, 0, NULL, NULL);
    if (result == SOCKET_ERROR) {
        int error = WSAGetLastError();
        if (error != WSAEWOULDBLOCK) {
            // 에러 처리
            std::cerr << "Failed to send message to client. Error code: " << error << std::endl;
        }
    }
}
>>>>>>> Stashed changes
