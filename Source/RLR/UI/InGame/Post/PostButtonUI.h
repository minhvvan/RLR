// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/UtilStructs.h"
#include "PostButtonUI.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPostButtonClickDelegate, const FPostResult&, UPostButtonUI*);

class UButton;
class UTextBlock;

UCLASS()
class RLR_API UPostButtonUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void SetPostInfo(const FPostResult& InPost, bool bIsSentPost);
    void SetReceivedPostInfo(const FPostResult& InPost);
    void SetSentPostInfo(const FPostResult& InPost);
    void SetButtonState(bool isPressed);
    FString GetPostTitle();
    FPostResult GetPostInfo() {return PostInfo;};

    virtual void NativeConstruct() override;
    virtual void NativePreConstruct() override;

    FOnPostButtonClickDelegate OnPostButtonClick;

private:
    UPROPERTY(meta = (BindWidget))
    UButton* PostButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* PostNameText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* PostTitleText;

    FPostResult PostInfo;

    UFUNCTION()
    void OnPostButtonClicked();
};
