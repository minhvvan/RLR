// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Network/Proto/Packet.pb.h"
#include "GameManager/RLRStruct.h"
#include "Structs/PlayerStructs.h"
#include "RLR.h"
#include "OtherUserManager.generated.h"

/**
 
	다른 유저를 관리하는 매니저.

	동기화 관리 및 다른 유저의 정보를 관리

 */


 class ARLRPlayerCharacter;
 class APlayerData;


UCLASS()
class RLR_API UOtherUserManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	UOtherUserManager();
	void AddPlayer(Protocol::UserCharacter& NewPlayer);
	ARLRPlayerCharacter* GetPlayer(int32 PlayerID);
	void RemovePlayer(int32 PlayerID);

	//Move Packet이 만들어지면 마저 완성. 
	//void MovePlayer();

	/*
		다른 플레이어 동기화 관련
	*/
	void UpdateOtherPlayerTransform(int32 PlayerID, int32 X, int32 Y, int32 Z);



	/*
		파티, 친구, 길드 관련
	*/

	void ReceivePartyInviteRequest(int32 PlayerID);					//파티 요청을 받음
	void ReplyPartyInviteRequest(bool Ret);									//파티 수락 or 거절
	void SendPartyInviteRequest(int32 PlayerID);						//파티 요청을 보냄


	void AddPlayerToParty(Protocol::UserCharacter& NewPlayer);

	TSubclassOf<ARLRPlayerCharacter> GetPlayerCharacterClass(ECharacterMainJobType JobType);

public:

	UPROPERTY()
	TMap<int32, ARLRPlayerCharacter*> OtherPlayerList;

	UPROPERTY()
	FPlayerMap PartyPlayerList;
};
