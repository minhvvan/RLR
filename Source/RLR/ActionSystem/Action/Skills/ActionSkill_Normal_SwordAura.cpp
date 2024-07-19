// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill_Normal_SwordAura.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "RLRObjects/Actors/RLRProjectile.h"
#include "GameManager/GameManager.h"
#include "GameManager/SkillManager.h"

UActionSkill_Normal_SwordAura::UActionSkill_Normal_SwordAura()
{
}

void UActionSkill_Normal_SwordAura::ActivateAction()
{
	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	AUserController* Controller = Cast<AUserController>(Player->GetController());
	if (!Controller) return;
	
	UActionSystemComponent* ASC = Player->GetActionSystemComponent();
	if (!ASC) return;

	FActionData ActionData;
	ASC->GetActionData(TriggerTag, ActionData);

	FVector MousePos = ActionData.MousePos;

	//Test
	if (!SkillData) return;
	float SkillRange = SkillData->CollisionRange.X;

	FVector StartPos = Player->GetActorLocation();
	FVector SkillDir = (MousePos - StartPos);

	FRotator Rotator = FRotationMatrix::MakeFromX(SkillDir).Rotator();
	Rotator.Pitch = 0.f;

	FVector Dir = Rotator.Vector().GetSafeNormal();

	ARLRProjectile* Aura = GetWorld()->SpawnActorDeferred<ARLRProjectile>(SwordAuraProjectile, FTransform::Identity, Player);
	Aura->SetFireDir(Dir);
	Aura->SetSkillRange(SkillRange);

	DrawDebugSphere(GetWorld(), StartPos + Dir * SkillRange, 10.f, 32, FColor::Red, false, 3.f, 0U, 3.f);

	FTransform SpanwLoc(Player->GetActorLocation() + Player->GetActorForwardVector() * 50);
	Aura->FinishSpawning(SpanwLoc);

	EndAction();
}