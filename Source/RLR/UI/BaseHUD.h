// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

/**
 * 
 */

 class UMainUI;
 class UBaseUI;

UCLASS()
class RLR_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, category=UI)
	FString MainUIClassName;

public:

	virtual void BeginPlay() override;
};
