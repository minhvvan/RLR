// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill_Area_Meteor.h"
#include "RLR.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "RLRObjects/Actors/RLRProjectile.h"
#include "GameManager/GameManager.h"
#include "GameManager/SkillManager.h"

void UActionSkill_Area_Meteor::ActivateAction()
{
	//TODO: Spawn Projectile || 판정
	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	AUserController* Controller = Cast<AUserController>(Player->GetController());
	if (!Controller) return;

	UActionSystemComponent* ASC = Player->GetActionSystemComponent();
	if (!ASC) return;

	FActionData ActionData;
	ASC->GetActionData(TriggerTag, ActionData);

	FVector StartPos = ActionData.MousePos;
	FVector EndPos = ActionData.MousePos;
	EndPos.Z += 500.f;

	DrawDebugSphere(GetWorld(), StartPos, 10.f, 32, FColor::Red, false, 3.f, 0U, 3.f);
	DrawDebugSphere(GetWorld(), EndPos, 10.f, 32, FColor::Red, false, 3.f, 0U, 3.f);

	//Test
	if (!SkillData) return;
	float SkillRange = SkillData->CollisionRange.X;

	DrawDebugCylinder(GetWorld(), StartPos, EndPos, SkillRange, 32, FColor::Red, false, 2.f, 0U, 3.f);

	EndAction();
}