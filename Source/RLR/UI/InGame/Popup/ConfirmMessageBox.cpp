// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Popup/ConfirmMessageBox.h"

void UConfirmMessageBox::NativeConstruct()
{
	Super::NativeConstruct();
}

void UConfirmMessageBox::Init()
{
	Super::Init();

	SetUIType(EUIType::CONFIRM_MESSAGE_BOX);
}

void UConfirmMessageBox::RefreshUI()
{
	Super::RefreshUI();
}

void UConfirmMessageBox::OpenUI()
{
	Super::OpenUI();
}

void UConfirmMessageBox::Clear()
{
	Super::Clear();
}

void UConfirmMessageBox::CloseUI()
{
	Super::CloseUI();
}
