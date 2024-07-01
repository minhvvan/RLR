// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "CharacterStatusUI.generated.h"

/**
 * 
 */

 class UEquipmentUI;

UCLASS()
class RLR_API UCharacterStatusUI : public USubUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UEquipmentUI> EquipmentUI;

	
};
