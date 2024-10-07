// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSettingQuickSlot.h"
#include "UI/InGame/Skill/SkillUI/SkillSetting/SkillSetting.h"
#include "UI/DraggableWidget.h"
#include "UI/BaseDragDropOperation.h"
#include "Components/Image.h"
#include "Components/Button.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "GameManager/GameManager.h"
#include "GameMAnager/UIManager.h"
#include "GameManager/InventoryManager.h"



void USkillSettingQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();
	SetSlotType(ESlotType::SKILL_SETTING_QUICK_SLOT);
}

//TODO
void USkillSettingQuickSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool USkillSettingQuickSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Ret = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if (Ret == false)
		return false;

	//스킬 목록이나 스킬 퀵 슬롯에서 가져온 경우만 통과 시켜준다.
	UBaseDragDropOperation* Operation = CheckValidAndType(InOperation, ESlotType::SKILL_SETTING_LIST_SLOT, ESlotType::SKILL_SETTING_QUICK_SLOT);
	if (IsValid(Operation) == false)
		return false;

	USlotUI* DraggedSlot = Operation->GetMaster();
	if (IsValid(DraggedSlot) == false)
		return false;

	/*
		Case 1. Skill Quick Slot -> Skill Quick Slot
			1-1. 그런데 이미 해당 슬롯에 정보가 들어 있다면?
				서로 위치를 바꿔준다.
			1-2. 해당 슬롯이 빈 슬롯이라면 바로 넣어준다. 그리고 옮겨진 슬롯이 기존에 있던 위치는 비워준다.

		Case 2	Skill List Slot -> Skill Quick Slot
			2-1. 해당 슬롯이 빈 슬롯이라면 바로 넣어준다.

			2-2. 해당 슬롯에 이미 다른 정보가 있다면, 비워주고 넣어준다.	
				=>결국 어떤 케이스든 그냥 바로 넣어주면 된다.
	
	*/

	if (DraggedSlot->GetSlotType() == ESlotType::SKILL_SETTING_QUICK_SLOT)
	{
		if (IsEmpty() == true)
		{
			SetSkillData(DraggedSlot->GetSkillData());
			SetSkillClassData(DraggedSlot->GetSkillClassData());
			DraggedSlot->Clear();
		}
		else if(IsEmpty() == false)
		{	
			FSkillData Temp = DraggedSlot->GetSkillData();
			FSkillClass TempResource = DraggedSlot->GetSkillClassData();
			SetSkillData(DraggedSlot->GetSkillData());
			SetSkillClassData(DraggedSlot->GetSkillClassData());
			DraggedSlot->SetSkillData(Temp);
			DraggedSlot->SetSkillClassData(TempResource);
			DraggedSlot->Clear();
		}
	}
	else if (DraggedSlot->GetSlotType() == ESlotType::SKILL_SETTING_LIST_SLOT)
	{
		SetSkillData(DraggedSlot->GetSkillData());
		SetSkillClassData(DraggedSlot->GetSkillClassData());
	}
	return true;
}

void USkillSettingQuickSlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
}

FReply USkillSettingQuickSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	Clear();

	return result;
}

void USkillSettingQuickSlot::RefreshUI()
{
	Super::RefreshUI();

	const FSkillData& SkillData = GetSkillData();

	if (SkillData == FSkillData::EmptySkillData)
	{
		SetSlotImage(GetDefaultSlotImage());
		return;
	}

	const FSkillClass& SkillClass = GetSkillClassData();

	if (SkillClass == FSkillClass::EmptySkillClass)
	{
		SetSlotImage(GetDefaultSlotImage());
		return;
	}

	SetSlotImage(SkillClass.SkillImage);
}

void USkillSettingQuickSlot::SetActionTag(FGameplayTag NewActionTag)
{

	ActionTag = NewActionTag;

}

void USkillSettingQuickSlot::SetInputTag(FGameplayTag NewInputTag)
{

	InputTag = NewInputTag;

}
