// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/BaseHUD.h"
#include "InGameHUD.generated.h"

/**
 
	MainUIClass 는 블루프린트에서 지정해준다.

 */

 class UMainUI;
UCLASS()
class RLR_API AInGameHUD : public ABaseHUD
{
	GENERATED_BODY()

public:
	AInGameHUD();

    virtual void BeginPlay() override;


	
};
