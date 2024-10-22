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
	FGameplayTag GetAbnormalTag(int AbnormalType);
	const FGameplayTagContainer* GetItemTags();

	FGameplayTag Attributes_MainStat_Health;
	FGameplayTag Attributes_MainStat_MaxHealth;

	//Default
	FGameplayTag Action_Default_Move;
	FGameplayTag Action_Default_Attack;
	FGameplayTag Action_Default_Jump;
	FGameplayTag Action_Default_PlayMontage;

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

	//Action.Skill.Type
	FGameplayTag Action_Skill_Type_Normal;
	FGameplayTag Action_Skill_Type_Area;
	FGameplayTag Action_Skill_Type_Holding;
	FGameplayTag Action_Skill_Type_Casting;
	FGameplayTag Action_Skill_Type_Movility;
	FGameplayTag Action_Skill_Type_Targeting;
	FGameplayTag Action_Skill_Type_Chain;

	FGameplayTag Action_Skill_SwordsMan_SwordAura;
	FGameplayTag Action_Skill_MAGE_Meteor;
	FGameplayTag Action_Skill_MAGE_TrippleCircle;


	FGameplayTagContainer SkillTags;

	//Action.Interaction
	FGameplayTag Action_Interaction;
	FGameplayTag Action_Interaction_Dialogue;
	FGameplayTag Action_Interaction_Logging;


	//Object.State
	FGameplayTag Object_State_Hittable;

	//Player.State
	FGameplayTag Player_State_Attacking;

	//Abnormal
	FGameplayTag Abnormal_Stun;
	FGameplayTag Abnormal_Bind;
	FGameplayTag Abnormal_Frozen;
	FGameplayTag Abnormal_Stiffen;
	FGameplayTag Abnormal_Provoke;
	FGameplayTag Abnormal_Electric;
	FGameplayTag Abnormal_Silence;
	FGameplayTag Abnormal_Burn;
	FGameplayTag Abnormal_Poison;
	FGameplayTag Abnormal_Slow;
	FGameplayTag Abnormal_Bleeding;

	FGameplayTagContainer AbnormalTags;

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

	FGameplayTagContainer ItemTags;

	/*
		Action UI
	*/

	FGameplayTag UI_Inventory;
	FGameplayTag UI_ItemInfomation;
	FGameplayTag UI_CharacterStatus;
	FGameplayTag UI_KeyOption;
	FGameplayTag UI_Skill;
	FGameplayTag UI_Quest;
	FGameplayTag UI_Chat;
	FGameplayTag UI_ChatOption;
	FGameplayTag UI_Party;
	
	FGameplayTag UI_SkillUpgrade;
	FGameplayTag UI_Close;


	FGameplayTag UI_Post;
	FGameplayTag UI_FriendList;
	FGameplayTag UI_OtherPlayerMenu;
	FGameplayTag UI_OtherPlayerStatus;
	FGameplayTag UI_Report;
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
