// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/CharacterListUI.h"
#include "UI/Lobby/CharacterListElement.h"
#include "UI/Lobby/LobbyMainUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/NetworkManager.h"

#include "Components/Button.h"
#include "Components/ListView.h"

#include "GameManager/RLRStruct.h"
#include "RLRObjects/Characters/RLRCharacter.h"

void UCharacterListUI::NativeConstruct()
{
	Super::NativeConstruct();

	CharacterCreateButton->OnClicked.AddUniqueDynamic(this, &UCharacterListUI::OnClickedCreateCharacterButton);
	CharacterDeleteButton->OnClicked.AddUniqueDynamic(this, &UCharacterListUI::OnClickedDeleteCharacterButton);
}

void UCharacterListUI::RefreshUI()
{
	Super::RefreshUI();
	Clear();

	if (IsValid(ListElementClass) == false)
	{
		ListElementClass = GetWidgetClass<UCharacterListElement>("WBP_CharacterListElement");
		if (IsValid(ListElementClass) == false)
		{
			DEBUG_MESSAGE;
			return;
		}
	}

	for (const TTuple<int32, FUserCharacter>& ListElement : UserCharacterList)
	{
		FUserCharacter Data = ListElement.Value;
		UCharacterListElement* newElement = Cast<UCharacterListElement>(CreateWidget(this, ListElementClass));
		newElement->SetParent(this); 
		newElement->SetUserCharacterData(Data);
		CharacterListView->AddItem(newElement);
	}
}

void UCharacterListUI::Clear()
{
	Super::Clear();
	CharacterListView->ClearListItems();
}

void UCharacterListUI::SetSelectedElement(UCharacterListElement* Element)
{
	if(IsValid(Element) == false)
		return;

	if(SelectedElement == Element)
		return;

	SelectedElement = Element;
	SpawnSelectedElementCharacter(SelectedElement->GetUserCharacterData());
}


void UCharacterListUI::SpawnSelectedElementCharacter(const FUserCharacter& Data)
{
	if (IsValid(SelectedCharacter) == true)
	{
	/*	if (SelectedCharacter->CurrentUseWeapon.IsValid() == true)
			SelectedCharacter->CurrentUseWeapon->Destroy();*/

		SelectedCharacter->Destroy();
		SelectedCharacter = nullptr;
	}

	/*
		소환할 캐릭터의 템플릿 아이디를 알아야 한다.
		하지만 지금은 알 수 없으므로 일단 기본 캐릭터 소환.
	*/

	TSubclassOf<ARLRCharacter> SpawnCharacterClass = GameInstance->GetDataManager()->GetObjectClass<ARLRCharacter>("BP_DefaultPlayer");
	if (IsValid(SpawnCharacterClass) == false)
	{
		DEBUG_MESSAGE;
		return;
	}

	FActorSpawnParameters SpawnParams;
	SelectedCharacter = GameInstance->GetWorld()->SpawnActor<ARLRCharacter>(SpawnCharacterClass, SpawnLocation, SpawnRotation, SpawnParams);
	/*
		TODO
		소환시 애니메이션 재생.
		지금 캐릭터 관련 코드까지 건들면 머지할 때 힘들테니, 머지하고 일단 나중에 수정해줄 것.
	*/
	//SelectedCharacter->Anim->PlayRespawnMontage();
}

void UCharacterListUI::OnClickedCreateCharacterButton()
{
	ULobbyMainUI* LobbyMainUI = Cast<ULobbyMainUI>(GetParent());
	if (IsValid(LobbyMainUI) == false)
	{
		DEBUG_MESSAGE;
		return;
	}
	LobbyMainUI->OpenCreateCharacterUI();
}

void UCharacterListUI::OnClickedDeleteCharacterButton()
{
	if(IsValid(SelectedElement) == false)
		return;

	/*
		캐릭터 삭제 패킷 보내기
	*/
	GetNetworkManager()->SendCharacterDeleteRequest(SelectedElement->GetUserCharacterData());	
}

void UCharacterListUI::AddUserCharacter(FUserCharacter NewCharacter)
{
	UserCharacterList.Add(NewCharacter.UserSeq, NewCharacter);
}
