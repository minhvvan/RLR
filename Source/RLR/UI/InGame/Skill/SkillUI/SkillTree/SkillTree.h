// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "SkillTree.generated.h"

/**
 * 
 */

 class UWrapBox;
 class UTextBlock;
 class USkillTreeSlot;
 class USkillPropertyContainer;

UCLASS()
class RLR_API USkillTree : public UBaseUI
{
	GENERATED_BODY()
public:


	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;

	void UpdateNormalSkill();
	void UpdateUniqueSkill();
	void UpdateUltimateSkill();



public:

	/*
		Bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UWrapBox> NormalSkillWrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UWrapBox>	UniqueSkillWrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UWrapBox>	UltimateSkillWrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillPointText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<USkillPropertyContainer> SkillPropertyContainer;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USkillTreeSlot> SkillTreeSlotClass;
	
};
