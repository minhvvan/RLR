// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/InGame/Inventory/InventorySlot.h"
#include "NPCShopInventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UNPCShopInventorySlot : public UInventorySlot
{
	GENERATED_BODY()
	
public:
	//virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	//virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
