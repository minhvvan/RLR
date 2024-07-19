// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill_Area_Meteor.h"
#include "RLR.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "RLRObjects/Actors/RLRProjectile.h"
#include "GameManager/GameManager.h"
#include "Physics/RLRCollision.h"
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

	//Test
	if (!SkillData) return;
	float SkillRange = SkillData->CollisionRange.X;

	USkillManager* SkillManager = GameInstance->GetSkillManager();
	if (!SkillManager)
	{
		EndAction();
		return;
	}

	//사거리에 맞게 Collision 생성(Test = 100)
	TArray<AActor*> OverlappedActor;
	AActor* Owner = GetAvatarActorFromActorInfo();
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams params(NAME_None, false, Owner);

	if (GetWorld()->OverlapMultiByChannel(OverlapResults,				/*Result*/
		Owner->GetActorLocation(),										/*Center*/
		FQuat::Identity,												/*Rotate*/
		CCHANNEL_RLRATTACK,												/*Channel*/
		FCollisionShape::MakeCapsule(SkillData->CollisionRange),		/*AttackRange*/
		params))
	{
		for (auto result : OverlapResults)
		{
			IActionSystemInterface* HitActor = Cast<IActionSystemInterface>(result.GetActor());
			if (!HitActor) continue;

			////Hittable Tag가 없으면 제외
			//if (!ASC->HasMatchingGameplayTag(HittableTag))
			//{
			//	RLR_LOG(LogRLR, Log, TEXT("This Actor Non-Hittable"));
			//	continue;
			//}

			OverlappedActor.Add(result.GetActor());
		}
	}
	
	if (SkillManager->RequestSkillResult(SkillData, OverlappedActor))
	{
		//Success
		DrawDebugCylinder(GetWorld(), StartPos, EndPos, SkillRange, 32, FColor::Green, false, 2.f, 0U, 3.f);
	}
	else
	{
		//fail
	}
}