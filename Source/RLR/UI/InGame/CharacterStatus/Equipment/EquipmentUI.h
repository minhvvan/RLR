// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "GameManager/DataManager.h"
#include "EquipmentUI.generated.h"

/**
 * 
 */

 class UEquipmentSlot;

UCLASS()
class RLR_API UEquipmentUI : public UBaseUI
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	void				EquipItem(FItemData ItemData);

public:

	//무기,  방어구
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquipmentSlot> WeaponSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquipmentSlot> SubWeaponSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquipmentSlot> HelmetSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquipmentSlot>	UpperBodyArmorSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquipmentSlot> LowerBodyArmorSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquipmentSlot> ShoesSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquipmentSlot> GlovesSlot;

	//장신구

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquipmentSlot> NecklaceSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquipmentSlot> EarringSlot_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquipmentSlot> EarringSlot_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquipmentSlot> RingSlot_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquipmentSlot> RingSlot_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquipmentSlot> BraceletSlot;

private:
	TArray<UEquipmentSlot*> EquipmentSlotList;
};
