#include <winsock2.h>
#include <windows.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <string>
#include <unordered_map>
#include <algorithm>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 6000
#define WORKER_THREADS 4
#define BUFFER_SIZE 512

std::unordered_map<std::string, SOCKET> clients;
std::mutex clientsMutex;
std::vector<std::string> filterWords = { "씨발", "섹스", "개새끼" }; // 필터링할 단어 목록

struct User
{
    SOCKET socket;
    std::string username;
};

struct ClientContext {
    OVERLAPPED overlapped;
    WSABUF wsabuf;
    char buffer[BUFFER_SIZE];
    SOCKET socket;
    DWORD bytesReceived;
    std::string clientId;
};

std::unordered_map<std::string, User> users;

void SendToClient(SOCKET clientSocket, const std::string& message) {
    WSABUF wsabuf;
    wsabuf.buf = const_cast<char*>(message.c_str());
    wsabuf.len = message.length();

    DWORD bytesSent;
    WSASend(clientSocket, &wsabuf, 1, &bytesSent, 0, NULL, NULL);
}

void SendMessageToUser(const std::string& username, const std::string& message)
{
    auto it = users.find(username);
    if (it != users.end())
    {
        const User& user = it->second;
        send(user.socket, message.c_str(), message.size(), 0);
    }
    else
    {
        std::cout << "User " << username << " not found." << std::endl;
    }
}

void BroadcastMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (const auto& client : clients) {
        SendToClient(client.second, message);
    }
}

std::string FilterMessage(const std::string& message) {
    std::string filteredMessage = message;
    for (const std::string& word : filterWords) {
        size_t pos = 0;
        while ((pos = filteredMessage.find(word, pos)) != std::string::npos) {
            filteredMessage.replace(pos, word.length(), std::string(word.length(), '*'));
            pos += word.length();
        }
    }
    return filteredMessage;
}

void WorkerThread(HANDLE completionPort) {
    DWORD bytesTransferred;
    ClientContext* context;
    OVERLAPPED* overlapped;

    while (true) {
        BOOL result = GetQueuedCompletionStatus(completionPort, &bytesTransferred, (PULONG_PTR)&context, &overlapped, INFINITE);

        if (!result) {
            std::cerr << "GetQueuedCompletionStatus failed: " << GetLastError() << std::endl;
            closesocket(context->socket);
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                clients.erase(context->clientId);
            }
            delete context;
            continue;
        }

        if (bytesTransferred == 0) {
            std::cout << "Client disconnected" << std::endl;
            closesocket(context->socket);
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                clients.erase(context->clientId);
            }
            delete context;
            continue;
        }

        context->buffer[bytesTransferred] = '\0';
        std::string receivedMessage(context->buffer);

        // 아이디가 없는 경우, 첫 메시지를 아이디로 간주
        if (context->clientId.empty()) {
            context->clientId = receivedMessage;
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                clients[context->clientId] = context->socket;
                users[context->clientId] = { context->socket, context->clientId };
            }
            std::cout << "Client ID set: " << context->clientId << std::endl;
        }
        else {
            std::string filteredMessage = FilterMessage(receivedMessage);
            std::string broadcastMessage = "[" + context->clientId + "]: " + filteredMessage;

            // 귓속말 메시지 처리
            if (filteredMessage.find("/w ") == 0) {
                size_t firstSpace = filteredMessage.find(' ', 3);
                if (firstSpace != std::string::npos) {
                    std::string targetId = filteredMessage.substr(3, firstSpace - 3);
                    std::string whisperMessage = "[" + context->clientId + " (whisper)]: " + filteredMessage.substr(firstSpace + 1);
                    std::lock_guard<std::mutex> lock(clientsMutex);
                    auto it = clients.find(targetId);
                    if (it != clients.end()) {
                        SendToClient(it->second, whisperMessage);
                        // 보낸 사람에게도 귓속말 메시지를 보냄
                        SendToClient(context->socket, whisperMessage);
                    }
                    else {
                        std::string errorMessage = "User \"" + targetId + "\" not found.";
                        SendToClient(context->socket, errorMessage);
                    }
                }
            }
            else {
                std::cout << "Received: " << broadcastMessage << std::endl;
                BroadcastMessage(broadcastMessage);
            }
        }

        // Continue to receive data
        context->wsabuf.buf = context->buffer;
        context->wsabuf.len = BUFFER_SIZE;
        DWORD flags = 0;
        WSARecv(context->socket, &context->wsabuf, 1, NULL, &flags, &context->overlapped, NULL);
    }
}

void HandleWhisperMessage(const std::string& fromUser, const std::string& toUser, const std::string& message)
{
    std::string fullMessage = "[Whisper from " + fromUser + "] " + message;

    // 로그 추가
    std::cout << "Sending whisper from " << fromUser << " to " << toUser << ": " << message << std::endl;

    // toUser에게 메시지 전송
    SendMessageToUser(toUser, fullMessage);
    // fromUser에게도 메시지 전송
    SendMessageToUser(fromUser, fullMessage);
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(listenSocket, SOMAXCONN);

    HANDLE completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

    // Create worker threads
    std::vector<std::thread> workers;
    for (int i = 0; i < WORKER_THREADS; ++i) {
        workers.emplace_back(WorkerThread, completionPort);
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    while (true) {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket != INVALID_SOCKET) {
            std::cout << "Client connected" << std::endl;

            ClientContext* context = new ClientContext();
            ZeroMemory(&context->overlapped, sizeof(OVERLAPPED));
            context->socket = clientSocket;
            context->wsabuf.buf = context->buffer;
            context->wsabuf.len = BUFFER_SIZE;

            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                clients[context->clientId] = clientSocket;
            }

            CreateIoCompletionPort((HANDLE)clientSocket, completionPort, (ULONG_PTR)context, 0);

            DWORD flags = 0;
            WSARecv(clientSocket, &context->wsabuf, 1, NULL, &flags, &context->overlapped, NULL);
        }
    }

    for (auto& worker : workers) {
        worker.join();
    }

    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
