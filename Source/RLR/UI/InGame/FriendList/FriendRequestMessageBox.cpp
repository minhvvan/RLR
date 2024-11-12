// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendRequestMessageBox.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"

void UFriendRequestMessageBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Slot))
	{
		CanvasSlot->SetSize(FVector2D(240.f, 100.f)); 
	}
}

void UFriendRequestMessageBox::InitializeWidget(const FString& SenderName)
{
	if (SenderNameText)
	{
		SenderNameText->SetText(FText::FromString(SenderName));
	}
}