// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill_Normal_SwordAura.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "DrawDebugHelpers.h"

UActionSkill_Normal_SwordAura::UActionSkill_Normal_SwordAura()
{
}

void UActionSkill_Normal_SwordAura::ActivateAction()
{
	//PlayAnim
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
	float SkillRange = 400.f;

	FVector StartPos = Player->GetActorLocation();
	FVector SkillDir = (MousePos - StartPos);

	FRotator Rotator = FRotationMatrix::MakeFromX(SkillDir).Rotator();
	Rotator.Pitch = 0.f;

	FVector DirPos = SkillDir;
	DirPos.Normalize();
	DirPos *= SkillRange/2;

	FVector FinalPos = StartPos + DirPos;
	DrawDebugSphere(GetWorld(), FinalPos, 10.f, 32, FColor::Green, false, 3.f, 0U, 3.f);
	DrawDebugBox(GetWorld(), FinalPos, FVector(SkillRange, 100, 100), Rotator.Quaternion(), FColor::Blue, false, 3.f, 0U, 3.f);
}