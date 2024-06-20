// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameManager/DataManager.h"
#include "InventorySlot.generated.h"

/**
 * 
 */

 class UImage;
 class UButton;

UCLASS()
class RLR_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UImage> ItemRarityImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> ItemButton;
	
public:

	UFUNCTION(BlueprintCallable)
	void				SetItemData(FItemData ItemData);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FItemData	GetItemData(){return SlotItemData;};

	UFUNCTION(BlueprintCallable)
	void				Clear();

public:
	UPROPERTY(EditAnywhere)
	FItemData SlotItemData;


	/*
		기본 이미지나, Rarity 색깔은 코드가 아니라  BP에서 설정.
	*/
	//기본 상태 슬롯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> DefaultSlotImage;

	//등급에 따른 배경색
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EItemRarity, TObjectPtr<UTexture2D>> RarityImage;

};
