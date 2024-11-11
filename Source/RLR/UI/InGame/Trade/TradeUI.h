// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "Structs/ItemStructs.h"
#include "TradeUI.generated.h"

/**
   개인 거래 UI.
 */

class UTradeList;
class UTradeListSlot;
class UTradeListElement;
class UButton;
class UTextBlock;
class UWidgetSwitcher;
class UItemCountMessageBox;
class UConfirmMessageBox;

UCLASS()
class RLR_API UTradeUI : public USubUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void Init() override;
	UFUNCTION()
	virtual void RefreshUI() override;
	virtual void OpenUI() override;
	virtual void Clear() override;
	virtual void CloseUI() override;

public:

	void HandleTradeUserResponse(int32 UserSeq);
	void HandleTradeStartResponse(int32 UserSeq1, FString UserName1, int32 UserSeq2, FString UserName2);
	void UpdateTradeData();
	void UpdateTradeState();
	void HandleTradeCompleteResponse();

	UFUNCTION()
	void SendTradeAddItemBySelf(const FItemData& NewTradeItem, int32 Quantity = 1);
	void SendTradeAddGoodBySelf(int32 Amount);

	void AddItemByTarget(const FItemData& NewTradeItem);
	void AddItemBySelf(const FItemData& NewTradeItem);
	void AddGoodBySelf(int32 Amount);
	void AddGoodByTarget(int32 Amount);

	UFUNCTION()
	void SendTradeLock();
	UFUNCTION()
	void SendTradeUnLock();

	void LockBySelf();
	void UnLockBySelf();
	void LockByTarget();
	void UnLockByTarget();

	UFUNCTION()
	void SendTradeCancelPacket();					//내가 거래 취소
	void HandleTradeCanceledByTarget();				//상대방이 취소했을 때 핸들.					//거래가 성공

public:

	void SetTradeLock(bool IsSelf);
	void SetTradeUnLock(bool IsSelf);

public:

	UFUNCTION()
	void		OnClickedAcceptButton(UConfirmMessageBox* MessageBox);
	UFUNCTION()
	void		OnClickedCancelButton(UConfirmMessageBox* MessageBox);

	UFUNCTION()
	void		OnClickedInventorySlot(const FItemData& NewTradeItem);
	UFUNCTION()
	void		OnConfirmItemCountMessageBox(UItemCountMessageBox* MessageBox);
	UFUNCTION()
	void		OnCancelItemCountMessageBox(UItemCountMessageBox* MessageBox);
	UFUNCTION()
	void		OnClickedAddGoldButton();

public:

	/*
		bind
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTradeList> MyTradeList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTradeList> TargetPlayerTradeList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> AddGoldButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> MyNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> TargetPlayerNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> MyGoldText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> TargetGoldText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> OfferStateText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> TradeStateText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> TradeStateWidgetSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> OfferButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> UnLockButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> ConfirmButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> CancelButton;
};
