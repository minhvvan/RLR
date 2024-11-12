// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Structs/CommunicationStructs.h"
#include "TradeManager.generated.h"

/**
	거래창, 경매장 같은 거래 정보를 관리하는 매니저
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateTradeManager);

UCLASS()
class RLR_API UTradeManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection);

public:
	
	//Trade
	void SetTradeState(int32 UserSeq1, int32 UserSeq2);
	void UpdateTradeState(const FTradeData& NewTradeState);
	//

public:

	const	FTradeData& GetTradeData(){return TradeData;};

public:

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FUpdateTradeManager UpdateTradeManager;
	void OnUpdateTradeManagerDelegate();

private:

	UPROPERTY()
	FTradeData TradeData;
};
