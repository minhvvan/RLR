// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/OtherUserManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"





UOtherUserManager::UOtherUserManager()
{
	/*
	* TODO
		PlayerCharaceterClass Load
	*/
	static ConstructorHelpers::FClassFinder<ARLRPlayerCharacter> PlayerCharacterBPClass(TEXT("/Game/Player/BP/BP_Player"));
	if (PlayerCharacterBPClass.Class != NULL) {
		PlayerCharacterClass = PlayerCharacterBPClass.Class;
	}
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

	if (IsValid(PlayerCharacterClass) == false)
	{
		DEBUG_LOG("PlayerCharacterClass is Null.");
		return;
	}

	ARLRPlayerCharacter* OtherPlayer = World->SpawnActor<ARLRPlayerCharacter>(PlayerCharacterClass, SpawnLocation, SpawnRotator, SpawnParams);
	int32 PlayerID = NewPlayer.playerseq();
	OtherPlayerList.Add(PlayerID, OtherPlayer);
}

void UOtherUserManager::RemovePlayer(int32 PlayerID)
{
	if(OtherPlayerList.Contains(PlayerID) == false)
		return;

	OtherPlayerList.Remove(PlayerID);
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
	NewPartyPlayer.SetUserChracterData(NewPlayer);
	PartyPlayerList.Add(NewPlayer.playerseq(), NewPartyPlayer);
	GameInstance->GetUIManager()->UpdatedPartyPlayerInfo.Broadcast(NewPartyPlayer);
}
