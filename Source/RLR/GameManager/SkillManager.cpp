// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/SkillManager.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/DataManager.h"

#include "Kismet/GameplayStatics.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/Action/Skills/ActionSkill.h"
#include "RLR.h"

#include "ActionSystem/StatSet/StatSetMonster.h"

void USkillManager::Initialize(FSubsystemCollectionBase& Collection)
{
	UpdatedTryActivateAction.Clear();
	UpdatedSkillSettingDelegate.Clear();
	UpdateTest.AddDynamic(this, &USkillManager::SetSelectedSkills);
}

void USkillManager::SkillStart(FGameplayTag TriggerTag)
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!Controller) return;

	ARLRPlayerCharacter* Character = Cast<ARLRPlayerCharacter>(Controller->GetPawn());
	if (!Character) return;

	UActionSystemComponent* ASC = Character->GetActionSystemComponent();
	if (!ASC) return;

	ASC->TryActivateAction(TriggerTag);
	UpdatedTryActivateAction.Broadcast(TriggerTag);
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

			auto skillTag = GetSkillTag(TriggerTag);
			ASC->TryCancelAction(skillTag);
		}
	}
}

const FSkillData* USkillManager::GetSkillData(FGameplayTag TriggerTag)
{
	for (auto& [Tag, Data] : OwnSkills)
	{
		if (TriggerTag.MatchesTag(Tag))
		{
			return &Data;
		}
	}

	return nullptr;
}

const FSkillDictionary<FGameplayTag, FSkillData>& USkillManager::GetOwnSkills()
{
	return OwnSkills;
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

FGameplayTag USkillManager::GetSkillTag(FGameplayTag TriggerTag)
{
	if (!OwnSkills.Contains(TriggerTag)) return FGameplayTag::EmptyTag;
	return OwnSkills[TriggerTag].SkillTag;
}

bool USkillManager::HasLearnedSkill(int32 SkillSeq)
{
	return LearnedSkills.Contains(SkillSeq);
}

void USkillManager::SetSelectedSkills(TArray<FSkillData>& SelectedSkills)
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!Controller || !Controller->GetPawn())
	{
		RLR_LOG(LogRLR, Warning, TEXT("PlayerController or Pawn is invalid."));
		return;
	}

	ARLRPlayerCharacter* Character = Cast<ARLRPlayerCharacter>(Controller->GetPawn());
	if (!Character)
	{
		RLR_LOG(LogRLR, Warning, TEXT("PlayerCharacter is invalid."));
		return;
	}

	UActionSystemComponent* ASC = Character->GetActionSystemComponent();
	if (!ASC)
	{
		RLR_LOG(LogRLR, Warning, TEXT("ActionSystemComponent is invalid."));
		return;
	}

	// GameplayTagManager
	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	const FGameplayTagContainer* SkillTags = TagManager.GetSkillTags();
	OwnSkills.Empty();

	for (int i = 0; i < SelectedSkills.Num(); i++)
	{
		const FSkillData& Data = SelectedSkills[i];
		if (Data == FSkillData::EmptySkillData)
		{
			RLR_LOG(LogRLR, Log, TEXT("Not Found Skill Class"));
			return;
		}
		const FActionResource& ActionResource = GameInstance->GetDataManager()->GetActionResource(Data.SkillSeq);
		if (ActionResource == FActionResource::EmptyActionResource)
		{
			RLR_LOG(LogRLR, Log, TEXT("Not Found Skill Class DataTable"));
			return;
		}

		FGameplayTag SkillTag = SkillTags->GetByIndex(Data.SkillIdx);
		OwnSkills.Add(SkillTag, Data);

		{
			FActionSpec Spec(ActionResource.ActionClass, 1, 0);
			ASC->GiveAction(Data.SkillTag, Spec);
		}
	}

	// Safely broadcast in game thread
	UpdatedSkillSettingBroadcast();
}

void USkillManager::SetLearnedSkills(const TArray<FSkillData>& LearnedSkillsList)
{
	LearnedSkills.Empty();

	TArray<FSkillData> selectedSkills;
	for (const FSkillData& SkillData : LearnedSkillsList)
	{
		LearnedSkills.Add(SkillData.SkillSeq, SkillData);
		if (0 <= SkillData.SkillIdx && SkillData.SkillIdx < 8)
		{
			selectedSkills.Add(SkillData);
		}
	}

	SetSelectedSkills(selectedSkills);
}

bool USkillManager::RequestSkillResult(const FSkillData* SkillData, TArray<AActor*> OverlappedActor)
{
	FAttackResult AttackResults;
	if (SkillData) {
		AttackResults.SkillSeq = SkillData->SkillSeq;
		AttackResults.Level = SkillData->Level;
		AttackResults.Timestamp = FDateTime::UtcNow().ToUnixTimestamp();
		AttackResults.UserSeq = 1; // PlayerManager userSeq
	}
	else {
		AttackResults.SkillSeq = 0;
		AttackResults.Level = 0;
		AttackResults.Timestamp = 0;
		AttackResults.UserSeq = 1;

	}
	
	
	for (auto Target : OverlappedActor)
	{
		ARLRCharacter* Monster = Cast<ARLRCharacter>(Target);
		UActionSystemComponent* ASC = Monster->GetActionSystemComponent();
		UStatSetMonster* MonsterStatus = ASC->GetStatSet<UStatSetMonster>();
		if (MonsterStatus) {
			AttackResults.TargetSeq.Add(MonsterStatus->GetMonsterId());
		}
		
	}

	return GameInstance->GetNetworkManager()->SendAttackPacket(AttackResults);
}

void USkillManager::UpdatedSkillSettingBroadcast()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			UpdatedSkillSettingDelegate.Broadcast();
		});
}

