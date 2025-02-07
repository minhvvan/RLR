// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ItemStructs.h"
#include "Structs/CommunicationStructs.h"
#include "PostWriteTabWidget.generated.h"

class UInputTransactionCost;
class UPostItemSlot;
class UWidgetSwitcher;
class UButton;
class UMultiLineEditableText;
class UEditableText;
class UTextBlock;
class UGridPanel;
class UListView;

UCLASS()
class RLR_API UPostWriteTabWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

	/* Bind Widget */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UGridPanel> PostSlotGridPanel;

    UPROPERTY(meta = (BindWidget))
    UButton* NormalPostButton;

    UPROPERTY(meta = (BindWidget))
    UButton* SpecialPostButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* PostCostText;

    UPROPERTY(meta = (BindWidget))
    UMultiLineEditableText* PostContentText;

    UPROPERTY(meta = (BindWidget))
    UEditableText* RecipientIdText;

    UPROPERTY(meta = (BindWidget))
    UEditableText* PostTitleText;

    //UPROPERTY(meta = (BindWidgetOptional))
    //UPostItemSlot* PostItemSlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
    UInputTransactionCost* RequestCostInput;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
    UInputTransactionCost* GrantCostInput;

    UPROPERTY(meta = (BindWidget))
    UButton* SendPostButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ClearPostButton;

 //   UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	//TArray<TObjectPtr<UPostItemSlot>> PostSlotList;

    bool bIsSpecialPost = false;
    UFUNCTION()
    void OnNormalPostButtonClicked();

    UFUNCTION()
    void OnSpecialPostButtonClicked();

    UFUNCTION()
    void OnSendPostButtonClicked();

    UFUNCTION()
    void OnClearPostButtonClicked();

    TArray<int64> GetAttachedItemsFromSlots();

    //UFUNCTION()
    //void UpdatePostCost();
    UFUNCTION()
    void AddItemToPostSlot(const FItemData& ItemData, int32 InventorySlotIndex);

public:
    void OpenBundleItemSend(const FItemData& ItemData, int32 InventorySlotIndex);
    void UpdatePage();

protected:
    UPostItemSlot* GetItemSlotWidget(int32 idx);
    void AddEmptySlotsToGridPanel();
};
