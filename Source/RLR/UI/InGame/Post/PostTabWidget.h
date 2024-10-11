// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/UtilStructs.h"
#include "PostTabWidget.generated.h"

class UButton;
class UTextBlock;
class UScrollBox;
class UEditableText;
class UMultiLineEditableText;
class UGridPanel;
class UPostButtonUI;
class AGameManager;


UCLASS()
class RLR_API UPostTabWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable)
    void UpdatePostList(const TArray<FPostResult>& Posts, bool bIsSent);

    UFUNCTION(BlueprintCallable)
    void RemovePost(FPostResult Post);

    UFUNCTION()
    void OnAcceptButtonClicked();

    UFUNCTION(BlueprintCallable)
    void OnRemoveButtonClicked();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post")
    bool bIsSentTab;

    UPROPERTY(meta = (BindWidget))
    UScrollBox* PostScrollBox;

    UPROPERTY(meta = (BindWidget))
    UEditableText* IdText;

    UPROPERTY(meta = (BindWidget))
    UEditableText* PostTitleText;

    UPROPERTY(meta = (BindWidget))
    UEditableText* TotalMoney;

    UPROPERTY(meta = (BindWidget))
    UMultiLineEditableText* PostContentText;

    UPROPERTY(meta = (BindWidget))
    UEditableText* ReadStatus;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
    UGridPanel* PostSlotGridPanel;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UPostButtonUI> PostButtonUIClass;

    UPROPERTY(meta = (BindWidget))
    UButton* AcceptAllButton;

    UPROPERTY(meta = (BindWidget))
    UButton* RemovePostButton;

    UPROPERTY()
    TMap<FString, UPostButtonUI*> PostButtons;

    UPROPERTY()
    FPostResult SelectedPost;

private:
    void ClearPostList();
    void AddPostButton(const FPostResult& Post, bool bIsSent);
    void UpdatePostDetails(const FPostResult& Post);

    UFUNCTION()
    void OnPostButtonClicked(const FPostResult& ClickedPost, UPostButtonUI* PostButtonUI);

public:
    void SetIsSentTab(bool bInIsSentTab) { bIsSentTab = bInIsSentTab; };
};