// Fill out your copyright notice in the Description page of Project Settings.


#include "UserController.h"
#include "Player/PlayerCharacter.h"

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

	APawn* ControlledPawn = GetPawn();
	player = Cast<APlayerCharacter>(ControlledPawn);

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
		OnCursorEffect();
		pressTime = 0.f;
	}
}
void AUserController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* component = Cast<UEnhancedInputComponent>(InputComponent))
	{
		InitBinding(component);
	}
}

void AUserController::InitBinding(UEnhancedInputComponent* component)
{
	component = Cast<UEnhancedInputComponent>(InputComponent);

	if (component != nullptr)
	{
		if (commands == nullptr)
		{
			commands = GetWorld()->SpawnActor<APlayerCommands>(commandClass);

			if (commands->Skill.Q == nullptr)
			{
				commands->Init();
			}
		}

		component->BindAction(commands->Move, ETriggerEvent::Started, this, &AUserController::OnCursorEffect);
		component->BindAction(commands->Move, ETriggerEvent::Started, this, &AUserController::OnMoveStarted);
		component->BindAction(commands->Move, ETriggerEvent::Triggered, this, &AUserController::OnMove);
		component->BindAction(commands->Move, ETriggerEvent::Completed, this, &AUserController::OnMoveCompleted);

		component->BindAction(commands->Skill.Q, ETriggerEvent::Started, this, &AUserController::OnAttackEffect);
		//TODO : 테스트 이후 스킬로 적용
		component->BindAction(commands->Skill.W, ETriggerEvent::Started, this, &AUserController::SetPlayerMove);
		//TODO : 모든 바인딩 적용하기.
	}
}

void AUserController::OnMoveStarted()
{
	if (IsMove())
	{
		StopMovement();
	}

	pressTime = 0.f;
}
void AUserController::OnMove()
{
	pressTime += GetWorld()->GetDeltaSeconds();
	
	if (IsMove())
	{
		deltaTime += GetWorld()->GetDeltaSeconds();
		player->SetMovement(GetClickPosition());
	}
}
void AUserController::OnMoveCompleted()
{
	if (IsMove())
	{
		if (deltaTime <= 0.3f)
		{
			player->SetSimpleMove(this, GetClickPosition());
		}

		deltaTime = 0.f;
	}
}

void AUserController::OnCursorEffect()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, cursor, GetClickPosition(), FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

FVector AUserController::GetClickPosition()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	return Hit.Location;
}

void AUserController::OnAttackEffect()
{
	if (explosion == nullptr)
	{
		explosion = CreateDefaultSubobject<ASkill_Explosion>(TEXT("EffectContainer"));
	}
	explosion->SkillAttack(GetClickPosition(), explosion->GetAttackParticle());
}

bool AUserController::IsMove()
{
	if (player->GetCharacterMovement()->MovementMode == MOVE_Walking)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// TODO : 테스트 이후 삭제
void AUserController::SetPlayerMove()
{
	player->SetMoveMode(MOVE_Walking);
}