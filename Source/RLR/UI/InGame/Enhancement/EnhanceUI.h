// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnhanceUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnhanceButtonClicked);

class UEnhanceStatInfo;
class UEnhanceSlot;
class UButton;

/**
 * 강화UI
 */
UCLASS()
class RLR_API UEnhanceUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnEnhanceButtonClicked();

	FOnEnhanceButtonClicked EnhanceButtonClicked;
public:
	UPROPERTY(meta = (BindWidget))
	UButton* EnhanceButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEnhanceStatInfo> BeforeEnhanceStatInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEnhanceStatInfo> AfterEnhanceStatInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEnhanceSlot> EnhanceSlot_Equip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEnhanceSlot> EnhanceSlot_Item1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEnhanceSlot> EnhanceSlot_Item2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEnhanceSlot> EnhanceSlot_Item3;
};
