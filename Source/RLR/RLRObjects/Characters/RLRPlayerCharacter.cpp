// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRPlayerCharacter.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "GameManager/GameplayTagManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/MonsterManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/ObjectManager.h"
#include "GameManager/SkillManager.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/RLRPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Structs/PlayerStructs.h"
#include "Structs/ObjectStructs.h"
#include "RLR.h"

// Sets default values
ARLRPlayerCharacter::ARLRPlayerCharacter():
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

	if (TargetLocation != FVector::ZeroVector)
	{
		FVector CurrentLocation = GetActorLocation();

		UE_LOG(LogTemp, Log, TEXT("타겟 로케이션 동작중"));

		// 보간을 사용하여 현재 위치에서 목표 위치로 부드럽게 이동
		float InterpSpeed = 5.0f; // 이동 속도 설정
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaSeconds, InterpSpeed);

		// 새로운 위치로 설정
		SetActorLocation(NewLocation);

		// 목표 위치에 거의 도달하면 위치 업데이트 중지
		if (FVector::Dist(NewLocation, TargetLocation) < 1.0f)
		{
			TargetLocation = FVector::ZeroVector;
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
	//플레이어 위치 설정
	AsyncTask(ENamedThreads::GameThread, [this, NewTransform]()
		{

			ARLRPlayerController* controller = Cast<ARLRPlayerController>(GetController());
	controller->SimpleMove(NewTransform);
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