// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/InGame/Storage/StorageUI.h"
#include "UserStorageUI.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UUserStorageUI : public UStorageUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
};
