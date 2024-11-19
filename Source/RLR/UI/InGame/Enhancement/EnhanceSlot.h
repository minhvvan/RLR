// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "EnhanceSlot.generated.h"

/**
 * 강화창의 아이템 슬롯
 */
UCLASS()
class RLR_API UEnhanceSlot : public USlotUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;
	virtual void Clear() override;

	void SetItemID(int64 NewItemId);

	UFUNCTION()
	void SetSlot(int64 NewitemId);

public:
	/*
		슬롯 이미지
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UImage> ItemRarityImage;

	UPROPERTY(EditAnywhere)
	int64 itemId;
};
