// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameManager/RLRStruct.h"
#include "GameManager/GameplayTagManager.h"

#include "UI/MainUI.h"
#include "InGameMainUI.generated.h"

UCLASS()
class RLR_API UInGameMainUI : public UMainUI
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void SetActionSystemComponent(AActor* Owner) override;

protected:
	UFUNCTION()
	void OnChangedTotalStatus();

	UFUNCTION()
	void OnChangedSetStatus();	
	
	UFUNCTION()
	void OnChangedExp();	
	
	UFUNCTION()
	void OnChangedTalent();

	UFUNCTION()
	void OnChangedLevel();

	virtual void OnPageActivated() override;
};