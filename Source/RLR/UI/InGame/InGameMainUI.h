// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

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
	TObjectPtr<UEquipmentUI> EquipmentUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UItemInformation> ItemInformation;

protected:
	TArray<class USubUI*> UserActionSubUI;

public:
	virtual bool ToggleSubUI(int inputID);
	virtual class USubUI* GetSubUI(int inputID);
};