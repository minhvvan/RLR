// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLRObjects/Characters/RLRCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "User/UserController.h"
#include "Camera/CameraComponent.h"
#include "Skill/Skill_Explosion.h"
#include "Player/PlayerData.h"
#include "RLRPlayerCharacter.generated.h"

class UAction;

UCLASS()
class RLR_API ARLRPlayerCharacter : public ARLRCharacter
{
	GENERATED_BODY()

public:
	ARLRPlayerCharacter();
	void SetMovement(FVector);
	void SetSimpleMove(APlayerController*, FVector);
	void SetOrientation(FVector);
	void SetMoveMode(EMovementMode);
	void BanInput(bool);
	void SetController();
	void SetIsAttack(bool value) { bIsAttack = value; };
	bool IsAttack() { return bIsAttack; };

	int32 GetPlayerSeq() const { return PlayerSeq; }
	void SetPlayerSeq(int32 Seq) { PlayerSeq = Seq; }

	virtual void Tick(float DeltaSeconds) override;
	void SetTargetRotation(FVector TargetLoc, float Speed = 1);

	void SetStat(const FUserCharacter& Stat);
	void UpdateTransform(FVector NewTransform);

private:

	FORCEINLINE class UCameraComponent* GetTopDown() const { return camera; };
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return cameraArm; };

	APlayerData* data;
	int32 PlayerSeq;
	
	UPROPERTY();
	AUserController* playerController;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"));
	class UCameraComponent* camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"));
	class USpringArmComponent* cameraArm;

	void SetCameraArm();
	void SetCharacterMovement();
	bool bIsAttack = true;

	FRotator TargetRotation;
	bool bShouldRotate;
	float RotationSpeed;

public:
	//-------------------------------------
	//Test Code
	//-------------------------------------

	UPROPERTY(EditAnywhere, Category = Action)
	UAnimMontage* AttackMontage;

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
};
