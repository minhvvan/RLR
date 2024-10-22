// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/OtherUserManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"





UOtherUserManager::UOtherUserManager()
{
	// PlayerCharacterClass에 기본 캐릭터 클래스 설정
	static ConstructorHelpers::FClassFinder<ARLRPlayerCharacter> PlayerCharacterBPClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Player/BP/BP_Player.BP_Player_C'"));
	if (PlayerCharacterBPClass.Succeeded())
	{
		PlayerCharacterClass = PlayerCharacterBPClass.Class;
	}
	else
	{
		RLR_LOG(LogRLR, Error, TEXT("Failed to load BP_Player character class"));
	}
}

void UOtherUserManager::AddPlayer(Protocol::UserCharacter& NewPlayer)
{
	AsyncTask(ENamedThreads::GameThread, [this, NewPlayer]()
		{

			FVector SpawnLocation = FVector::ZeroVector;
			FTransform SpawnTransform;
			SpawnLocation.X = NewPlayer.transx();
			SpawnLocation.Y = NewPlayer.transy();
			SpawnLocation.Z = NewPlayer.transz();

			FUserCharacter UserCharacter;
			UserCharacter.MakeUserCharacter(NewPlayer);
			UserCharacter.MapId = 1;
			UserCharacter.ChannelId = 1;
			SpawnTransform.SetLocation(SpawnLocation);
			SpawnTransform.SetRotation(FQuat::Identity);
			SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

			UWorld* World = GetWorld();
			if (World == nullptr)
			{
				RLR_LOG(LogRLR, Error, TEXT("World is nullptr"));
				return;
			}

			// Deferred spawning
			ARLRPlayerCharacter* OtherPlayer = World->SpawnActorDeferred<ARLRPlayerCharacter>(PlayerCharacterClass, SpawnTransform);

			// Check if the spawn failed
			if (!OtherPlayer)
			{
				RLR_LOG(LogRLR, Error, TEXT("Failed to spawn Character"));
				return;
			}

			// Add player to list before FinishSpawning
			int32 PlayerID = NewPlayer.userseq();
			OtherPlayerList.Add(PlayerID, OtherPlayer);

			// Finalize the spawning process
			OtherPlayer->FinishSpawning(SpawnTransform);

			// Optional: Log success
			RLR_LOG(LogRLR, Warning, TEXT("Player %d spawned successfully"), PlayerID);
		});
	
	
}

ARLRPlayerCharacter* UOtherUserManager::GetPlayer(int32 PlayerID)
{
	// 먼저 PlayerID가 TMap에 존재하는지 확인
	if (!OtherPlayerList.Contains(PlayerID)) {
		return nullptr;  // PlayerID가 없으면 nullptr 반환
	}

	// TMap에서 PlayerID에 해당하는 값을 가져옴
	ARLRPlayerCharacter* Player = *OtherPlayerList.Find(PlayerID);
	if (Player == nullptr) {
		return nullptr;  // 플레이어가 nullptr이면 nullptr 반환
	}

	return Player;  // 유효한 플레이어 반환
}

void UOtherUserManager::RemovePlayer(int32 PlayerID)
{
	if(OtherPlayerList.Contains(PlayerID) == false)
		return;

	ARLRPlayerCharacter* Player = OtherPlayerList[PlayerID];
	OtherPlayerList.Remove(PlayerID);

	/*
		Player를 파괴해준다.
		RLRCharacter에 Destroy 함수를 래핑하는 함수 하나 만들어주기
	*/
	if(Player->IsActorBeingDestroyed() == false)
		Player->Destroy();
}

void UOtherUserManager::UpdateOtherPlayerTransform(int32 PlayerID, int32 X, int32 Y, int32 Z)
{
	ARLRPlayerCharacter* OtherPlayer = GetPlayer(PlayerID);
	if(IsValid(OtherPlayer) == false)
		return;

	OtherPlayer->UpdateTransform(FVector(X, Y , Z));
}

void UOtherUserManager::ReceivePartyInviteRequest(int32 PlayerID)
{
	/*
		플레이어에게 파티에 참여할 건지 수락, 거절 UI를 띄운다.
	*/
}

void UOtherUserManager::ReplyPartyInviteRequest(bool Ret)
{
	/*
		받은 파티 요청에 대한 답장 패킷 보내기
	*/

}

void UOtherUserManager::SendPartyInviteRequest(int32 PlayerID)
{
	/*
		다른 플레이어에게 파티 참여 요청 패킷을 보낸다.
	*/
}

void UOtherUserManager::AddPlayerToParty(Protocol::UserCharacter& NewPlayer)
{
	/*
		Player ID를 받아서 OtherPlayerList에서 정보를 찾아 처리할까 고민했지만, 
		혹시라도 다른 필드에 있는 플레이어가 파티 요청을 보낼 수도 있으니,
		아예 플레이어 정보를 통째로 받기로 함.
	*/

	FUserCharacter NewPartyPlayer;
	NewPartyPlayer.MakeUserCharacter(NewPlayer);
	
	GameInstance->GetUIManager()->UpdatedPartyPlayerInfo.Broadcast(PartyPlayerList.Add(NewPlayer.playerseq(), NewPartyPlayer));
}

TSubclassOf<ARLRPlayerCharacter> UOtherUserManager::GetPlayerCharacterClass(ECharacterMainJobType JobType)
{
	FString JobString = UEnum::GetValueAsString(JobType);

	return GameInstance->GetDataManager()->GetCharacterClass<ARLRPlayerCharacter>(JobString);
}

