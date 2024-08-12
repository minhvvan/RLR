// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "DialogueUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnd);

class UButton;
class UTextBlock;

UCLASS()
class RLR_API UDialogueUI : public UBaseUI
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	TObjectPtr<UButton> BtnTest;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtTest;

protected:
	virtual void NativeConstruct();

public:
	FOnDialogueEnd OnDialogueEnd;

	//Test
	void SetDialogueData(FString DialogueString);

protected:
	UFUNCTION()
	void OnDialogueEnded();
};
