// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/TradeManager.h"
#include "GameManager/GameManager.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

void UTradeManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UpdateTradeManager.Clear();
}

void UTradeManager::SetTradeState(int32 UserSeq1, int32 UserSeq2)
{
	bool IsUserSeq1 = GameInstance->GetUserSeq() == UserSeq1;
	TradeData.IsUserSeq1 = IsUserSeq1;
	TradeData.UserSeq1 = UserSeq1;
	TradeData.UserSeq2 = UserSeq2;
}

void UTradeManager::UpdateTradeState(const FTradeData& NewTradeState)
{
	TradeData.UserItemList1 = NewTradeState.UserItemList1;
	TradeData.UserItemList2 = NewTradeState.UserItemList2;
	TradeData.UserLockState1 = NewTradeState.UserLockState1;
	TradeData.UserLockState2 = NewTradeState.UserLockState2;
	TradeData.UserMoney1 = NewTradeState.UserMoney1;
	TradeData.UserMoney2 = NewTradeState.UserMoney2;
	OnUpdateTradeManagerDelegate();
}

void UTradeManager::OnUpdateTradeManagerDelegate()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			// 유효성 검사 추가
			if (!IsValid(this))
			{
				DEBUG_MESSAGE;
				return;
			}
			UpdateTradeManager.Broadcast();
		});
}
