// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/FNetworkReceiver.h"
#include "Network/Handler/ClientPacketHandler.h"

#include "GameManager/NetworkManager.h"
#include "GameManager/GameManager.h"

FNetworkReceiver::FNetworkReceiver(FSocket* InSocket) : Socket(InSocket), bStopRequested(false) {}
FNetworkReceiver::~FNetworkReceiver() { Stop(); }

bool FNetworkReceiver::Init() {
    
    return true; 
}

uint32 FNetworkReceiver::Run()
{
    uint8 Buffer[8192];
    int32 BytesRead = 0;

    while (!bStopRequested)
    {
        if (Socket->Recv(Buffer, sizeof(Buffer), BytesRead, ESocketReceiveFlags::None) && BytesRead > 0)
        {
            
            ProcessReceivedData(Buffer, BytesRead);
        }
    }

    return 0;
}

void FNetworkReceiver::Stop() { bStopRequested = true; }
void FNetworkReceiver::ProcessReceivedData(const uint8* Data, int32 Size)
{
    
    if(GameInstance == nullptr)
        return;

    int32 processedBytes = 0;

    while (processedBytes < Size)
    {
        const uint8* packetData = Data + processedBytes;
        const PacketHeader* header = reinterpret_cast<const PacketHeader*>(packetData);

        // 패킷 헤더 로그 출력
       

        // 패킷 크기가 유효한지 확인
        if (header->size > Size - processedBytes)
        {
            UE_LOG(LogTemp, Error, TEXT("Invalid packet size. Received size is larger than remaining data."));
            break;
        }


        // 핸들러가 유효한지 확인
        if (GPacketHandler[header->id])
		{

				uint16 id = header->id;
				uint8 size = header->size;
				TSharedPtr<PacketSession> session = MakeShared<PacketSession>();
				GPacketHandler[header->id](session, const_cast<uint8*>(packetData), header->size);

        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("No handler found for packet id: %d"), header->id);
        }

        processedBytes += header->size;
    }
}