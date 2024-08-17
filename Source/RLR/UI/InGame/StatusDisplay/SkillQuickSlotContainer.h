// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "SkillQuickSlotContainer.generated.h"

/**
 
	스킬 슬롯을 드래그해서 넣으면 해당 칸에 정보가 들어가야 한다.

 */

class UGridPanel;
class USkillQuickSlot;

UCLASS()
class RLR_API USkillQuickSlotContainer : public UBaseUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;
	void AddChild(USkillQuickSlot* NewSlot, int32 Index);
	virtual void Clear() override;

public:
	
	/*
		Bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UGridPanel> SkillQuickSlotGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32	MaxColunm = 4;

};
