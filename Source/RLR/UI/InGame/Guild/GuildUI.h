// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "GuildUI.generated.h"

class UWidgetSwitcher;

/**
 * 
 */
UCLASS()
class RLR_API UGuildUI : public USubUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void Init();

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	bool IsInUI(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);


	UFUNCTION(BlueprintCallable)
	virtual void RefreshUI();

	UFUNCTION()
	void OpenApplyGuildUI();

	UFUNCTION()
	void OpenCreateGuildUI();

public:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	UButton* CreateGuildButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ApplyGuildButton;
};
