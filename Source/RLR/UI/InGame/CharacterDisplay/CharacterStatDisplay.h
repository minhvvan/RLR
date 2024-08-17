// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "CharacterStatDisplay.generated.h"

class UActionSystemComponent;
class UOverlay;
struct FAbnormalMark;

UCLASS()
class RLR_API UCharacterStatDisplay : public UBaseUI
{
	GENERATED_BODY()
	
public:
	UCharacterStatDisplay(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UTextBlock> Name;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UOverlay> OverlayAbnormalText;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> AbnormalTextClass;

public:
	virtual void NativeConstruct() override;
	virtual void SetActionSystemComponent(AActor* Owner) override;

	void ShowAbnormal(const FString Text);
};
