// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseDragDropOperation.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"


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

void UBaseDragDropOperation::SetSkillData(const FSkillData& NewSkillData)
{
    SkillData = NewSkillData;
}

void UBaseDragDropOperation::SetSkillClassData(const FSkillClass& NewSkillClassData)
{
    SkillClassData = NewSkillClassData;
}

const FItemData& UBaseDragDropOperation::GetItemData()
{
    return ItemData;
}

const FSkillData& UBaseDragDropOperation::GetSkillData()
{
    return SkillData;
}

const FItemResource UBaseDragDropOperation::GetItemResource()
{
   return ItemData.GetItemResource();
}

const FSkillClass& UBaseDragDropOperation::GetSkillClassData()
{
    int32 SKillSeq = SkillData.SkillSeq;
    SkillClassData = GameInstance->GetDataManager()->GetSkillResource(SKillSeq);
    return SkillClassData;
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
