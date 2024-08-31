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



 /*
  민환님이 지금 정리 중이니 임시 배치. 나중에 머지되면 RLRStruct 어딘가에 옮겨줄 예정.
*/
  USTRUCT(Atomic, BlueprintType)
struct FLevelData
{
	GENERATED_BODY()

	/*
		나중에 현석님한테 서버 리스트에서 채울 데이터 어떻게 구성할지 물어보기.
	*/

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 LevelSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FText LevelName;			//(맵)레벨 이름.
};

UCLASS()
class RLR_API ULevelManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	//bool LoadLevel(FString LevelName
	UFUNCTION(BlueprintCallable)
	bool LoadLevel(FName LevelName);

	UFUNCTION(BlueprintCallable)
	bool IsValidLevel(FName LevelName);
};
