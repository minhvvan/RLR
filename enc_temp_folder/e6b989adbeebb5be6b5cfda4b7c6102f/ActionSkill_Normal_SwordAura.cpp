// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill_Normal_SwordAura.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "Player/RLRPlayerController.h"
#include "DrawDebugHelpers.h"
#include "RLRObjects/Actors/RLRProjectile.h"
#include "GameManager/GameManager.h"
#include "GameManager/SkillManager.h"
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
	FVector StartPos = Player->GetActorLocation();
	FVector SkillDir = (MousePos - StartPos);

	FRotator Rotator = FRotationMatrix::MakeFromX(SkillDir).Rotator();
	Rotator.Pitch = 0.f;

	FVector Dir = Rotator.Vector().GetSafeNormal();

	ARLRProjectile* Aura = GetWorld()->SpawnActorDeferred<ARLRProjectile>(SwordAuraProjectile, FTransform::Identity, Player);
	Aura->SetFireDir(Dir);
	Aura->SetSkillRange(SkillRange);

	Aura->OnFinishSkill.AddDynamic(this, &UActionSkill_Normal_SwordAura::OnFinishSkill);

	FTransform SpanwLoc(Player->GetActorLocation() + Player->GetActorForwardVector() * 50);
	Aura->FinishSpawning(SpanwLoc);
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