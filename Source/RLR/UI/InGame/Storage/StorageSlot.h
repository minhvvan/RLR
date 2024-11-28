// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "StorageSlot.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UStorageSlot : public USlotUI, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual void RefreshUI() override;

protected:
	UFUNCTION()
	void StorageToInventoryMessageBoxCallback(class UMessageBoxUI* MessageBox);

	void SendPktStroageToInventory(const FItemData& Item, int Amount);
};
