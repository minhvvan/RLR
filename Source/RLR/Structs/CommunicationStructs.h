// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStructs.h"
#include "Network/Proto/Trade.pb.h"
#include "CommunicationStructs.generated.h"

//거래 정보를 저장하는 구조체
USTRUCT(Atomic, BlueprintType)
struct FTradeData
{
	GENERATED_BODY()

	FTradeData()
	{
		UserSeq1 = -1;
		UserItemList1.Empty();
		UserMoney1 = 0;
		UserLockState1 = 0;
		UserSeq2 = -1;
		UserItemList2.Empty();
		UserMoney2 = 0;
		UserLockState2 = 0;
	}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserSeq1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FItemData> UserItemList1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserMoney1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserLockState1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserSeq2;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FItemData> UserItemList2;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserMoney2;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserLockState2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsUserSeq1 = true;

public:

	void MakeTradeState(Protocol::SC_TradeStateResponse& pkt);
};
