// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/InGame/CharacterOverhead/CharacterOverHead.h"
#include "PlayerOverHead.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UPlayerOverHead : public UCharacterOverHead
{
	GENERATED_BODY()
	
public:
	void SetActionSystemComponent(AActor* Owner) override;
};
