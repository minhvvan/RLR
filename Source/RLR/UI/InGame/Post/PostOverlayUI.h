// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "PostItemSlot.h"
#include "PostWriteTabWidget.h"
#include "Structs/CommunicationStructs.h"
#include "PostOverlayUI.generated.h"

class UButton;
class UWidgetSwitcher;


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

    //void UpdateReceivedPostList(const TArray<FPost>& ReceivedPosts);
    //void UpdateSentPostList(const TArray<FPost>& SentPosts);

public:

	/* Bind Widget */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UPostWriteTabWidget> PostWriteTabWidget;

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
};
