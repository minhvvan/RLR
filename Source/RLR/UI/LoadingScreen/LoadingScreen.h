// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "LoadingScreen.generated.h"

/**
 * 
 */

 class UButton;

UCLASS()
class RLR_API ULoadingScreen : public UBaseUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClickedLoadingScreen();

	void SetNextLevel(FName LevelName){NextLevel = LevelName;}
	void SetLoadingResult(EAsyncLoadingResult::Type Ret){ LoadingResult = Ret;}
	EAsyncLoadingResult::Type GetLoadingResult(){return LoadingResult; }

public:

	/*
		Bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UButton> LoadingScreenButton;


private:

	FName NextLevel = FName("Title");
	EAsyncLoadingResult::Type LoadingResult = EAsyncLoadingResult::Canceled;
	
};
