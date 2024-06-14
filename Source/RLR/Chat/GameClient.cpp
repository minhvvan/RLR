// Fill out your copyright notice in the Description page of Project Settings.


#include "GameClient.h"




// Called every frame
void AGameClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


AGameClient::AGameClient()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AGameClient::BeginPlay()
{
    Super::BeginPlay();

    // Initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        UE_LOG(LogTemp, Error, TEXT("WSAStartup failed with error: %d"), result);
        return;
    }
}


bool AGameClient::ConnectToServer(const FString& ServerAddress, const FString& Port)
{
    struct addrinfo* result = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int res = getaddrinfo(TCHAR_TO_UTF8(*ServerAddress), TCHAR_TO_UTF8(*Port), &hints, &result);
    if (res != 0)
    {
        UE_LOG(LogTemp, Error, TEXT("getaddrinfo failed with error: %d"), res);
        WSACleanup();
        return false;
    }

    ClientSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ClientSocket == INVALID_SOCKET)
    {
        UE_LOG(LogTemp, Error, TEXT("socket failed with error: %ld"), WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return false;
    }

    res = connect(ClientSocket, result->ai_addr, (int)result->ai_addrlen);
    if (res == SOCKET_ERROR)
    {
        closesocket(ClientSocket);
        ClientSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);

    if (ClientSocket == INVALID_SOCKET)
    {
        UE_LOG(LogTemp, Error, TEXT("Unable to connect to server!"));
        WSACleanup();
        return false;
    }

    return true;
}

bool AGameClient::SendData(const FString& DataToSend)
{
    if (ClientSocket == INVALID_SOCKET) return false;

    std::string Utf8String = TCHAR_TO_UTF8(*DataToSend);
    const char* serializedChar = Utf8String.c_str();
    int32 size = Utf8String.length();

    int result = send(ClientSocket, serializedChar, size, 0);
    if (result == SOCKET_ERROR)
    {
        UE_LOG(LogTemp, Error, TEXT("send failed with error: %d"), WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return false;
    }

    return true;
}

bool AGameClient::SendMovePacket(int32 PlayerId, float NewX, float NewY)
{
    if (ClientSocket == INVALID_SOCKET) return false;

    // Packet structure: [PacketType, PlayerId, NewX, NewY]
    char packet[256];
    int offset = 0;

    PacketType packetType =  PacketType::MOVE_REQUEST;
    memcpy(packet + offset, &packetType, sizeof(packetType));
    offset += sizeof(packetType);
    memcpy(packet + offset, &PlayerId, sizeof(PlayerId));
    offset += sizeof(PlayerId);
    memcpy(packet + offset, &NewX, sizeof(NewX));
    offset += sizeof(NewX);
    memcpy(packet + offset, &NewY, sizeof(NewY));
    offset += sizeof(NewY);

    int packetSize = offset;

    int result = send(ClientSocket, packet, packetSize, 0);
    if (result == SOCKET_ERROR)
    {
        UE_LOG(LogTemp, Error, TEXT("send failed with error: %d"), WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return false;
    }

    return true;
}

void AGameClient::CloseConnection()
{
    if (ClientSocket != INVALID_SOCKET)
    {
        closesocket(ClientSocket);
        WSACleanup();
    }
}