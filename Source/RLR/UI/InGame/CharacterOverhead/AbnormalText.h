// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "AbnormalText.generated.h"

class UTextBlock;
class UWidgetAnimation;

UCLASS()
class RLR_API UAbnormalText : public UBaseUI
{
	GENERATED_BODY()
	
public:
	UAbnormalText(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> AbnormalText;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> AbnormalTextAnim;

public:
	void SetAbnormalText(const FString Text);
	void PlayWidgetAnim();

	UFUNCTION()
	void OnEndedWidgetAnim();

protected:
	FWidgetAnimationDynamicEvent EndDelegate;
};
