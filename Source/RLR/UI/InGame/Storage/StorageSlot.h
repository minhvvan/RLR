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

	virtual void RefreshUI() override;
};
