// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterStatus/CharacterStatusUI.h"
#include "UI/InGame/CharacterStatus/Equipment/EquipmentUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"

#include "Structs/PlayerStructs.h"
#include "Structs/UtilStructs.h"

void UCharacterStatusUI::NativeConstruct()
{
	Super::NativeConstruct();
	SetUIType(EUIType::CHARACTER_STATUS_UI);
	//SetUITag(FGameplayTagManager::Get().UI_CharacterStatus);


	//GameInstance->GetUIManager()->UpdatedPlayerInfo.AddDynamic(this, &UCharacterStatusUI::SetPlayerInfo);
}

void UCharacterStatusUI::RefreshUI()
{
	/*
		나중에 다른 탭들이 추가되면 추가로 RefreshUI를 해준다`.
	*/

}

//TODO: 필요하면 살리기
//void UCharacterStatusUI::SetPlayerInfo(FUserCharacter NewPlayerInfo)
//{
	//PlayerInfo = NewPlayerInfo;
	//RefreshUI();
//}

void UCharacterStatusUI::UpdateTotalStat(const FTotalStatus& NewTotalStat)
{
	//델리게이트는 InGameMainUI에서 등록되어 있다.
	EquipmentUI->RefreshStatUI(NewTotalStat);
}