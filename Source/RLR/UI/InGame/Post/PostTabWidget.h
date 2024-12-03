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
class UPostDetailUI;
class UPostOverlayUI;
class AGameManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRemovePostsButtonClicked);

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

    UFUNCTION()
    void OpenRemovePostsConfirmBox();
    
    /* 우편 삭제 관련 */
    FOnRemovePostsButtonClicked OnRemovePostsButtonClicked;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post")
    bool bIsSentTab;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* SelectAllCheckBox;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UPostButtonUI> PostButtonUIClass;
    
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
    UTextBlock* CurrentPageText;
    
    UPROPERTY(meta = (BindWidget))
    UTextBlock* PostCountText;

    UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* PageSwitcher;

    // 한 페이지에 표시할 버튼 최대 수 = 5
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    int32 MaxButtonsPerPage = 7;  

    // 현재 사용 중인 VerticalBox
    UVerticalBox* NewPage;
    TArray<UVerticalBox*> VerticalBoxes;

    UPROPERTY()
    TMap<FString, UPostButtonUI*> PostButtons;

    UPROPERTY()
    FPostResult SelectedPost;

    UPROPERTY()
    UPostButtonUI* SelectedPostButton;

    TObjectPtr<UPostOverlayUI> PostOverlayUI;
private:
    void ClearPostList();

    // 새 페이지 생성
    void CreateNewPage();
    void AddPostButton(const FPostResult& Post, bool bIsSent);
    void UpdatePostDetails(const FPostResult& Post);
    void RemoveOldestPost();

    UFUNCTION()
    void OnPostButtonClicked(const FPostResult& ClickedPost, UPostButtonUI* PostButtonUI);

public:
    void SetIsSentTab(bool bInIsSentTab) { bIsSentTab = bInIsSentTab; };

private:
    int32 postCount;
};