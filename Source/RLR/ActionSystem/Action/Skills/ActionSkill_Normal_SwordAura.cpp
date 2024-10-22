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

UActionSkill_Normal_SwordAura::UActionSkill_Normal_SwordAura()
{
	InstancingPolicy = EActionInstancingPolicy::NonInstanced;
}

void UActionSkill_Normal_SwordAura::OnAnimNotifyTriggered()
{
	Super::OnAnimNotifyTriggered();

	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	UActionSystemComponent* ASC = Player->GetActionSystemComponent();
	if (!ASC) return;

	if (!SkillData) return;

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
	
	Aura->SetSkillData(MakeShared<FSkillData>(*SkillData));
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