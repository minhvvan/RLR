// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "Structs/UtilStructs.h"
#include "PostOverlayUI.generated.h"

class UButton;
class UWidgetSwitcher;
class UPostReceivedTabWidget;
class UPostWriteTabWidget;
class UPostSentTabWidget;
class UPostItemSlot;
class UPostTabWidget;


UCLASS()
class RLR_API UPostOverlayUI : public USubUI
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void RefreshUI();

    UFUNCTION()
    void OnReceivedPostButtonClicked();

    UFUNCTION()
    void OnSentPostButtonClicked();

    UFUNCTION()
    void OnWritePostButtonClicked();

    UFUNCTION(BlueprintCallable)
	void	SetMaxSlotCount(int32 Count);
	UFUNCTION(BlueprintCallable)
	int32	GetMaxSlotCount(){return MaxPostSlotCount;};

    void UpdatePostWidget();

    void SetPostResults(const TArray<FPostResult>& NewPostResult);

public:

	/* Bind Widget */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UPostWriteTabWidget> PostWriteTabWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UPostTabWidget> PostReceivedTabWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UPostTabWidget> PostSentTabWidget;

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
	TArray<FPostResult> PostResults;

    FCriticalSection PostDataMutex;
};
