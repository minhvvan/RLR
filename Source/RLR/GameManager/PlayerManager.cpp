// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/PlayerManager.h"
#include "Kismet/GameplayStatics.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"

UPlayerManager::UPlayerManager()
{
}

void UPlayerManager::SetPlayerData(FUserCharacter PlayerData)
{
	if (UWorld* world = GetWorld())
	{
		if (!PlayerCharacter)
		{
			ARLRPlayerCharacter* player = Cast<ARLRPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(world, 0));
			if (player)
			{
				PlayerCharacter = player;
			}
		}

		PlayerCharacter->SetStat(PlayerData);
	}
}

void UPlayerManager::UpdatePlayerTotalStatus(const FTotalStatus& NewTotalStatus)
{
	if (UWorld* world = GetWorld())
	{
		if (!PlayerCharacter)
		{
			ARLRPlayerCharacter* player = Cast<ARLRPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(world, 0));
			if (player)
			{
				PlayerCharacter = player;
			}
		}

		UActionSystemComponent* ASC = PlayerCharacter->GetActionSystemComponent();
		if (!ASC) return;

		UStatSetPlayer* statSet = ASC->GetStatSet<UStatSetPlayer>();
		if (!statSet) return;

		FStatChangeSpec<FTotalStatus> spec;
		spec.ChangedStat = statSet->GetTotalStatusStat();
		spec.NewValue = NewTotalStatus;

		statSet->ApplyChangeStat(spec);
	}
}
