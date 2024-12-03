// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Popup/ItemCountMessageBox.h"

#include "GameManager/GameplayTagManager.h"
#include "GameManager/LiteralManager.h"

#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Structs/UtilStructs.h"

void UItemCountMessageBox::NativeConstruct()
{
	Super::NativeConstruct();

}

void UItemCountMessageBox::Init()
{
	Super::Init();

	SetUITag(RLRTAG.UI_Popup_ItemCountMessageBox);
}

void UItemCountMessageBox::RefreshUI()
{
	Super::RefreshUI();

	if(ItemData == FItemData::EmptyItemData)
		return;

	FText Text1 = STRING_TO_FTEXT(RLRLITERAL.ItemCountMsg_InputQuantity);
	FText MessageTextFormat = FText::Format(FText::FromString("[{0}] {1}"), ItemData.NAME, Text1);
	MessageText->SetText(MessageTextFormat);
}

void UItemCountMessageBox::OpenUI()
{
	Super::OpenUI();
}

void UItemCountMessageBox::Clear()
{
	Super::Clear();
	SetItemData(FItemData::EmptyItemData);
	InputEditableTextBox->SetText(FText());
}

void UItemCountMessageBox::CloseUI()
{
	Super::CloseUI();
}

void UItemCountMessageBox::OnClickedConfirmButton()
{
	Super::OnClickedConfirmButton();
	CloseUI();
}

void UItemCountMessageBox::OnClickedCancelButton()
{
	Super::OnClickedCancelButton();
	CloseUI();
}

int32 UItemCountMessageBox::GetItemCount()
{
	FString CountString = InputEditableTextBox->GetText().ToString();
	int32 ItemCount = FCString::Atoi(*CountString);
	return ItemCount;
}
