// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "InGameMenuTabListElement.generated.h"

/**
	InGameMenuTabList의 항목.
	항목에 필요한 기능을 함수 포인터로 넘겨준다.
 */

 class UButton;
 class UTextBlock;
 class UInGameMenuUI;

UCLASS()
class RLR_API UInGameMenuTabListElement : public UBaseUI, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	void SetElementText(FText Text);

	UFUNCTION(BlueprintCallable)
	void OnElementButtonClicked();


public:


	UPROPERTY()
	TObjectPtr<UInGameMenuUI> InGameMenuUI;

	UPROPERTY()
	FText ElementText;

	/*
		Bind
	*/
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> ElementButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> ElementTextBlock;

	/*
	
		Bind Func
	*/

	TFunction<void(UInGameMenuUI*)> ButtonClickedFunc = nullptr;
};
