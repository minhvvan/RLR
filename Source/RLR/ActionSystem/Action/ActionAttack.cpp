// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/ActionAttack.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "Player/RLRPlayerController.h"
#include "RLR.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/SkillManager.h"
#include "GameManager/LiteralManager.h"
#include "GameManager/GameManager.h"
#include "Physics/RLRCollision.h"
#include "DrawDebugHelpers.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "Structs/PlayerStructs.h"
#include "ActionSystem/AnimNotify_ActivateAction.h"

UActionAttack::UActionAttack()
{
	InstancingPolicy = EActionInstancingPolicy::InstancedPerActor;
}

bool UActionAttack::PreActivateAction()
{
	bool bPossible = Super::PreActivateAction();

	for (const auto& notify : ActionMontage->Notifies)
	{
		UAnimNotify_ActivateAction* noti = Cast<UAnimNotify_ActivateAction>(notify.Notify);
		if (!noti) continue;

		noti->OnTriggered.AddUniqueDynamic(this, &ThisClass::OnAnimNotifyTriggered);
	}

	return bPossible;
}

void UActionAttack::ActivateAction()
{
	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	ARLRPlayerController* Controller = Cast<ARLRPlayerController>(Player->GetController());
	if (!Controller) return;

	//Set Actor Orientation
	Controller->StopMovement();
	FVector MousePos = Controller->GetClickPosition();
	Player->SetTargetRotation(MousePos, RotationSpeed);

	UActionTask_PlayMontage* AT = UActionTask_PlayMontage::CreatePlayMontageTask(this, RLRLITERAL.ActionAttack_PlayAttackAnim, Player->AttackMontage);
	AT->OnCompleted.AddDynamic(this, &UActionAttack::OnCompletePlayMontage);
	AT->ReadyForActivation();
	
	Super::ActivateAction();
}

void UActionAttack::ActivateActionForce(const FActionResult& ActionResult)
{
	Super::ActivateActionForce(ActionResult);
	PlayActionMontage();
}

void UActionAttack::CancelAction()
{
	Super::CancelAction();
}

void UActionAttack::EndAction()
{
	Super::EndAction();
}

void UActionAttack::OnAnimNotifyTriggered()
{	
	Super::OnAnimNotifyTriggered();

	if (IsOtherUserAction()) return;

	AActor* Owner = GetAvatarActorFromActorInfo();
	auto* player = Cast<ARLRPlayerCharacter>(Owner);
	if (!player)return;
	
	auto* ASC = player->GetActionSystemComponent();
	if (!ASC)return;

	auto* statSet = ASC->GetStatSet<UStatSetPlayer>();
	if (!statSet) return;

	//float attackRange = statSet->GetTotalStatus().ATTACK_RANGE;
	float attackRange = 100.f;

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

	TArray<AActor*> OverlappedActor;
	if (GetWorld()->OverlapMultiByChannel(OverlapResults,	/*Result*/
		Owner->GetActorLocation(),							/*Center*/
		FQuat::Identity,									/*Rotate*/
		CCHANNEL_RLRATTACK,									/*Channel*/
		FCollisionShape::MakeSphere(attackRange),			/*AttackRange*/
		params))
	{
		DrawDebugSphere(GetWorld(), Owner->GetActorLocation(), attackRange, 32.f, FColor::Green, false, 1.f, 0.f, 1.f);

		for (auto result : OverlapResults)
		{
			IActionSystemInterface* HitActor = Cast<IActionSystemInterface>(result.GetActor());
			if (!HitActor) continue;

			UActionSystemComponent* victimASC = HitActor->GetActionSystemComponent();
			if (!victimASC) continue;

			//Hittable Tag가 없으면 제외
			if (!victimASC->HasMatchingGameplayTag(HittableTag))
			{
				RLR_LOG(LogRLR, Log, TEXT("This Actor Non-Hittable"));
				continue;
			}

			//Make TargetData
			RLR_LOG(LogRLR, Log, TEXT("Hit Actor: %s"), *result.GetActor()->GetName());

			OverlappedActor.Add(result.GetActor());
		}

		SkillManager->RequestSkillResult(nullptr, OverlappedActor);
	}
	else
	{
		//No Hit
		DrawDebugSphere(GetWorld(), Owner->GetActorLocation(), attackRange, 32.f, FColor::Red, false, 1.f, 0.f, 1.f);
	}
}
