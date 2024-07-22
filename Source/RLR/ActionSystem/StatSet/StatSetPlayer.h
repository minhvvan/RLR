// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/StatSet/StatSet.h"
#include "GameManager/RLRStruct.h"
#include "StatSetPlayer.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UStatSetPlayer : public UStatSet
{
	GENERATED_BODY()
	

public:


	ALL_STAT_SETTER(FUserCharacter);
    STAT_ACCESSORS(UStatSetPlayer, UserSeq , int32);
    STAT_ACCESSORS(UStatSetPlayer, PlayerSeq, int32);
    STAT_ACCESSORS(UStatSetPlayer, Name, FString);
    STAT_ACCESSORS(UStatSetPlayer, Level, int32);
    STAT_ACCESSORS(UStatSetPlayer, NobilityRank, int32);
    STAT_ACCESSORS(UStatSetPlayer, MainJob, ECharacterMainJobType);
    STAT_ACCESSORS(UStatSetPlayer, SubJob, ECharacterSubJobType);
    STAT_ACCESSORS(UStatSetPlayer, Exp, int32);
    STAT_ACCESSORS(UStatSetPlayer, AdventureRank, int32);
    STAT_ACCESSORS(UStatSetPlayer, SetStatus, FSetStatus);
    STAT_ACCESSORS(UStatSetPlayer, TotalStatus, FTotalStatus);


private:
	FUserCharacter Stat;
};

/*
    int32 userSeq = 1;
    int32 playerSeq = 2;
    string name = 3;
    int32 level = 4;
    int32 nobilityRank = 5;
    int32 mainJob = 6;
    int32 subJob = 7;
    int32 exp = 8;
    int32 adventurerRank = 9;
    float transX = 10;
    float transY = 11;
    float transZ = 12;
    int32 mapTransX = 13;
    int32 mapTransY = 14;
    UserSetStatus setStatus = 15;
    UserTotalStatus totalStatus = 16;
*/