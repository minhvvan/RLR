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
	SkillClassTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_SkillClass.DT_SkillClass'")));
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
		FSkillClass* Data = SkillClassTable->FindRow<FSkillClass>(*FString::FromInt(0), TEXT(""));
		if (Data == nullptr)
		{
			RLR_LOG(LogRLR, Log, TEXT("Not Found SKill Class"));
			return;
		}

		FGameplayTagManager TagManager = FGameplayTagManager::Get();
		OwnSkills.Add({ TagManager.Action_Skill_Anim_Q, Data->SkillClass });

		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (!Controller) return;

		ARLRPlayerCharacter* Character = Cast<ARLRPlayerCharacter>(Controller->GetPawn());
		if (!Character) return;

		UActionSystemComponent* ASC = Character->GetActionSystemComponent();
		if (!ASC) return;

		{
			//Chain HitCheck Class(for Transfer Data)
			FActionSpec Spec(Data->SkillAnimClass, 1, 0);
			Spec.FollowActionTag = TagManager.Action_Skill_Q;
			ASC->GiveAction(TagManager.Action_Skill_Anim_Q, Spec);
		}
		{
			FActionSpec Spec(Data->SkillClass, 1, 0);
			ASC->GiveAction(TagManager.Action_Skill_Q, Spec);
		}
	}
}

void USkillManager::SkillAttack(FGameplayTag TriggerTag)
{
	if (!OwnSkills.Contains(TriggerTag)) Init();
	//APlayerSkill* Skill = GetWorld()->SpawnActor<APlayerSkill>(OwnSkTriggerTagills[inputID]->StaticClass(), SpawnLocation, rotator, SpawnParams);
	//if (Skill != nullptr) return;
	//Skill->SkillAttack(ClickedPos);

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!Controller) return;

	ARLRPlayerCharacter* Character = Cast<ARLRPlayerCharacter>(Controller->GetPawn());
	if (!Character) return;

	UActionSystemComponent* ASC = Character->GetActionSystemComponent();
	if (!ASC) return;

	ASC->TryActivateAction(TriggerTag);
}