// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/PlayerManager.h"
#include "Kismet/GameplayStatics.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "RLR.h"
#include "GameManager.h"
#include "GameManager/NetworkManager.h"

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

void UPlayerManager::UpdatePlayerExp(int32 NewExp)
{
	UStatSetPlayer* statSet = GetStatSet();
	if (!statSet) return;

	FStatChangeSpec<int32> spec;
	spec.ChangedStat = statSet->GetExpStat();
	spec.NewValue = NewExp;

	statSet->ApplyChangeStat(spec);
}

bool UPlayerManager::RequestMove(const FMoveResult& MoveResult)
{
	//TODO: Send to Server
	RLR_LOG(LogRLR, Log, TEXT("MoveTo: %s"), *MoveResult.TargetTransform.ToString());
	GameInstance->GetNetworkManager()->SendMovePacket(MoveResult.UserSeq, MoveResult.TargetTransform, MoveResult.MapId, MoveResult.ChannelId);

	return true;
}

void UPlayerManager::UpdatePlayerTransform(const FVector& NewTransform)
{
	if (!PlayerCharacter)
	{
		ARLRPlayerCharacter* player = Cast<ARLRPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (player)
		{
			PlayerCharacter = player;
		}
	}

	PlayerCharacter->UpdateTransform(NewTransform);
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
