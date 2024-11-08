// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GuildReportAndExitUI.generated.h"

class UButton;
class UTextBlock;
class UEditableText;
class UMultiLineEditableText;
class UPlayerGuildUI;

/**
 * 길드 신고 및 탈퇴를 할 수 있는 UI
 */
UCLASS()
class RLR_API UGuildReportAndExitUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnReportTitleChanged(const FText& Text);
	UFUNCTION()
	void OnReportContentChanged(const FText& Text);
	UFUNCTION()
	void OnReportButtonClicked();
	UFUNCTION()
	void OnCloseButtonClicked();

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GuildNameText;

	/* TODO : 신고 유형 (DropDown 형식?) */

	UPROPERTY(meta = (BindWidget))
	UEditableText* ReportTitleText;

	UPROPERTY(meta = (BindWidget))
	UMultiLineEditableText* ReportContentText;

	UPROPERTY(meta = (BindWidget))
	UButton* ReportButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UPROPERTY()
    UPlayerGuildUI* PlayerGuildUI;

private:
	int32 TitleMaxCharacter = 25;
	int32 ContentMaxCharacter = 300;
};
