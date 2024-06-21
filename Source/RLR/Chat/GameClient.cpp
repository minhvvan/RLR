#include "GameClient.h"
#include "Networking.h"
#include "Runtime/Core/Public/HAL/RunnableThread.h"
#include "EngineUtils.h"
#include "Engine/World.h"
AGameClient::AGameClient()
{
    PrimaryActorTick.bCanEverTick = true;
    ClientSocket = INVALID_SOCKET;
    static ConstructorHelpers::FClassFinder<APlayerCharacter> PlayerCharacterBPClass(TEXT("/Game/Player/BP/BP_Player"));
    if (PlayerCharacterBPClass.Class != NULL)
    {
        PlayerCharacterClass = PlayerCharacterBPClass.Class;
    }
}

void AGameClient::BeginPlay()
{
    Super::BeginPlay();
    FString ServerAddress = TEXT("127.0.0.1"); // 서버 주소
    int32 ServerPort = 27015; // 서버 포트

    if (!InitializeSocket(ServerAddress, ServerPort))
    {
        UE_LOG(LogTemp, Error, TEXT("소켓 초기화 실패"));
    }
    else
    {
       UE_LOG(LogTemp, Log, TEXT("서버에 성공적으로 연결"));
    }
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), FoundActors);

    if (FoundActors.Num() > 0)
    {
        MyPlayerCharacter = Cast<APlayerCharacter>(FoundActors[0]);
        if (MyPlayerCharacter)
        {
            UE_LOG(LogTemp, Log, TEXT("MyPlayerCharacter 객체를 찾았습니다."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("MyPlayerCharacter 객체를 찾지 못했습니다."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("APlayerCharacter 클래스를 가진 객체가 없습니다."));
    }
}

void AGameClient::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Socket)
    {
        if (Socket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromMilliseconds(100)))
        {
            uint8 Buffer[sizeof(MoveResponsePacket)];
            int32 BytesRead = 0;
            if (Socket->Recv(Buffer, sizeof(Buffer), BytesRead))
            {
                if (BytesRead > 0)
                {
                    ProcessMoveResponse(reinterpret_cast<const char*>(Buffer));
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("패킷 수신 실패 또는 읽은 바이트가 없습니다."));
                }
            }
        }
    }
}

void AGameClient::ProcessMoveResponse(const char* data)
{
    MoveResponsePacket packet = MoveResponsePacket::Deserialize(data);

    int32 userSeq = packet.playerSeq;
    float newX = packet.newX;
    float newY = packet.newY;
    bool success = packet.success;

    UE_LOG(LogTemp, Log, TEXT("받은 Response Player: %d"), userSeq);
    UE_LOG(LogTemp, Log, TEXT("받은 Response newX: %f"), newX);
    UE_LOG(LogTemp, Log, TEXT("받은 Response newY: %f"), newY);
    UE_LOG(LogTemp, Log, TEXT("받은 Response Success: %d"), success);

    APlayerCharacter* PlayerCharacter = FindPlayerCharacterBySeq(userSeq,newX,newY);
    if (PlayerCharacter && success)
    {
        FVector NewPosition(newX, newY, PlayerCharacter->GetActorLocation().Z);
        PlayerCharacter->SetActorLocation(NewPosition);
    }
}

bool AGameClient::InitializeSocket(const FString& ServerAddress, int32 Port)
{
    FIPv4Address IP;
    if (!FIPv4Address::Parse(ServerAddress, IP))
    {
        UE_LOG(LogTemp, Error, TEXT("서버 주소 파싱 실패: %s"), *ServerAddress);
        return false;
    }

    TSharedRef<FInternetAddr> InternetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    InternetAddr->SetIp(IP.Value);
    InternetAddr->SetPort(Port);

    Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
    if (!Socket)
    {
        UE_LOG(LogTemp, Error, TEXT("소켓 생성 실패"));
        return false;
    }

    if (!Socket->Connect(*InternetAddr))
    {
        UE_LOG(LogTemp, Error, TEXT("서버에 연결 실패"));
        return false;
    }

    UE_LOG(LogTemp, Log, TEXT("서버에 성공적으로 연결: %s:%d"), *ServerAddress, Port);
    return true;
}

bool AGameClient::SendMovePacket(int32 PlayerId, float NewX, float NewY)
{
    if (!Socket) return false;

    MoveRequestPacket packet;
    packet.packetType = MOVE_REQUEST;
    packet.playerSeq = PlayerId;
    packet.newX = NewX;
    packet.newY = NewY;

    int32 BytesSent = 0;
    bool bIsSent = Socket->Send(reinterpret_cast<uint8*>(&packet), sizeof(packet), BytesSent);

    if (!bIsSent || BytesSent != sizeof(packet))
    {
        UE_LOG(LogTemp, Error, TEXT("패킷 전송 실패"));
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

bool AGameClient::ReceiveData(uint8* buffer, int32 bufferSize)
{
    if (!Socket) return false;

    int32 BytesRead = 0;
    UE_LOG(LogTemp, Log, TEXT("Receive to server."));

    return Socket->Recv(buffer, bufferSize, BytesRead);
}

APlayerCharacter* AGameClient::FindPlayerCharacterBySeq(int32_t userSeq, float newX, float newY)
{
    for (TActorIterator<APlayerCharacter> It(GetWorld()); It; ++It)
    {
        APlayerCharacter* PlayerCharacter = *It;
        if (PlayerCharacter)
        {
            UE_LOG(LogTemp, Log, TEXT("Checking PlayerCharacter: %s"), *PlayerCharacter->GetName());
            if (PlayerCharacter->GetPlayerSeq() == userSeq)
            {
                UE_LOG(LogTemp, Log, TEXT("Found PlayerCharacter: %s"), *PlayerCharacter->GetName());
                return PlayerCharacter;
            }
        }
    }

        // Log a warning if no player character was found
        UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter with Seq %d not found"), userSeq);

    // If no player character was found, create a new one
    if (APlayerCharacter* NewPlayerCharacter = SpawnNewPlayerCharacter(userSeq, newX, newY))
    {
        UE_LOG(LogTemp, Log, TEXT("Spawned new PlayerCharacter: %s"), *NewPlayerCharacter->GetName());
        return NewPlayerCharacter;
    }

    // Log an error if spawning the player character failed
    UE_LOG(LogTemp, Error, TEXT("Failed to spawn PlayerCharacter with Seq %d"), userSeq);
    return nullptr;
}
APlayerCharacter* AGameClient::SpawnNewPlayerCharacter(int32_t userSeq, float newX, float newY)
{
    // Ensure the player character class is valid
    if (!PlayerCharacterClass)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerCharacterClass is not set"));
        return nullptr;
    }

  
        // Get the current world
        UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("World is null"));
        return nullptr;
    }

    // Set the spawn parameters
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = nullptr;
    SpawnParams.Instigator = GetInstigator();

    // Spawn the new player character at a default location
    FVector SpawnLocation(newX, newY, 92.1064);
    FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
    APlayerCharacter* NewPlayerCharacter = World->SpawnActor<APlayerCharacter>(PlayerCharacterClass, SpawnLocation, SpawnRotation, SpawnParams);

    // If spawning succeeded, set the player sequence number
    if (NewPlayerCharacter)
    {
        NewPlayerCharacter->SetPlayerSeq(userSeq);
    }

    return NewPlayerCharacter;
}
