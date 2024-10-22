// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "NPCCartSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCartClicked, const FItemData&, Item);

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
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void RefreshUI() override;

	FOnCartClicked OnCartClicked;
};
