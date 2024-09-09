// Copyright Epic Games, Inc. All Rights Reserved.

#include "RLRCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSet.h"
#include "UI/ASCWidgetComponent.h"
#include "UI/InGame/CharacterDisplay/CharacterStatDisplay.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "RLR.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ARLRCharacter::ARLRCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Set Mesh Transform
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f , 0.f , -90.f) , FRotator(0.f , -90.f , 0.f));

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->MaxAcceleration = 1000.f;
	GetCharacterMovement()->BrakingDecelerationWalking= 1000.f;
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	ASC = CreateDefaultSubobject<UActionSystemComponent>(TEXT("ASC"));

	StatDisplay = CreateDefaultSubobject<UASCWidgetComponent>(TEXT("StatDisplay"));
	StatDisplay->SetupAttachment(RootComponent);
	StatDisplay->SetRelativeLocation(FVector(0.f, 0.f, 50.f));

	StatDisplay->SetWidgetSpace(EWidgetSpace::Screen);
	StatDisplay->SetDrawSize({ 150.f, 150.f });
}

UActionSystemComponent* ARLRCharacter::GetActionSystemComponent() const
{
	return ASC.Get();
}

void ARLRCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ARLRCharacter::DisplayAbnormalText(const FString AbnormalText)
{
	UCharacterStatDisplay* statDisplay = Cast<UCharacterStatDisplay>(StatDisplay->GetWidget());
	if (!statDisplay) return;

	statDisplay->ShowAbnormal(AbnormalText);
}

void ARLRCharacter::DisplayAbnormalFX(UNiagaraSystem* AbnormalFX)
{
	//show off
	if (AbnormalNiagaraComp) AbnormalNiagaraComp->Deactivate();
	if (AbnormalFX == nullptr) return;

	AbnormalNiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(AbnormalFX, GetMesh(), TEXT("Socket_Abnormal"), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
	if (AbnormalNiagaraComp) AbnormalNiagaraComp->Activate();
}

void ARLRCharacter::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);
}

void ARLRCharacter::SetRevive()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	SetActorEnableCollision(true);
}

void ARLRCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARLRCharacter::PlayDeadAnimation()
{
	if (DeadMontage.IsNull()) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage, 1.0f);
}