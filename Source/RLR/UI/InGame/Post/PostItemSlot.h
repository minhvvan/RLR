// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "UI/BaseUI.h"
#include "PostItemSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnPostItemSlotClicked, int32, InventorySlotIndex, int32, PostSlotIndex, const FItemData&, ItemData, ESlotType, SlotType);

class UTextBlock;
class UTImage;
class UPostWriteTabWidget;
class UPostOverlayUI;


UCLASS()
class RLR_API UPostItemSlot : public USlotUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void RefreshUI() override;

	virtual void NativeOnMouseEnter( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual void NativeOnMouseLeave( const FPointerEvent& InMouseEvent ) override;
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;

	UFUNCTION()
	void SetSlot(int64 NewitemId);

	virtual void Clear() override;

	void SetItemAmountShow(bool bVisible);

	void SetInventorySlotIndex(int32 index);
	int32 GetInventorySlotIndex();

	UPROPERTY(BlueprintAssignable, Category = "Post Item")
	FOnPostItemSlotClicked OnPostItemSlotClicked;
public:

	/*
		슬롯 이미지
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UImage> ItemRarityImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtItemCount;

	UPROPERTY(EditAnywhere)
	int64 itemId;

	int32 inventorySlotIndex;

public:
	UPostOverlayUI* PostUI;
};
