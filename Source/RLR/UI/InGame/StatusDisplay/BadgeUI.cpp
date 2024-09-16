// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/StatusDisplay/BadgeUI.h"
#include "UI/InGame/StatusDisplay/ExpProgressBar.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "GameManager/GameManager.h"
#include "GameManager/PlayerManager.h"
#include "Structs/UtilStructs.h"
#include <Kismet\GameplayStatics.h>

void UBadgeUI::NativeConstruct()
{
	Super::NativeConstruct();
	SetUIType(EUIType::BADGE_UI);
	SetUserLevel();
	// Test Code
	ExpProgressBar->UpdateMaxExp(userLevel);
}

void UBadgeUI::SetUserLevel()
{
	// TODO : Login Logic 
	/*UStatSetPlayer* stat = GameInstance->GetPlayerManager()->GetStatSet();
	userLevel = stat->GetLevel();*/
	// TODO : 임시 
	userLevel = 1;
}

void UBadgeUI::UpdateExp(int32 NewExp)
{
	if (IsLevelUP())
	{
		++userLevel;
		ExpProgressBar->UpdateMaxExp(userLevel);
		ExpProgressBar->ResetCurrentExp();
	}

	ExpProgressBar->UpdateExp(NewExp);
}

bool UBadgeUI::IsLevelUP()
{
	if (ExpProgressBar->GetCurrentExp() >= ExpProgressBar->GetMaxExp())
	{
		return true;
	}
	else
	{
		return false;
	}
}
