// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseDragDropOperation.h"

void UBaseDragDropOperation::SetItemData(const FItemData& NewItemData)
{
    ItemData = NewItemData;
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
