// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseHUD.h"
#include "TitleHUD.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API ATitleHUD : public ABaseHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;	
};
