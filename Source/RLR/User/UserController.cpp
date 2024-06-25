// Fill out your copyright notice in the Description page of Project Settings.

#include "UserController.h"
#include "Player/PlayerCharacter.h"

AUserController::AUserController()
{
<<<<<<< HEAD
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	explosion = CreateDefaultSubobject<ASkill_Explosion>(TEXT("EffectContainer"));
=======
    PrimaryActorTick.bCanEverTick = true;
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;
    explosion = CreateDefaultSubobject<ASkill_Explosion>(TEXT("EffectContainer"));

    movePacketInterval = 10.0f; // 10000ms마다 이동 패킷 전송
    timeSinceLastMovePacket = 0.0f;
    lastSentPosition = FVector::ZeroVector;
>>>>>>> 052cd924b32fc4d9142365eedb59d3321ffff4c3
}

void AUserController::BeginPlay()
{
	Super::BeginPlay();

<<<<<<< HEAD
	APawn* ControlledPawn = GetPawn();
	// TODO : player name modify
	player = Cast<APlayerCharacter>(ControlledPawn);
	player->SetController();
	if (player)
	{
		AssignPlayerSeq(); // Assign player sequence ID
	}
=======
    APawn* ControlledPawn = GetPawn();
    player = Cast<APlayerCharacter>(ControlledPawn);
	  player->SetController();

    if (player)
    {
        AssignPlayerSeq(); // Assign player sequence ID
    }
>>>>>>> 052cd924b32fc4d9142365eedb59d3321ffff4c3

	if (UEnhancedInputLocalPlayerSubsystem* system = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		system->AddMappingContext(currentContext, 0);
	}

<<<<<<< HEAD
	gameClient = NewObject<AGameClient>();
	if (gameClient && !gameClient->ConnectToServer(TEXT("127.0.0.1"), TEXT("27015")))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to server"));
	}
=======
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameClient::StaticClass(), FoundActors);
    lastSentPosition = player->GetActorLocation();
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
   
>>>>>>> 052cd924b32fc4d9142365eedb59d3321ffff4c3
}

void AUserController::Tick(float DeltaTime)
{
<<<<<<< HEAD
	Super::Tick(DeltaTime);
	if (pressTime >= 1.f)
	{
		OnCursorEffect();
		pressTime = 0.f;
	}
=======
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
        FVector CurrentPosition = player->GetActorLocation();

        if (FVector::DistSquared(CurrentPosition, lastSentPosition) > KINDA_SMALL_NUMBER)
        {
            GameClient->SendMovePacket(player->GetPlayerSeq(), CurrentPosition.X, CurrentPosition.Y);
            GameClient->SendInventoryPacket(player->GetPlayerSeq());
            lastSentPosition = CurrentPosition;
        }

        timeSinceLastMovePacket = 0.0f;
    }

>>>>>>> 052cd924b32fc4d9142365eedb59d3321ffff4c3
}

void AUserController::AssignPlayerSeq()
{
	static int32 NextPlayerSeq = 1; // Static variable to keep track of the next ID

	if (player)
	{
		player->SetPlayerSeq(NextPlayerSeq);
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
		if (commands == nullptr)
		{
			commands = GetWorld()->SpawnActor<APlayerCommands>(commandClass);

			if (commands->Skill.Q == nullptr)
			{
				commands->Init();
			}
		}

		//TODO : 모든 바인딩 적용하기.
		component->BindAction(commands->Move, ETriggerEvent::Started, this, &AUserController::OnCursorEffect);
		component->BindAction(commands->Move, ETriggerEvent::Started, this, &AUserController::OnMoveStarted);
		component->BindAction(commands->Move, ETriggerEvent::Triggered, this, &AUserController::OnMove);
		component->BindAction(commands->Move, ETriggerEvent::Completed, this, &AUserController::OnMoveCompleted);

		component->BindAction(commands->Skill.Q, ETriggerEvent::Started, this, &AUserController::OnAttackEffect);
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
<<<<<<< HEAD
	pressTime += GetWorld()->GetDeltaSeconds();

	if (IsMove())
	{
		UE_LOG(LogTemp, Log, TEXT("이동 중"));
		deltaTime += GetWorld()->GetDeltaSeconds();
		player->SetMovement(GetClickPosition());
	}

	// TODO : Test Code
	if (gameClient)
	{
		gameClient->SendMovePacket(player->GetPlayerSeq(), GetClickPosition().X, GetClickPosition().Y);
	}
=======
	
  if (GameClient)
  {
    GameClient->SendMovePacket(Player->GetPlayerSeq(), GetClickPosition().X, GetClickPosition().Y);
    player->SetMovement(GetClickPosition());
	}
  
>>>>>>> 052cd924b32fc4d9142365eedb59d3321ffff4c3
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
	if (player->IsAttack())
	{
		if (explosion == nullptr)
		{
			explosion = CreateDefaultSubobject<ASkill_Explosion>(TEXT("EffectContainer"));
		}
		explosion->SkillAttack(GetClickPosition(), explosion->GetAttackParticle());
		//스킬에맞는 공격 애니메이션 
	}
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
