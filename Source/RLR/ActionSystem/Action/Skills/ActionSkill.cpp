// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/Action/Skills/ActionSkill.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/ActionTask/ActionTask_PlayMontage.h"
#include "ActionSystem/AnimNotify_ActivateAction.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "Player/RLRPlayerController.h"
#include "UI/InGame/Skill/TimerProgressBar.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "Structs/SkillStructs.h"

UActionSkill::UActionSkill()
{
}

void UActionSkill::ActivateActionForce(const FActionResult& ActionResult)
{
	Super::ActivateActionForce(ActionResult);
	PlayActionMontage();
}

//void UActionSkill::PlaySkillMontage()
//{
//	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
//	if (!Player) return;
//
//	UActionSystemComponent* ASC = Player->GetActionSystemComponent();
//	if (!ASC) return;
//
//	AController* Controller = Player->GetController();
//	if (!Controller) return;
//
//	FActionData Data;
//	if (ASC->GetActionData(TriggerTag, Data))
//	{
//		Controller->StopMovement();
//		Player->SetTargetRotation(Data.MousePos, RotationSpeed);
//	}
//
//	for (const auto& notify : ActionMontage->Notifies)
//	{
//		UAnimNotify_ActivateAction* noti = Cast<UAnimNotify_ActivateAction>(notify.Notify);
//		if (!noti) continue;
//
//		noti->OnTriggered.Clear();
//		noti->OnTriggered.AddUniqueDynamic(this, &ThisClass::OnAnimNotifyTriggered);
//	}
//
//	//Play Montage
//	UActionTask_PlayMontage* AT = UActionTask_PlayMontage::CreatePlayMontageTask(this, TEXT("PlaySkillAnim"), ActionMontage);
//	AT->OnCompleted.AddUniqueDynamic(this, &ThisClass::OnCompletePlayMontage);
//	AT->OnCancelled.AddUniqueDynamic(this, &ThisClass::OnCompletePlayMontage);
//
//	AT->ReadyForActivation();
//}

bool UActionSkill::PreActivateAction()
{
	if (!SkillData) SetSkillData();

	//Timer Widget 생성
	if (TimerWidgetClass)
	{
		TimerWidget = CreateWidget<UTimerProgressBar>(GetWorld(), TimerWidgetClass);
	}

	return Super::PreActivateAction();
}

void UActionSkill::ActivateAction()
{
	Super::ActivateAction();
	
	//Timer Widget 부착
	if (TimerWidget) TimerWidget->AddToViewport();
}

void UActionSkill::SetSkillData()
{
	auto* DataManager = GameInstance->GetDataManager();
	if (!DataManager) return;

	SkillData = &DataManager->GetSkillDataByTag(TriggerTag);
}