// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ItemStructs.h"
#include "GuildShopTabWidget.generated.h"

class UGuildPersonalShopUI;
class UGuildShopUI;
class UWidgetSwitcher;
class UButton;
/**
 * 길드 상점 탭 (개인상점, 길드상점)
 */
UCLASS()
class RLR_API UGuildShopTabWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void RefreshUI();

	UFUNCTION()
	void SwitchToPersonalShop();
	UFUNCTION()
	void SwitchToGuildShop();

public:
	/* 길드->개인용품 상점 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGuildPersonalShopUI> GuildPersonalShopUI;
	
	/* 길드->길드용품 상점 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGuildShopUI> GuildShopUI;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PersonalShopButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> GuildShopButton;
};
