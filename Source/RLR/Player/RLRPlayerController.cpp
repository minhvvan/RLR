// Fill out your copyright notice in the Description page of Project Settings.

#include "RLRPlayerController.h"
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

#include "Player/PlayerCommands.h"
#include "Player/RLREnhancedInputComponent.h"

ARLRPlayerController::ARLRPlayerController():
	movePacketInterval(1.f),
	timeSinceLastMovePacket(1.f),
	lastSentPosition(FVector::ZeroVector)
{
    PrimaryActorTick.bCanEverTick = true;
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;
}

void ARLRPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PlayerManager = GameInstance->GetPlayerManager();
}

void ARLRPlayerController::OnPossess(APawn* InPawn)
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

void ARLRPlayerController::Tick(float DeltaTime)
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
			if (!ASC) {
				UE_LOG(LogTemp, Warning, TEXT("ASC Not in Player"));
				return;
			}
			UStatSetPlayer* statSet = ASC->GetStatSet<UStatSetPlayer>();
			if (!statSet) {
				UE_LOG(LogTemp, Warning, TEXT("statSet Not in ASC"));
				return;
			}
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

void ARLRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* system = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		system->AddMappingContext(CurrentContext, 0);
	}

	InitBinding();
}

void ARLRPlayerController::InitBinding()
{
	UEnhancedInputComponent* component = Cast<UEnhancedInputComponent>(InputComponent);
	if (component == nullptr) return;

	if (Commands == nullptr)
	{
		Commands = GetWorld()->SpawnActor<APlayerCommands>(CommandClass);
	}


	URLREnhancedInputComponent* Component = Cast<URLREnhancedInputComponent>(InputComponent);
	if (Component &&  Commands)
	{
		Component->ClearActionBindings();
		Component->ClearActionEventBindings();
		Component->ClearActionValueBindings();
		Commands->BIndInput(this);
	}
}

void ARLRPlayerController::OnMoveStarted()
{
	if (IsMove())
	{
		StopMovement();
	}

	pressTime = 0.f;
}

void ARLRPlayerController::OnMove()
{
	pressTime += GetWorld()->GetDeltaSeconds();

	if (IsMove())
	{
		deltaTime += GetWorld()->GetDeltaSeconds();
		PlayerCharacter->SetMovement(GetClickPosition());
	}
}

void ARLRPlayerController::OnMoveCompleted()
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

void ARLRPlayerController::OnCursorEffect()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Cursor, GetClickPosition(), FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

FVector ARLRPlayerController::GetClickPosition()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	return Hit.Location;
}

void ARLRPlayerController::OnDefaultAction(FGameplayTag TriggerTag)
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

void ARLRPlayerController::OnSkillStarted(FGameplayTag TriggerTag)
{
	USkillManager* SkillManager = GameInstance->GetSkillManager();
	if (SkillManager == nullptr) return;

	SkillManager->SkillAttack(TriggerTag);
}

void ARLRPlayerController::OnSkillCompleted(FGameplayTag TriggerTag)
{
	USkillManager* SkillManager = GameInstance->GetSkillManager();
	if (SkillManager == nullptr) return;

	SkillManager->SkillComplete(TriggerTag);
}

void ARLRPlayerController::OnSkillHeld(FGameplayTag TriggerTag)
{
	/*
		나중에 홀딩하는 스킬 생기면 넣어주기
	*/


}

void ARLRPlayerController::OnConsumeItem(int inputID)
{
	//Consume Item
	RLR_LOG(LogRLR, Log, TEXT("OnConsumeItem: %d"), inputID);
}

void ARLRPlayerController::OnConsumeItem(FGameplayTag InputTag)
{

}

void ARLRPlayerController::OnOpenUI(FGameplayTag InputTag)
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (GM == nullptr) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	UIManager->ToggleSubUI(InputTag);
}

bool ARLRPlayerController::IsMove()
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
