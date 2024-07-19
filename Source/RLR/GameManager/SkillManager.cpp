// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/SkillManager.h"
#include "GameManager/GameplayTagManager.h"
#include "Skill/Skill_Explosion.h"
#include "Kismet/GameplayStatics.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/Action/Skills/ActionSkill.h"
#include "RLR.h"

void USkillManager::Initialize(FSubsystemCollectionBase& Collection)
{
	SkillClassTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_SkillData.DT_SkillData'")));
	if (IsValid(SkillClassTable) == false)
	{
		RLR_LOG(LogRLR, Log, TEXT("Skill Table Can't Load"));
	}
}

void USkillManager::Init()
{
	if (SkillClassTable)
	{
		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (!Controller) return;

		ARLRPlayerCharacter* Character = Cast<ARLRPlayerCharacter>(Controller->GetPawn());
		if (!Character) return;

		UActionSystemComponent* ASC = Character->GetActionSystemComponent();
		if (!ASC) return;

		FGameplayTagManager TagManager = FGameplayTagManager::Get();
		const FGameplayTagContainer* SkillTags = TagManager.GetSkillTags();
		const FGameplayTagContainer* SkillAnimTags = TagManager.GetSkillAnimTags();

		for (int i = 0; i < 8; i++)
		{
			FSkillData* Data = SkillClassTable->FindRow<FSkillData>(*FString::FromInt(i), TEXT(""));
			if (Data == nullptr)
			{
				RLR_LOG(LogRLR, Log, TEXT("Not Found SKill Class"));
				return;
			}

			FGameplayTag SkillTag = SkillTags->GetByIndex(i);
			FGameplayTag SkillAnimTag = SkillAnimTags->GetByIndex(i);

			OwnSkills.Add({ SkillTag, Data });

			//TriggerAction
			{
				FActionSpec Spec(Data->SkillAnimClass, 1, 0);
				//Chain HitCheck Class(for Transfer Data)
				Spec.FollowActionTag = SkillTag;

				if (Data->SkillType == ESkillType::AREA || Data->SkillType == ESkillType::HOLDING)
				{
					Spec.bCancelable = true;
				}

				ASC->GiveAction(SkillAnimTag, Spec);
			}

			//CheckAction 
			{
				FActionSpec Spec(Data->SkillClass, 1, 0);
				ASC->GiveAction(SkillTag, Spec);
			}
		}
	}
}

void USkillManager::SkillAttack(FGameplayTag TriggerTag)
{
	if (!HasSkillTag(TriggerTag)) Init();

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!Controller) return;

	ARLRPlayerCharacter* Character = Cast<ARLRPlayerCharacter>(Controller->GetPawn());
	if (!Character) return;

	UActionSystemComponent* ASC = Character->GetActionSystemComponent();
	if (!ASC) return;

	ASC->TryActivateAction(TriggerTag);
}

void USkillManager::SkillComplete(FGameplayTag TriggerTag)
{
	if (!HasSkillTag(TriggerTag)) return;

	if (auto* Data = GetSkillData(TriggerTag))
	{
		if (Data->SkillType == ESkillType::HOLDING)
		{
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (!Controller) return;

			ARLRPlayerCharacter* Character = Cast<ARLRPlayerCharacter>(Controller->GetPawn());
			if (!Character) return;

			UActionSystemComponent* ASC = Character->GetActionSystemComponent();
			if (!ASC) return;

			ASC->TryCancelAction(TriggerTag);
		}
	}
}

const FSkillData* USkillManager::GetSkillData(FGameplayTag TriggerTag)
{
	FSkillData* Result = nullptr;

	for (auto& [Tag, Data] : OwnSkills)
	{
		if (TriggerTag.MatchesTag(Tag))
		{
			Result = Data;
		}
	}

	return Result;
}

bool USkillManager::HasSkillTag(FGameplayTag TriggerTag)
{
	bool bResult = false;
	for (auto& [Tag, Data] : OwnSkills)
	{
		if (TriggerTag.MatchesTag(Tag))
		{
			bResult = true;
			break;
		}
	}

	return bResult;
}
