// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WrapBox.h"
#include "Structs/SkillStructs.h"
#include "SkillTreeSlotContainer.generated.h"

/**
 * 
 */

 class USkillTreeSlot;

UCLASS()
class RLR_API USkillTreeSlotContainer : public UWrapBox
{
	GENERATED_BODY()
	
public:
	
	virtual void Init(int32 MaxSlotCount = 30);
	virtual void RefreshUI();
	virtual void Clear();
	virtual void AddChild(FSkillData SkillData);

public:

	UPROPERTY()
	TMap<int32, USkillTreeSlot*> SlotMap;

};
