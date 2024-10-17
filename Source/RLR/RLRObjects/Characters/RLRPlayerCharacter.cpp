// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRPlayerCharacter.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/MonsterManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/ObjectManager.h"
#include "GameManager/SkillManager.h"
#include "AIController.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/RLRPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Structs/PlayerStructs.h"
#include "Structs/ObjectStructs.h"
#include "RLR.h"

// Sets default values
ARLRPlayerCharacter::ARLRPlayerCharacter() :
	bShouldRotate(false),
	RotationSpeed(0.f)
{
	SetCharacterMovement();
	SetCameraArm();
	//data = CreateDefaultSubobject<APlayerData>(TEXT("Data"));
}

void ARLRPlayerCharacter::SetCameraArm()
{
	cameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	cameraArm->SetupAttachment(RootComponent);
	cameraArm->SetUsingAbsoluteRotation(true);
	cameraArm->TargetArmLength = 800.f;
	cameraArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	cameraArm->bDoCollisionTest = false;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(cameraArm, USpringArmComponent::SocketName);
	camera->bUsePawnControlRotation = false;
}

void ARLRPlayerCharacter::SetCharacterMovement()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

void ARLRPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	int inputID = 0;
	for (auto [Tag, Action] : DefaultActions)
	{
		FActionSpec Spec(Action);
		ASC->GiveAction(Tag, Spec);
	}
}

void ARLRPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<AAIController>(GetController());
}

void ARLRPlayerCharacter::SetMoveMode(EMovementMode mode)
{
	GetCharacterMovement()->SetMovementMode(mode);
}

void ARLRPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bShouldRotate)
	{
		//TargetForward로 iterpolate
		FRotator NewRot = FMath::Lerp(GetActorRotation(), TargetRotation, DeltaSeconds * RotationSpeed);
		SetActorRotation(NewRot);

		if (TargetRotation.Equals(GetActorRotation(), 10.f))
		{
			TargetRotation = FRotator::ZeroRotator;
			bShouldRotate = false;
		}
	}
}

void ARLRPlayerCharacter::SetTargetRotation(FVector TargetLoc, float Speed)
{
	TargetLoc -= GetActorLocation();
	FRotator Rotator = FRotationMatrix::MakeFromX(TargetLoc).Rotator();
	Rotator.Pitch = 0.f;

	TargetRotation = Rotator;
	RotationSpeed = Speed;
	bShouldRotate = true;
}

void ARLRPlayerCharacter::SetStat(const FUserCharacter& Stat)
{
	UStatSetPlayer* statSet = ASC->GetStatSet<UStatSetPlayer>();
	if (statSet == nullptr)
	{
		ASC->CreateStatSet<UStatSetPlayer>();
		statSet = ASC->GetStatSet<UStatSetPlayer>();
	}

	AsyncTask(ENamedThreads::GameThread, [statSet, Stat]()
		{
			statSet->SetStatData(Stat);
	statSet->UpdateStat();
		});

}

const UStatSetPlayer* ARLRPlayerCharacter::GetStat()
{
	return ASC->GetStatSet<UStatSetPlayer>();
}

void ARLRPlayerCharacter::UpdateTransform(FVector NewTransform)
{
	if (AIController)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, NewTransform);
	}
	else
	{
		AAIController* controller = Cast<AAIController>(GetController());
	}
}

void ARLRPlayerCharacter::UpdateAction(std::string tagName)
{
	if (AIController)
	{
		if (!ASC) return;

		auto TagManager = FGameplayTagManager::Get();
		auto playMontageAction = ASC->GetActionInstance(TagManager.Action_Default_PlayMontage);

		auto DataManager = GameInstance->GetDataManager();
		FGameplayTag Tag = FGameplayTag::RequestGameplayTag(FName(*FString(tagName.c_str())));

		ASC->TryActivateAction(Tag);
	}
}

void ARLRPlayerCharacter::SpawnTransform(FVector NewTransform)
{
	//플레이어 위치 설정
	AsyncTask(ENamedThreads::GameThread, [this, NewTransform]()
		{
			SetActorLocation(NewTransform);
		});

}

void ARLRPlayerCharacter::SetDead()
{
	Super::SetDead();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		//TODO: UI는 건들수있게 해야할 듯
		DisableInput(PlayerController);
	}
}