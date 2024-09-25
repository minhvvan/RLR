// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/AnimNotify_ActivateAction.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionSystemInterface.h"
#include "GameManager/GameManager.h"
#include "GameManager/SkillManager.h"

UAnimNotify_ActivateAction::UAnimNotify_ActivateAction()
{
}

void UAnimNotify_ActivateAction::Notify(USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp , Animation , EventReference);

	IActionSystemInterface* Owner = Cast<IActionSystemInterface>(MeshComp->GetOwner());
	if ( !Owner ) return;

	UActionSystemComponent* ASC=Owner->GetActionSystemComponent();;
	if ( !ASC ) return;

	OnTriggered.Broadcast();
	GameInstance->GetSkillManager()->SkillAttack(TriggerActionTag);
}
