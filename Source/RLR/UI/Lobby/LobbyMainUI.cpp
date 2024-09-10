// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/LobbyMainUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/LevelManager.h"
#include "GameManager/NetworkManager.h"
#include "Structs/PlayerStructs.h"
void ULobbyMainUI::NativeConstruct()
{
	Super::NativeConstruct();

}

void ULobbyMainUI::RefreshUI()
{
	Super::RefreshUI();

}

void ULobbyMainUI::Clear()
{
	Super::Clear();

}

void ULobbyMainUI::SetInputMode()
{
	ChangeInputModeUIOnly();
}

void ULobbyMainUI::OpenCreateCharacterUI()
{
	FUserCharacter character;
	character.UserSeq = 1;
	character.MapId = 1;
	
	GameInstance->GetLevelManager()->LoadLevel("Main");


	
	GameInstance->GetNetworkManager()->SendEnterGameFromLobbyReqeust(character);
}
