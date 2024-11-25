// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "Structs/UtilStructs.h"
#include "PostOverlayUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPostUIEnd);

class UButton;
class UWidgetSwitcher;
class UPostReceivedTabWidget;
class UPostWriteTabWidget;
class UPostSentTabWidget;
class UPostItemSlot;
class UPostTabWidget;
class UConfirmMessageBox;

UENUM()
enum class EPostAction : uint8
{
    ClearWriteTab,
    RemoveSelectedPosts,
    RemoveSinglePost
};

UCLASS()
class RLR_API UPostOverlayUI : public USubUI
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void Init();

	UFUNCTION(BlueprintCallable)
	virtual void RefreshUI() override;

    UFUNCTION()
    void CreatePostSlots();

    void CreatePostSlotWriteTab(int32 SlotCount);
    void CreatePostSlotSentTab(int32 SlotCount);

    UFUNCTION()
    void OnReceivedPostButtonClicked();

    UFUNCTION()
    void OnSentPostButtonClicked();

    UFUNCTION()
    void OnWritePostButtonClicked();

    UFUNCTION(BlueprintCallable)
	void SetMaxSlotCount(int32 Count);

	UFUNCTION(BlueprintCallable)
	int32 GetMaxSlotCount(){return MaxPostSlotCount;};

    void HandlePostAction(UConfirmMessageBox* MessageBox, EPostAction ActionType);
    void ShowConfirmMessage(const FText& MessageText, FName ConfirmFunctionName, FName CancelFunctionName);

    UFUNCTION()
	void OnClickedAcceptButton(UConfirmMessageBox* MessageBox);
	UFUNCTION()
	void OnClickedCancelButton(UConfirmMessageBox* MessageBox);

    UFUNCTION()
    void ConfirmDeletePosts();
    UFUNCTION()
    void ConfirmDeletePost();

    UFUNCTION()
    void OnClickedDeletePostsConfirmButton(UConfirmMessageBox* MessageBox);
    UFUNCTION()
    void OnClickedDeletePostConfirmButton(UConfirmMessageBox* MessageBox);

    UFUNCTION()
    void OnReplyButtonClicked(FText SIdText);

    void UpdatePostWidget();

    void SetSentPostData(const TArray<FPostResult>& NewPostResult);
    void SetRecvPostData(const TArray<FPostResult>& NewPostResult);

    void OnPostGetRequestComplete();
    void OnPostSentRequestComplete();

    bool GetWritingPostStatus();
    void ManageWritingPost();

    FOnPostUIEnd OnPostUIEnd;
public:

	/* Bind Widget */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UPostWriteTabWidget> PostWriteTabWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UPostTabWidget> PostReceivedTabWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UPostTabWidget> PostSentTabWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UConfirmMessageBox> ConfirmMessageBox;

    UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* PostWidgetSwitcher;

    UPROPERTY(meta = (BindWidget))
    UButton* ReceivedPostButton;

    UPROPERTY(meta = (BindWidget))
    UButton* SentPostButton;

    UPROPERTY(meta = (BindWidget))
    UButton* WritePostButton;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxPostSlotCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UPostItemSlot>> PostSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPostResult> SentPostData;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPostResult> RecvPostData;

    FCriticalSection PostDataMutex;

private:
    int32 ChangeTabIndex;
};
