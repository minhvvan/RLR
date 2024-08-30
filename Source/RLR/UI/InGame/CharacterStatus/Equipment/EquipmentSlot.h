// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameManager/DataManager.h"
#include "UI/BaseUI.h"
#include "UI/SlotUI.h"
#include "EquipmentSlot.generated.h"

/**
 * 
 */

 class UImage;
 class UButton;

UCLASS()
class RLR_API UEquipmentSlot : public USlotUI
{
	GENERATED_BODY()

public:
	UEquipmentSlot(const FObjectInitializer& ObjectInitializer);

	virtual void	NativeConstruct() override;
	virtual void	RefreshUI() override;

	virtual void	OnClickedSlotButton() override;
	virtual void	OnHoveredSlotButton() override;
	virtual void	OnUnHoveredSlotButton() override;
public:


	//Bind Widget

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemRarityImage;

		//등급에 따른 배경색
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EItemRarity, TObjectPtr<UTexture2D>> RarityImage;

	EEquipmentType EquipmentSlotType;
};
