// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LoadingScreen/LoadingScreen.h"

#include "Components/Button.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void ULoadingScreen::NativeConstruct()
{
	Super::NativeConstruct();

	LoadingScreenButton->OnClicked.AddUniqueDynamic(this, &ULoadingScreen::OnClickedLoadingScreen);
}

void ULoadingScreen::OnClickedLoadingScreen()
{
	//Cancel에서는 아무런 반응도 하지 않는다.
	if(LoadingResult == EAsyncLoadingResult::Canceled)
		return;

	OpenNextLevel();
}

void ULoadingScreen::OpenNextLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), NextLevel);
}

void ULoadingScreen::SetLoadingResult(EAsyncLoadingResult::Type Ret)
{
	LoadingResult = Ret;

	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			// 유효성 검사 추가
			if (IsValid(this) == false)
			{
				DEBUG_MESSAGE;
				return;
			}

			//로딩 성공
			if (LoadingResult == EAsyncLoadingResult::Succeeded)
			{
				
			}
			else
			//로딩 실패
			{
				
			}
			OpenNextLevel();
		});
}
