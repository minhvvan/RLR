// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Popup/NotificationMessageBox.h"

#include "GameManager/GameplayTagManager.h"

#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Structs/UtilStructs.h"

void UNotificationMessageBox::NativeConstruct()
{
	Super::NativeConstruct();
}

void UNotificationMessageBox::Init()
{
	Super::Init();

	SetUIType(EUIType::NOTIFICATION_MESSAGE_BOX);
}

void UNotificationMessageBox::RefreshUI()
{
	Super::RefreshUI();
}

void UNotificationMessageBox::OpenUI()
{
	Super::OpenUI();
}

void UNotificationMessageBox::Clear()
{
	Super::Clear();
}

void UNotificationMessageBox::CloseUI()
{
	Super::CloseUI();
}

void UNotificationMessageBox::OnClickedConfirmButton()
{
	CloseUI();
}
