// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "SkillSettingListSlot.generated.h"

/**
 * 
 */

 class UTextBlock;

UCLASS()
class RLR_API USkillSettingListSlot : public USlotUI
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;
	virtual void SetEquipped(bool Value);

	virtual void OnClickedSlotButton() override;

	void SetSkillData(FSkillData& NewSkilData);


public:

	/*
		Binding
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> EquipStateText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillLevelText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillNameText;



private:

	UPROPERTY()
	FSkillData SkillData = FSkillData::EmptySkillData;

	UPROPERTY()
	bool IsEquipped = false;

};
