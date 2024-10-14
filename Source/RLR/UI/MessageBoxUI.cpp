// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MessageBoxUI.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

void UMessageBoxUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMessageBoxUI::Init()
{
	Super::Init();

	if(IsValid(ConfirmButton) == true)
		ConfirmButton->OnClicked.AddUniqueDynamic(this, &UMessageBoxUI::OnClickedConfirmButton);
	if (IsValid(CancelButton) == true)
		CancelButton->OnClicked.AddUniqueDynamic(this, &UMessageBoxUI::OnClickedCancelButton);
	OnConfirmButtonClickedDelegate.Unbind();
	OnCancelButtonClickedDelegate.Unbind();
}

void UMessageBoxUI::RefreshUI()
{
	Super::RefreshUI();
}

void UMessageBoxUI::OpenUI()
{
	Super::OpenUI();
	Clear();
}

void UMessageBoxUI::Clear()
{
	Super::Clear();
	MessageText->SetText(FText());
	OnConfirmButtonClickedDelegate.Unbind();
	OnCancelButtonClickedDelegate.Unbind();
}

void UMessageBoxUI::CloseUI()
{
	Super::CloseUI();
	Clear();
}

void UMessageBoxUI::OnClickedConfirmButton()
{
	OnConfirmButtonClickedDelegate.ExecuteIfBound(this);
}

void UMessageBoxUI::OnClickedCancelButton()
{
	OnCancelButtonClickedDelegate.ExecuteIfBound(this);
}

void UMessageBoxUI::SetText(FString MessageString)
{
	//FText Text = STRING_TO_FTEXT(MessageString);
	//FText MessageTextFormat = FText::Format(FText::FromString("[{0}] {1}"), ItemData.NAME, Text1);
	FText Text = FText::FromString(MessageString);
	MessageText->SetText(Text);
}
