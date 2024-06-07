// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Skill_Explosion.h"
#include "PlayerData.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class RLR_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();


private:

	FORCEINLINE class UCameraComponent* GetTopDown() const { return Camera; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraArm; }
	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraArm;

	void SetCameraArm();
	void SetCharacterMovement();

};
