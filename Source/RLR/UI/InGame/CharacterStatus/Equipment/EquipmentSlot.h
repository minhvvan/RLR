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

	virtual void NativeConstruct() override;


	virtual void OnClickedSlotButton() override;
	virtual void	OnHoveredSlotButton() override;
	virtual void	OnUnHoveredSlotButton() override;

	UFUNCTION(BlueprintCallable)
	void				SetItemData(FItemData ItemData);
	UFUNCTION(BlueprintCallable)
	FItemData	GetItemData(){return SlotItemData;}

	virtual void	Clear();

	//Item_ID가 -1이면 아이템 정보가 없다는 뜻. 그러니 비어있는 것으로 판단해준다.
	virtual bool	IsEmpty(){return SlotItemData.ITEM_ID == -1; }

public:


	//Bind Widget

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemRarityImage;

		//등급에 따른 배경색
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EItemRarity, TObjectPtr<UTexture2D>> RarityImage;

	EEquipmentType SlotType = EEquipmentType::NONE;



private:

	UPROPERTY()
	FItemData SlotItemData;
};
