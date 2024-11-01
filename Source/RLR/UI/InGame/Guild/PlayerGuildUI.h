// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerGuildUI.generated.h"

class UGuildManagementUI;
class UGuildMemberUI;
class UGuildInfoUI;
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

public:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	UButton* GuildInfoButton;

	UPROPERTY(meta = (BindWidget))
	UButton* GuildMemberButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ManageGuildButton;

	/* 길드 정보, 길드 멤버목록, 길드 관리 */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UGuildInfoUI> GuildInfoUI;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UGuildMemberUI> GuildMemberUI;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UGuildManagementUI> GuildManagementUI;
};
