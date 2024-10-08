// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/UtilStructs.h"
#include "PostAlertUI.generated.h"

class UEditableText;
class UMultiLineEditableText;
class UGridPanel;
class UButton;
class USizeBox;

UCLASS()
class RLR_API UPostAlertUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable)
    void UpdatePost(const FPostResult& Post);

    UFUNCTION(BlueprintCallable)
    void UpdatePostItemSlot(const FPostResult& Post);

    UFUNCTION()
    void OnCloseButtonClicked();

    UFUNCTION()
    void OnAcceptButtonClicked();

    UFUNCTION()
    void OnRemovePostButtonClicked();

public:
	UPROPERTY(meta = (BindWidget))
    UEditableText* IdText;

    UPROPERTY(meta = (BindWidget))
    UEditableText* PostTitleText;

    UPROPERTY(meta = (BindWidget))
    UEditableText* TotalMoney;

    UPROPERTY(meta = (BindWidget))
    UMultiLineEditableText* PostContentText;

    UPROPERTY(meta = (BindWidget))
    UGridPanel* PostSlotGridPanel;

    UPROPERTY(meta = (BindWidget))
    UButton* RemovePostButton;

    UPROPERTY(meta = (BindWidget))
    UButton* AcceptAllButton;

    UPROPERTY(meta = (BindWidget))
    UButton* CloseButton;

    UPROPERTY()
    FPostResult PostData;
};
