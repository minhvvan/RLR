// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "Structs/ItemStructs.h"
#include "TradeList.generated.h"

/**
 * 
 */

 class UScrollBox;
 class UTradeListSlot;
 class UTradeListElement;

UCLASS()
class RLR_API UTradeList : public UBaseUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void Init() override;
	virtual void RefreshUI() override;
	virtual void Clear() override;

public:
	
	void AddTradeItem(const FItemData& NewItem);
	void RemoveTradeItem(int32 RemoveItemID);
	void SetCanDrag(bool Ret);

public:

	/*
		bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UScrollBox> TradeListScrollBox;

public:

	//<Slot Idx, UTradeListElement>
	UPROPERTY()
	TMap<int32, UTradeListElement*> TradeListElementMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TradeListElementMaxCount = 7;	//리스트 최대 갯수
	
};
