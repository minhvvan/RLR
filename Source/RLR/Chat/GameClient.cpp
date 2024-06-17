#include "GameClient.h"
#include "Networking.h"
#include "Runtime/Core/Public/HAL/RunnableThread.h"
#include "EngineUtils.h"
#include "Engine/World.h"

AGameClient::AGameClient()
{
    PrimaryActorTick.bCanEverTick = true;
    ClientSocket = INVALID_SOCKET;
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

void AGameClient::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    char buffer[256];
    if (ReceiveData(buffer, sizeof(buffer)))
    {
        uint8_t packetType = buffer[0];
        switch (packetType)
        {
        case MOVE_RESPONSE:
            UE_LOG(LogTemp, Log, TEXT("MOVE_RESPONSE packet received"));
            ProcessMoveResponse(buffer);
            break;
        default:
            UE_LOG(LogTemp, Warning, TEXT("Unknown packet type: %d"), packetType);
            break;
        }
    }
}

bool AGameClient::ConnectToServer(const FString& ServerAddress, const FString& Port)
{
    ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ClientSocket == INVALID_SOCKET)
    {
        UE_LOG(LogTemp, Error, TEXT("socket failed with error: %ld"), WSAGetLastError());
        WSACleanup();
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(FCString::Atoi(*Port));
    serverAddr.sin_addr.s_addr = inet_addr(TCHAR_TO_UTF8(*ServerAddress));

    int res = connect(ClientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (res == SOCKET_ERROR)
    {
        UE_LOG(LogTemp, Error, TEXT("connect failed with error: %ld"), WSAGetLastError());
        closesocket(ClientSocket);
        ClientSocket = INVALID_SOCKET;
        WSACleanup();
        return false;
    }

    UE_LOG(LogTemp, Log, TEXT("연결 완료, Client Socket: %d"), ClientSocket);
    return true;
}

bool AGameClient::SendMovePacket(int32 PlayerId, float NewX, float NewY)
{
    if (ClientSocket == INVALID_SOCKET) return false;

    // Packet structure: [PacketType, PlayerId, NewX, NewY]
    char packet[256];
    int offset = 0;
    UE_LOG(LogTemp, Log, TEXT("이동은 들어왔음"));
    PacketType packetType = PacketType::MOVE_REQUEST;
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
        int error = WSAGetLastError();
        UE_LOG(LogTemp, Error, TEXT("send failed with error: %d"), error);

        if (error == WSAECONNRESET)
        {
            UE_LOG(LogTemp, Error, TEXT("Connection reset by peer"));
        }

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

bool AGameClient::ReceiveData(char* buffer, int bufferSize)
{
    if (ClientSocket == INVALID_SOCKET) return false;
    UE_LOG(LogTemp, Log, TEXT("Receive Start"));

    int result = recv(ClientSocket, buffer, bufferSize, 0);
    if (result > 0)
    {
        return true;
    }
    else if (result == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Connection closed"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("recv failed with error: %d"), WSAGetLastError());
    }

    return false;
}

void AGameClient::ProcessMoveResponse(const char* data)
{
    MoveResponsePacket packet;
    memcpy(&packet, data, sizeof(MoveResponsePacket));

    int32_t userSeq = packet.playerSeq;
    float newX = packet.newX;
    float newY = packet.newY;
    bool success = packet.success;

    // Find the player actor in the game world and update its position
    APlayerCharacter* PlayerCharacter = FindPlayerCharacterBySeq(userSeq);
    if (PlayerCharacter && success)
    {
        FVector NewPosition(newX, newY, PlayerCharacter->GetActorLocation().Z);
        PlayerCharacter->SetActorLocation(NewPosition);
    }
}

APlayerCharacter* AGameClient::FindPlayerCharacterBySeq(int32_t userSeq)
{
    for (TActorIterator<APlayerCharacter> It(GetWorld()); It; ++It)
    {
        APlayerCharacter* PlayerCharacter = *It;
        if (PlayerCharacter && PlayerCharacter->GetPlayerSeq() == userSeq)
        {
            return PlayerCharacter;
        }
    }

    return nullptr;
}
