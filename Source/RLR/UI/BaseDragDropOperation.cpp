// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseDragDropOperation.h"


UBaseDragDropOperation::UBaseDragDropOperation():
    ItemData(FItemData::EmptyItemData),
    SkillData(FSkillData::EmptySkillData),
    DragOffset(FVector::ZeroVector),
    DragedSlotType(ESlotType::NONE)
{
}

void UBaseDragDropOperation::SetItemData(const FItemData& NewItemData)
{
    ItemData = NewItemData;
}

void UBaseDragDropOperation::SetItemResourceData(const FItemResource& NewItemResourceData)
{
    ItemResourceData = NewItemResourceData;
}

void UBaseDragDropOperation::SetSkillData(const FSkillData& NewSkillData)
{
    SkillData = NewSkillData;
}

const FItemData& UBaseDragDropOperation::GetItemData()
{
    return ItemData;
}

const FSkillData& UBaseDragDropOperation::GetSkillData()
{
    return SkillData;
}

const FItemResource& UBaseDragDropOperation::GetItemResource()
{
   return ItemResourceData;
}

void UBaseDragDropOperation::Clear()
{
    SetItemData(FItemData::EmptyItemData);
    SetSkillData(FSkillData::EmptySkillData);
}

bool UBaseDragDropOperation::IsEmpty()
{
    bool Ret = (ItemData == FItemData::EmptyItemData && SkillData == FSkillData::EmptySkillData);

    return Ret;
}
