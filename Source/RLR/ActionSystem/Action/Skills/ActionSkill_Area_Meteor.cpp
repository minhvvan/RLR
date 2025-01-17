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
#include <Player/RLRPlayerController.h>

#include "NiagaraFunctionLibrary.h"
#include "Structs/SkillStructs.h"

void UActionSkill_Area_Meteor::OnAnimNotifyTriggered()
{
	//Callback 제거
	Super::OnAnimNotifyTriggered();
	
	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	ARLRPlayerController* Controller = Cast<ARLRPlayerController>(Player->GetController());
	if (!Controller) return;

	UActionSystemComponent* ASC = Player->GetActionSystemComponent();
	if (!ASC) return;

	FActionData ActionData;
	ASC->GetActionData(TriggerTag, ActionData);

	FVector EndPos = ActionData.MousePos;
	HitPoint = EndPos;
	EndPos.Z += SkillData->SkillDistance;

	if (!SkillData) return;
	USkillManager* SkillManager = GameInstance->GetSkillManager();
	if (!SkillManager)
	{
		EndAction();
		return;
	}

	ARLRProjectile* meteor = Player->GetWorld()->SpawnActorDeferred<ARLRProjectile>(MeteorProjectile, FTransform::Identity, Player);
	
	meteor->SetSkillData(MakeShared<FSkillData>(*SkillData));
	meteor->OnFinishSkill.AddDynamic(this, &UActionSkill_Area_Meteor::OnFinishSkill);
	meteor->SetFireDirection(FVector::DownVector);
	
	FTransform SpawnLoc(EndPos);
	meteor->FinishSpawning(SpawnLoc);
}


void UActionSkill_Area_Meteor::OnFinishSkill()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), GroundHitFX, HitPoint);
}