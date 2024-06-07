// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <NiagaraFunctionLibrary.h>
#include "EnhancedInputComponent.h"
#include <EnhancedInputSubsystems.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "Skill_Explosion.h"
#include "UserController.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API AUserController : public APlayerController
{
	GENERATED_BODY()

public:
	AUserController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

private:

	void OnMoveStarted();
	void OnMoveTriggered();
	void OnMoveCompleted();
	void OnAttackStarted();
	void OnMove();
	void OnCursorEffect(FVector);
	void OnAttackEffect();
	FVector GetClickPosition();

	ASkill_Explosion* explosion;

	UPROPERTY(EditAnywhere, Category = Input);
	UNiagaraSystem* cursor;


	UPROPERTY(EditAnywhere, Category = Input);
	UInputMappingContext* currentContext;

	UPROPERTY(EditAnywhere, Category = Input);
	UInputAction* move;

	UPROPERTY(EditAnywhere, Category = Input);
	UInputAction* defalutAttack;


	float deltaTime;
	float pressTime;
};
