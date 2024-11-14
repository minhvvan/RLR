// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "AbnormalDisplay.generated.h"

struct FAbnormalMark;
class UOverlay;

UCLASS()
class RLR_API UAbnormalDisplay : public UBaseUI
{
	GENERATED_BODY()

public:
	UAbnormalDisplay(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UOverlay> OverlayAbnormalText;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> AbnormalTextClass;
	
public:
	virtual void NativeConstruct() override;
	void SetActionSystemComponent(AActor* Owner) override;

	void ShowAbnormal(const FString Text);
};
