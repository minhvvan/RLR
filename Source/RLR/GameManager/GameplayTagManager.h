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

	//Object.State
	FGameplayTag Object_State_Hittable;

	//Player.State
	FGameplayTag Player_State_Attacking;

private:
	static FGameplayTagManager GameplayTags;


};
