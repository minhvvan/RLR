// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GuildManagementUI.generated.h"

class UWidgetSwitcher;
class UButton;

/**
 * 길드 관리 탭
 */
UCLASS()
class RLR_API UGuildManagementUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ChangeNameButtonClicked();
	
	UFUNCTION()
	void InviteButtonClicked();
	
	UFUNCTION()
	void QuitGuldButtonClicked();

	UFUNCTION()
	void DeleteGuildButtonClicked();

public:
	/* 나중에 기획 보고 WidgetSwitcher 필요하다 싶으면 추가 */
	UPROPERTY(meta = (BindWidgetOptional))
	UWidgetSwitcher* WidgetSwitcher;

	/* 길드 관리 탭  - 길드 이름 변경, 길드 초대, 길드 탈퇴 */
	UPROPERTY(meta = (BindWidget))
	UButton* ChangeGuildNameButton;
	UPROPERTY(meta = (BindWidget))
	UButton* InviteToGuildButton;
	UPROPERTY(meta = (BindWidget))
	UButton* QuitGuildButton;

	/* 길드장에게만 노출 */
	UPROPERTY(meta = (BindWidget))
	UButton* DeleteGuildButton;

};
