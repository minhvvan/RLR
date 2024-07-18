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
	//TODO: 스킬 등록
	if (SkillClassTable)
	{
		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (!Controller) return;

		ARLRPlayerCharacter* Character = Cast<ARLRPlayerCharacter>(Controller->GetPawn());
		if (!Character) return;

		UActionSystemComponent* ASC = Character->GetActionSystemComponent();
		if (!ASC) return;

		for (int i = 0; i < 3; i++)
		{
			FSkillData* Data = SkillClassTable->FindRow<FSkillData>(*FString::FromInt(i), TEXT(""));
			if (Data == nullptr)
			{
				RLR_LOG(LogRLR, Log, TEXT("Not Found SKill Class"));
				return;
			}

			//Temp
			FGameplayTagManager TagManager = FGameplayTagManager::Get();
			if (i == 0)
			{
				OwnSkills.Add({ TagManager.Action_Skill_Q, *Data });

				{
					//Chain HitCheck Class(for Transfer Data)
					FActionSpec Spec(Data->SkillAnimClass, 1, 0);
					Spec.FollowActionTag = TagManager.Action_Skill_Q;
					ASC->GiveAction(TagManager.Action_Skill_Q_Anim, Spec);
				}
				{
					FActionSpec Spec(Data->SkillClass, 1, 0);
					ASC->GiveAction(TagManager.Action_Skill_Q, Spec);
				}
			}
			else if(i == 1)
			{
				OwnSkills.Add({ TagManager.Action_Skill_W, *Data });

				{
					//Chain HitCheck Class(for Transfer Data)
					FActionSpec Spec(Data->SkillAnimClass, 1, 0);
					Spec.FollowActionTag = TagManager.Action_Skill_W;
					Spec.bCancelable = true;
					ASC->GiveAction(TagManager.Action_Skill_W_Anim, Spec);
				}
				{
					FActionSpec Spec(Data->SkillClass, 1, 0);
					ASC->GiveAction(TagManager.Action_Skill_W, Spec);
				}
			}
			else
			{
				OwnSkills.Add({ TagManager.Action_Skill_E, *Data });

				{
					//Chain HitCheck Class(for Transfer Data)
					FActionSpec Spec(Data->SkillAnimClass, 1, 0);
					Spec.FollowActionTag = TagManager.Action_Skill_E;
					Spec.bCancelable = true;
					ASC->GiveAction(TagManager.Action_Skill_E_Anim, Spec);
				}
				{
					FActionSpec Spec(Data->SkillClass, 1, 0);
					ASC->GiveAction(TagManager.Action_Skill_E, Spec);
				}
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

void USkillManager::SKillComplete(FGameplayTag TriggerTag)
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
			Result = &Data;
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
