// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "TradeListElement.generated.h"

/**
 * 
 */

 class UTextBlock;
 class UTradeListSlot;
 class URichTextBlock;

UCLASS()
class RLR_API UTradeListElement : public UBaseUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void Init() override;
	virtual void RefreshUI() override;
	virtual void Clear() override;

public:

	void SetItemData(const FItemData& ItemData);
	bool IsEmpty();
	void SetCanDrag(bool Ret);

public:

	/*
		bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTradeListSlot> TradeListSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemNameText;

	bool IsMySlot = false;
};
