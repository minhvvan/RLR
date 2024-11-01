// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/UtilStructs.h"
#include "FriendRequestTabWidget.generated.h"

class UFriendButtonUI;
class UScrollBox;

/**
 * 친구 요청 탭
 */
UCLASS()
class RLR_API UFriendRequestTabWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	void UpdateFriendRequestTab(TMap<int32, FString> RequestFriendData);

	void AddFriendButton(int32 friendSeq, FString friendName);

private:
	void ClearFriendRequestList();

public:
	UPROPERTY(meta = (BindWidget))
	UScrollBox* FriendRequestScrollBox;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UFriendButtonUI> FriendButtonUIClass;

	TMap<int32, UFriendButtonUI*> FriendButtons;
};
