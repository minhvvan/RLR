// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Structs/ItemStructs.h"
#include "EnhanceManager.generated.h"

class UEnhanceOverlayUI;
class UEquipmentButton;

/**
 * 아이템 강화 매니저
 */
UCLASS()
class RLR_API UEnhanceManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	void SetEnhanceInfo(FItemData EnhancedItemResult);	
	FItemData GetEnhanceInfo();

	void OpenSuccessUI();
	void OpenFailUI();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData EnhancedItemData;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TObjectPtr<UEnhanceOverlayUI> EnhanceOverlayUI;

	TArray<FItemData> EquipItemList;
};
