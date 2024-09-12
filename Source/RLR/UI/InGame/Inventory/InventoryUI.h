// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/SubUI.h"
#include "GameManager/DataManager.h"
#include "InventoryUI.generated.h"

/**
 * 
 */

 class UGridPanel;
 class UButton;
 class UTextBlock;
 class UInventorySlot;

UCLASS()
class RLR_API UInventoryUI : public USubUI
{
	GENERATED_BODY()


public:
	UInventoryUI(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void RefreshUI();

	UFUNCTION(BlueprintCallable)
	void RefreshGoldAndCashUI();

	UFUNCTION(BlueprintCallable)
	void ShowItemsByType(EItemType ItemType);

	UFUNCTION(BlueprintCallable)
	void SortItem();

	UFUNCTION(BlueprintCallable)
	void SetItemData(FItemData& NewItem);

public:

	//Bind Widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UGridPanel> InventoryGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UTextBlock> CopperText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UTextBlock> SilberText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UTextBlock> GoldText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UTextBlock> PlatinumText;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UButton> AllButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UButton> EquipmentButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UButton> ConsumableButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UButton> EtcItemButton;

	//Quest Item Button은 추후 기획에 따라 추가할지 제거할지 결정
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	//TObjectPtr<UButton> QuestItemButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UButton> SortButton;

	UFUNCTION(BlueprintCallable)
	void OnAllButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnEquipmentButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnConsumableButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnEtcItemButtonClicked();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxColumm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxInventorySlotCount;

	UFUNCTION(BlueprintCallable)
	void	SetMaxSlotCount(int32 Count);
	UFUNCTION(BlueprintCallable)
	int32	GetMaxSlotCount(){return MaxInventorySlotCount;};
public:
	//인벤토리 클래스 정보는 BP에서 설정.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UInventorySlot> InventorySlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UInventorySlot>> InventorySlotList;

	EItemType CurrentFilter;

public:
	void RemoveSaleItem(const FItemData& Item);
};
