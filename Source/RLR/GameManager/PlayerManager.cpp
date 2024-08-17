// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/PlayerManager.h"
#include "GameManager.h"
#include "GameManager/NetworkManager.h"

#include "Kismet/GameplayStatics.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"

#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"

#include "RLR.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

UPlayerManager::UPlayerManager()
{

}

ARLRPlayerCharacter* UPlayerManager::GetPlayerCharacter()
{
	if(IsValid(PlayerCharacter) == false)
	{ 
		DEBUG_LOG("GetPlayerCharacter Error. Player Character Is Null");
		return nullptr;
	}

	return PlayerCharacter;
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

int32 UPlayerManager::GetPlayerSeq()
{
	if (IsValid(PlayerCharacter) == false)
	{
		DEBUG_LOG("GetPlayerSeq Error. Player Character Is Null");
		return 1;
	}

	return PlayerCharacter->GetPlayerSeq();
}

int32 UPlayerManager::GetUserSeq()
{
	/*
		아직 미구현
	*/

	return 1;
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

void UPlayerManager::UpdateTalent(const FTalent& NewTalent)
{
	UStatSetPlayer* statSet = GetStatSet();
	if (!statSet) return;

	FStatChangeSpec<FTalent> spec;
	spec.ChangedStat = statSet->GetTalentStat();
	spec.NewValue = NewTalent;

	statSet->ApplyChangeStat(spec);
}

void UPlayerManager::ApplyAbnormal(const FAbnormal2& Abnormal)
{
	UStatSetPlayer* statSet = GetStatSet();
	if (!statSet) return;

	statSet->ApplyAbnormal(Abnormal);
}

bool UPlayerManager::RequestMove(const FMoveResult& MoveResult)
{
	return GameInstance->GetNetworkManager()->SendMovePacket(MoveResult.UserSeq, MoveResult.TargetTransform, MoveResult.MapId, MoveResult.ChannelId);
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

bool UPlayerManager::RequestTalent(int TalentOrder)
{
	//TODO: TalentOrder에 맞는 재능 변경 요청

	return false;
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
