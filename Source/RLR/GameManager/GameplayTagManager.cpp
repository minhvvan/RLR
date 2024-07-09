// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayTagManager.h"

FGameplayTagManager FGameplayTagManager::GameplayTags;

void FGameplayTagManager::Init()
{
	GameplayTags.Attributes_MainStat_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.MainStat.Health"), FString(TEXT("체력")));
	GameplayTags.Attributes_MainStat_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.MainStat.MaxHealth"), FString(TEXT("최대 체력")));
	
	GameplayTags.Action_Default_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Default.Attack"), FString(TEXT("기본공격")));
	GameplayTags.Action_Default_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Default.Jump"), FString(TEXT("점프")));
}