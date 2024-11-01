// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GuildEntryUI.generated.h"

class UGuildCreationUI;
class UWidgetSwitcher;
class UButton;

/**
 * 길드에 속해있지 않을 때
 */
UCLASS()
class RLR_API UGuildEntryUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

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

	/* 길드 생성, 길드 신청(추가할 예정) */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UGuildCreationUI> GuildCreationUI;
};
