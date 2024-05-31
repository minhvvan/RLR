#include <iostream>
#include <vector>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

struct ClientInfo {
    SOCKET socket;
    sockaddr_in address;
};

vector<ClientInfo> clients;

DWORD WINAPI ClientThread(LPVOID lpParam) {
    SOCKET clientSocket = (SOCKET)lpParam;

    char buffer[1024];
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            cout << "Received: " << buffer << endl;

            // ����: Ŭ���̾�Ʈ�� ���� �޽����� �ٸ� Ŭ���̾�Ʈ���� ��ε�ĳ��Ʈ
            for (const auto& otherClient : clients) {
                if (otherClient.socket != clientSocket) {
                    send(otherClient.socket, buffer, bytesReceived, 0);
                }
                else {
                    send(otherClient.socket, buffer, bytesReceived, 0);
                }
            }
        }
        else if (bytesReceived == 0 || bytesReceived == SOCKET_ERROR) {
            // Ŭ���̾�Ʈ ������ ������ �� ó��
            cout << "Client disconnected" << endl;
            closesocket(clientSocket);

            // Ŭ���̾�Ʈ ��Ͽ��� �ش� Ŭ���̾�Ʈ ����
            clients.erase(
                remove_if(clients.begin(), clients.end(), [&](const ClientInfo& info) {
                    return info.socket == clientSocket;
                    }),
                clients.end());

            break;
        }
    }

    return 0;
}

int main() {
    // Winsock �ʱ�ȭ
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed" << endl;
        return 1;
    }

    // ���� ���� ����
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        cerr << "Error creating socket: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    // ���� �ּ� ���� �� ���ε�
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(11021); // ��Ʈ ��ȣ ����
    serverAddr.sin_addr.s_addr = INADDR_ANY; // ��� ��� ������ �ּҷκ��� ������ ���� ����
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Bind failed with error: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Ŭ���̾�Ʈ ��� �ʱ�ȭ
    clients.clear();

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        cerr << "Listen failed with error: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Server started, waiting for connections..." << endl;

    // Accept incoming connections and spawn client threads
    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            cerr << "Accept failed with error: " << WSAGetLastError() << endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        // Add client information to the vector
        ClientInfo clientInfo;
        clientInfo.socket = clientSocket;
        int addressLength = sizeof(clientInfo.address);
        getpeername(clientSocket, (sockaddr*)&clientInfo.address, &addressLength);

        clients.push_back(clientInfo);

        // Spawn a new thread to handle client communication
        thread clientThread(ClientThread, (LPVOID)clientSocket);
        clientThread.detach();
    }

    // Winsock ����
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
