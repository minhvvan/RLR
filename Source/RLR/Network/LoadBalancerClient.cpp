#include "LoadBalancerClient.h"
#include "Proto/Packet.pb.h"
#include "SocketSubsystem.h"
#include <Networking.h>
#include "Handler/ClientPacketHandler.h"

LoadBalancerClient::LoadBalancerClient(const std::string& host, int port)
    : host(host), port(port), responseReceived(false), mainServerPort(0), monsterServerPort(0)
{
}

std::string LoadBalancerClient::RequestServer(int32 userSeq)
{
    Connect();
    SendRequest(userSeq);

    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this]() { return responseReceived; });

    return mainServerAddress + ";" + std::to_string(mainServerPort) + ";" + monsterServerAddress + ";" + std::to_string(monsterServerPort);
}

void LoadBalancerClient::Connect()
{
    FIPv4Address IP;
    FString fhost = *FString(host.c_str());
    FIPv4Address::Parse(fhost, IP);

    TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    Addr->SetIp(IP.Value);
    Addr->SetPort(port);

    FSocket* Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("LoadBalancerSocket"), false);

    if (Socket->Connect(*Addr))
    {
        // 연결 성공
        uint8 Buffer[8192];
        int32 BytesRead = 0;

        // 데이터 수신 대기
        while (Socket->Recv(Buffer, sizeof(Buffer), BytesRead, ESocketReceiveFlags::None) && BytesRead > 0)
        {
            OnRecv(Buffer, BytesRead);
        }

        Socket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
    }
    else
    {
        // 연결 실패
        UE_LOG(LogTemp, Error, TEXT("Failed to connect to LoadBalancer at %s:%d"), *FString(host.c_str()), port);
    }
}

void LoadBalancerClient::SendRequest(int32 userSeq)
{

    Protocol::CS_EnterGamePacket request;
    request.set_userseq(userSeq);

    // 패킷 생성
    const int32 dataSize = request.ByteSizeLong();
    TArray<uint8> Data;
    Data.SetNumUninitialized(dataSize + sizeof(PacketHeader));

    PacketHeader* header = reinterpret_cast<PacketHeader*>(Data.GetData());
    header->size = dataSize + sizeof(PacketHeader);
    header->id = PKT_ENTER_GAME_REQUEST;

    request.SerializeToArray(Data.GetData() + sizeof(PacketHeader), dataSize);

    // 서버에 패킷 전송
    FIPv4Address IP;
    FString fhost = *FString(host.c_str());
    FIPv4Address::Parse(fhost, IP);

    TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    Addr->SetIp(IP.Value);
    Addr->SetPort(port);

    FSocket* Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("LoadBalancerSocket"), false);

    if (Socket->Connect(*Addr))
    {
        int32 BytesSent = 0;
        Socket->Send(Data.GetData(), Data.Num(), BytesSent);

        if (BytesSent != Data.Num())
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to send request to LoadBalancer"));
        }

        Socket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
    }
}

void LoadBalancerClient::OnRecv(const uint8* buffer, int32 len)
{
    Protocol::SC_EnterGameResponsePacket response;
    if (response.ParseFromArray(buffer, len))
    {
        std::unique_lock<std::mutex> lock(mutex);
        if (response.success())
        {
            mainServerAddress = response.mainserveraddress();
            mainServerPort = response.mainserverport();
            monsterServerAddress = response.monsterserveraddress();
            monsterServerPort = response.monsterserverport();
        }
        responseReceived = true;
        cv.notify_one();
    }
}
