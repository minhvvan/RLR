// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "SlotUI.generated.h"

/**
 * 
 */

 class USizeBox;

UCLASS()
class RLR_API USlotUI : public UBaseUI
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USizeBox> RootSizeBox;
	
};
