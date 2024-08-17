// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/EffectManager.h"
#include "RLRStruct.h"
#include "NiagaraFunctionLibrary.h"
#include <NiagaraSystem.h>

UEffectManager::UEffectManager()
{
	SpawnMonsterHitEffect();

	min = -50.0f;
	max = 50.0f;
}
void UEffectManager::SpawnMonsterHitEffect()
{
	UDataTable* EffectDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_EffectDataTable.DT_EffectDataTable'"));

	if (EffectDataTable)
	{
		static const FString ContextString(TEXT("Effect Data Context"));
		FEffectData* EffectData = EffectDataTable->FindRow<FEffectData>(*FString::FromInt(1), ContextString);

		if (EffectData)
		{
			effect = LoadObject<UNiagaraSystem>(nullptr, *EffectData->EffectPath);
		}
	}
}

void UEffectManager::SpawnPlayerHitEffect(FVector location)
{
	if (effect)
	{
		FVector result = location;
		result.Z += 10;
		EffectLocation = result;

		for (int32 i = 0; i < 3; ++i)
		{
			GetWorld()->GetTimerManager().SetTimer(
				TimerHandle,
				this,
				&UEffectManager::GenerateRandomLocation,
				0.1f,
				true
			);
			FVector RandomLocation = GenerateRandomOffset(result);
		}
	}
}

FVector UEffectManager::GenerateRandomOffset(FVector location)
{
	float RandomX = FMath::RandRange(min, max);
	float RandomY = FMath::RandRange(min, max);
	float RandomZ = FMath::RandRange(min, max);

	return location + FVector(RandomX, RandomY, RandomZ);
}

void UEffectManager::GenerateRandomLocation()
{
	if (RemainingCalls > 0)
	{
		FVector RandomLocation = GenerateRandomOffset(EffectLocation);
		UE_LOG(LogTemp, Log, TEXT("좌표값 : %s"), *RandomLocation.ToString());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), effect, RandomLocation);

		RemainingCalls--;
	}
	else
	{
		// 호출 횟수를 모두 사용한 후 타이머를 클리어합니다.
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}