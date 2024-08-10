// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameManager/DataManager.h"
#include "UI/BaseUI.h"
#include "UI/SlotUI.h"
#include "InventorySlot.generated.h"

/**
 * 
 */

 class UImage;
 class UButton;
 class UInventoryUI;

UCLASS()
class RLR_API UInventorySlot : public USlotUI
{
	GENERATED_BODY()
	
public:

	virtual void	NativeConstruct() override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	//virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


	UFUNCTION(BlueprintImplementableEvent)
	void				DisplayEquippedItems(bool IsEquiped = false);

	virtual void	OnClickedSlotButton() override;
	virtual void	OnHoveredSlotButton() override;
	virtual void	OnUnHoveredSlotButton() override;

	UFUNCTION(BlueprintCallable)
	void				SetItemData(FItemData ItemData);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FItemData	GetItemData(){return SlotItemData;};

	virtual void	Clear();

	//Item_ID가 -1이면 아이템 정보가 없다는 뜻. 그러니 비어있는 것으로 판단해준다.
	virtual bool	IsEmpty(){return SlotItemData.ITEM_ID == -1; }

public:

	/*
		슬롯 이미지
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UImage> ItemRarityImage;


public:

	UPROPERTY(EditAnywhere)
	FItemData SlotItemData;

	UPROPERTY(EditAnywhere)
	UInventoryUI* Inventory;
};
