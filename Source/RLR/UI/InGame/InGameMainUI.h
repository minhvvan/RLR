// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMainUI.generated.h"

/**
 * 
 */

 class UChatUI;
 class UInventoryUI;

UCLASS()
class RLR_API UInGameMainUI : public UUserWidget
{
	GENERATED_BODY()



public:

	UFUNCTION(BlueprintCallable)
	UChatUI* GetChatUI(){return ChatUI;}


public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UChatUI> ChatUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UInventoryUI> InventoryUI;
};
