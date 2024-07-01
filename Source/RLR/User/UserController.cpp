<<<<<<< Updated upstream
// Fill out your copyright notice in the Description page of Project Settings.

#include "UserController.h"
#include "Player/PlayerCharacter.h"
#include "GameManager/GameManager.h"
#include "GameManager/SkillManager.h"
#include "GameManager/UIManager.h"
#include "UI/MainUI.h"
#include "UI/InGame/InGameHUD.h"
#include "RLR.h"
=======
#include "UserController.h"
>>>>>>> Stashed changes

AUserController::AUserController()
{
    PrimaryActorTick.bCanEverTick = true;
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;
<<<<<<< Updated upstream

    movePacketInterval = 10.0f; // 10000ms마다 이동 패킷 전송
    timeSinceLastMovePacket = 0.0f;
    lastSentPosition = FVector::ZeroVector;
=======
    explosion = CreateDefaultSubobject<ASkill_Explosion>(TEXT("EffectContainer"));
>>>>>>> Stashed changes
}

void AUserController::BeginPlay()
{
<<<<<<< Updated upstream
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

void AUserController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (GM == nullptr) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	AInGameHUD* HUD = Cast<AInGameHUD>(GetHUD());
	if (!HUD) return;

	UIManager->OpenMainUI(HUD->MainUIClass);
=======
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
>>>>>>> Stashed changes
}

void AUserController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (pressTime >= 1.f)
    {
        OnCursorEffect();
        pressTime = 0.f;
<<<<<<< Updated upstream

    }
    /*if (!GameClient || !Player) return;

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
    }*/
=======
    }
>>>>>>> Stashed changes
}

void AUserController::AssignPlayerSeq()
{
<<<<<<< Updated upstream
	static int32 NextPlayerSeq = 1; // Static variable to keep track of the next ID

	if (Player)
	{
		Player->SetPlayerSeq(NextPlayerSeq);
		NextPlayerSeq = (NextPlayerSeq == 1) ? 2 : 1; // Alternate between 1 and 2
	}
=======
    static int32 NextPlayerSeq = 1; // Static variable to keep track of the next ID

    if (Player)
    {
        Player->SetPlayerSeq(NextPlayerSeq);
        NextPlayerSeq = (NextPlayerSeq == 1) ? 2 : 1; // Alternate between 1 and 2
    }
>>>>>>> Stashed changes
}

void AUserController::SetupInputComponent()
{
<<<<<<< Updated upstream
	Super::SetupInputComponent();

	InitBinding();
}

void AUserController::InitBinding()
{
	UEnhancedInputComponent* component = Cast<UEnhancedInputComponent>(InputComponent);
	if (component == nullptr) return;

	if (Commands == nullptr)
	{
		Commands = GetWorld()->SpawnActor<APlayerCommands>(CommandClass);
	}

	//bind Default Action
	Commands->BindDefaultAction(this);
	Commands->BindSkillAction(this);
	Commands->BindConsumeAction(this);
	Commands->BindUserAction(this);
=======
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
>>>>>>> Stashed changes
}

void AUserController::OnMoveStarted()
{
<<<<<<< Updated upstream
	if (IsMove())
	{
		StopMovement();
	}

	pressTime = 0.f;
=======
    StopMovement();
    pressTime = 0.f;
>>>>>>> Stashed changes
}

void AUserController::OnMove()
{
<<<<<<< Updated upstream
	pressTime += GetWorld()->GetDeltaSeconds();

	if (IsMove())
	{
		deltaTime += GetWorld()->GetDeltaSeconds();
		Player->SetMovement(GetClickPosition());
	}
=======
    UE_LOG(LogTemp, Log, TEXT("이동 중"));
    deltaTime += GetWorld()->GetDeltaSeconds();
    pressTime += GetWorld()->GetDeltaSeconds();
    Player->SetMovement(GetClickPosition());

    if (GameClient)
    {
        GameClient->SendMovePacket(Player->GetPlayerSeq(), GetClickPosition().X, GetClickPosition().Y);
    }
>>>>>>> Stashed changes
}

void AUserController::OnMoveCompleted()
{
<<<<<<< Updated upstream
	if (IsMove())
	{
		if (deltaTime <= 0.3f)
		{

			Player->SetSimpleMove(this, GetClickPosition());

		}
		deltaTime = 0.f;
	}
=======
    if (deltaTime <= 0.3f)
    {
        Player->SetSimpleMove(this, GetClickPosition());
    }
    deltaTime = 0.f;
>>>>>>> Stashed changes
}

void AUserController::OnCursorEffect()
{
<<<<<<< Updated upstream
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Cursor, GetClickPosition(), FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
=======
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, cursor, GetClickPosition(), FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
>>>>>>> Stashed changes
}

FVector AUserController::GetClickPosition()
{
<<<<<<< Updated upstream
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	return Hit.Location;
}

void AUserController::OnJump()
{
	RLR_LOG(LogRLR, Log, TEXT("OnJump"));
}

void AUserController::OnAttack()
{
	RLR_LOG(LogRLR, Log, TEXT("OnAttack"));
}

void AUserController::OnAttackEffect(int inputID)
{
	if (!Player->IsAttack()) return;

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (GM == nullptr) return;

	USkillManager* SkillManager = GM->GetSkillManager();
	if (SkillManager == nullptr) return;

	SkillManager->SkillAttack(inputID, GetClickPosition());

	//스킬에맞는 공격 애니메이션
}

void AUserController::OnConsumeItem(int inputID)
{
	//Consume Item
	RLR_LOG(LogRLR, Log, TEXT("OnConsumeItem: %d"), inputID);
}

void AUserController::OnOpenUI(int inputID)
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (GM == nullptr) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	RLR_LOG(LogRLR, Log, TEXT("OnOpenUI: %d"), inputID);

	UIManager->ToggleSubUI(inputID);
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
=======
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
>>>>>>> Stashed changes
}
