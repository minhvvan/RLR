// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubUI.h"
#include "GameManager/UIManager.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void USubUI::NativeConstruct()
{
	Super::NativeConstruct();
	if (DragButton)
	{
		DragButton->OnPressed.AddUniqueDynamic(this, &USubUI::OnDragStarted);
		DragButton->OnReleased.AddUniqueDynamic(this, &USubUI::OnDragEnded);

	}
}

void USubUI::SetVisibilityToggle()
{
	ESlateVisibility CurrentVisivility = GetVisibility();
	if (CurrentVisivility == ESlateVisibility::Hidden)
		OpenUI();
	else
		CloseUI();
}

void USubUI::OpenUI()
{
	UUIManager* UIManager = GetUIManager();
	if (IsValid(UIManager))
	{
		UIManager->ShowSubUI(this);
	}
}

void USubUI::CloseUI()
{
	UUIManager* UIManager = GetUIManager();
	if (IsValid(UIManager))
	{
		UIManager->CloseSubUI(this);
	}
}

void USubUI::OnDragStarted()
{
	GetUIManager()->SetZOderUI(this);

	FVector2D V1 = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2D V2 = Cast<UCanvasPanelSlot>(Slot)->GetPosition();
	ClickedFirstPoint = V1 - V2;

	UpdateLocation();
}

void USubUI::UpdateLocation()
{
	GetWorld()->GetTimerManager().SetTimer(DragTimer,
	[this](){
	
		ClickedCurrentPoint = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		Cast<UCanvasPanelSlot>(Slot)->SetPosition(ClickedCurrentPoint-ClickedFirstPoint);
	}, 0.1f, true);
}

void USubUI::UpdateLocationStop()
{
	GetWorld()->GetTimerManager().ClearTimer(DragTimer);
}

void USubUI::OnDragEnded()
{
	UpdateLocationStop();
}
