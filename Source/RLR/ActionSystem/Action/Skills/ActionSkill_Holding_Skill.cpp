// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill_Holding_Skill.h"
#include <RLRObjects/Characters/RLRPlayerCharacter.h>
#include "ActionSystem/ActionSystemComponent.h"
#include "RLRObjects/Actors/RLRProjectile.h"
#include <Player/RLRPlayerController.h>
#include "GameManager/GameManager.h"
#include "GameManager/SkillManager.h"
#include <Physics/RLRCollision.h>


void UActionSkill_Holding_Skill::ActivateAction()
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

	if (!SkillData) return;
	float SkillRange = SkillData->CollisionRange.X;

	USkillManager* SkillManager = GameInstance->GetSkillManager();
	if (!SkillManager)
	{
		EndAction();
		return;
	}

	FRotator PlayerRotation = Player->GetActorRotation();
	PlayerRotation.Pitch = 0.f;

	ARLRProjectile* HoldingProjectile = GetWorld()->SpawnActorDeferred<ARLRProjectile>(HoldingSkillProjectile, FTransform::Identity, Player);
	HoldingProjectile->SetSkillRange(SkillRange);

	FTransform SpawnLocation(Player->GetActorLocation() + Player->GetActorForwardVector() * 50);
	SpawnLocation.SetRotation(PlayerRotation.Quaternion());
	HoldingProjectile->FinishSpawning(SpawnLocation);


	TArray<AActor*> OverlappedActors;
	AActor* Owner = GetAvatarActorFromActorInfo();
	FCollisionQueryParams Params(NAME_None, false, Player);
	/* 서버 연결해서 데미지 들어가는지 확인해야 함 */
	TArray<FOverlapResult> OverlapResults;
	if (GetWorld()->OverlapMultiByChannel(OverlapResults,			/* Result */
		HoldingProjectile->GetActorLocation(),				        /* Projectile 위치 */
		FQuat::Identity,											/* 회전 없음 */
		CCHANNEL_RLRATTACK,											/* 충돌 채널 (적절한 채널로 변경 가능) */
		FCollisionShape::MakeCapsule(SkillData->CollisionRange),	/* 충돌 범위 (구형) */
		Params))
	{
		for (const FOverlapResult& Result : OverlapResults)
		{
			IActionSystemInterface* HitActor = Cast<IActionSystemInterface>(Result.GetActor());
			if (!HitActor) continue;
			/* projectile 간 충돌 무시 */
			ARLRProjectile* HitProjectile = Cast<ARLRProjectile>(Result.GetActor());
			if (HitProjectile == HoldingProjectile) continue;

			OverlappedActors.Add(Result.GetActor());
		}

		if (SkillManager->RequestSkillResult(SkillData, OverlappedActors))
		{
			// 스킬 처리 성공
			UE_LOG(LogTemp, Log, TEXT("ActionSkill_Holding_Skill: Skill result applied to overlapped actors."));
		}
		else
		{
			// 스킬 처리 실패
			UE_LOG(LogTemp, Warning, TEXT("ActionSkill_Holding_Skill: Skill result application failed."));
		}
	}
}
