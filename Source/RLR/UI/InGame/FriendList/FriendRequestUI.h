// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "FriendRequestUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCloseRequestUISignature, bool, bIsClosed);

class UFriendButtonUI;
class UEditableText;
class UScrollBox;
class UButton;

UCLASS()
class RLR_API UFriendRequestUI : public USubUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnFriendNameTextChanged(const FText& Text);

	UFUNCTION()
	void OnSendRequestClicked();	
	UFUNCTION()
	void OnCancelClicked();

	bool CheckIfFriendExists(const FString& FriendName);
	void AddFriendButtonIfExists(const FString& FriendName);
	void AddFriendButton(const FString& FriendName);

public:
	/* 친구 요청 관련 */
	UPROPERTY(meta = (BindWidget))
	UEditableText* FriendNameText;
	
	UPROPERTY(meta = (BindWidget))
	UScrollBox* FriendScrollBox;

	UPROPERTY(meta = (BindWidget))
	UButton* SendRequestButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelRequestButton;

	UPROPERTY()
    TMap<int, UFriendButtonUI*> FriendButtons;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UFriendButtonUI> UFriendButtonUIClass;

	FOnCloseRequestUISignature OnCloseRequestUISignature;

	UPROPERTY()
	int FriendSeq;
};
