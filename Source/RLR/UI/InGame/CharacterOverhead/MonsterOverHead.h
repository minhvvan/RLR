// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/InGame/CharacterOverhead/CharacterOverHead.h"
#include "MonsterOverHead.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UMonsterOverHead : public UCharacterOverHead
{
	GENERATED_BODY()
	
public:
	UMonsterOverHead(const FObjectInitializer& ObjectInitializer);

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
	float MaxHp;
	float CurrentHp;
	float TargetHp;
};
