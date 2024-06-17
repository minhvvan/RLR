// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Windows/AllowWindowsPlatformTypes.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include "Windows/HideWindowsPlatformTypes.h"
#include "../Player/PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "GameClient.generated.h"


UCLASS()
class RLR_API AGameClient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameClient();



private:
	SOCKET ClientSocket;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool ConnectToServer(const FString& ServerAddress, const FString& Port);
	bool SendMovePacket(int32 userSeq, float NewX, float NewY);
	void CloseConnection();
	bool ReceiveData(char* buffer, int bufferSize);

	void ProcessMoveResponse(const char* data);

	APlayerCharacter* FindPlayerCharacterBySeq(int32_t userSeq);

};
enum PacketType : uint8
{
	MOVE_REQUEST = 1,
	MOVE_RESPONSE = 2,
	Whisper,
	Country,
	World,
	Guild,
	Raid,
	Party,
	Continent,
	Nearby
};

struct MoveResponsePacket
{


	uint8 packetType;
	int32 playerSeq;
	float newX;
	float newY;
	bool success;

	MoveResponsePacket()
		: packetType(MOVE_RESPONSE), playerSeq(0), newX(0.0f), newY(0.0f), success(false)
	{};
};