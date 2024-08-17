// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/InGame/CharacterDisplay/CharacterStatDisplay.h"
#include "PlayerStatDisplay.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UPlayerStatDisplay : public UCharacterStatDisplay
{
	GENERATED_BODY()
	
public:
	void SetActionSystemComponent(AActor* Owner) override;
};
