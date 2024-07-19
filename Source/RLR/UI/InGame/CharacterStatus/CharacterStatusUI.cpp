// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterStatus/CharacterStatusUI.h"
#include "UI/InGame/CharacterStatus/Equipment/EquipmentUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"

void UCharacterStatusUI::NativeConstruct()
{
	Super::NativeConstruct();
	SetUIType(EUIType::CHARACTERSTAT);


	GameInstance->GetUIManager()->UpdatedPlayerInfo.AddDynamic(this, &UCharacterStatusUI::SetPlayerInfo);
}

void UCharacterStatusUI::RefreshUI()
{

	FTotalStatus PlayerStatus;
	PlayerStatus.MakeStatus(PlayerInfo.UserCharacterData.totalstatus());
	EquipmentUI->RefreshStatUI(PlayerStatus);

	/*
		나중에 다른 탭들이 추가되면 추가로 RefreshUI를 해준다`.
	*/

}

void UCharacterStatusUI::SetPlayerInfo(FUserCharacter NewPlayerInfo)
{
	PlayerInfo = NewPlayerInfo;
	RefreshUI();
}
