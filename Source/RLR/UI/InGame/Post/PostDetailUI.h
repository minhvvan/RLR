// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "Blueprint/UserWidget.h"
#include "Structs/UtilStructs.h"
#include "PostDetailUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRemoveOnePostButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPostReplyButtonClicked, FText, IdText);

class UButton;
class USizeBox;
class UTextBlock;
class UGridPanel;

/**
 * 우편 상세 정보 UI
 */
UCLASS()
class RLR_API UPostDetailUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;
    void UpdatePostDetails(const FPostResult& Post, bool bIsSentTab);
    void ClearPostSlots();

    void SetTabNameText(FText TabName);

    UFUNCTION()
	void OpenRemovePostConfirmBox();

    UFUNCTION()
	void OnReplyButtonClicked();

    UFUNCTION()
    void OnAcceptButtonClicked();

    /* 우편 개별 삭제 기능 */
    FOnRemoveOnePostButtonClicked OnRemoveOnePostButtonClicked;
    /* 우편 답신 관련 */
    FOnPostReplyButtonClicked OnPostReplyButtonClicked;

public:
	UPROPERTY(meta = (BindWidget))
    USizeBox* PostList_SizeBox;

	UPROPERTY(meta = (BindWidget))
    UTextBlock* IdText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* PostTitleText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TotalMoney;
    
    UPROPERTY(meta = (BindWidget))
    UTextBlock* TabNameText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* PostContentText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ReadStatus;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
    UGridPanel* PostSlotGridPanel;

    /* 선택한 우편 내부에서 첨부물 받기 버튼*/
    UPROPERTY(meta = (BindWidgetOptional))
    UButton* AcceptAllButton;
    /* 선택한 우편 내부에서 해당 우편 삭제 버튼*/
    UPROPERTY(meta = (BindWidget))
    UButton* RemovePostButton;
    /* 우편 답신 버튼 */
    UPROPERTY(meta = (BindWidgetOptional))
    UButton* ReplyButton;

private:
    FPostResult SelectedPost;
    bool bSentTab;
};
