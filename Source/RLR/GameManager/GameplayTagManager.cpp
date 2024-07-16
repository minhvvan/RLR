// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayTagManager.h"

FGameplayTagManager FGameplayTagManager::GameplayTags;

void FGameplayTagManager::Init()
{
	GameplayTags.Attributes_MainStat_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.MainStat.Health"), FString(TEXT("체력")));
	GameplayTags.Attributes_MainStat_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.MainStat.MaxHealth"), FString(TEXT("최대 체력")));
	
	//Action
	GameplayTags.Action_Default_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Default.Attack"), FString(TEXT("기본공격")));
	GameplayTags.Action_Default_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Default.Jump"), FString(TEXT("점프")));
	
	GameplayTags.Action_Attack_HitCheck = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Attack.HitCheck"), FString(TEXT("공격판정")));
	
	//Skill
	GameplayTags.Action_Skill_Q = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Q"), FString(TEXT("Q스킬")));
	GameplayTags.Action_Skill_W = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.W"), FString(TEXT("W스킬")));
	GameplayTags.Action_Skill_E = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.E"), FString(TEXT("E스킬")));
	GameplayTags.Action_Skill_R = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.R"), FString(TEXT("R스킬")));
	GameplayTags.Action_Skill_A = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.A"), FString(TEXT("A스킬")));
	GameplayTags.Action_Skill_S = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.S"), FString(TEXT("S스킬")));
	GameplayTags.Action_Skill_D = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.D"), FString(TEXT("D스킬")));
	GameplayTags.Action_Skill_F = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.F"), FString(TEXT("F스킬")));
	
	//Skill.Anim
	GameplayTags.Action_Skill_Anim_Q = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Anim.Q"), FString(TEXT("Q애니메이션")));
	GameplayTags.Action_Skill_Anim_W = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Anim.W"), FString(TEXT("W애니메이션")));
	GameplayTags.Action_Skill_Anim_E = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Anim.E"), FString(TEXT("E애니메이션")));
	GameplayTags.Action_Skill_Anim_R = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Anim.R"), FString(TEXT("R애니메이션")));
	GameplayTags.Action_Skill_Anim_A = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Anim.A"), FString(TEXT("A애니메이션")));
	GameplayTags.Action_Skill_Anim_S = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Anim.S"), FString(TEXT("S애니메이션")));
	GameplayTags.Action_Skill_Anim_D = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Anim.D"), FString(TEXT("D애니메이션")));
	GameplayTags.Action_Skill_Anim_F = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Anim.F"), FString(TEXT("F애니메이션")));
	
	//Object
	GameplayTags.Object_State_Hittable = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Object.State.Hittable"), FString(TEXT("공격가능")));
	
	//Player
	GameplayTags.Player_State_Attacking = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.State.Attacking"), FString(TEXT("공격중")));
}