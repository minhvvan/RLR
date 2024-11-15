// Fill out your copyright notice in the Description page of Project Settings.


#include "Structs/PlayerStructs.h"
#include "Network/Proto/Packet.pb.h"

void FSetStatus::MakeSetStatus(Protocol::UserSetStatus Data)
{
    UserHP = Data.userhp();
    UserMP = Data.usermp();
    UserSTR = Data.userstr();
    UserAGI = Data.useragi();
    UserINT = Data.userint();
}

void FTotalStatus::MakeStatus(Protocol::UserTotalStatus Status)
{
    HP = Status.userhp();
    HP_ABSORB = Status.userhpabsorb();
    MP = Status.usermp();
    MP_ABSORB = Status.usermpabsorb();

    STRENGTH = Status.userstrength();
    AGILITY = Status.useragility();
    INTELLIGENCE = Status.userintelligence();

    MAX_HP = Status.usermaxhp();
    MAX_MP = Status.usermaxmp();

    ATTACK = Status.userattack();
    DEFENCE = Status.userdefence();
    ATTACK_SPEED = Status.userattackspeed();
    MOVE_SPEED = Status.usermovespeed();
    CRITICAL_CHANCE = Status.usercriticalchance();
    CRITICAL_DAMAGE = Status.usercriticaldamage();
    AVOID = Status.useravoid();
    COOLDOWN_REDUCTION = Status.usercooldownreduction();
}

void FTalent::MakeTalent(Protocol::Talent Data)
{
    Talents.Add(TPair<int32, int32>(Data.firsttalent(), Data.firsttalent()));
    Talents.Add(TPair<int32, int32>(Data.secondtalent(), Data.secondlevel()));
    Talents.Add(TPair<int32, int32>(Data.thirdtalent(), Data.thirdlevel()));
}

void FUserCharacter::MakeUserCharacter(Protocol::UserCharacter Data)
{
    UserSeq = Data.userseq();
    NickName = UTF8_TO_TCHAR(Data.name().c_str());
    Level = Data.level();
    NobilityRank = Data.nobilityrank();

    MainJob = (ECharacterMainJobType)Data.mainjob();
    SubJob = (ECharacterSubJobType)Data.subjob();

    Exp = Data.exp();
    AdventureRank = Data.adventurerrank();

    TotalStatus.MakeStatus(Data.totalstatus());
    SetStatus.MakeSetStatus(Data.setstatus());
    Talent.MakeTalent(Data.talent());
    Transform = FVector(Data.transx(), Data.transy(), Data.transz());
}

