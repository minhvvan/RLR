// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill_Holding_Skill.h"
#include <RLRObjects/Characters/RLRPlayerCharacter.h>
#include "ActionSystem/ActionSystemComponent.h"
#include "RLRObjects/Actors/RLRProjectile.h"
#include <Player/RLRPlayerController.h>
#include "GameManager/GameManager.h"
#include "GameManager/SkillManager.h"
#include "Physics/RLRCollision.h"
#include "Structs/SkillStructs.h"

void UActionSkill_Holding_Skill::OnAnimNotifyTriggered()
{
	Super::OnAnimNotifyTriggered();

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
	float SkillRange = SkillData->SkillRange.X;

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
	/* TODO : 50은 나중에 데이터 처리 */
	FTransform SpawnRange(Player->GetActorLocation() + Player->GetActorForwardVector() * 50);
	SpawnRange.SetRotation(PlayerRotation.Quaternion());
	HoldingProjectile->FinishSpawning(SpawnRange);

	TArray<AActor*> OverlappedActors;
	AActor* Owner = GetAvatarActorFromActorInfo();
	FCollisionQueryParams Params(NAME_None, false, Player);

	TArray<FOverlapResult> OverlapResults;
	if (GetWorld()->OverlapMultiByChannel(OverlapResults,			/* Result */
		HoldingProjectile->GetActorLocation(),				        /* Projectile 위치 */
		FQuat::Identity,											/* 회전 없음 */
		CCHANNEL_RLRATTACK,											/* 충돌 채널 (적절한 채널로 변경 가능) */
		FCollisionShape::MakeCapsule(SkillData->SkillRange),	/* 충돌 범위 (구형) */
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
	}

	if (SkillManager->RequestSkillResult(SkillData, OverlappedActors))
	{
		/* IActionSystemInterface와 충돌 성공 */

	}
	else
	{

	}
}
