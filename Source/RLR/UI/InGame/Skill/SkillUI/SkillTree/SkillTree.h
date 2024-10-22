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
 class USkillTreeSlotContainer;
 class USkillPropertyContainer;

UCLASS()
class RLR_API USkillTree : public UBaseUI
{
	GENERATED_BODY()
public:


	virtual void NativeConstruct() override;
	virtual void Init() override;
	virtual void RefreshUI() override;
	virtual void Clear() override;
	void LoadSkillList();
	void ClearSkillList();

public:

	/*
		Bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<USkillTreeSlotContainer> NormalSkillWrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<USkillTreeSlotContainer>	UniqueSkillWrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<USkillTreeSlotContainer>	UltimateSkillWrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillPointText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<USkillPropertyContainer> SkillPropertyContainer;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USkillTreeSlot> SkillTreeSlotClass;
	
};
