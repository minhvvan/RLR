// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCommands.h"
#include "User/UserController.h"
#include "GameManager/GameplayTagManager.h"

APlayerCommands::APlayerCommands()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCommands::BindDefaultAction(TObjectPtr<AUserController> Controller)
{
	UEnhancedInputComponent* component = Cast<UEnhancedInputComponent>(Controller->InputComponent);
	if (component == nullptr) return;

	component->BindAction(Move, ETriggerEvent::Started, Controller.Get(), &AUserController::OnCursorEffect);
	component->BindAction(Move, ETriggerEvent::Started, Controller.Get(), &AUserController::OnMoveStarted);
	component->BindAction(Move, ETriggerEvent::Triggered, Controller.Get(), &AUserController::OnMove);
	component->BindAction(Move, ETriggerEvent::Completed, Controller.Get(), &AUserController::OnMoveCompleted);

	FGameplayTagManager TagManager = FGameplayTagManager::Get();

	component->BindAction(SPACE, ETriggerEvent::Started, Controller.Get(), &AUserController::OnDefaultAction, TagManager.Action_Default_Jump);
	component->BindAction(Attack, ETriggerEvent::Started, Controller.Get(), &AUserController::OnDefaultAction, TagManager.Action_Default_Attack);
}

void APlayerCommands::BindSkillAction(TObjectPtr<class AUserController> Controller)
{
	UEnhancedInputComponent* component = Cast<UEnhancedInputComponent>(Controller->InputComponent);
	if (component == nullptr) return;

	//Commands가 Enum이면 반복문으로 코드 줄일 수 있음
	int inputID = 0;

	FGameplayTagManager TagManager = FGameplayTagManager::Get();

	component->BindAction(Skill.Q, ETriggerEvent::Started, Controller.Get(), &AUserController::OnSkillStart, TagManager.Action_Skill_Q_Anim);
	component->BindAction(Skill.W, ETriggerEvent::Started, Controller.Get(), &AUserController::OnSkillStart, TagManager.Action_Skill_W_Anim);
	component->BindAction(Skill.E, ETriggerEvent::Started, Controller.Get(), &AUserController::OnSkillStart, TagManager.Action_Skill_E_Anim);
	component->BindAction(Skill.R, ETriggerEvent::Started, Controller.Get(), &AUserController::OnSkillStart, TagManager.Action_Skill_R_Anim);
	component->BindAction(Skill.A, ETriggerEvent::Started, Controller.Get(), &AUserController::OnSkillStart, TagManager.Action_Skill_A_Anim);
	component->BindAction(Skill.S, ETriggerEvent::Started, Controller.Get(), &AUserController::OnSkillStart, TagManager.Action_Skill_S_Anim);
	component->BindAction(Skill.D, ETriggerEvent::Started, Controller.Get(), &AUserController::OnSkillStart, TagManager.Action_Skill_D_Anim);
	component->BindAction(Skill.F, ETriggerEvent::Started, Controller.Get(), &AUserController::OnSkillStart, TagManager.Action_Skill_F_Anim);
}

void APlayerCommands::BindConsumeAction(TObjectPtr<class AUserController> Controller)
{
	UEnhancedInputComponent* component = Cast<UEnhancedInputComponent>(Controller->InputComponent);
	if (component == nullptr) return;

	int inputID = 0;
	component->BindAction(Consume.Num0, ETriggerEvent::Started, Controller.Get(), &AUserController::OnConsumeItem, inputID++);
	component->BindAction(Consume.Num1, ETriggerEvent::Started, Controller.Get(), &AUserController::OnConsumeItem, inputID++);
	component->BindAction(Consume.Num2, ETriggerEvent::Started, Controller.Get(), &AUserController::OnConsumeItem, inputID++);
	component->BindAction(Consume.Num3, ETriggerEvent::Started, Controller.Get(), &AUserController::OnConsumeItem, inputID++);
	component->BindAction(Consume.Num4, ETriggerEvent::Started, Controller.Get(), &AUserController::OnConsumeItem, inputID++);
	component->BindAction(Consume.Num5, ETriggerEvent::Started, Controller.Get(), &AUserController::OnConsumeItem, inputID++);
	component->BindAction(Consume.Num6, ETriggerEvent::Started, Controller.Get(), &AUserController::OnConsumeItem, inputID++);
	component->BindAction(Consume.Num7, ETriggerEvent::Started, Controller.Get(), &AUserController::OnConsumeItem, inputID++);
	component->BindAction(Consume.Num8, ETriggerEvent::Started, Controller.Get(), &AUserController::OnConsumeItem, inputID++);
	component->BindAction(Consume.Num9, ETriggerEvent::Started, Controller.Get(), &AUserController::OnConsumeItem, inputID++);
}						  

void APlayerCommands::BindUserAction(TObjectPtr<class AUserController> Controller)
{
	UEnhancedInputComponent* component = Cast<UEnhancedInputComponent>(Controller->InputComponent);
	if (component == nullptr) return;

	int inputID = 0;
	component->BindAction(User.I, ETriggerEvent::Started, Controller.Get(), &AUserController::OnOpenUI, inputID++);
	component->BindAction(User.O, ETriggerEvent::Started, Controller.Get(), &AUserController::OnOpenUI, inputID++);
	component->BindAction(User.P, ETriggerEvent::Started, Controller.Get(), &AUserController::OnOpenUI, inputID++);
	component->BindAction(User.J, ETriggerEvent::Started, Controller.Get(), &AUserController::OnOpenUI, inputID++);
	component->BindAction(User.K, ETriggerEvent::Started, Controller.Get(), &AUserController::OnOpenUI, inputID++);
	component->BindAction(User.L, ETriggerEvent::Started, Controller.Get(), &AUserController::OnOpenUI, inputID++);
	component->BindAction(User.N, ETriggerEvent::Started, Controller.Get(), &AUserController::OnOpenUI, inputID++);
	component->BindAction(User.M, ETriggerEvent::Started, Controller.Get(), &AUserController::OnOpenUI, inputID++);
	component->BindAction(User.G, ETriggerEvent::Started, Controller.Get(), &AUserController::OnOpenUI, inputID++);
	component->BindAction(User.U, ETriggerEvent::Started, Controller.Get(), &AUserController::OnOpenUI, inputID++);
	component->BindAction(User.F4, ETriggerEvent::Started, Controller.Get(), &AUserController::OnOpenUI, inputID++);
	component->BindAction(User.ESC, ETriggerEvent::Started, Controller.Get(), &AUserController::OnOpenUI, inputID++);
}
