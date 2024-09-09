// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LoadingScreen/LoadingScreen.h"

#include "Components/Button.h"

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


	UGameplayStatics::OpenLevel(GetWorld(), NextLevel);
}
