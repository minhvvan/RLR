// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentList.generated.h"

class UEquipmentButton;
class UEnhanceUI;
class UVerticalBox;

/**
 * 강화장의 장비목록
 */
UCLASS()
class RLR_API UEquipmentList : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void AddEquipButton(int64 itemID);

	UFUNCTION()
	void OnEquipItemClicked(int64 itemID);

public:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UEquipmentButton> EquipButtonUIClass;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* EquipListContainer;

	UEnhanceUI* EnhanceUI;

};
