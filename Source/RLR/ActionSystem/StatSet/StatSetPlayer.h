// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/StatSet/StatSet.h"
#include "GameManager/RLRStruct.h"
#include "StatSetPlayer.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangedLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangedExp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangedTotalStatus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangedSetStatus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangedTalent);

UCLASS()
class RLR_API UStatSetPlayer : public UStatSet
{
	GENERATED_BODY()
	

public:
	ALL_STAT_SETTER(FUserCharacter);
    STAT_ACCESSORS(UStatSetPlayer, FUserCharacter, UserSeq , int32);
    STAT_ACCESSORS(UStatSetPlayer, FUserCharacter, PlayerSeq, int32);
    STAT_ACCESSORS(UStatSetPlayer, FUserCharacter, MapId, int64);
    STAT_ACCESSORS(UStatSetPlayer, FUserCharacter, ChannelId, int64);
    STAT_ACCESSORS(UStatSetPlayer, FUserCharacter, Name, FString);
    STAT_ACCESSORS(UStatSetPlayer, FUserCharacter, Level, int32);
    STAT_ACCESSORS(UStatSetPlayer, FUserCharacter, NobilityRank, int32);
    STAT_ACCESSORS(UStatSetPlayer, FUserCharacter, MainJob, ECharacterMainJobType);
    STAT_ACCESSORS(UStatSetPlayer, FUserCharacter, SubJob, ECharacterSubJobType);
    STAT_ACCESSORS(UStatSetPlayer, FUserCharacter, Exp, int32);
    STAT_ACCESSORS(UStatSetPlayer, FUserCharacter, AdventureRank, int32);
    STAT_ACCESSORS(UStatSetPlayer, FUserCharacter, TotalStatus, FTotalStatus);
    STAT_ACCESSORS(UStatSetPlayer, FUserCharacter, SetStatus, FSetStatus);
    STAT_ACCESSORS(UStatSetPlayer, FUserCharacter, Talent, FTalent);


    template<typename T>
    void ApplyChangeStat(FStatChangeSpec<T>& ChangeSpec)
    {
        if (ChangeSpec.ChangedStat == GetLevelStat())
        {
            UpdateLevel(ChangeSpec.NewValue);
        }
        else if (ChangeSpec.ChangedStat == GetExpStat())
        {
            UpdateExp(ChangeSpec.NewValue);
        }
    };

    template<>
    void ApplyChangeStat(FStatChangeSpec<FTotalStatus>& ChangeSpec)
    {
        UpdateTotalStatus(ChangeSpec.NewValue);
    }

    template<>
    void ApplyChangeStat(FStatChangeSpec<FSetStatus>& ChangeSpec)
    {
        UpdateSetStatus(ChangeSpec.NewValue);
    }

    template<>
    void ApplyChangeStat(FStatChangeSpec<FTalent>& ChangeSpec)
    {
        UpdateTalent(ChangeSpec.NewValue);
    }

    void UpdateStat();
    void ClearBindFunc();

    //Delegates
    FOnChangedLevel         OnChangedLevel;
    FOnChangedExp           OnChangedExp;
    FOnChangedTotalStatus   OnChangedTotalStatus;
    FOnChangedSetStatus     OnChangedSetStatus;
    FOnChangedTalent        OnChangedTalent;

private:
	FUserCharacter Stat;

protected:
    void UpdateLevel(int32 NewLevel);
    void UpdateExp(int32 NewExp);
    void UpdateTotalStatus(FTotalStatus NewTotalStatus);
    void UpdateSetStatus(FSetStatus NewSetStatus);
    void UpdateTalent(FTalent NewTalent);
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