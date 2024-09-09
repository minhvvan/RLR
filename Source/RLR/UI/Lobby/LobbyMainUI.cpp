// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/LobbyMainUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/LevelManager.h"
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
	GameInstance->GetLevelManager()->LoadLevel("Main");
}
