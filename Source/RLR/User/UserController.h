// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <NiagaraFunctionLibrary.h>
#include "EnhancedInputComponent.h"
#include <EnhancedInputSubsystems.h>
#include "Player/PlayerCommands.h"
#include "Player/PlayerCharacter.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "Skill/Skill_Explosion.h"
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
	void OnMoveCompleted();
	void OnMove();
	void OnCursorEffect();
	void OnAttackEffect();
	void InitBinding(UEnhancedInputComponent*);
	FVector GetClickPosition();

	ASkill_Explosion* explosion;

	UPROPERTY(EditAnywhere, Category = Input);
	UNiagaraSystem* cursor;

	APlayerCharacter* Player;

	UPROPERTY(EditAnywhere, Category = Input);
	UInputMappingContext* currentContext;

	UPROPERTY(EditAnywhere, Category = Input);
	UInputAction* move;
	UPROPERTY(EditAnywhere, Category = Input);
	UInputAction* defalutAttack;
	
	UPROPERTY(EditAnywhere, Category = Input);
	APlayerCommands* Commands;

	UPROPERTY(EditAnywhere, Category = Input);
	UClass* CommandClass;
	
	float deltaTime;
	float pressTime;

};
