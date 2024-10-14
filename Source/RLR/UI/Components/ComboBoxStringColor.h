// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ComboBoxString.h"
#include "ComboBoxStringColor.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UComboBoxStringColor : public UComboBoxString
{
	GENERATED_BODY()
	
public:
	void SetDefaultOptionColor(FSlateColor Color);
};
