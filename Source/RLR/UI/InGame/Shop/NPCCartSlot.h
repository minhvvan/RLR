// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "NPCCartSlot.generated.h"

class UTextBlock;

UCLASS()
class RLR_API UNPCCartSlot : public USlotUI, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtItemAmount;

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	//드래그 드랍
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void OnClickedSlotButton();
	virtual void OnHoveredSlotButton();
	virtual void OnUnHoveredSlotButton();

	virtual void RefreshUI() override;
};
