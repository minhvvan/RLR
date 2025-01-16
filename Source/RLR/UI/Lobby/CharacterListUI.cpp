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
#include "Components/TextBlock.h"

#include "GameManager/RLRStruct.h"
#include "RLRObjects/Characters/RLRCharacter.h"

void UCharacterListUI::NativeConstruct()
{
	Super::NativeConstruct();

	CharacterCreateButton->OnClicked.AddUniqueDynamic(this, &UCharacterListUI::OnClickedCreateCharacterButton);
	CharacterDeleteButton->OnClicked.AddUniqueDynamic(this, &UCharacterListUI::OnClickedDeleteCharacterButton);
}

void UCharacterListUI::Init()
{
	Super::Init();

	TSubclassOf<UCharacterListElement> ListElementClass = GetWidgetClass<UCharacterListElement>(RLRLITERAL.WBP_CharacterListElement);
	if (IsValid(ListElementClass) == false)
	{
		DEBUG_MESSAGE;
		return;
	}

	CharacterListElementMap.Empty();
	CharacterListView->ClearListItems();
}

void UCharacterListUI::RefreshUI()
{
	Super::RefreshUI();
	Clear();

	for (const TTuple<int32, FUserCharacter>& Iter : UserCharacterList)
	{
		FUserCharacter Data = Iter.Value;

		int32 CharacterSlotIndex = Data.UserSeq;
		if (!CharacterListElementMap.Contains(CharacterSlotIndex))
		{
			AddUserCharacter(Data);
		}

		UCharacterListElement* Element = CharacterListElementMap[CharacterSlotIndex];
		Element->SetUserCharacterData(Data);
		Element->CharacterNameText->SetText(FText::FromString(Data.NickName));
		Element->RefreshUI();
	}
}

void UCharacterListUI::Clear()
{
	Super::Clear();

	for (TTuple<int32, UCharacterListElement*> Iter : CharacterListElementMap)
	{
		int32 CharacterSlotIndex = Iter.Key;
		UCharacterListElement* CharacterListElement = Iter.Value;

		CharacterListElement->Clear();
	}
}

void UCharacterListUI::SetSelectedElement(UCharacterListElement* Element)
{
	if (IsValid(Element) == false)
		return;

	if (SelectedElement == Element)
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

	TSubclassOf<ARLRCharacter> SpawnCharacterClass = GameInstance->GetDataManager()->GetObjectClass<ARLRCharacter>(RLRLITERAL.BP_DefaultPlayer);
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
	if (IsValid(SelectedElement) == false)
		return;

	/*
		캐릭터 삭제 패킷 보내기
	*/
	GetNetworkManager()->SendCharacterDeleteRequest(SelectedElement->GetUserCharacterData());
}

void UCharacterListUI::AddUserCharacter(FUserCharacter NewCharacter)
{
	if (CharacterListElementMap.Num() >= CharacterElementMaxCount)
	{
		DEBUG_MESSAGE;
		return;
	}

	int32 CharacterSlotIndex = NewCharacter.UserSeq;

	if (CharacterListElementMap.Contains(CharacterSlotIndex))
	{
		return;
	}

	TSubclassOf<UCharacterListElement> ListElementClass = GetWidgetClass<UCharacterListElement>(RLRLITERAL.WBP_CharacterListElement);
	if (!ListElementClass) return;

	UCharacterListElement* NewElement = Cast<UCharacterListElement>(CreateWidget(this, ListElementClass));
	if (!NewElement) return;

	NewElement->CharacterSlotIndex = CharacterSlotIndex;
	NewElement->SetParent(this);
	NewElement->SetUserCharacterData(NewCharacter);

	// UI 갱신을 강제
	NewElement->RefreshUI();
	CharacterListView->AddItem(NewElement);
	CharacterListElementMap.Add(CharacterSlotIndex, NewElement);
	UserCharacterList.Add(NewCharacter.UserSeq, NewCharacter);

	// ListView 강제 갱신
	CharacterListView->RequestRefresh();
}
