// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetSwitcher.h"
#include "Structs/UtilStructs.h"
#include "PageSwitcher.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UPageSwitcher : public UWidgetSwitcher
{
	GENERATED_BODY()
	
public:
	void SetWidgetAtIndex(int index, UWidget* newWidget);
};
