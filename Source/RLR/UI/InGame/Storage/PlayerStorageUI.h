// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/InGame/Storage/StorageUI.h"
#include "PlayerStorageUI.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UPlayerStorageUI : public UStorageUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
};
