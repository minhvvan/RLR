// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/UtilStructs.h"
#include "PostTabWidget.generated.h"

class UButton;
class UTextBlock;
class UScrollBox;
class USizeBox;
class UCheckBox;
class UWidgetSwitcher;
class UMultiLineEditableText;
class UGridPanel;
class UVerticalBox;
class UPostButtonUI;
class AGameManager;


UCLASS()
class RLR_API UPostTabWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnSelectAllCheckBoxChanged(bool bIsChecked);

    UFUNCTION(BlueprintCallable)
    void UpdatePostList(const TArray<FPostResult>& Posts, bool bIsSent);

    UFUNCTION(BlueprintCallable)
    void RemovePost(FPostResult Post);

    UFUNCTION()
    void OnAcceptButtonClicked();

    UFUNCTION(BlueprintCallable)
    void OnRemoveButtonClicked();

    UFUNCTION()
    void OnReceiveAllAttachmentsButtonClicked(); 

    UFUNCTION()
    void OnRemoveSelectedButtonClicked();

    UFUNCTION()
    void SwitchPostPage();
    UFUNCTION()
    void SwitchPrevPage();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post")
    bool bIsSentTab;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* SelectAllCheckBox;

    UPROPERTY(meta = (BindWidget))
    USizeBox* PostList_SizeBox;

    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PostVerticalBox;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* IdText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* PostTitleText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TotalMoney;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* PostContentText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ReadStatus;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
    UGridPanel* PostSlotGridPanel;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UPostButtonUI> PostButtonUIClass;

    /* 선택한 우편 내부에서 첨부물 받기 버튼*/
    UPROPERTY(meta = (BindWidgetOptional))
    UButton* AcceptAllButton;
    /* 선택한 우편 내부에서 해당 우편 삭제 버튼*/
    UPROPERTY(meta = (BindWidget))
    UButton* RemovePostButton;
    
    /* 체크박스로 선택한 우편 첨부물 모두 받기 버튼 */
    UPROPERTY(meta = (BindWidgetOptional))
    UButton* ReceiveAttachmentsButton;
    /* 체크박스로 선택한 우편 첨부물 모두 삭제 버튼 */
    UPROPERTY(meta = (BindWidget))
    UButton* RemoveSelectedButton;

    UPROPERTY(meta = (BindWidget))
    UButton* PrevPageButton;

    UPROPERTY(meta = (BindWidget))
    UButton* PostPageButton;

    UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* PageSwitcher;

    // 한 페이지에 표시할 버튼 최대 수
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    int32 MaxButtonsPerPage = 10;  

    // 현재 사용 중인 VerticalBox
    UVerticalBox* CurrentVerticalBox;


    UPROPERTY()
    TMap<FString, UPostButtonUI*> PostButtons;

    UPROPERTY()
    FPostResult SelectedPost;

    UPROPERTY()
    UPostButtonUI* SelectedPostButton;

private:
    void ClearPostList();

    // 새 페이지 생성
    void CreateNewPage();
    void AddPostButton(const FPostResult& Post, bool bIsSent);
    void UpdatePostDetails(const FPostResult& Post);

    UFUNCTION()
    void OnPostButtonClicked(const FPostResult& ClickedPost, UPostButtonUI* PostButtonUI);

public:
    void SetIsSentTab(bool bInIsSentTab) { bIsSentTab = bInIsSentTab; };
};