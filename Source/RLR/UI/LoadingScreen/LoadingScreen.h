// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "LoadingScreen.generated.h"

/**
 * 
 */

 class UButton;

 /*

	현재는 미사용.
	대신 Async Loading Screen 플러그인 사용.

	참고로 Async Loading Screen은 에디터 뷰 실행이 아니라, 
	Standalon Game 실행 혹은 패키징된 게임에서만 작동함.
 
 */

UCLASS()
class RLR_API ULoadingScreen : public UBaseUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClickedLoadingScreen();
	void OpenNextLevel();

	void SetNextLevel(FName LevelName){NextLevel = LevelName;}
	void SetLoadingResult(EAsyncLoadingResult::Type Ret);
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
