// Fill out your copyright notice in the Description page of Project Settings.

#include "UserController.h"
#include "Player/PlayerCharacter.h"

AUserController::AUserController()
{
    PrimaryActorTick.bCanEverTick = true;
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;
    Explosion = CreateDefaultSubobject<ASkill_Explosion>(TEXT("EffectContainer"));

    movePacketInterval = 10.0f; // 10000ms마다 이동 패킷 전송
    timeSinceLastMovePacket = 0.0f;
    lastSentPosition = FVector::ZeroVector;
}

void AUserController::BeginPlay()
{
	Super::BeginPlay();

	APawn* ControlledPawn = GetPawn();
	Player = Cast<APlayerCharacter>(ControlledPawn);
	Player->SetController();
	if (Player)
	{
		AssignPlayerSeq(); // Assign player sequence ID
	}

	if (UEnhancedInputLocalPlayerSubsystem* system = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		system->AddMappingContext(CurrentContext, 0);
	}

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameClient::StaticClass(), FoundActors);
    lastSentPosition = Player->GetActorLocation();
    if (FoundActors.Num() > 0)

    {
        GameClient = Cast<AGameClient>(FoundActors[0]);
        if (GameClient)
        {
            UE_LOG(LogTemp, Log, TEXT("GameClient 객체를 찾았습니다."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("GameClient 객체를 찾지 못했습니다."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("APlayerCharacter 클래스를 가진 객체가 없습니다."));
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
    if (!GameClient || !Player) return;

    timeSinceLastMovePacket += DeltaTime;

    if (timeSinceLastMovePacket >= movePacketInterval)
    {
        FVector CurrentPosition = Player->GetActorLocation();

        if (FVector::DistSquared(CurrentPosition, lastSentPosition) > KINDA_SMALL_NUMBER)
        {
            GameClient->SendMovePacket(Player->GetPlayerSeq(), CurrentPosition.X, CurrentPosition.Y);
            GameClient->SendInventoryPacket(Player->GetPlayerSeq());
            lastSentPosition = CurrentPosition;
        }

        timeSinceLastMovePacket = 0.0f;
    }
}

void AUserController::AssignPlayerSeq()
{
	static int32 NextPlayerSeq = 1; // Static variable to keep track of the next ID

	if (Player)
	{
		Player->SetPlayerSeq(NextPlayerSeq);
		NextPlayerSeq = (NextPlayerSeq == 1) ? 2 : 1; // Alternate between 1 and 2
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
		if (Commands == nullptr)
		{
			Commands = GetWorld()->SpawnActor<APlayerCommands>(CommandClass);

			if (Commands->Skill.Q == nullptr)
			{
				Commands->Init();
			}
		}

		//TODO : 모든 바인딩 적용하기.
		component->BindAction(Commands->Move, ETriggerEvent::Started, this, &AUserController::OnCursorEffect);
		component->BindAction(Commands->Move, ETriggerEvent::Started, this, &AUserController::OnMoveStarted);
		component->BindAction(Commands->Move, ETriggerEvent::Triggered, this, &AUserController::OnMove);
		component->BindAction(Commands->Move, ETriggerEvent::Completed, this, &AUserController::OnMoveCompleted);

		component->BindAction(Commands->Skill.Q, ETriggerEvent::Started, this, &AUserController::OnAttackEffect);
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
		UE_LOG(LogTemp, Log, TEXT("이동 중"));
		deltaTime += GetWorld()->GetDeltaSeconds();
		Player->SetMovement(GetClickPosition());

		if (GameClient)
		{
			GameClient->SendMovePacket(Player->GetPlayerSeq(), GetClickPosition().X, GetClickPosition().Y);
		}
	}
}

void AUserController::OnMoveCompleted()
{

	if (IsMove())
	{
		if (deltaTime <= 0.3f)
		{

			Player->SetSimpleMove(this, GetClickPosition());

		}
		deltaTime = 0.f;
	}
}

void AUserController::OnCursorEffect()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Cursor, GetClickPosition(), FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

FVector AUserController::GetClickPosition()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	return Hit.Location;
}

void AUserController::OnAttackEffect()
{
	if (Player->IsAttack())
	{
		if (Explosion == nullptr)
		{
			Explosion = CreateDefaultSubobject<ASkill_Explosion>(TEXT("EffectContainer"));
		}
		Explosion->SkillAttack(GetClickPosition(), Explosion->GetAttackParticle());
		//스킬에맞는 공격 애니메이션 
	}
}

bool AUserController::IsMove()
{
	if (Player->GetCharacterMovement()->MovementMode == MOVE_Walking)
	{
		return true;
	}
	else
	{
		return false;
	}
}
