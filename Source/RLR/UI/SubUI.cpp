// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubUI.h"
#include "UI/SlotUI.h"
#include "UI/DialogueUI.h"
#include "GameManager/UIManager.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/TextBlock.h"
#include "Structs/UtilStructs.h"

void USubUI::NativeConstruct()
{
	Super::NativeConstruct();
	if (DragButton)
	{
		DragButton->OnPressed.AddUniqueDynamic(this, &USubUI::OnDragStarted);
		DragButton->OnReleased.AddUniqueDynamic(this, &USubUI::OnDragEnded);

	}
}

void USubUI::OpenUI()
{
	SetVisible(true);
	RefreshUI();
}

void USubUI::CloseUI()
{
	SetVisible(false);
	Clear();
}

void USubUI::SetVisibilityToggle()
{
	ESlateVisibility CurrentVisivility = GetVisibility();
	if (CurrentVisivility == ESlateVisibility::Hidden)
		OpenUI();
	else
		CloseUI();
}

void USubUI::OnDragStarted()
{
	UMainUI* mainUI = Cast<UMainUI>(GetParent());
	if (!mainUI) return;

	mainUI->SetZOrderToTop(UITag);

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

void USubUI::SetPosition(FVector2D pos)
{
	if (auto slot = Cast<UCanvasPanelSlot>(Slot))
	{
		slot->SetPosition(pos);
	}
}

void USubUI::CloseUIByManager()
{
	GetUIManager()->CloseSubUI(UITag);
}

void USubUI::SetTitle(const FString& Title) const
{
	TxtTitle->SetText(FText::FromString(Title));
}
