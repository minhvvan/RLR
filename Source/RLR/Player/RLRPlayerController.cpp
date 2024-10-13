// Fill out your copyright notice in the Description page of Project Settings.

#include "RLRPlayerController.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "GameManager/GameManager.h"
#include "GameManager/SkillManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/RLRStruct.h"
#include "GameManager/NetworkManager.h"
#include "Network/Handler/ClientPacketHandler.h"
#include "Structs/UtilStructs.h"
#include "UI/MainUI.h"
#include "UI/InGame/InGameHUD.h"
#include "UI/InGame/OtherUser/OtherPlayerMenu.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "RLR.h"
#include "Player/PlayerCommands.h"
#include "Player/RLREnhancedInputComponent.h"
#include "Physics/RLRCollision.h"
#include "Structs/UtilStructs.h"
#include "Structs/PlayerStructs.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"

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

	//Set PlayerCharacter
	PlayerCharacter = Cast<ARLRPlayerCharacter>(InPawn);
}

void ARLRPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	if (!PlayerManager || !Player) return;

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
		Commands->BindInput(this);
	}
}

void ARLRPlayerController::OnInput()
{
	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	GameInstance->GetUIManager()->CloseSubUI(TagManager.UI_OtherPlayerMenu);
}

void ARLRPlayerController::OnMoveStarted(FGameplayTag TriggerTag)
{
	UActionSystemComponent* ASC = PlayerCharacter->GetActionSystemComponent();
	if (!ASC) return;

	FActionData actionData;
	actionData.MousePos = GetClickPosition();
	actionData.TriggerType = EInputTriggerType::TRIGGER_START;
	ASC->AddActionData(TriggerTag, actionData);

	ASC->TryActivateAction(TriggerTag);
}

void ARLRPlayerController::OnMove(FGameplayTag TriggerTag)
{
	UActionSystemComponent* ASC = PlayerCharacter->GetActionSystemComponent();
	if (!ASC) return;

	FActionData actionData;
	actionData.MousePos = GetClickPosition();
	actionData.TriggerType = EInputTriggerType::TRIGGER_TRIGGER;
	ASC->AddActionData(TriggerTag, actionData);

	ASC->TryActivateAction(TriggerTag);
}

void ARLRPlayerController::OnMoveCompleted(FGameplayTag TriggerTag)
{
	UActionSystemComponent* ASC = PlayerCharacter->GetActionSystemComponent();
	if (!ASC) return;

	FActionData actionData;
	actionData.MousePos = GetClickPosition();
	actionData.TriggerType = EInputTriggerType::TRIGGER_COMPLETE;
	ASC->AddActionData(TriggerTag, actionData);

	ASC->TryActivateAction(TriggerTag);
}

void ARLRPlayerController::OnUserClick()
{
	FHitResult Hit;
	GetHitResultUnderCursor(CCHANNEL_RLRUSERCLICK, true, Hit);

	if (auto otherUser = Cast<ARLRPlayerCharacter>(Hit.GetActor()))
	{
		FGameplayTagManager TagManager = FGameplayTagManager::Get();
		auto UIManger = GameInstance->GetUIManager();
		auto otherUserMenu = Cast<UOtherPlayerMenu>(UIManger->GetUI(EUIType::OTHER_PLAYER_MENU));
		if (otherUserMenu)
		{
			auto asc = otherUser->GetActionSystemComponent();
			auto statSet = asc->GetStatSet<UStatSetPlayer>();
			if (!statSet) return;

			FUserCharacter* otherUserData = statSet->GetStatData();
			otherUserMenu->SetOtherUserData(MakeShared<FUserCharacter>(*otherUserData));
		}

		UIManger->SetSubUIPosition(TagManager.UI_OtherPlayerMenu, UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()));
		OnOpenUI(TagManager.UI_OtherPlayerMenu);
	}
}

FVector ARLRPlayerController::GetClickPosition()
{
	FHitResult Hit;
	GetHitResultUnderCursor(CCHANNEL_RLRMOVE, true, Hit);
	return Hit.Location;
}

void ARLRPlayerController::OnDefaultAction(FGameplayTag TriggerTag)
{
	UActionSystemComponent* ASC = PlayerCharacter->GetActionSystemComponent();
	if (!ASC) return;

	FActionData actionData;
	actionData.MousePos = GetClickPosition();
	actionData.TriggerType = EInputTriggerType::TRIGGER_COMPLETE;
	ASC->AddActionData(TriggerTag, actionData);

	//Active Skill Check
	if (ASC->ActivateWaitAction())
	{
		return;
	}

	UNetworkManager* NetworkManager = GameInstance->GetNetworkManager();
	NetworkManager->SendActionPacket(PlayerCharacter->GetPlayerSeq(), TCHAR_TO_UTF8(*TriggerTag.GetTagName().ToString()));
	ASC->TryActivateAction(TriggerTag);
}

void ARLRPlayerController::OnSkillStarted(FGameplayTag TriggerTag)
{
	USkillManager* SkillManager = GameInstance->GetSkillManager();
	if (SkillManager == nullptr) return;
	SkillManager->SkillStart(TriggerTag);
	
	UNetworkManager* NetworkManager = GameInstance->GetNetworkManager();
	NetworkManager->SendActionPacket(PlayerCharacter->GetPlayerSeq(),TCHAR_TO_UTF8(*TriggerTag.GetTagName().ToString()));
	
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
	//TODO: Action 내부에서 처리가능(확인하면 삭제)
}

void ARLRPlayerController::OnConsumeItem(int inputID)
{
	//Consume Item
	RLR_LOG(LogRLR, Log, TEXT("OnConsumeItem: %d"), inputID);
}

void ARLRPlayerController::OnConsumeItem(FGameplayTag InputTag)
{
	USkillManager* SkillManager = GameInstance->GetSkillManager();
	if (SkillManager == nullptr) return;

	SkillManager->UsingItem(InputTag);	
}

void ARLRPlayerController::OnOpenUI(FGameplayTag InputTag)
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (GM == nullptr) return;

	UUIManager* UIManager = GM->GetUIManager();
	if (UIManager == nullptr) return;

	UIManager->ToggleSubUI(InputTag);
	soundEvent.Broadcast();;
}

void ARLRPlayerController::OnActionStart(FGameplayTag InputTag)
{
	if (!PlayerCharacter) return;

	UActionSystemComponent* ASC =  PlayerCharacter->GetActionSystemComponent();
	if (!ASC) return;

	ASC->TryActivateAction(InputTag);
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
