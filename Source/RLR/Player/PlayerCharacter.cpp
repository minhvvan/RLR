// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "ActionSystem/ActionSystemComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	SetCharacterMovement();
	SetCameraArm();
	data = CreateDefaultSubobject<APlayerData>(TEXT("Data"));
	ASC = CreateDefaultSubobject<UActionSystemComponent>(TEXT("ASC"));
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

UActionSystemComponent* APlayerCharacter::GetActionSystem()
{
	return ASC;
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	int inputID = 0;
	for (auto [Tag, Action] : DefaultActions)
	{
		FActionSpec Spec(Action, 1, inputID++);
		ASC->GiveAction(Tag, Spec);
	}
}

// Check Collision Over lap
// 몬스터, Character, Object
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
	// if (skill == fire) , skill == freeze,  또는 물리 로직 -> 데이터 서버 -> 물리 로직 적용
	// Character.Anim = anim.hit
	// Attakc -> Hit 체크 이후 패킷 전송 -> 		  서버 -> 데미지 처리 -> 클라에 적용 -> UI 적용
	//					               클라 -> 피격 애니메이션                
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

// 모든 플레이어 Input 정지 및 해제
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
// 컨트롤러 이닛
void APlayerCharacter::SetController()
{
	playerController = Cast<AUserController>(GetWorld()->GetFirstPlayerController());
}