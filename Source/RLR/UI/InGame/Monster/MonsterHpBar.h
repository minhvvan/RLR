// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "MonsterHpBar.generated.h"

class UActionSystemComponent;

UCLASS()
class RLR_API UMonsterHpBar : public UBaseUI
{
	GENERATED_BODY()
	
public:
	UMonsterHpBar(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UTextBlock> Name;

public:
	virtual void NativeConstruct() override;
	void SetActionSystemComponent(AActor* Owner) override;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	void UpdateHp();

	UFUNCTION()
	void OnHpChanged();

protected:
	bool bCompletedChange;
	int MaxHp;
	int CurrentHp;
	int TargetHp;
};
