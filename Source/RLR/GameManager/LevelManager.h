// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelManager.generated.h"

/**
 
	1.타이틀 -> 로비 -> 인게임

	2.인게임 안에서 레벨 이동 관리.
	
	3.그외 레벨과 관련된 모든 것...

 */


UCLASS()
class RLR_API ULevelManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	//bool LoadLevel(FString LevelName
	UFUNCTION(BlueprintCallable)
	bool LoadLevel(FName LevelName);
	bool LoadLevel(int32 LevelSeq);
};
