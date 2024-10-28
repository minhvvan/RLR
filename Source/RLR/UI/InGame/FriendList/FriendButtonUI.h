// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendButtonUI.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFriendButtonClickDelegate, int, UFriendButtonUI*);
DECLARE_DELEGATE_TwoParams(FOnFriendRightClickedSignature, FVector2D, UFriendButtonUI*);

class UButton;
class UTextBlock;

/*
    친구가 추가되면 동적으로 생성되는 버튼
*/

UCLASS()
class RLR_API UFriendButtonUI : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    void SetFriendInfo(int NewFriendSeq, FString NewFriendName);
    FString GetFriendName();
    UFUNCTION()
    int32 GetFriendSeq() const { return FriendSeq; }

    void SetGroupSeq(int32 NewGroupSeq) {GroupSeq = NewGroupSeq;};
    int32 GetGroupSeq() {return GroupSeq;};

    UFUNCTION()
    void OnFriendButtonClicked();

    void SetButtonState(bool isPressed);

    FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

    FOnFriendButtonClickDelegate OnFriendRequestButtonClick;
    FOnFriendRightClickedSignature OnFriendRightClicked;
public:
    /* TODO : 친구목록의 플레이어 정보 더 추가하기 */
    UPROPERTY(meta = (BindWidget))
    UButton* FriendButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* FriendNameText;

private:
    int FriendSeq;
    FString FriendName;
    int GroupSeq;
};
