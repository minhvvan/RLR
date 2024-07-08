#include "GameClient.h"
#include "Networking.h"
#include "Runtime/Core/Public/HAL/RunnableThread.h"
#include "../Player/PlayerCharacter.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "../Network/ClientPacketHandler.h"


AGameClient::AGameClient() {
    PrimaryActorTick.bCanEverTick = true;
    clientSocket = INVALID_SOCKET;
    static ConstructorHelpers::FClassFinder<APlayerCharacter> PlayerCharacterBPClass(TEXT("/Game/Player/BP/BP_Player"));
    if (PlayerCharacterBPClass.Class != NULL) {
        playerCharacterClass = PlayerCharacterBPClass.Class;
    }
    networkReceiver = nullptr;
}

void AGameClient::BeginPlay() {
    Super::BeginPlay();
    FString serverAddress = TEXT("127.0.0.1");
    int32 serverPort = 27015; // 로그인 서버 포트
    ClientPacketHandler::Init();
    if (InitializeSocket(serverAddress, serverPort))
    {
        networkReceiver = new FNetworkReceiver(socket);
        Thread = FRunnableThread::Create(networkReceiver, TEXT("NetworkReceiverThread"));
        UE_LOG(LogTemp, Log, TEXT("로그인 서버에 성공적으로 연결"));
        SendInventoryPacket(1); // 테스트 플레이어 ID
        SendInventoryPacket(1); // 테스트 플레이어 ID
        SendStatusPacket(1); // 테스트 스테이터스
        SendMovePacket(1,2123.08f,1997.092f,91.2371f);
    }
    else {
        UE_LOG(LogTemp, Log, TEXT("로그인 서버에 연결 실패!"));
    }
}

void AGameClient::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    
}


bool AGameClient::SendLoginPacket(const FString& playerId) {
    if (!socket) return false;

   

    return true;
}

void AGameClient::ProcessLoginResponse(const char* data) {
  
}

bool AGameClient::SendMovePacket(int32 userSeq, float NewX, float NewY, float NewZ) {

  /*  if (!socket) return false;

    Protocol::MoveRequestPacket packet;
    packet.set_userseq(userSeq);
    packet.set_transx(NewX);
    packet.set_transy(NewY);
    packet.set_transz(NewZ);
    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
    int32 BytesSent = 0;
    bool bSuccess = socket->Send(sendBuffer->GetBuffer(), sendBuffer->Capacity(), BytesSent);

    if (!bSuccess) {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 실패"));
    }
    else {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 성공"));
    }


    return bSuccess && BytesSent == sendBuffer->Capacity();*/
    return true;
}
//bool AGameClient::SendEnterGamePacket(int32 userSeq, float NewX, float NewY, float NewZ) {
//
//    if (!socket) return false;
//
//    Protocol::MoveRequestPacket packet;
//    packet.set_userseq(userSeq);
//    packet.set_transx(NewX);
//    packet.set_transy(NewY);
//    packet.set_transz(NewZ);
//    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet, PKT_MOVE_REQUEST);
//    int32 BytesSent = 0;
//    bool bSuccess = socket->Send(sendBuffer->GetBuffer(), sendBuffer->Capacity(), BytesSent);
//
//    if (!bSuccess) {
//        UE_LOG(LogTemp, Log, TEXT("패킷 송신 실패"));
//    }
//    else {
//        UE_LOG(LogTemp, Log, TEXT("패킷 송신 성공"));
//    }
//
//
//    return bSuccess && BytesSent == sendBuffer->Capacity();
//}
bool AGameClient::SendStatusPacket(int32 userSeq)
{
    if (!socket) return false;

    Protocol::StatusRequestPacket packet;
    packet.set_userseq(userSeq);
    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet, PKT_STATUS_REQUEST);
    int32 BytesSent = 0;
   bool bSuccess = socket->Send(sendBuffer->GetBuffer(), sendBuffer->Capacity(), BytesSent);

   if (!bSuccess) {
       UE_LOG(LogTemp, Log, TEXT("패킷 송신 실패"));
   }
   else {
       UE_LOG(LogTemp, Log, TEXT("패킷 송신 성공"));
   }


   return bSuccess && BytesSent == sendBuffer->Capacity();
}
bool AGameClient::SendInventoryPacket(int32 userSeq)
{
    if (!socket) return false;

    Protocol::InventoryRequestPacket packet;
    packet.set_userseq(userSeq);
    TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet, PKT_INVENTORY_REQUEST);
    int32 BytesSent = 0;
    bool bSuccess = socket->Send(sendBuffer->GetBuffer(), sendBuffer->Capacity(), BytesSent);

    if (!bSuccess) {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 실패"));
    }
    else {
        UE_LOG(LogTemp, Log, TEXT("패킷 송신 성공"));
    }


    return bSuccess && BytesSent == sendBuffer->Capacity();
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
    /*MoveResponsePacket packet = MoveResponsePacket::Deserialize(data);

    int32 playerSeq = packet.playerSeq;
    float newX = packet.newX;
    float newY = packet.newY;
    bool success = packet.success;

    UE_LOG(LogTemp, Log, TEXT("MoveResponse: PlayerSeq=%d, NewX=%f, NewY=%f, Success=%d"), playerSeq, newX, newY, success);

    APlayerCharacter* PlayerCharacter = FindPlayerCharacterBySeq(playerSeq, newX, newY);
    if (PlayerCharacter && success) {
        FVector NewPosition(newX, newY, PlayerCharacter->GetActorLocation().Z);
        PlayerCharacter->SetActorLocation(NewPosition);
    }*/
}

void AGameClient::ProcessInventoryResponse(const char* data, int32 dataSize) {
    

    /*InventoryResponsePacket packet = InventoryResponsePacket::Deserialize(data);

    UE_LOG(LogTemp, Log, TEXT("Received Inventory Response: PlayerSeq=%d, ItemCount=%d"), packet.playerSeq, packet.itemCount);
    for (const auto& item : packet.items) {
        UE_LOG(LogTemp, Log, TEXT("ItemSeq=%d, ItemValue=%d, ItemMax=%d,  ItemId=%d, ItemSlotIdx=%d"),
            item.itemSeq, item.itemValue, item.itemMax,  item.itemId, item.itemSlotIdx);
        break;
    }*/
}



void AGameClient::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (networkReceiver)
    {
        networkReceiver->Stop();
        Thread->WaitForCompletion();
        delete networkReceiver;
        networkReceiver = nullptr;
    }

    if (socket)
    {
        socket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(socket);
    }
}