// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerGuildUI.generated.h"

class UGuildReportAndExitUI;
class UGuildManagementUI;
class UGuildMemberUI;
class UGuildMainUI;
class UWidgetSwitcher;
class UButton;

/**
 * 길드에 속해 있을 때
 */
UCLASS()
class RLR_API UPlayerGuildUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SwitchToGuildInfo();

	UFUNCTION()
	void SwitchToGuildMember();

	UFUNCTION()
	void SwitchToGuildManagement();

	UFUNCTION()
	void CloseGuildWidget();
	
	UFUNCTION()
	void OpenGuildReportUI();

	void SetGuildOpenState(bool bOpenState);

public:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	UButton* GuildMainButton;

	UPROPERTY(meta = (BindWidget))
	UButton* GuildQuestButton;

	UPROPERTY(meta = (BindWidget))
	UButton* GuildShopButton;

	UPROPERTY(meta = (BindWidget))
	UButton* GuildActivityLogButton;

	UPROPERTY(meta = (BindWidget))
	UButton* GuildMemberButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ManageGuildButton;

	UPROPERTY(meta = (BindWidget))
	UButton* GuildReportButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	/* 길드 정보, 길드 멤버목록, 길드 관리 */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UGuildMainUI> GuildMainUI;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UGuildMemberUI> GuildMemberUI;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UGuildManagementUI> GuildManagementUI;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UGuildReportAndExitUI> GuildReportAndExitUI;

private:
	bool bOpenGuildReport;
};
