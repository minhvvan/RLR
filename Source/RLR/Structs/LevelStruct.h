// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelStruct.generated.h"

/*
	레벨과 관련된 데이터
*/


UENUM(BlueprintType)
enum class ETestType : uint8
{
	//무기, 방어구
	WEAPON,
	SUBWEAPON,
};


USTRUCT(Atomic, BlueprintType)
struct FLevelData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	FLevelData();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 LevelSeq = -1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString LevelName = FString();				//언리얼 프로젝트 레벨 이름.

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FText MapName	= FText();					//플레이어가 볼 맵 이름

	static const FLevelData EmptyData;

	/** Operators */
	FORCEINLINE bool operator==(FLevelData const& Other) const
	{
		if (LevelSeq != Other.LevelSeq)
			return false;
		return true;
	}
};
