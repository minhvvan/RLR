<<<<<<< Updated upstream
﻿#include <iostream>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h> 
#include<thread>
#include"chrono"
#pragma comment(lib, "ws2_32.lib")

using std::thread;
SOCKET messageSocket;
void RecvMessage();
void SendMessages();
std::string message = "";
int main() {
    thread recvThread(RecvMessage);
    thread sendThread(SendMessages);
    // Initialize Winsock
    sendThread.join();
    recvThread.join();


    return 0;
}
void RecvMessage() {
    std::this_thread::sleep_for(std::chrono::microseconds(500));

    while (true) {
        if (message.compare("/quit") != 0) {
            char buffer[1024];
            int bytesReceived = recv(messageSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) {
                // 전송 성공
                buffer[bytesReceived] = '\0';
                std::cout << "[받은 내용]: " << buffer << std::endl;
            }
            else if (bytesReceived == 0) {
                // 오류 발생
                std::cout << "오류가 일어났습니다." << std::endl;
            }
            else {
                // recv 실패
                std::cerr << "recv 실패." << std::endl;
            }
        }
        else break;

        
    }
}


void SendMessages() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;

    }

    // Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        WSACleanup();

    }
    messageSocket = clientSocket;
    // Connect to server
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6000); // Server port
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // Server IP address
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();

    }

    std::cout << "Connected to chat server! Type '/quit' to exit." << std::endl;


    while (true) {
        std::cout << "Enter message: ";
        std::getline(std::cin, message);


        send(clientSocket, message.c_str(), message.length(), 0);


        if (message == "/quit") {

            break;
        }
        // Receive messages from server

    }

    // Close the socket
   
    closesocket(clientSocket);
    WSACleanup();

=======
﻿#include <iostream>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h> 
#include<thread>
#include"chrono"
#pragma comment(lib, "ws2_32.lib")

using std::thread;
SOCKET messageSocket;
void RecvMessage();
void SendMessages();
std::string message = "";
int main() {
    thread recvThread(RecvMessage);
    thread sendThread(SendMessages);
    // Initialize Winsock
    sendThread.join();
    recvThread.join();


    return 0;
}
void RecvMessage() {
    std::this_thread::sleep_for(std::chrono::microseconds(500));

    while (true) {
        if (message.compare("/quit") != 0) {
            char buffer[1024];
            int bytesReceived = recv(messageSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) {
                // 전송 성공
                buffer[bytesReceived] = '\0';
                std::cout << "[받은 내용]: " << buffer << std::endl;
            }
            else if (bytesReceived == 0) {
                // 오류 발생
                std::cout << "오류가 일어났습니다." << std::endl;
            }
            else {
                // recv 실패
                std::cerr << "recv 실패." << std::endl;
            }
        }
        else break;

        
    }
}


void SendMessages() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;

    }

    // Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        WSACleanup();

    }
    messageSocket = clientSocket;
    // Connect to server
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6000); // Server port
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // Server IP address
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();

    }

    std::cout << "Connected to chat server! Type '/quit' to exit." << std::endl;


    while (true) {
        std::cout << "Enter message: ";
        std::getline(std::cin, message);


        send(clientSocket, message.c_str(), message.length(), 0);


        if (message == "/quit") {

            break;
        }
        // Receive messages from server

    }

    // Close the socket
   
    closesocket(clientSocket);
    WSACleanup();

>>>>>>> Stashed changes
}