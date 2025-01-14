// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "Structs/UtilStructs.h"
#include "GuildMemberButtonMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerInfoClicked, int32, GuildMemberSeq);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRemoveMemberClicked);

class UTextBlock;
class UButton;
/**
 * 길드 멤버들 Ctrl + 우클릭 시 뜨는 메뉴 (초대하기, 귓속말, 친구신청, 추방하기)
 */
UCLASS()
class RLR_API UGuildMemberButtonMenu : public USubUI
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OpenPlayerInfoUI();

	UFUNCTION()
	void RemoveMember();

	UFUNCTION()
	void SetGuildMember(FGuildRank SelectedGuildMember);

	UFUNCTION()
	void OpenWhisperChat();

	UFUNCTION()
	void InviteParty();

	UFUNCTION()
	void RequestAddFriend();

	void SetPlayerNameText(FString CurrentFriendName);

	FOnPlayerInfoClicked OnPlayerInfoClicked;
	FOnRemoveMemberClicked OnMoveGroupClicked;
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNameText;

	UPROPERTY(meta = (BindWidget))
	UButton* PlayerInfoButton;

	UPROPERTY(meta = (BindWidget))
	UButton* InviteButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* WhisperChatButton;

	UPROPERTY(meta = (BindWidget))
	UButton* AddFriendButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RemoveMemberButton;

private:
	FGuildRank currentGuildMember;
};
