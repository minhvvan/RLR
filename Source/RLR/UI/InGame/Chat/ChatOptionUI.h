// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "GameOptionData/GameOptionData.h"
#include "ChatOptionUI.generated.h"

/**
 * 
 */

 class UCheckBox;
 class UButton;
 class UChatUI;

UCLASS()
class RLR_API UChatOptionUI : public USubUI
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;
    void Init();
    virtual void OpenUI() override;
    virtual void CloseUI() override;
    
    UFUNCTION(BlueprintCallable)
    void OnFilterChanged(bool bIsChecked);

public:

        //채팅 옵션을 저장해준다.
    UFUNCTION(BlueprintCallable)
    void SaveChatOption();

    //채팅 옵션을 불러온다.
    UFUNCTION(BlueprintCallable)
    void LoadChatOption();

public:

    UFUNCTION(BlueprintCallable)
    void OnConfirmButtonClicked();

     UFUNCTION(BlueprintCallable)
    void OnCancelButtonClicked();

public:

    UPROPERTY(meta = (BindWidget))
    UCheckBox* GeneralCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* WhisperCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* GuildCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* RaidCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* PartyCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CountryCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* ContinentCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* NearbyCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* WorldCheckBox;

    UPROPERTY(meta = (BindWidget))
    UButton* ConfirmButton;

    UPROPERTY(meta = (BindWidget))
    UButton* CancelButton;

public:

     UPROPERTY()
    TMap<EChatType, UCheckBox*> CheckBoxMap;
};
