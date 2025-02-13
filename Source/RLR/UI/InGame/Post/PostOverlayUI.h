// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "Structs/UtilStructs.h"
#include "PostOverlayUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPostUIEnd);

class UButton;
class UWidgetSwitcher;
class UCanvasPanel;
class UPostReceivedTabWidget;
class UPostWriteTabWidget;
class UPostSentTabWidget;
class UPostItemSlot;
class UPostDetailUI;
class UPostTabWidget;
class UConfirmMessageBox;

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
    void OnReceivedPostButtonClicked();

    UFUNCTION()
    void OnSentPostButtonClicked();

    UFUNCTION()
    void OnWritePostButtonClicked();

    UFUNCTION(BlueprintCallable)
	void SetMaxSlotCount(int32 Count);

	UFUNCTION(BlueprintCallable)
	int32 GetMaxSlotCount(){return MaxPostSlotCount;};

    void ShowConfirmMessage(const FText& MessageText, FName ConfirmFunctionName, FName CancelFunctionName);

    UFUNCTION()
	void OnClickedAcceptButton(UConfirmMessageBox* MessageBox);
	UFUNCTION()
	void OnClickedCancelButton(UConfirmMessageBox* MessageBox);

    UFUNCTION()
    void ConfirmDeletePosts();

    UFUNCTION()
    void OnClickedDeletePostsConfirmButton(UConfirmMessageBox* MessageBox);

    UFUNCTION()
    void OnReplyButtonClicked(FText SIdText);

    void UpdatePostWidget();
    void UpdatePostWriteTabSlot();

    void SetSentPostData(const TArray<FPostResult>& NewPostResult);
    void SetRecvPostData(const TArray<FPostResult>& NewPostResult);

    void OnPostGetRequestComplete();
    void OnPostSentRequestComplete();

    bool GetWritingPostStatus();
    void ManageWritingPost();

    bool CanSendItem();
    UPanelSlot* AddChild(UUserWidget* Child);

    void SetButtonsEnable();

    FOnPostUIEnd OnPostUIEnd;
public:

	/* Bind Widget */
    UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Canvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UPostWriteTabWidget> PostWriteTabWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UPostTabWidget> PostReceivedTabWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UPostTabWidget> PostSentTabWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UConfirmMessageBox> ConfirmMessageBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UPostDetailUI> PostDetailUI;

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
    FText DeletePostsConfirmText;
    FText WritingPostWarningText;
};
