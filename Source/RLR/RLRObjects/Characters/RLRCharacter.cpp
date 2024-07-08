// Copyright Epic Games, Inc. All Rights Reserved.

#include "RLRCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

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
}

UActionSystemComponent* ARLRCharacter::GetActionSystemComponent() const
{
	return ASC.Get();
}

void ARLRCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ARLRCharacter::BeginPlay()
{
	Super::BeginPlay();
}