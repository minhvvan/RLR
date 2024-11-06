// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "GuildUI.generated.h"

class UWidgetSwitcher;
class UPlayerGuildUI;
class UGuildEntryUI;

/**
 *	길드 통합 창
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

public:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	/* Guild에 속해있는지 유무에 따라 Switch Widget */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UGuildEntryUI> GuildEntryUI;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UPlayerGuildUI> PlayerGuildUI;
};
