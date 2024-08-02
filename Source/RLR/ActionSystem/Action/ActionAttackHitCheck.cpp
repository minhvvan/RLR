// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/ActionAttackHitCheck.h"
#include "RLR.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionSystemInterface.h"
#include "GameManager/GameplayTagManager.h"
#include "Physics/RLRCollision.h"
#include "DrawDebugHelpers.h"
#include "GameManager/SkillManager.h"
#include "GameManager/GameManager.h"


UActionAttackHitCheck::UActionAttackHitCheck()
{
	InstancingPolicy=EActionInstancingPolicy::InstancedPerActor;
}

void UActionAttackHitCheck::ActivateAction()
{
	//사거리 Get
	//CurrentActorInfo->ActionSystemComponent->GetAttribute()
	
	//사거리에 맞게 Collision 생성(Test = 100)
	AActor* Owner = GetAvatarActorFromActorInfo();
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams params(NAME_None, false, Owner);

	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	FGameplayTag HittableTag = TagManager.Object_State_Hittable;
	USkillManager* SkillManager = GameInstance->GetSkillManager();
	if (!SkillManager)
	{
		EndAction();
		return;
	}

	//사거리에 맞게 Collision 생성(Test = 100)
	TArray<AActor*> OverlappedActor;
	if (GetWorld()->OverlapMultiByChannel(OverlapResults,	/*Result*/
		Owner->GetActorLocation(),							/*Center*/
		FQuat::Identity,									/*Rotate*/
		CCHANNEL_RLRATTACK,									/*Channel*/
		FCollisionShape::MakeSphere(100.f),					/*AttackRange*/
		params))
	{
		DrawDebugSphere(GetWorld(), Owner->GetActorLocation(), 100.f, 32.f, FColor::Green, false, 1.f, 0.f, 1.f);

		for (auto result : OverlapResults)
		{
			IActionSystemInterface* HitActor = Cast<IActionSystemInterface>(result.GetActor());
			if (!HitActor) continue;

			UActionSystemComponent* ASC = HitActor->GetActionSystemComponent();
			if (!ASC) continue;

			//Hittable Tag가 없으면 제외
			if (!ASC->HasMatchingGameplayTag(HittableTag))
			{
				RLR_LOG(LogRLR, Log, TEXT("This Actor Non-Hittable"));
				continue;
			}

			//Make TargetData
			RLR_LOG(LogRLR, Log, TEXT("Hit Actor: %s"), *result.GetActor()->GetName());

			//TODO: 판정된 Actor를 Server에 보낼 클래스 필요
			OverlappedActor.Add(result.GetActor());
		}
		//TODO: 판정된 Actor를 Server에 보낼 클래스 필요
		
		if (SkillManager->RequestSkillResult(SkillData, OverlappedActor))
		{
			
		}
		else
		{
			//fail
		}

	}
	else
	{
		//No Hit
		DrawDebugSphere(GetWorld(), Owner->GetActorLocation(), 100.f, 32.f, FColor::Red, false, 1.f, 0.f, 1.f);
	}

	EndAction();
}

void UActionAttackHitCheck::CancelAction()
{
	Super::CancelAction();
}

void UActionAttackHitCheck::EndAction()
{
	Super::EndAction();
}