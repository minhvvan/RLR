#include "GameClient.h"
#include "Networking.h"
#include "Runtime/Core/Public/HAL/RunnableThread.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AGameClient::AGameClient() {
    PrimaryActorTick.bCanEverTick = true;
    clientSocket = INVALID_SOCKET;
    static ConstructorHelpers::FClassFinder<APlayerCharacter> PlayerCharacterBPClass(TEXT("/Game/Player/BP/BP_Player"));
    if (PlayerCharacterBPClass.Class != NULL) {
        playerCharacterClass = PlayerCharacterBPClass.Class;
    }
}

void AGameClient::BeginPlay() {
    Super::BeginPlay();
    FString serverAddress = TEXT("127.0.0.1");
    int32 serverPort = 27015; // 로그인 서버 포트

    if (!InitializeSocket(serverAddress, serverPort)) {
        UE_LOG(LogTemp, Error, TEXT("소켓 초기화 실패"));
    }
    else {
        UE_LOG(LogTemp, Log, TEXT("로그인 서버에 성공적으로 연결"));
        SendLoginPacket(TEXT("admin")); // 테스트 플레이어 ID
    }
}

void AGameClient::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    if (socket) {
        if (socket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromMilliseconds(100))) {
            uint8 Buffer[2048];
            int32 BytesRead = 0;
            if (socket->Recv(Buffer, sizeof(Buffer), BytesRead)) {
                if (BytesRead > 0) {
                    uint8_t packetType = Buffer[0];
                    switch (packetType) {
                    case MOVE_RESPONSE:
                        ProcessMoveResponse(reinterpret_cast<const char*>(Buffer));
                        break;
                    case INVENTORY_RESPONSE:
                        ProcessInventoryResponse(reinterpret_cast<const char*>(Buffer), BytesRead);
                        break;
                    case LOGIN_RESPONSE:
                        ProcessLoginResponse(reinterpret_cast<const char*>(Buffer));
                        break;
                    default:
                        UE_LOG(LogTemp, Warning, TEXT("알 수 없는 패킷 유형: %d"), packetType);
                        break;
                    }
                }
                else {
                    UE_LOG(LogTemp, Warning, TEXT("패킷 수신 실패 또는 읽은 바이트가 없습니다."));
                }
            }
        }
    }
}


bool AGameClient::SendLoginPacket(const FString& playerId) {
    if (!socket) return false;

    LoginRequestPacket packet;
    packet.packetType = LOGIN_REQUEST;
    strncpy_s(packet.playerId, TCHAR_TO_ANSI(*playerId), sizeof(packet.playerId) - 1);

    int32 BytesSent = 0;
    bool bIsSent = socket->Send(reinterpret_cast<uint8*>(&packet), sizeof(packet), BytesSent);

    if (!bIsSent || BytesSent != sizeof(packet)) {
        UE_LOG(LogTemp, Error, TEXT("로그인 패킷 전송 실패"));
        return false;
    }

    return true;
}

void AGameClient::ProcessLoginResponse(const char* data) {
    LoginResponsePacket packet = LoginResponsePacket::Deserialize(data);

    if (packet.success) {
        FString gameServerAddress = ANSI_TO_TCHAR(packet.gameServerAddress);
        int32 gameServerPort = packet.gameServerPort;

        CloseConnection();
        if (InitializeSocket(gameServerAddress, gameServerPort)) {
            UE_LOG(LogTemp, Log, TEXT("게임 서버에 성공적으로 연결: %s:%d"), *gameServerAddress, gameServerPort);
           
        }
        else {
            UE_LOG(LogTemp, Error, TEXT("게임 서버 연결 실패"));
        }
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("로그인 실패"));
    }
}

bool AGameClient::SendMovePacket(int32 playerSeq, float NewX, float NewY) {
    if (!socket) return false;  // 'socket'을 'Socket'으로 수정

    MoveRequestPacket packet;
    packet.packetType = MOVE_REQUEST;
    packet.playerSeq = playerSeq;
    packet.newX = NewX;
    packet.newY = NewY;

    int32 BytesSent = 0;
    bool bIsSent = socket->Send(reinterpret_cast<uint8*>(&packet), sizeof(packet), BytesSent);

    if (!bIsSent || BytesSent != sizeof(packet)) {
        UE_LOG(LogTemp, Error, TEXT("패킷 전송 실패"));
        return false;
    }

    return true;
}
bool AGameClient::SendInventoryPacket(int32 playerSeq)
{
    if (!socket) return false;

    InventoryRequestPacket packet;
    packet.packetType = INVENTORY_REQUEST;
    packet.playerSeq = playerSeq;


    int32 BytesSent = 0;
    bool bIsSent = socket->Send(reinterpret_cast<uint8*>(&packet), sizeof(packet), BytesSent);

    if (!bIsSent || BytesSent != sizeof(packet))
    {
        UE_LOG(LogTemp, Error, TEXT("패킷 전송 실패"));
        return false;
    }

    UE_LOG(LogTemp, Log, TEXT("InventoryRequestPacket 전송: playerSeq=%d, packetType=%d"), playerSeq, packet.packetType);

    return true;
}

void AGameClient::CloseConnection() {
    if (clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
        WSACleanup();
    }
}

bool AGameClient::InitializeSocket(const FString& serverAddress, int32 port) {
    FIPv4Address IP;
    if (!FIPv4Address::Parse(serverAddress, IP)) {
        UE_LOG(LogTemp, Error, TEXT("서버 주소 파싱 실패: %s"), *serverAddress);
        return false;
    }

    TSharedRef<FInternetAddr> InternetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    InternetAddr->SetIp(IP.Value);
    InternetAddr->SetPort(port);

    socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
    if (!socket) {
        UE_LOG(LogTemp, Error, TEXT("소켓 생성 실패"));
        return false;
    }

    if (!socket->Connect(*InternetAddr)) {
        UE_LOG(LogTemp, Error, TEXT("서버에 연결 실패"));
        return false;
    }

    UE_LOG(LogTemp, Log, TEXT("서버에 성공적으로 연결: %s:%d"), *serverAddress, port);
    return true;
}

bool AGameClient::ReceiveData(uint8* buffer, int32 bufferSize) {
    if (!socket) return false;

    int32 BytesRead = 0;
    UE_LOG(LogTemp, Log, TEXT("서버로부터 데이터 수신"));

    return socket->Recv(buffer, bufferSize, BytesRead);
}

APlayerCharacter* AGameClient::FindPlayerCharacterBySeq(int32_t playerSeq, float newX, float newY) {
    for (TActorIterator<APlayerCharacter> It(GetWorld()); It; ++It) {
        APlayerCharacter* PlayerCharacter = *It;
        if (PlayerCharacter && PlayerCharacter->GetPlayerSeq() == playerSeq) {
            return PlayerCharacter;
        }
    }

    return SpawnNewPlayerCharacter(playerSeq, newX, newY);
}

APlayerCharacter* AGameClient::SpawnNewPlayerCharacter(int32_t playerSeq, float newX, float newY) {
    if (!playerCharacterClass) {
        UE_LOG(LogTemp, Error, TEXT("PlayerCharacterClass가 설정되지 않았습니다."));
        return nullptr;
    }

    UWorld* World = GetWorld();
    if (!World) {
        UE_LOG(LogTemp, Error, TEXT("월드가 존재하지 않습니다."));
        return nullptr;
    }

    FVector SpawnLocation(newX, newY, 92.1064f);
    FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
    FActorSpawnParameters SpawnParams;
    APlayerCharacter* NewPlayerCharacter = World->SpawnActor<APlayerCharacter>(playerCharacterClass, SpawnLocation, SpawnRotation, SpawnParams);

    if (NewPlayerCharacter) {
        NewPlayerCharacter->SetPlayerSeq(playerSeq);
    }

    return NewPlayerCharacter;
}

void AGameClient::ProcessMoveResponse(const char* data) {
    MoveResponsePacket packet = MoveResponsePacket::Deserialize(data);

    int32 playerSeq = packet.playerSeq;
    float newX = packet.newX;
    float newY = packet.newY;
    bool success = packet.success;

    UE_LOG(LogTemp, Log, TEXT("MoveResponse: PlayerSeq=%d, NewX=%f, NewY=%f, Success=%d"), playerSeq, newX, newY, success);

    APlayerCharacter* PlayerCharacter = FindPlayerCharacterBySeq(playerSeq, newX, newY);
    if (PlayerCharacter && success) {
        FVector NewPosition(newX, newY, PlayerCharacter->GetActorLocation().Z);
        PlayerCharacter->SetActorLocation(NewPosition);
    }
}

void AGameClient::ProcessInventoryResponse(const char* data, int32 dataSize) {
    

    InventoryResponsePacket packet = InventoryResponsePacket::Deserialize(data);

    UE_LOG(LogTemp, Log, TEXT("Received Inventory Response: PlayerSeq=%d, ItemCount=%d"), packet.playerSeq, packet.itemCount);
    for (const auto& item : packet.items) {
        UE_LOG(LogTemp, Log, TEXT("ItemSeq=%d, ItemValue=%d, ItemMax=%d,  ItemId=%d, ItemSlotIdx=%d"),
            item.itemSeq, item.itemValue, item.itemMax,  item.itemId, item.itemSlotIdx);
        break;
    }
}



