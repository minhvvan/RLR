// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/InGame/CharacterDisplay/CharacterStatDisplay.h"
#include "MonsterStatDisplay.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UMonsterStatDisplay : public UCharacterStatDisplay
{
	GENERATED_BODY()
	
public:
	UMonsterStatDisplay(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UProgressBar> HpProgressBar;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	void UpdateHp();

	UFUNCTION()
	void OnHpChanged();

public:
	void SetActionSystemComponent(AActor* Owner) override;

protected:
	bool bCompletedChange;
	int MaxHp;
	int CurrentHp;
	int TargetHp;
};
