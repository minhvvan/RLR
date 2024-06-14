#include "pch.h"
#include "ClientHandler.h"
#include "Filter.h"
#include "UserManager.h"
#include "Server.h"
#include <iostream>
#include "Whisper.h"
void StopListening() {
    // 클라이언트 연결 대기 종료
    std::cout << "Stopped listening for clients" << std::endl;
}
void RemoveClient(const std::string& clientId) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    auto it = users.find(clientId);
    if (it != users.end()) {
        closesocket(it->second.socket);
        users.erase(it);
        clients.erase(clientId);
        std::cout << "Client " << clientId << " removed." << std::endl;
    }
}

void HandleClientMessage(ClientContext* context, const std::string& message) {
    if (context->clientId.empty()) {
        context->clientId = message;
        {
            std::lock_guard<std::mutex> lock(clientsMutex);
            clients[context->clientId] = context->socket;
            users[context->clientId] = { context->socket, context->clientId, "근처", "", "", "", "", "" };
        }
        std::cout << "Client ID set: " << context->clientId << std::endl;
    }
    else {
        if (message.compare("/quit") == 0) {
            RemoveClient(context->clientId);
        }
        else if (message.find("/setlocation ") == 0) {
            std::string location = message.substr(13);
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                users[context->clientId].location = location;
            }
            std::cout << "Client " << context->clientId << " location set to " << location << std::endl;
        }
        else if (message.find("/setguild ") == 0) {
            std::string guild = message.substr(10);
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                users[context->clientId].guild = guild;
            }
            std::cout << "Client " << context->clientId << " guild set to " << guild << std::endl;
        }
        else if (message.find("/setparty ") == 0) {
            std::string party = message.substr(10);
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                users[context->clientId].party = party;
            }
            std::cout << "Client " << context->clientId << " party set to " << party << std::endl;
        }
        else if (message.find("/setraid ") == 0) {
            std::string raid = message.substr(9);
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                users[context->clientId].raid = raid;
            }
            std::cout << "Client " << context->clientId << " raid set to " << raid << std::endl;
        }
        else if (message.find("/setcountry ") == 0) {
            std::string country = message.substr(12);
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                users[context->clientId].country = country;
            }
            std::cout << "Client " << context->clientId << " country set to " << country << std::endl;
        }
        else if (message.find("/setcontinent ") == 0) {
            std::string continent = message.substr(14);
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                users[context->clientId].continent = continent;
            }
            std::cout << "Client " << context->clientId << " continent set to " << continent << std::endl;
        }
        
        else {  
            std::string filteredMessage = FilterMessage(message);
            std::string broadcastMessage = "[일반] " + context->clientId + ": " + filteredMessage;

            if (filteredMessage.find("/w ") == 0) {
                size_t firstSpace = filteredMessage.find(' ', 3);
                if (firstSpace != std::string::npos) {
                    std::string targetId = filteredMessage.substr(3, firstSpace - 3);
                    std::string completeMessage = filteredMessage.substr(firstSpace + 1);
                    HandleWhisperMessage(context->clientId, targetId, completeMessage);
                }
            }
            else if (filteredMessage.find("/chat ") == 0) {
                size_t firstSpace = filteredMessage.find(' ', 6);
                if (firstSpace != std::string::npos) {
                    std::string scopeStr = filteredMessage.substr(6, firstSpace - 6);
                    std::string chatMessage = filteredMessage.substr(firstSpace + 1);
                    ChatScope scope;

                    if (scopeStr == "일반") {
                        scope = GENERAL;
                    }
                    else if (scopeStr == "귓속말") {
                        scope = WHISPER;
                    }
                    else if (scopeStr == "동료") {
                        scope = NEARBY;
                    }
                    else if (scopeStr == "파티") {
                        scope = PARTY;
                    }
                    else if (scopeStr == "길드") {
                        scope = GUILD;
                    }
                    else if (scopeStr == "레이드") {
                        scope = RAID;
                    }
                    else if (scopeStr == "국가") {
                        scope = COUNTRY;
                    }
                    else if (scopeStr == "대륙") {
                        scope = CONTINENT;
                    }
                    else if (scopeStr == "세계") {
                        scope = WORLD;
                    }
                    else {
                        std::cout << "Invalid chat scope: " << scopeStr << std::endl;
                        return;
                    }

                    SendMessageToScope(context->clientId, chatMessage, scope);
                }
            }
            else {
                std::cout << "Received: " << broadcastMessage << std::endl;
                BroadcastMessage(broadcastMessage);
            }
        }
    }

    context->wsabuf.buf = context->buffer;
    context->wsabuf.len = BUFFER_SIZE;
    DWORD flags = 0;
    WSARecv(context->socket, &context->wsabuf, 1, NULL, &flags, &context->overlapped, NULL);
}
