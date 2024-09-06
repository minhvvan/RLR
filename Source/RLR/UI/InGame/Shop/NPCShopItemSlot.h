// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "NPCShopItemSlot.generated.h"

class UImage;
class UTextBlock;
class UNPCPurchaseTab;

UCLASS()
class RLR_API UNPCShopItemSlot : public USlotUI, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtItemName;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtPrice;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> ImgPrice;

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	//드래그 드랍
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override {};
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override { return false; };
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override {};
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

	virtual void OnClickedSlotButton() {};
	virtual void OnHoveredSlotButton() {};
	virtual void OnUnHoveredSlotButton() {};

	virtual void RefreshUI() override;

public:
	virtual void SetParent(TObjectPtr<UNPCPurchaseTab> Parent);
	TObjectPtr<UNPCPurchaseTab> GetParentUI() { return ParentUI; }

protected:
	UPROPERTY()
	TObjectPtr<UNPCPurchaseTab> ParentUI;
};
