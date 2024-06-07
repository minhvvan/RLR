// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	SetCharacterMovement();
	SetCameraArm();
	data = CreateDefaultSubobject<APlayerData>(TEXT("PlayerData"));
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
	if (data != nullptr)
	{
		data->Status.HpCurrent -= explosion->GetDamage() * data->Status.AttackDamage;
		UE_LOG(LogTemp, Log, TEXT("HP : %d"), data->Status.HpCurrent);
		UE_LOG(LogTemp, Log, TEXT("Damage : %d"), explosion->GetDamage());
		UE_LOG(LogTemp, Log, TEXT("AttackDamage : %d"), data->Status.AttackDamage);
		if (data->Status.HpCurrent <= 0)
		{
			UE_LOG(LogTemp, Log, TEXT("Destroy : %d"), data->Status.HpCurrent);

			Destroy();
		}
	}
	else
	{
		data = CreateDefaultSubobject<APlayerData>(TEXT("PlayerData"));
	}
	other->Destroy();
}

