// Fill out your copyright notice in the Description page of Project Settings.

#include "UserController.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "GameManager/GameManager.h"
#include "GameManager/SkillManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/RLRStruct.h"
#include "UI/MainUI.h"
#include "UI/InGame/InGameHUD.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "NiagaraFunctionLibrary.h"
#include "Player/PlayerCommands.h"
#include "EnhancedInputComponent.h"
#include "RLR.h"

AUserController::AUserController():
	movePacketInterval(1.f),
	timeSinceLastMovePacket(1.f),
	lastSentPosition(FVector::ZeroVector)
{
    PrimaryActorTick.bCanEverTick = true;
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;
}

void AUserController::BeginPlay()
{
	Super::BeginPlay();
	PlayerManager = GameInstance->GetPlayerManager();
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

	//Set PlayerCharacter
	PlayerCharacter = Cast<ARLRPlayerCharacter>(InPawn);
}

void AUserController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	if (!PlayerManager || !Player) return;

	if (pressTime >= 1.f)
    {
        OnCursorEffect();
        pressTime = 0.f;
    }

    timeSinceLastMovePacket += DeltaTime;
    if (timeSinceLastMovePacket >= movePacketInterval)
    {
        FVector CurrentPosition = PlayerCharacter->GetActorLocation();

        if (FVector::DistSquared(CurrentPosition, lastSentPosition) > KINDA_SMALL_NUMBER)
        {
			UActionSystemComponent* ASC = PlayerCharacter->GetActionSystemComponent();
			if (!ASC) return;

			UStatSetPlayer* statSet = ASC->GetStatSet<UStatSetPlayer>();
			if (!statSet) return;

			FMoveResult moveResult;
			moveResult.UserSeq = statSet->GetUserSeq();
			moveResult.MapId = statSet->GetMapId();
			moveResult.ChannelId = statSet->GetChannelId();
			moveResult.TargetTransform = CurrentPosition;

			if (PlayerManager->RequestMove(moveResult))
			{
				lastSentPosition = CurrentPosition;
			}
        }

        timeSinceLastMovePacket = 0.0f;
    }
}

void AUserController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* system = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		system->AddMappingContext(CurrentContext, 0);
	}

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
		PlayerCharacter->SetMovement(GetClickPosition());
	}
}

void AUserController::OnMoveCompleted()
{
	if (IsMove())
	{
		if (deltaTime <= 0.3f)
		{
			PlayerCharacter->SetSimpleMove(this, GetClickPosition());
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

void AUserController::OnDefaultAction(FGameplayTag TriggerTag)
{
	UActionSystemComponent* ASC = PlayerCharacter->GetActionSystemComponent();
	if (!ASC) return;

	//Active Skill Check
	if (ASC->ActivateWaitAction())
	{
		return;
	}

	ASC->TryActivateAction(TriggerTag);
}

void AUserController::OnSkillStarted(FGameplayTag TriggerTag)
{
	USkillManager* SkillManager = GameInstance->GetSkillManager();
	if (SkillManager == nullptr) return;

	SkillManager->SkillAttack(TriggerTag);
}

void AUserController::OnSkillCompleted(FGameplayTag TriggerTag)
{
	USkillManager* SkillManager = GameInstance->GetSkillManager();
	if (SkillManager == nullptr) return;

	SkillManager->SkillComplete(TriggerTag);
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
	if (PlayerCharacter->GetCharacterMovement()->MovementMode == MOVE_Walking)
	{
		return true;
	}
	else
	{
		return false;
	}
}
