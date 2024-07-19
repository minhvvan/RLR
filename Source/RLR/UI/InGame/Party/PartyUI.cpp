// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Party/PartyUI.h"
#include "UI/InGame/Party/PartyListElement.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"

#include "Components/ListView.h"
#include "Components/ScrollBox.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "RLRObjects/Characters/RLRPLayerCharacter.h"

void UPartyUI::NativeConstruct()
{
	Super::NativeConstruct();
	SetUIType(EUIType::PARTY);

	UUIManager* UI  = GameInstance->GetUIManager();
	if(IsValid(UI) == false)
		return;

	UI->UpdatedPartyPlayerInfo.AddDynamic(this, &UPartyUI::AddPlayer);
}

void UPartyUI::RefreshUI()
{
	Super::RefreshUI();

	for (TPair<int32, UPartyListElement*> ElementPair : PlayerMap)
	{
		UPartyListElement* Element = ElementPair.Value;
		if (Element)
		{
			Element->RefreshUI();
		}
	}
}

void UPartyUI::AddPlayer(FUserCharacter NewPlayer)
{
	if (PartyListElementClass == nullptr)
	{
		DEBUG_LOG("UPartyUI::AddPlaye Error.PartyListElementClass is Null.");
		return;
	}

	OpenUI();

	UPartyListElement* NewPlayerListElement = CreateWidget<UPartyListElement>(GetWorld(), PartyListElementClass);
	NewPlayerListElement->SetUserCharacterData(NewPlayer);
	PlayerList->AddItem(NewPlayerListElement);
	PlayerMap.Add(NewPlayer.GetUserCharacterData().playerseq(), NewPlayerListElement);

	RefreshUI();
}

void UPartyUI::RemovePlayer(FUserCharacter LeavePlayer)
{
	int32 PlayerID = LeavePlayer.GetUserCharacterData().playerseq();

	if(PlayerMap.Contains(PlayerID) == false)
		return;

	UPartyListElement* Element = PlayerMap[PlayerID];
	if(IsValid(Element) == false)
		return;

	PlayerMap.Remove(PlayerID);
	Element->RemoveFromParent();

	//파티 중인 플레이어가 없으면 감춰준다.
	if (PlayerMap.Num() <= 0)
	{
		CloseUI();
	}
}
