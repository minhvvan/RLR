// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameManager/RLRStruct.h"
#include "UI/MainUI.h"
#include "InGameMainUI.generated.h"

/**
 * 
 */

 class UChatUI;
 class UInventoryUI;
 class UChatOptionUI;
 class UEquipmentUI;
 class UItemInformation;
 class UCharacterStatusUI;
 class UMinimapUI;
 class UStatusDisplay;
 class UInGameMenuUI;

UCLASS()
class RLR_API UInGameMainUI : public UMainUI
{
	GENERATED_BODY()



public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	UChatUI* GetChatUI(){return ChatUI;}

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UChatUI> ChatUI;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UChatOptionUI> ChatOptionUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UInventoryUI> InventoryUI;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UCharacterStatusUI> CharacterStatusUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UItemInformation> ItemInformation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UMinimapUI> Minimap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UStatusDisplay> StatusDisplayUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UInGameMenuUI> InGameMenuUI;

protected:
	TMap<EUIType, class USubUI*> UserActionSubUI;

public:
	virtual bool ToggleSubUI(int inputID);
	virtual class USubUI* GetSubUI(int inputID);
};