// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "TradeUI.generated.h"

/**
   개인 거래 UI.

  * 1.아이템을 올리고 제시를 한다.
	: 혹은 취소 버튼을 눌러 거래를 닫는다.
  * 2.제시를 하면 내 거래창이 잠긴다.
	: 이후 잠금 해제를 해서, 다시 제시를 하거나 상대방이 제시 할 때까지 기다린다.
  * 3.서로 제시가 끝났으면 '거래'버튼이 활성화 된다.
 */

class UTradeList;
class UTradeListSlot;
class UTradeListElement;
class UButton;
class UTextBlock;
class UWidgetSwitcher;

UENUM(BlueprintType)
enum class ETradeState : uint8
{
	NORMAL,
	LOCK,
	NONE,
};

UCLASS()
class RLR_API UTradeUI : public USubUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void Init() override;
	virtual void RefreshUI() override;
	virtual void OpenUI() override;
	virtual void Clear() override;
	virtual void CloseUI() override;

public:

	UFUNCTION()
	void SendAddTradeItemBySelf(const FItemData& NewTradeItem, int32 Quantity = 1);
	void SendAddTradeCurrencyBySelf(int32 Amount);
	void SendRemoveTradeItemBySelf(const FItemData& NewTradeItem, int32 Quantity = 1);

	void HandleAddTradeItemByTarget(const FItemData& NewTradeItem);
	void HandleAddTradeItemBySelf(const FItemData& NewTradeItem);
	void HandleUpdateTradeCurrencyBySelf(int32 Amount);
	void HandleUpdateCurrencyByTarget(int32 Amount);

	void HandleRemoveTradeItemByTarget(int32 ItemID);
	void HandleRemoveTradeItemBySelf(int32 ItemID);

	void HandleLockTradeBySelf();
	void HandleUnLockTradeBySelf();
	void HandleLockTradeByTarget();
	void HandleUnLockTradeByTarget();

	void SendLockTrade();
	void SendUnLockTrade();
	void SendConfirmTrade();
	void SendCancelTradePacket();					//내가 거래 취소
	void HandleTradeCanceledByTarget();//상대방이 취소했을 때 핸들.

public:

	UFUNCTION()
	void		OnClickedAddGoldButton();

	void		SetMyTradeState(ETradeState TradeType);
	ETradeState GetMyTradeState(){return MyTradeState;}

	void		SetTargetTradeState(ETradeState TradeType);
	ETradeState GetTargetTradeState() { return TargetTradeState; }

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
	TObjectPtr<UTextBlock> MyGoldText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> TargetGoldText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> OfferAndConfirmWidgetSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> OfferButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> ConfirmButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> CancelButton;

private:

	ETradeState TargetTradeState = ETradeState::NORMAL;
	ETradeState MyTradeState = ETradeState::NORMAL;

};
