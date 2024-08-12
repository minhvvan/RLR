// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/StatusDisplay/SkillQuickSlotContainer.h"
#include "UI/InGame/StatusDisplay/SkillQuickSlot.h"


#include "Components/GridPanel.h"

void USkillQuickSlotContainer::NativeConstruct()
{
	Super::NativeConstruct();

}

void USkillQuickSlotContainer::RefreshUI()
{
	Super::RefreshUI();
}

void USkillQuickSlotContainer::AddChild(USkillQuickSlot* NewSlot, int32 Index)
{
	SkillQuickSlotGridPanel->AddChildToGrid(NewSlot, Index / MaxColunm, Index % MaxColunm);
}

void USkillQuickSlotContainer::Clear()
{
	Super::Clear();

	SkillQuickSlotGridPanel->ClearChildren();
}
