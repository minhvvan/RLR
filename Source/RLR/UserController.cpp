// Fill out your copyright notice in the Description page of Project Settings.


#include "UserController.h"

AUserController::AUserController()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	explosion = CreateDefaultSubobject<ASkill_Explosion>(TEXT("EffectContainer"));

}

void AUserController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* system = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		system->AddMappingContext(currentContext, 0);
	}
}

void AUserController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (pressTime >= 1.f)
	{
		OnCursorEffect(GetClickPosition());
		pressTime = 0.f;
	}
}

void AUserController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* component = Cast<UEnhancedInputComponent>(InputComponent))
	{
		component->BindAction(move, ETriggerEvent::Started, this, &AUserController::OnMoveStarted);
		component->BindAction(move, ETriggerEvent::Triggered, this, &AUserController::OnMoveTriggered);
		component->BindAction(move, ETriggerEvent::Completed, this, &AUserController::OnMoveCompleted);
		
		component->BindAction(defalutAttack, ETriggerEvent::Started, this, &AUserController::OnAttackStarted);
	}
}


void AUserController::OnMoveStarted()
{
	StopMovement();
	OnCursorEffect(GetClickPosition());
}
void AUserController::OnMoveTriggered()
{
	OnMove();
}
void AUserController::OnMoveCompleted()
{
	if (deltaTime <= 0.3f)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, GetClickPosition());
	}
	deltaTime = 0.f;
}

void AUserController::OnAttackStarted()
{
	OnAttackEffect();
}

void AUserController::OnMove()
{
	deltaTime += GetWorld()->GetDeltaSeconds();
	pressTime += GetWorld()->GetDeltaSeconds();
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (GetClickPosition() - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AUserController::OnCursorEffect(FVector position)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, cursor, position, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

void AUserController::OnAttackEffect()
{
	if (explosion)
	{
		explosion->SkillAttack(GetClickPosition(), explosion->GetAttackParticle());
	}
}
FVector AUserController::GetClickPosition()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	return Hit.Location;
}
