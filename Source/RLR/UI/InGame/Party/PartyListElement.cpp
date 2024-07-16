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
	float MaxHp =  UserCharacterData.GetUserCharacterData().totalstatus().usermaxhp();
	float CurrentHp = UserCharacterData.GetUserCharacterData().totalstatus().userhp();

	float Value = FMath::Clamp(CurrentHp/ MaxHp, 0, 1);
	SetPercentHpBar(Value);

	FString ConvertString = UTF8_TO_TCHAR(UserCharacterData.GetUserCharacterData().name().c_str());
	SetPlayerName(ConvertString);
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
