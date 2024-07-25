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
	UStatSetPlayer* statSet = GetStatSet();
	if (!statSet) return;

	FStatChangeSpec<FTotalStatus> spec;
	spec.ChangedStat = statSet->GetTotalStatusStat();
	spec.NewValue = NewTotalStatus;

	statSet->ApplyChangeStat<FTotalStatus>(spec);
}

void UPlayerManager::UpdatePlayerSetStatus(const FSetStatus& NewSetStatus)
{
	UStatSetPlayer* statSet = GetStatSet();
	if (!statSet) return;

	FStatChangeSpec<FSetStatus> spec;
	spec.ChangedStat = statSet->GetSetStatusStat();
	spec.NewValue = NewSetStatus;

	statSet->ApplyChangeStat<FSetStatus>(spec);
}

void UPlayerManager::UpdatePlayerExp(float NewExp)
{
	UStatSetPlayer* statSet = GetStatSet();
	if (!statSet) return;

	FStatChangeSpec spec;
	spec.ChangedStat = statSet->GetExpStat();
	spec.NewValue = NewExp;

	statSet->ApplyChangeStat(spec);
}

UStatSetPlayer* UPlayerManager::GetStatSet()
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
		if (!ASC) return nullptr;

		UStatSetPlayer* statSet = ASC->GetStatSet<UStatSetPlayer>();
		if (!statSet) return nullptr;

		return statSet;
	}

	return nullptr;
}
