// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "StorageUI.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UStorageUI : public USubUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
};
