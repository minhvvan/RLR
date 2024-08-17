// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/OtherUserManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"





UOtherUserManager::UOtherUserManager()
{
	
}

void UOtherUserManager::AddPlayer(Protocol::UserCharacter& NewPlayer)
{
	/*
		TODO
		플레이어 스폰.
	*/


	UWorld* World = GetWorld();
	if(World == nullptr)
		return;


	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotator;
	FVector SpawnLocation = FVector::ZeroVector;

	SpawnLocation.X = NewPlayer.transx();
	SpawnLocation.Y = NewPlayer.transy();
	SpawnLocation.Z = NewPlayer.transz();

	FUserCharacter UserCharacter;
	UserCharacter.MakeUserCharacter(NewPlayer);

	TSubclassOf<ARLRPlayerCharacter> PlayerClass = GetPlayerCharacterClass(UserCharacter.MainJob);
	if(CHECK_VALID(PlayerClass) == false)
		return;

	ARLRPlayerCharacter* OtherPlayer = World->SpawnActor<ARLRPlayerCharacter>(PlayerClass, SpawnLocation, SpawnRotator, SpawnParams);
	
	/*
		TODO
		OhterPlayer->SetUserCharacter()
	*/
	
	int32 PlayerID = NewPlayer.playerseq();
	OtherPlayerList.Add(PlayerID, OtherPlayer);
}

ARLRPlayerCharacter* UOtherUserManager::GetPlayer(int32 PlayerID)
{
	return OtherPlayerList[PlayerID];
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

	/*
		패킷 안에는 다른 플레이어가 움직이는 방향, Velocity, 상태 값이 들어 있어야 한다?
		다른 플레이어가 뛰고 있는지, 걷고 있는지,
		얼마나 가속을 받았는지,
		어떤 방향으로 움직이고 있는지,

		일단은 위치값만 받아서 동기화를 해본다.
	*/

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
	PartyPlayerList.Add(NewPlayer.playerseq(), NewPartyPlayer);

	GameInstance->GetUIManager()->UpdatedPartyPlayerInfo.Broadcast(NewPartyPlayer);
}

TSubclassOf<ARLRPlayerCharacter> UOtherUserManager::GetPlayerCharacterClass(ECharacterMainJobType JobType)
{
	FString JobString = UEnum::GetValueAsString(JobType);

	return GameInstance->GetDataManager()->GetCharacterClass<ARLRPlayerCharacter>(JobString);
}
