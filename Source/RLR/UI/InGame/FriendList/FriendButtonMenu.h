// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "FriendButtonMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFriendInfoClicked, int32, FriendSeq);

class UExistingGroupList;
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
	void SetFriendSeq(int CurrentFriendSeq) {FriendSeq = CurrentFriendSeq;};

	UFUNCTION()
	int GetFriendSeq() const {return FriendSeq;};

	FOnFriendInfoClicked OnFriendInfoClicked;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* PlayerInfoButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RemoveFriendButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MoveGroupButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
    TObjectPtr<UExistingGroupList> GroupListUI;

private:
	int FriendSeq;
	bool bIsGroupListOpen;
};
