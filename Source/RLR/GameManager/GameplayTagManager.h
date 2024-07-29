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

	const FGameplayTagContainer* GetSkillTags();
	const FGameplayTagContainer* GetSkillAnimTags();

	FGameplayTag Attributes_MainStat_Health;
	FGameplayTag Attributes_MainStat_MaxHealth;

	FGameplayTag Action_Default_Attack;
	FGameplayTag Action_Default_Jump;

	//Action.Attack
	FGameplayTag Action_Attack_HitCheck;

	//Action.Skill
	FGameplayTag Action_Skill_1;
	FGameplayTag Action_Skill_2;
	FGameplayTag Action_Skill_3;
	FGameplayTag Action_Skill_4;
	FGameplayTag Action_Skill_5;
	FGameplayTag Action_Skill_6;
	FGameplayTag Action_Skill_7;
	FGameplayTag Action_Skill_8;

	FGameplayTagContainer SkillTags;
	FGameplayTagContainer SkillAnimTags;

	//Action.Skill.Anim
	FGameplayTag Action_Skill_1_Anim;
	FGameplayTag Action_Skill_2_Anim;
	FGameplayTag Action_Skill_3_Anim;
	FGameplayTag Action_Skill_4_Anim;
	FGameplayTag Action_Skill_5_Anim;
	FGameplayTag Action_Skill_6_Anim;
	FGameplayTag Action_Skill_7_Anim;
	FGameplayTag Action_Skill_8_Anim;

	//Object.State
	FGameplayTag Object_State_Hittable;

	//Player.State
	FGameplayTag Player_State_Attacking;


	/*
		Action Item Quick Slot
	*/

	FGameplayTag Action_ItemQuickSlot_1;
	FGameplayTag Action_ItemQuickSlot_2;
	FGameplayTag Action_ItemQuickSlot_3;
	FGameplayTag Action_ItemQuickSlot_4;
	FGameplayTag Action_ItemQuickSlot_5;
	FGameplayTag Action_ItemQuickSlot_6;
	FGameplayTag Action_ItemQuickSlot_7;
	FGameplayTag Action_ItemQuickSlot_8;
	FGameplayTag Action_ItemQuickSlot_9;



	/*
		Action UI
	*/

	FGameplayTag UI_Inventory;
	FGameplayTag UI_CharacterStatus;
	FGameplayTag UI_KeyOption;
	/*
	
			키 입력 바인딩에 사용되는 태그
			Input Tag

	*/

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_Shift;
	FGameplayTag InputTag_Ctrl;
	FGameplayTag InputTag_ESC;

	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_5;
	FGameplayTag InputTag_6;
	FGameplayTag InputTag_7;
	FGameplayTag InputTag_8;
	FGameplayTag InputTag_9;

	FGameplayTag InputTag_A;
	FGameplayTag InputTag_B;
	FGameplayTag InputTag_C;
	FGameplayTag InputTag_D;
	FGameplayTag InputTag_E;
	FGameplayTag InputTag_F;
	FGameplayTag InputTag_G;
	FGameplayTag InputTag_H;
	FGameplayTag InputTag_I;
	FGameplayTag InputTag_J;
	FGameplayTag InputTag_K;
	FGameplayTag InputTag_L;
	FGameplayTag InputTag_M;
	FGameplayTag InputTag_N;
	FGameplayTag InputTag_O;
	FGameplayTag InputTag_P;
	FGameplayTag InputTag_Q;
	FGameplayTag InputTag_R;
	FGameplayTag InputTag_S;
	FGameplayTag InputTag_T;
	FGameplayTag InputTag_U;
	FGameplayTag InputTag_V;
	FGameplayTag InputTag_W;
	FGameplayTag InputTag_X;
	FGameplayTag InputTag_Y;
	FGameplayTag InputTag_Z;


	FGameplayTag None = FGameplayTag();

private:
	static FGameplayTagManager GameplayTags;


};
