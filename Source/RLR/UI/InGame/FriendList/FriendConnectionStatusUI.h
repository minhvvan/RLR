// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendConnectionStatusUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStatusChangedDelegate, FText, StatusText);


class UTextBlock;
class UButton;

/**
 * 플레이어 접속 상태 선택 창
 */
UCLASS()
class RLR_API UFriendConnectionStatusUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetPlayerStatusOnline();
	UFUNCTION()
	void SetPlayerStatusOffline();
	UFUNCTION()
	void SetPlayerStatusAway();

	FOnPlayerStatusChangedDelegate OnPlayerStatusChangedDelegate;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* PlayerStatusOnline;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerStatusOnlineText;

	UPROPERTY(meta = (BindWidget))
	UButton* PlayerStatusOffline;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerStatusOfflineText;

	UPROPERTY(meta = (BindWidget))
	UButton* PlayerStatusAway;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerStatusAwayText;
};
