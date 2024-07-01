// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCommands.h"
<<<<<<< Updated upstream
#include "User/UserController.h"
=======
>>>>>>> Stashed changes

APlayerCommands::APlayerCommands()
{
	PrimaryActorTick.bCanEverTick = true;
}

<<<<<<< Updated upstream
void APlayerCommands::BindDefaultAction(TObjectPtr<AUserController> Controller)
{
	UEnhancedInputComponent* component = Cast<UEnhancedInputComponent>(Controller->InputComponent);
	if (component == nullptr) return;

	component->BindAction(Move, ETriggerEvent::Started, Controller.Get(), &AUserController::OnCursorEffect);
	component->BindAction(Move, ETriggerEvent::Started, Controller.Get(), &AUserController::OnMoveStarted);
	component->BindAction(Move, ETriggerEvent::Triggered, Controller.Get(), &AUserController::OnMove);
	component->BindAction(Move, ETriggerEvent::Completed, Controller.Get(), &AUserController::OnMoveCompleted);

	component->BindAction(SPACE, ETriggerEvent::Started, Controller.Get(), &AUserController::OnJump);
	component->BindAction(Attack, ETriggerEvent::Started, Controller.Get(), &AUserController::OnAttack);
}

void APlayerCommands::BindSkillAction(TObjectPtr<class AUserController> Controller)
{
	UEnhancedInputComponent* component = Cast<UEnhancedInputComponent>(Controller->InputComponent);
	if (component == nullptr) return;

	//Commands가 Enum이면 반복문으로 코드 줄일 수 있음
	int inputID = 0;
	component->BindAction(Skill.Q, ETriggerEvent::Started, Controller.Get(), &AUserController::OnAttackEffect, inputID++);
	component->BindAction(Skill.W, ETriggerEvent::Started, Controller.Get(), &AUserController::OnAttackEffect, inputID++);
	component->BindAction(Skill.E, ETriggerEvent::Started, Controller.Get(), &AUserController::OnAttackEffect, inputID++);
	component->BindAction(Skill.R, ETriggerEvent::Started, Controller.Get(), &AUserController::OnAttackEffect, inputID++);
	component->BindAction(Skill.A, ETriggerEvent::Started, Controller.Get(), &AUserController::OnAttackEffect, inputID++);
	component->BindAction(Skill.S, ETriggerEvent::Started, Controller.Get(), &AUserController::OnAttackEffect, inputID++);
	component->BindAction(Skill.D, ETriggerEvent::Started, Controller.Get(), &AUserController::OnAttackEffect, inputID++);
	component->BindAction(Skill.F, ETriggerEvent::Started, Controller.Get(), &AUserController::OnAttackEffect, inputID++);
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
=======

void APlayerCommands::Init()
{
	// TODO : 모든 스킬 커맨드 적용할 방식 찾아 적용하기.
	ConstructorHelpers::FObjectFinder<UInputAction>container(TEXT("/Game/Player/Input/Action_SkillQ"));
	if (container.Succeeded())
	{
		Skill.Q = container.Object;
	}
}

void APlayerCommands::TestLog()
{
	UE_LOG(LogTemp, Log, TEXT("Test Log Command Key : Q"));
>>>>>>> Stashed changes
}
