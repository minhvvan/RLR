// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "ExpProgressBar.generated.h"

class UProgressBar;

UCLASS()
class RLR_API UExpProgressBar : public UBaseUI
{
	GENERATED_BODY()

public:

	UExpProgressBar(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	void UpdateMaxExp(int32 CurrentLevel);

	void UpdateExp(int32 UpdatedExp);

	int64 GetMaxExp();
	int64 GetCurrentExp();
	void ResetCurrentExp();

public:
	/*
		Bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UProgressBar> ExpProgressBar;


protected:
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UDataTable> MaxExpTable;

	int64 maxExp;
	int64 currentExp;
};
