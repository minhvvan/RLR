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

// Check Collision Over lap
// 몬스터, Character, Object
void ARLRPlayerCharacter::NotifyActorBeginOverlap(AActor* other)
{
	//APlayerSkill* explosion = Cast<APlayerSkill>(other);
	//if (!explosion) return;

	//// TODO : GetDamage * Stat Logic
	//if (data == nullptr)
	//{
	//	data = CreateDefaultSubobject<APlayerData>(TEXT("Data"));
	//}

	//data->Status.HpCurrent -= explosion->GetDamage() * data->Status.AttackDamage;

	//if (data->Status.HpCurrent <= 0)
	//{
	//	Destroy();
	//}

	//explosion->SetIsHit(true);
	//explosion->Abnormal->ApplyAbnormal(this, explosion->GetDuration());
	//// if (skill == fire) , skill == freeze,  또는 물리 로직 -> 데이터 서버 -> 물리 로직 적용
	//// Character.Anim = anim.hit
	//// Attakc -> Hit 체크 이후 패킷 전송 -> 		  서버 -> 데미지 처리 -> 클라에 적용 -> UI 적용
	////					               클라 -> 피격 애니메이션     

	if (other != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT(" other Actor name : %s"), *other->GetName());
	}
}

void ARLRPlayerCharacter::SetMovement(FVector location)
{
	if (ASC)
	{
		FGameplayTagManager TagManager = FGameplayTagManager::Get();
		if (ASC->HasMatchingGameplayTag(TagManager.Player_State_Attacking)) return;
	}

	FVector WorldDirection = (location - GetActorLocation()).GetSafeNormal();
	AddMovementInput(WorldDirection, 1.0f, false);
}

void ARLRPlayerCharacter::SetOrientation(FVector Location)
{
	Location -= GetActorLocation();
	FRotator Rotator = FRotationMatrix::MakeFromX(Location).Rotator();
	Rotator.Pitch = 0.f;
	SetActorRotation(Rotator);
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
	//플레이어 위치 설정
	SetActorLocation(NewTransform);
}
