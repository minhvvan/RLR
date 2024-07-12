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
 class UButton;
 class USizeBox;
 class UTextBlock;

UCLASS()
class RLR_API UEquipmentUI : public UBaseUI
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	void				EquipItem(FItemData ItemData);

	UFUNCTION()
	void ToggleShowDetailStatUI();

	UFUNCTION(BlueprintCallable)
	void RefreshStatUI(FStatus NewStatus);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> DetailStatButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USizeBox> DetailStatSizeBox;

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


	/*
		Stat UI
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> HPStatText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> MPStatText;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthStatText;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> MagicStatText;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> StrengthStatText;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> AgilityStatText;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> INTStatText;


	//Detail Stat
		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> DamageStatText;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> DefenceStatText;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> AttackSpeedStatText;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CoolTimeStatText;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> MoveSpeedStatText;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> EvasionStatText;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> LifeStealStatText;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CriticalChanceStatText;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CriticalDamageStatText;

private:
	TArray<UEquipmentSlot*> EquipmentSlotList;
};