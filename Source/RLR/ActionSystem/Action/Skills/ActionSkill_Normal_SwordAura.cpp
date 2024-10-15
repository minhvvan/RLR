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
}

void UActionSkill_Normal_SwordAura::ActivateAction()
{
	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	ARLRPlayerController* Controller = Cast<ARLRPlayerController>(Player->GetController());
	if (!Controller) return;
	
	UActionSystemComponent* ASC = Player->GetActionSystemComponent();
	if (!ASC) return;

	if (!SkillData) return;

	FActionData ActionData;
	ASC->GetActionData(TriggerTag, ActionData);

	FVector MousePos = ActionData.MousePos;

	float SkillRange = SkillData->SkillDistance;
	FVector StartPos = Player->GetActorLocation();
	FVector SkillDir = (MousePos - StartPos);
	FRotator Rotator = SkillDir.ToOrientationRotator();
	Rotator.Pitch = 0.f;

	ARLRProjectile* Aura = GetWorld()->SpawnActorDeferred<ARLRProjectile>(SwordAuraProjectile, FTransform::Identity, Player);
	Aura->SetSkillRange(SkillRange);
	Aura->OnFinishSkill.AddDynamic(this, &UActionSkill_Normal_SwordAura::OnFinishSkill);

	FTransform SpawnLoc(Player->GetActorLocation() + Player->GetActorForwardVector() * 50);
	SpawnLoc.SetRotation(Rotator.Quaternion());

	Aura->FinishSpawning(SpawnLoc);
}

void UActionSkill_Normal_SwordAura::OnFinishSkill(TArray<AActor*> OverlappedActor)
{
	USkillManager* SkillManager = GameInstance->GetSkillManager();
	if (SkillManager)
	{
		SkillManager->RequestSkillResult(SkillData, OverlappedActor);
	}

	EndAction();
}