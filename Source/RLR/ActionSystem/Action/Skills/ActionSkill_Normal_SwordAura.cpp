// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill_Normal_SwordAura.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "Player/RLRPlayerController.h"
#include "DrawDebugHelpers.h"
#include "RLRObjects/Actors/RLRProjectile.h"
#include "GameManager/GameManager.h"
#include "GameManager/SkillManager.h"
#include "RLR.h"
#include "GameManager/RLRStruct.h"
#include "Structs/SkillStructs.h"
#include "ActionSystem/AnimNotify_ActivateAction.h"

UActionSkill_Normal_SwordAura::UActionSkill_Normal_SwordAura()
{
	InstancingPolicy = EActionInstancingPolicy::NonInstanced;
}

void UActionSkill_Normal_SwordAura::OnAnimNotifyTriggered()
{
	for (const auto& notify : ActionMontage->Notifies)
	{
		auto* noti = Cast<UAnimNotify_ActivateAction>(notify.Notify);
		if (!noti) continue;

		//TODO: 모든 Callback을 없애지 말고 해당 Callback만 제거하도록 변경되어야 함
		noti->OnTriggered.Clear();
	}

	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	UActionSystemComponent* ASC = Player->GetActionSystemComponent();
	if (!ASC) return;

	if (!SkillData) return;

	float SkillRange = SkillData->SkillDistance;
	FVector StartPos = Player->GetActorLocation();
	FVector MousePos = StartPos + Player->GetActorForwardVector() * 100;

	FActionData ActionData;
	if (ASC->GetActionData(TriggerTag, ActionData))
	{
		MousePos = ActionData.MousePos;
	}

	FVector SkillDir = (MousePos - StartPos);
	FRotator Rotator = SkillDir.ToOrientationRotator();
	Rotator.Pitch = 0.f;

	ARLRProjectile* Aura = Player->GetWorld()->SpawnActorDeferred<ARLRProjectile>(SwordAuraProjectile, FTransform::Identity, Player);
	Aura->SetSkillRange(SkillRange);
	Aura->OnFinishSkill.AddDynamic(this, &UActionSkill_Normal_SwordAura::OnFinishSkill);

	FTransform SpawnLoc(Player->GetActorLocation() + Player->GetActorForwardVector() * 50);
	SpawnLoc.SetRotation(Rotator.Quaternion());

	Aura->FinishSpawning(SpawnLoc);
}

void UActionSkill_Normal_SwordAura::OnFinishSkill(TArray<AActor*> OverlappedActor)
{
	if (!IsOtherUserAction())
	{
		USkillManager* SkillManager = GameInstance->GetSkillManager();
		if (SkillManager)
		{
			SkillManager->RequestSkillResult(SkillData, OverlappedActor);
		}
	}
}