// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "FriendButtonMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFriendInfoClicked, int32, FriendSeq);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveGroupClicked);

class UExistingGroupList;
class UMoveGroupMessageBox;
class UComboBoxString;
class UTextBlock;
class UButton;

/**
 *	친구 목록에서 친구 우클릭시 뜨는 버튼
 */
UCLASS()
class RLR_API UFriendButtonMenu : public USubUI
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OpenFriendInfoUI();

	UFUNCTION()
	void RemoveFriend();

	UFUNCTION()
	void MoveGroup();

	UFUNCTION()
	void SetFriendInfo(int CurrentFriendSeq, FString CurrentFriendName) { friendSeq = CurrentFriendSeq; friendName = CurrentFriendName;};

	UFUNCTION()
	int GetFriendSeq() const { return friendSeq; };

	UFUNCTION()
	void OpenWhisperChat();

	UFUNCTION()
	void SendTradeRequest();

	void SetPlayerNameText(FString CurrentFriendName);
	FOnFriendInfoClicked OnFriendInfoClicked;
	FOnMoveGroupClicked OnMoveGroupClicked;
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNameText;

	UPROPERTY(meta = (BindWidget))
	UButton* PlayerInfoButton;

	UPROPERTY(meta = (BindWidget))
	UButton* InviteButton;

	UPROPERTY(meta = (BindWidget))
	UButton* TradeButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* WhisperChatButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RemoveFriendButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MoveGroupButton;

private:
	int friendSeq;
	FString friendName;
	bool bIsGroupListOpen;
	UMoveGroupMessageBox* MoveGroupMessageBox;
};
