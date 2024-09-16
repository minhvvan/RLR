// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "GameplayTagsManager.h"
#include "ItemQuickSlotContainer.generated.h"

/**
 * 
 */

 class UGridPanel;
 class UItemQuickSlot;

UCLASS()
class RLR_API UItemQuickSlotContainer : public UBaseUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void Init() override;
	virtual void RefreshUI() override;
	virtual void Clear() override;

public:

	/*
		bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UGridPanel> ItemQuickSlotGridPanel;

public:

	UPROPERTY()
	TMap<FGameplayTag, UItemQuickSlot*> QuickSlotMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32	MaxColunm = 4;

};
