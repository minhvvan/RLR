// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagsManager.h"

/**`
	Gameplay Tag를 관리하기 위한 구조체겸 싱글톤
 */

struct FGameplayTagManager
{
public:
	static const FGameplayTagManager& Get() { return GameplayTags; }
	static void	Init();


	FGameplayTag Attributes_MainStat_Health;
	FGameplayTag Attributes_MainStat_MaxHealth;

	FGameplayTag Action_Default_Attack;
	FGameplayTag Action_Default_Jump;

	//Action.Attack
	FGameplayTag Action_Attack_HitCheck;

	//Action.Skill
	FGameplayTag Action_Skill_Q;
	FGameplayTag Action_Skill_W;
	FGameplayTag Action_Skill_E;
	FGameplayTag Action_Skill_R;
	FGameplayTag Action_Skill_A;
	FGameplayTag Action_Skill_S;
	FGameplayTag Action_Skill_D;
	FGameplayTag Action_Skill_F;

	//Action.Skill.Anim
	FGameplayTag Action_Skill_Anim_Q;
	FGameplayTag Action_Skill_Anim_W;
	FGameplayTag Action_Skill_Anim_E;
	FGameplayTag Action_Skill_Anim_R;
	FGameplayTag Action_Skill_Anim_A;
	FGameplayTag Action_Skill_Anim_S;
	FGameplayTag Action_Skill_Anim_D;
	FGameplayTag Action_Skill_Anim_F;

	//Object.State
	FGameplayTag Object_State_Hittable;

	//Player.State
	FGameplayTag Player_State_Attacking;


private:
	static FGameplayTagManager GameplayTags;


};
