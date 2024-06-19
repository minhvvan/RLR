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

    APawn* ControlledPawn = GetPawn();
    Player = Cast<APlayerCharacter>(ControlledPawn);
    if (Player)
    {
        AssignPlayerSeq(); // Assign player sequence ID
    }

    if (UEnhancedInputLocalPlayerSubsystem* system = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        system->AddMappingContext(currentContext, 0);
    }

    GameClient = NewObject<AGameClient>();
    if (GameClient && !GameClient->ConnectToServer(TEXT("127.0.0.1"), TEXT("27015")))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to connect to server"));
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

        component->BindAction(Commands->Move, ETriggerEvent::Started, this, &AUserController::OnCursorEffect);

        component->BindAction(Commands->Move, ETriggerEvent::Started, this, &AUserController::OnMoveStarted);
        component->BindAction(Commands->Move, ETriggerEvent::Triggered, this, &AUserController::OnMove);
        component->BindAction(Commands->Move, ETriggerEvent::Completed, this, &AUserController::OnMoveCompleted);

        component->BindAction(Commands->Skill.Q, ETriggerEvent::Started, this, &AUserController::OnAttackEffect);
        component->BindAction(Commands->Skill.Q, ETriggerEvent::Started, Commands, &APlayerCommands::TestLog);
    }
}

void AUserController::OnMoveStarted()
{
    StopMovement();
    pressTime = 0.f;
}

void AUserController::OnMove()
{
    UE_LOG(LogTemp, Log, TEXT("이동 중"));
    deltaTime += GetWorld()->GetDeltaSeconds();
    pressTime += GetWorld()->GetDeltaSeconds();
    Player->SetMovement(GetClickPosition());

    if (GameClient)
    {
        GameClient->SendMovePacket(Player->GetPlayerSeq(), GetClickPosition().X, GetClickPosition().Y);
    }
}

void AUserController::OnMoveCompleted()
{
    if (deltaTime <= 0.3f)
    {
        Player->SetSimpleMove(this, GetClickPosition());
    }
    deltaTime = 0.f;
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
