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
	UpdatedItemSettingDelegate.Clear();

	UpdateTest.AddDynamic(this, &USkillManager::SetSelectedSkills);
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
	const FGameplayTagContainer* SkillAnimTags = TagManager.GetSkillAnimTags();
	OwnSkills.Empty();

	for (int i = 0; i < SelectedSkills.Num(); i++)
	{
		const FSkillData& Data = SelectedSkills[i];
		if (Data == FSkillData::EmptySkillData)
		{
			RLR_LOG(LogRLR, Log, TEXT("Not Found Skill Class"));
			return;
		}
		const FSkillClass& SkillClassData = GameInstance->GetDataManager()->GetSkillResource(Data.SkillSeq);
		if (SkillClassData == FSkillClass::EmptySkillClass)
		{
			RLR_LOG(LogRLR, Log, TEXT("Not Found Skill Class DataTable"));
			return;
		}

		//스킬 태그는 퀵 슬롯 인덱스 번호로 맞춰야 함  -> Skill.{퀵 슬롯 인덱스 번호}
		//퀵 슬롯 세팅 리스트를 따로 빧는게 아니라 지금은 배운 스킬 목록을 받아서, 세팅을 하고 있다. 
		//그래서 일단 배운 스킬 목록 중에서 SkillIdx 값의 유무에 따라 예외처리. 
		if(Data.SkillIdx < 0 || Data.SkillIdx > 8)
			continue;

		FGameplayTag SkillTag = SkillTags->GetByIndex(Data.SkillIdx);
		FGameplayTag SkillAnimTag = SkillAnimTags->GetByIndex(Data.SkillIdx);

		OwnSkills.Add(SkillTag, SelectedSkills[i]);

		// TriggerAction
		{
			FActionSpec Spec(SkillClassData.SkillAnimClass, 1, 0);
			Spec.FollowActionTag = SkillTag;
			ASC->GiveAction(SkillAnimTag, Spec);
		}

		// CheckAction
		{
			FActionSpec Spec(SkillClassData.SkillClass, 1, 0);
			ASC->GiveAction(SkillTag, Spec);
		}
	}

	// Safely broadcast in game thread
	UpdatedSkillSettingBroadcast();
}

void USkillManager::SetLearnedSkills(const TArray<FSkillData>& LearnedSkillsList)
{
	LearnedSkills.Empty();
	for (const FSkillData& SkillData : LearnedSkillsList)
	{
		LearnedSkills.Add(SkillData.SkillSeq, SkillData);
	}
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

	for (int i = 0; i < SelectedSkills.Num(); i++)
	{
		const FSkillData& Data = SelectedSkills[i];
		if (Data == FSkillData::EmptySkillData)
		{
			RLR_LOG(LogRLR, Log, TEXT("Not Found SKill Class"));
			return false;
		}
		const FSkillClass& SkillClassData = GameInstance->GetDataManager()->GetSkillResource(Data.SkillSeq);
		if (SkillClassData == FSkillClass::EmptySkillClass)
		{
			RLR_LOG(LogRLR, Log, TEXT("Not Found Skill Class DataTable"));
			return false;
		}

		FGameplayTag SkillTag = SkillTags->GetByIndex(Data.SkillIdx);
		FGameplayTag SkillAnimTag = SkillAnimTags->GetByIndex(Data.SkillIdx);

		OwnSkills.Add(SkillTag, SelectedSkills[i]);

		//TriggerAction
		{
			FActionSpec Spec(SkillClassData.SkillAnimClass, 1, 0);
			//Chain HitCheck Class(for Transfer Data)
			Spec.FollowActionTag = SkillTag;
			ASC->GiveAction(SkillAnimTag, Spec);
		}

		//CheckAction 
		{
			FActionSpec Spec(SkillClassData.SkillAnimClass, 1, 0);
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
		if (MonsterStatus) {
			AttackResults.TargetSeq.Add(MonsterStatus->GetMonsterId());
		}
		
	}

	//TODO: Send To Server(Skill Result) Using NetworkManager
	GameInstance->GetNetworkManager()->SendAttackPacket(AttackResults);
	return false;
}

void USkillManager::UsingItem(FGameplayTag TriggerTag)
{
	if (!HasSkillTag(TriggerTag)) Init();

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!Controller) return;

	ARLRPlayerCharacter* Character = Cast<ARLRPlayerCharacter>(Controller->GetPawn());
	if (!Character) return;

	UActionSystemComponent* ASC = Character->GetActionSystemComponent();
	if (!ASC) return;

	{
		//TODO. 서버에 아이템 사용 패킷을 보낸다.
		//이 부분은 여기서 바로 패킷을 보낼 건지, ActionComponent에서 처리할 건지 민환님이랑 이야기해볼 것.
		//const FItemData* ItemData = GetItemData(TriggerTag);
		//GameInstance->GetNetworkManager()->SendUsingItemPacket(*ItemData);
	}

	UpdatedTryUsingItemAction.Broadcast(TriggerTag);
}

const FItemData* USkillManager::GetItemData(FGameplayTag TriggerTag)
{
	for (auto& [Tag, Data] : OwnItems)
	{
		if (TriggerTag.MatchesTag(Tag))
		{
			return &Data;
		}
	}
	return nullptr;
}

const FSkillDictionary<FGameplayTag, FItemData>& USkillManager::GetOwnItems()
{
	return OwnItems;
}

bool USkillManager::HasItemTag(FGameplayTag TriggerTag)
{
	bool bResult = false;
	for (auto& [Tag, Data] : OwnItems)
	{
		if (TriggerTag.MatchesTag(Tag))
		{
			bResult = true;
			break;
		}
	}

	return bResult;
}

void USkillManager::SetSelectedItems(TArray<FItemData>& SelectedItems)
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
	const FGameplayTagContainer* ItemTags = TagManager.GetItemTags();
	OwnItems.Empty();

	for (int i = 0; i < SelectedItems.Num(); i++)
	{
		const FItemData& Data = SelectedItems[i];
		if (Data == FItemData::EmptyItemData)
		{
			RLR_LOG(LogRLR, Log, TEXT("Not Found Skill Class"));
			return;
		}

		//아이템 태는 퀵 슬롯 인덱스 번호로 맞춰야 함  -> ItemQuickSlot.{퀵 슬롯 인덱스 번호}
		FGameplayTag ItemTag = ItemTags->GetByIndex(Data.ITEM_SLOT_IDX);
		OwnItems.Add(ItemTag, SelectedItems[i]);
	}

	UpdatedItemSettingBroadcast();
}

void USkillManager::UpdatedSkillSettingBroadcast()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			// 유효성 검사 추가
			if (!IsValid(this))
			{
				RLR_LOG(LogRLR, Warning, TEXT("SkillManager is invalid during broadcast."));
				return;
			}
			UpdatedSkillSettingDelegate.Broadcast();
		});
}

void USkillManager::UpdatedItemSettingBroadcast()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			// 유효성 검사 추가
			if (!IsValid(this))
			{
				RLR_LOG(LogRLR, Warning, TEXT("SkillManager is invalid during broadcast."));
				return;
			}
			UpdatedItemSettingDelegate.Broadcast();
		});
}
