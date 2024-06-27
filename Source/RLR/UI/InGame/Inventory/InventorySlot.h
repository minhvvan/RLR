// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameManager/DataManager.h"
#include "UI/BaseUI.h"
#include "UI/SlotUI.h"
#include "InventorySlot.generated.h"

/**
 * 
 */

 class UImage;
 class UButton;

UCLASS()
class RLR_API UInventorySlot : public USlotUI
{
	GENERATED_BODY()
	
public:

	virtual void	NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void				DisplayEquippedItems(bool IsEquiped = false);


	UFUNCTION(BlueprintCallable)
	void				OnClickedItemSlot();

	UFUNCTION(BlueprintCallable)
	void				OnHoveredItemSlot();

	UFUNCTION(BlueprintCallable)
	void				OnUnHoveredItemSlot();

	UFUNCTION(BlueprintCallable)
	void				SetItemData(FItemData ItemData);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FItemData	GetItemData(){return SlotItemData;};

	UFUNCTION(BlueprintCallable)
	void				Clear();

	//Item_ID가 -1이면 아이템 정보가 없다는 뜻. 그러니 비어있는 것으로 판단해준다.
	UFUNCTION(BlueprintCallable)
	bool				IsEmpty(){return SlotItemData.ITEM_ID == -1; }

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UImage> ItemRarityImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> ItemButton;

public:
	UPROPERTY(EditAnywhere)
	FItemData SlotItemData;


	/*
		기본 이미지나, Rarity 색깔은 코드가 아니라  BP에서 설정.
	*/
	//기본 상태 슬롯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> DefaultSlotImage;
};
