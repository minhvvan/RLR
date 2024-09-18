// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLRObjects/Characters/RLRCharacter.h"
#include "GameManager/RLRStruct.h"
#include "RLRPlayerCharacter.generated.h"

class UAction;
class UCameraComponent;
class USpringArmComponent;
class UStatSetPlayer;
class AAIController;

UCLASS()
class RLR_API ARLRPlayerCharacter : public ARLRCharacter
{
	GENERATED_BODY()

public:
	ARLRPlayerCharacter();
	void SetMoveMode(EMovementMode);

	virtual void Tick(float DeltaSeconds) override;
	void SetTargetRotation(FVector TargetLoc, float Speed = 1);
	int32 GetPlayerSeq() const { return PlayerSeq; }
	void SetPlayerSeq(int32 Seq) { PlayerSeq = Seq; }
	void SetStat(const FUserCharacter& Stat);
	const UStatSetPlayer* GetStat();

	void UpdateTransform(FVector NewTransform);

	void SpawnTransform(FVector NewTransform);

	virtual void SetDead() override;


private:
	
	FORCEINLINE class UCameraComponent* GetTopDown() const { return camera; };
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return cameraArm; };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"));
	class UCameraComponent* camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"));
	class USpringArmComponent* cameraArm;

	//APlayerData* data;
	int32 PlayerSeq;

	void SetCameraArm();
	void SetCharacterMovement();

	FRotator TargetRotation;
	bool bShouldRotate;
	float RotationSpeed;
	AAIController* AIController;

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
