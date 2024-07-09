// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "InGameMenuTab.generated.h"

/**
 * 
 */


 class UInGameMenuTabList;
 class UInGameMenuUI;
 class UMenuAnchor;
 class UScrollBox;
 class UTextBlock;
 class UButton;

 /*
 
	InGameMenuUI 안에 들어 있는 탭.
	
	탭이 포커스를 잃을 때는 , 저절로 닫히게 해준다.

 */


UCLASS()
class RLR_API UInGameMenuTab : public UBaseUI
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetTabText(FText Text);

	UFUNCTION(BlueprintCallable)
	void OnTabButtonClicked();

	UFUNCTION(BlueprintCallable)
	void ToggleTabList();

public:


	/*
	* 
		Bind

	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> TabButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock>TabTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UInGameMenuTabList> InGameMenuTabList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInGameMenuUI> InGameMenuUI;

};
