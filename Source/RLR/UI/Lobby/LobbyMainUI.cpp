// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/LobbyMainUI.h"
#include "UI/Lobby/CharacterListUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/LevelManager.h"

void ULobbyMainUI::NativeConstruct()
{
	Super::NativeConstruct();

}

void ULobbyMainUI::RefreshUI()
{
	Super::RefreshUI();
	CharacterListUI->RefreshUI();
}

void ULobbyMainUI::Clear()
{
	Super::Clear();

}

void ULobbyMainUI::SetInputMode()
{
	ChangeInputModeUIOnly();
}

void ULobbyMainUI::AddUserCharacter(FUserCharacter NewCharacter)
{
	CharacterListUI->AddUserCharacter(NewCharacter);
}

void ULobbyMainUI::OpenCreateCharacterUI()
{
}
