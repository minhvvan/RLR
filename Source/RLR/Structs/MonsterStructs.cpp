// Fill out your copyright notice in the Description page of Project Settings.


#include "Structs/MonsterStructs.h"

const FMonsterStatus FMonsterStatus::EmptyMonsterData;

void FMonsterStatus::MakeMonsterData(const Protocol::Monster monsterData)
{
    //(X=1250.000000,Y=1930.000000,Z=96.000000)
    MonsterSeq = monsterData.monsterseq();
    MonsterName = UTF8_TO_TCHAR(monsterData.monstername().c_str());
    MonsterLevel = monsterData.monsterlevel();
    MonsterExp = monsterData.monsterexp();
    MonsterAttackRate = monsterData.monsterdamage();
    MonsterDefence = monsterData.monsterdefence();
    MonsterMaxHp = monsterData.monstermaxhp();
    MonsterHp = monsterData.monsterhp();
    MonsterAttackRange = 10;  // Packet 추가 예정
    MonsterTransform = { monsterData.monstertransx(), monsterData.monstertransy(), monsterData.monstertransz() };
    MonsterId = monsterData.monsterid();
    MonsterMapId = monsterData.monstermapid();
}