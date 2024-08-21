// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill_Normal_SwordAura.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "Player/RLRPlayerController.h"
#include "DrawDebugHelpers.h"
#include "RLRObjects/Actors/RLRProjectile.h"
#include "GameManager/GameManager.h"
#include "GameManager/SkillManager.h"
#include "RLR.h"
#include "GameManager/RLRStruct.h"

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

	FActionData ActionData;
	ASC->GetActionData(TriggerTag, ActionData);

	FVector MousePos = ActionData.MousePos;

	//Test
	if (!SkillData)
	{

		UE_LOG(LogTemp, Log, TEXT("asdsagfdg"));
		return;
	}

	float SkillRange = 1000.f;
	/*FVector StartPos = Player->GetActorLocation();
	FVector SkillDir = (MousePos - StartPos);*/
	FRotator playerRotation = Player->GetActorRotation();
	playerRotation.Pitch = 0.f;
	/*FRotator Rotator = FRotationMatrix::MakeFromX(SkillDir).Rotator();
	Rotator.Pitch = 0.f;*/


	ARLRProjectile* Aura = GetWorld()->SpawnActorDeferred<ARLRProjectile>(SwordAuraProjectile, FTransform::Identity, Player);
	/*Aura->SetFireDir();*/
	Aura->SetSkillRange(SkillRange);
	Aura->OnFinishSkill.AddDynamic(this, &UActionSkill_Normal_SwordAura::OnFinishSkill);

	FTransform SpawnLoc(Player->GetActorLocation() + Player->GetActorForwardVector() * 50);
	SpawnLoc.SetRotation(playerRotation.Quaternion());

	Aura->FinishSpawning(SpawnLoc);
}

void UActionSkill_Normal_SwordAura::OnFinishSkill(TArray<AActor*> OverlappedActor)
{
	USkillManager* SkillManager = GameInstance->GetSkillManager();
	if (!SkillManager) return;

	if (SkillManager->RequestSkillResult(SkillData, OverlappedActor))
	{
		//Success
	}
	else
	{
		//fail
	}

	EndAction();
}