// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/InGameHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/InGame/InGameMainUI.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AInGameHUD::AInGameHUD()
{
}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	AMyPlayerController* PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->InitializeChatUI(PC->GetChatClient());
	}
}
