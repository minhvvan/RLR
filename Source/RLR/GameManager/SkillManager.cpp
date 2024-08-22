// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/SkillManager.h"
#include "GameManager/GameplayTagManager.h"
#include "Kismet/GameplayStatics.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/Action/Skills/ActionSkill.h"
#include "RLR.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include <ActionSystem/StatSet/StatSetMonster.h>

void USkillManager::Initialize(FSubsystemCollectionBase& Collection)
{
	SkillClassTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_SkillClass.DT_SkillClass'")));
	if (IsValid(SkillClassTable) == false)
	{
		RLR_LOG(LogRLR, Log, TEXT("Skill Table Can't Load"));
	}
	UpdatedTryActivateAction.Clear();
	UpdatedSkillManager.Clear();
}

void USkillManager::Init()
{
	if (!RequestGetSelectedSkills())
	{
		RLR_LOG(LogRLR, Log, TEXT("Fail GetSelected Skill Load"));
		return;
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

			ASC->TryCancelAction(TriggerTag);
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

const TMap<FGameplayTag, FSkillData>& USkillManager::GetOwnSkills()
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

void USkillManager::SetSelectedSkills(TArray<FSkillData>& SelectedSkills)
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

	for (int i = 0; i < SelectedSkills.Num(); i++)
	{
		FSkillClass* Data = SkillClassTable->FindRow<FSkillClass>(*FString::FromInt(SelectedSkills[i].SkillSeq - 1), TEXT(""));
		if (Data == nullptr)
		{
			RLR_LOG(LogRLR, Log, TEXT("Not Found SKill Class"));
			return;
		}

		FGameplayTag SkillTag = SkillTags->GetByIndex(i);
		FGameplayTag SkillAnimTag = SkillAnimTags->GetByIndex(i);

		OwnSkills.Add({ SkillTag, SelectedSkills[i]});

		//TriggerAction
		{
			FActionSpec Spec(Data->SkillAnimClass, 1, 0);
			//Chain HitCheck Class(for Transfer Data)
			Spec.FollowActionTag = SkillTag;
			ASC->GiveAction(SkillAnimTag, Spec);
		}

		//CheckAction 
		{
			FActionSpec Spec(Data->SkillClass, 1, 0);
			ASC->GiveAction(SkillTag, Spec);
		}
	}

	UpdatedSkillManager.Broadcast();
}

bool USkillManager::RequestGetSelectedSkills()
{
	TArray<FSkillData> SelectedSkills;
	//TODO: Request Get Selected Skill
	//내가 설정한 8개를 가져와줘
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!Controller) return false;

	ARLRPlayerCharacter* Character = Cast<ARLRPlayerCharacter>(Controller->GetPawn());
	if (!Character) return false;

	UActionSystemComponent* ASC = Character->GetActionSystemComponent();
	if (!ASC) return false;

	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	const FGameplayTagContainer* SkillTags = TagManager.GetSkillTags();
	const FGameplayTagContainer* SkillAnimTags = TagManager.GetSkillAnimTags();

	{
		FSkillData asd;
		asd.SkillSeq = 1;
		asd.SkillType = ESkillType::NORMAL;
		SelectedSkills.Add(asd);
	}

	{
		FSkillData asd;
		asd.SkillSeq = 2;
		asd.SkillType = ESkillType::AREA;
		asd.CollisionRange = FVector(100.f);
		SelectedSkills.Add(asd);
	}

	{
		FSkillData asd;
		asd.SkillSeq = 3;
		asd.Duration = 4;
		asd.SkillType = ESkillType::HOLDING;
		asd.CollisionRange = FVector(400.f, 0.f, 0.f);
		SelectedSkills.Add(asd);
	}

	for (int i = 0; i < SelectedSkills.Num(); i++)
	{
		FSkillClass* Data = SkillClassTable->FindRow<FSkillClass>(*FString::FromInt(SelectedSkills[i].SkillSeq - 1), TEXT(""));
		if (Data == nullptr)
		{
			RLR_LOG(LogRLR, Log, TEXT("Not Found SKill Class"));
			return false;
		}

		FGameplayTag SkillTag = SkillTags->GetByIndex(i);
		FGameplayTag SkillAnimTag = SkillAnimTags->GetByIndex(i);

		OwnSkills.Add({ SkillTag, SelectedSkills[i] });

		//TriggerAction
		{
			FActionSpec Spec(Data->SkillAnimClass, 1, 0);
			//Chain HitCheck Class(for Transfer Data)
			Spec.FollowActionTag = SkillTag;
			ASC->GiveAction(SkillAnimTag, Spec);
		}

		//CheckAction 
		{
			FActionSpec Spec(Data->SkillClass, 1, 0);
			ASC->GiveAction(SkillTag, Spec);
		}
	}
	return true;
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
		
		//AttackResults.TargetSeq.Add(MonsterStatus->GetMonsterId());
	}

	//TODO: Send To Server(Skill Result) Using NetworkManager
	GameInstance->GetNetworkManager()->SendAttackPacket(AttackResults);
	return false;
}
