// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GuildManagementUI.generated.h"

class UGuildIconImage;
class UWidgetSwitcher;
class UEditableText;
class UScrollBox;
class UGridPanel;
class UBorder;
class UButton;
class UImage;

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
	void ChangeInfoButtonClicked();

	//UFUNCTION()
	//void ChangeImageButtonClicked();
	
	UFUNCTION()
	void QuitGuldButtonClicked();

	UFUNCTION()
	void DeleteGuildButtonClicked();

UFUNCTION()
	void OnIconSelected(UGuildIconImage* ClickedGuildIconImage);
	
	UFUNCTION()
	void ConfirmButtonClicked();

	UFUNCTION()
	void CancelButtonClicked();

	UFUNCTION()
	void CloseChangeGuildInfoButtonClicked();

	void EnableButtons(bool bEnabled);
	UTexture2D* LoadTextureFromPath(const FString& Path);

public:
	/* TODO : 길드 가입 신청한 플레이어 버튼 생성(승인 버튼 포함) */
	UPROPERTY(meta = (BindWidget))
	UScrollBox* JoinGuildWaitingListScrollBox;
	
	/* 길드 관리 탭  - 길드 이름 변경, 길드 초대, 길드 탈퇴 */
	UPROPERTY(meta = (BindWidget))
	UButton* ChangeGuildInfoButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ExpandGuildButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* GrantPermissionButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* UserRankUpgradeButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* GuildRewardPayoutButton;

	UPROPERTY(meta = (BindWidget))
	UButton* DeleteGuildButton;

	/* ChangeGuildInfoButton 클릭 시 뜨는 위젯들 */
	UPROPERTY(meta = (BindWidget))
	UButton* CloseChangeGuildInfoButton;

	UPROPERTY(meta = (BindWidget))
	UBorder* ChangeGuildInfoBorder;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	UEditableText* NewGuildNameText;
	
	UPROPERTY(meta = (BindWidget))
	UImage* NewGuildImage;

	UPROPERTY(meta = (Bindwidget))
	UGridPanel* IconGridPanel;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGuildIconImage> GuildIconImageClass;

private:
	bool bIsChangeGuildNameOpen;
	UTexture2D* SelectedIconTexture;
	UGuildIconImage* LastClickedImage = nullptr;
};
