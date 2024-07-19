// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Party/PartyListElement.h"
#include "Components/ProgressBar.h"
#include "Components/RichTextBlock.h"

void UPartyListElement::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	UPartyListElement* Element = Cast<UPartyListElement>(ListItemObject);

	FUserCharacter Data = Element->GetUserCharacterData();
	SetUserCharacterData(Data);
}

void UPartyListElement::RefreshUI()
{
	float MaxHp =  UserCharacterData.TotalStatus.MAX_HP;
	float CurrentHp = UserCharacterData.TotalStatus.HP;

	float Value = FMath::Clamp(CurrentHp/ MaxHp, 0, 1);
	SetPercentHpBar(Value);

	SetPlayerName(UserCharacterData.Name);
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

void UPartyListElement::SetUserCharacterData(FUserCharacter Data)
{
	UserCharacterData = Data;
	RefreshUI();
}
