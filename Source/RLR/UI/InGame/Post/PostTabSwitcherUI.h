// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/CommunicationStructs.h"
#include "PostTabSwitcherUI.generated.h"

class UButton;
class UListView;
class UWidgetSwitcher;

UCLASS()
class RLR_API UPostTabSwitcherUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* PostContentSwitcher;

    UPROPERTY(meta = (BindWidget))
    UButton* ReceivedPostButton;

    UPROPERTY(meta = (BindWidget))
    UButton* SentPostButton;

    UPROPERTY(meta = (BindWidget))
    UButton* WritePostButton;

    // 새로 추가된 리스트뷰, 각각 클래스를 새로 만들어서 멤버변수로 추가하기
    //UPROPERTY(meta = (BindWidget))
    //UListView* ReceivedPostListView;

    //UPROPERTY(meta = (BindWidget))
    //UListView* SentPostListView;

public:
    UFUNCTION()
    void OnReceivedPostButtonClicked();

    UFUNCTION()
    void OnSentPostButtonClicked();

    UFUNCTION()
    void OnWritePostButtonClicked();

    UFUNCTION()
    void SwitchToTab(int32 TabIndex);

    //void UpdateReceivedPostList(const TArray<FPost>& ReceivedPosts);
    //void UpdateSentPostList(const TArray<FPost>& SentPosts);


};
