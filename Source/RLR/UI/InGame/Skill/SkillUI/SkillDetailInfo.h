// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "Structs/SkillStructs.h"
#include "Structs/UtilStructs.h"
#include "SkillDetailInfo.generated.h"

/**
 * 
 */



 class UTextBlock;
 class UImage;
 class UButton;
 class USkillUpgrade;

UCLASS()
class RLR_API USkillDetailInfo : public UBaseUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;

	void SetSkillData(const FSkillData& SkillData);
	void SetSkillLearned(bool bLearned);
	void Clear();

	UFUNCTION()
	void OnClickedUpgradeSkillButton();

	UFUNCTION()
	void OnClickedShowChainSkillButton();

public:

	/*
		Binding
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillInfoText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> SkillImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> UpgradeSkillButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> ShowChainSkillButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> UpgradeSkillButtonText;

public:
	UPROPERTY()
	FSkillData SkillData = FSkillData::EmptySkillData;

	UPROPERTY()
	FActionResource ActionResource = FActionResource::EmptyActionResource;
};
