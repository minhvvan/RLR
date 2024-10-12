// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MessageBoxUI.h"

#include "Components/TextBlock.h"

void UMessageBoxUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMessageBoxUI::Init()
{
	Super::Init();
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
