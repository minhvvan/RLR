// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "GameManager/RLRStruct.h"
#include "SkillTreeSlot.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API USkillTreeSlot : public USlotUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

	virtual void OnClickedSlotButton() override;
	virtual void	OnHoveredSlotButton() override;
	virtual void	OnUnHoveredSlotButton() override;

	void SetSkillData(FSkillData& NewSkillData);
	virtual void RefreshUI() override;


public:

	/*
	
	*/


private:

	FSkillData SkillData;
	
};
