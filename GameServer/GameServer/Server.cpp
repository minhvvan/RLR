#include "pch.h"
#include "Server.h"
#include "ClientHandler.h"
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 6000
#define WORKER_THREADS 16

std::unordered_map<std::string, SOCKET> clients;
std::mutex clientsMutex;

void InitializeServer() {
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
}

void StartServer()
{

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
        if (receivedMessage.compare("/quit") == 0) {
            RemoveClient(context->clientId);
            delete context;
            continue;
        }
       HandleClientMessage(context, receivedMessage);
    }
}

void ShutdownServer() {
    // 서버 종료 코드
    std::cout << "Server shutting down" << std::endl;
    StopListening(); // 클라이언트 연결 종료
}
