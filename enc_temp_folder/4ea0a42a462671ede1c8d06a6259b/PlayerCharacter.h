// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "User/UserController.h"
#include "Camera/CameraComponent.h"
#include "Skill/Skill_Explosion.h"
#include "PlayerData.h"
#include "PlayerCharacter.generated.h"

class AUserController;

UCLASS()
class RLR_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	void SetMovement(FVector);
	void SetSimpleMove(APlayerController*, FVector);
	bool IsMove() { return bIsMove; };
	void SetIsMove(bool bValue) { bIsMove = bValue; };
	void StopMove(FVector);
	void SetOrientation();
private:

	FORCEINLINE class UCameraComponent* GetTopDown() const { return camera; };
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return cameraArm; };

	UPROPERTY(EditAnywhere, Category = Data);
	APlayerData* data;
	
	UPROPERTY();
	AUserController* playerController;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"));
	class UCameraComponent* camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"));
	class USpringArmComponent* cameraArm;

	void SetCameraArm();
	void SetCharacterMovement();
	bool bIsMove = true;
};
