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

UActionSkill::UActionSkill():
	RotationSpeed(10.f)
{
}

void UActionSkill::PlaySkillMontage()
{
	ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!Player) return;

	UActionSystemComponent* ASC = Player->GetActionSystemComponent();
	if (!ASC) return;

	ARLRPlayerController* Controller = Cast<ARLRPlayerController>(Player->GetController());
	if (Controller)
	{
		//Set Actor Orientation
		Controller->StopMovement();
		FVector MousePos = Controller->GetClickPosition();
		Player->SetTargetRotation(MousePos, RotationSpeed);

		FActionData Data;
		Data.MousePos = MousePos;
		ASC->AddActionData(FollowTriggerTag, Data);
	}

	for (const auto& notify : SkillAnim->Notifies)
	{
		UAnimNotify_ActivateAction* noti = Cast<UAnimNotify_ActivateAction>(notify.Notify);
		if (!noti) continue;

		noti->OnTriggered.AddDynamic(this, &ThisClass::OnAnimNotifyTriggered);
	}

	//Play Montage
	UActionTask_PlayMontage* AT = UActionTask_PlayMontage::CreatePlayMontageTask(this, TEXT("PlaySkillAnim"), SkillAnim);
	AT->OnCompleted.AddDynamic(this, &ThisClass::OnCompletePlayMontage);
	AT->OnCancelled.AddDynamic(this, &ThisClass::OnCompletePlayMontage);

	AT->ReadyForActivation();
}

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

void UActionSkill::OnCompletePlayMontage()
{
	EndAction();
}

void UActionSkill::SetSkillData()
{
	auto* DataManager = GameInstance->GetDataManager();
	if (!DataManager) return;

	SkillData = &DataManager->GetSkillDataByTag(TriggerTag);
}