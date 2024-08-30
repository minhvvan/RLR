// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/EffectManager.h"
#include "RLRStruct.h"
#include "NiagaraFunctionLibrary.h"
#include "Structs/UtilStructs.h"
#include "NiagaraSystem.h"

UEffectManager::UEffectManager()
{
	// TODO :  This -> DataManager 
	UDataTable* EffectDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_EffectDataTable.DT_EffectDataTable'"));

	if (EffectDataTable)
	{
		static const FString ContextString(TEXT("Effect Data Context"));
		// TODO : 다형성 맞춰서 제작
		FEffectData* EffectData = EffectDataTable->FindRow<FEffectData>(*FString::FromInt(1), ContextString);

		if (EffectData)
		{
			effect = LoadObject<UNiagaraSystem>(nullptr, *EffectData->EffectPath);
		}
	}
	min = -50.0f;
	max = 50.0f;
}
void UEffectManager::SpawnMonsterHitEffect()
{
	
}

void UEffectManager::SpawnPlayerHitEffect(FVector location)
{
	if (effect)
	{
		FVector result = location;
		result.Z += 10;
		EffectLocation = result;
		RemainingCalls = 3;

		SpawnEffect();

		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			this,
			&UEffectManager::SpawnEffect,
			0.2f,
			true
		);

	}
}

FVector UEffectManager::GetRandomLocation(FVector location)
{
	float RandomX = FMath::RandRange(min, max);
	float RandomY = FMath::RandRange(min, max);
	float RandomZ = FMath::RandRange(min, max);

	return location + FVector(RandomX, RandomY, RandomZ);
}

void UEffectManager::SpawnEffect()
{
	if (RemainingCalls > 0)
	{
		FVector RandomLocation = GetRandomLocation(EffectLocation);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), effect, RandomLocation);

		RemainingCalls--;
	}
	else
	{
		// 호출 횟수를 모두 사용한 후 타이머를 클리어합니다.
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}