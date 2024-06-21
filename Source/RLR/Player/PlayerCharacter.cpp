// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	SetCharacterMovement();
	SetCameraArm();
	data = CreateDefaultSubobject<APlayerData>(TEXT("Data"));
}

void APlayerCharacter::SetCameraArm()
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

void APlayerCharacter::SetCharacterMovement()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

// Check Collision Over lap
void APlayerCharacter::NotifyActorBeginOverlap(AActor* other)
{
	APlayerSkill* explosion = Cast<APlayerSkill>(other);
	// TODO : GetDamage * Stat Logic
	if (data == nullptr)
	{
		data = CreateDefaultSubobject<APlayerData>(TEXT("Data"));
	}

	data->Status.HpCurrent -= explosion->GetDamage() * data->Status.AttackDamage;

	if (data->Status.HpCurrent <= 0)
	{
		Destroy();
	}

	explosion->SetIsHit(true);
	explosion->Abnormal->ApplyAbnormal(this, explosion->GetDuration());
}

void APlayerCharacter::SetMovement(FVector location)
{
	FVector WorldDirection = (location - GetActorLocation()).GetSafeNormal();
	AddMovementInput(WorldDirection, 1.0f, false);
}

void APlayerCharacter::SetSimpleMove(APlayerController* controller, FVector goalLocation)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, goalLocation);
}

void APlayerCharacter::SetOrientation(FVector Location)
{
	Location -= GetActorLocation();
	FRotator Rotator = FRotationMatrix::MakeFromX(Location).Rotator();
	Rotator.Pitch = 0.f;
	SetActorRotation(Rotator);
}

void APlayerCharacter::SetMoveMode(EMovementMode mode)
{
	GetCharacterMovement()->SetMovementMode(mode);
}

void APlayerCharacter::BanInput(bool value)
{
	playerController->StopMovement();
	if (value == true)
	{
		playerController->DisableInput(playerController);
	}
	else
	{
		playerController->EnableInput(playerController);
	}
	
}

void APlayerCharacter::SetController()
{
	playerController = Cast<AUserController>(GetWorld()->GetFirstPlayerController());
}