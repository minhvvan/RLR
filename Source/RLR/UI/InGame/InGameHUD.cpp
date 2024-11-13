// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/InGameHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/InGame/InGameMainUI.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "RLR.h"

AInGameHUD::AInGameHUD()
{
}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (GameInstance)
	{
		UUIManager* UIManager = GameInstance->GetUIManager();
		if (!UIManager) return;

		UInGameMainUI* InGameUI = UIManager->GetPage<UInGameMainUI>(RLRTAG.Page_InGame);
		if (!InGameUI) return;

		ARLRPlayerCharacter* playerCharacter = Cast<ARLRPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (!playerCharacter) return;

		InGameUI->SetActionSystemComponent(playerCharacter);
	}
}
