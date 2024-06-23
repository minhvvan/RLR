// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <NiagaraFunctionLibrary.h>
#include "EnhancedInputComponent.h"
#include <EnhancedInputSubsystems.h>
#include "Player/PlayerCommands.h"
#include "Player/PlayerCharacter.h"
#include "../Chat/GameClient.h"
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
	void OnMoveStarted();
private:

	void OnMoveCompleted();
	void OnMove();
	void OnCursorEffect();
	void OnAttackEffect();
	void InitBinding(UEnhancedInputComponent*);
	FVector GetClickPosition();

	ASkill_Explosion* explosion;

	UPROPERTY(EditAnywhere, Category = Input);
	UNiagaraSystem* cursor;

	APlayerCharacter* player;

	UPROPERTY(EditAnywhere, Category = Input);
	UInputMappingContext* currentContext;
	
	UPROPERTY(EditAnywhere, Category = Input);
	APlayerCommands* commands;

	UPROPERTY(EditAnywhere, Category = Input);
	UClass* CommandClass;
	void AssignPlayerSeq();
	UPROPERTY()
	AGameClient* GameClient;
	float deltaTime;
	float pressTime;
	bool IsMove();
};
