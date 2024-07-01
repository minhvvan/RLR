// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/SkillManager.h"
#include "Skill/Skill_Explosion.h"

USkillManager::USkillManager()
{
	OwnSkills.SetNum(8);
}

void USkillManager::Init()
{
	//TODO: 스킬 등록
	for (int i = 0; i < 8; i++)
	{
		//DT써도 될듯
		//OwnSkills.Add()
	}	
}

void USkillManager::SkillAttack(int inputID, FVector ClickedPos)
{
	FActorSpawnParameters SpawnParams;
	FRotator rotator;
	FVector  SpawnLocation = ClickedPos;

	if (!OwnSkills[inputID]) Init();
	APlayerSkill* Skill = GetWorld()->SpawnActor<APlayerSkill>(OwnSkills[inputID]->StaticClass(), SpawnLocation, rotator, SpawnParams);
	if (Skill != nullptr) return;
	Skill->SkillAttack(ClickedPos);
}