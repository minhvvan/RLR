// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Party/PartyListElement.h"
#include "Components/ProgressBar.h"
#include "Components/RichTextBlock.h"
#include "Structs/PlayerStructs.h"

void UPartyListElement::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	UPartyListElement* Element = Cast<UPartyListElement>(ListItemObject);

	if (Element->GetUserCharacterData() != nullptr)
	{
		SetUserCharacterData(*Element->GetUserCharacterData());
	}
}

void UPartyListElement::RefreshUI()
{
	auto data = GetUserCharacterData();
	if (data == nullptr) return;

	float MaxHp = data->TotalStatus.MAX_HP;
	float CurrentHp = data->TotalStatus.HP;

	float Value = FMath::Clamp(CurrentHp/ MaxHp, 0, 1);
	SetPercentHpBar(Value);

	SetPlayerName(data->NickName);
}

void UPartyListElement::SetPercentHpBar(float Value)
{
	PlayerProgressBar->SetPercent(Value);
}

void UPartyListElement::SetPlayerName(FString String)
{
	FText Name = FText::FromString(String);
	PlayerNameText->SetText(Name);
}

void UPartyListElement::SetUserCharacterData(const FUserCharacter& Data)
{
	UserCharacterData = MakeShared<FUserCharacter>(Data);
	RefreshUI();
}

FUserCharacter* UPartyListElement::GetUserCharacterData()
{
	if (UserCharacterData.IsValid()) return nullptr;
	return UserCharacterData.Get();
}
