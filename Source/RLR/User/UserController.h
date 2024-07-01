// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <NiagaraFunctionLibrary.h>
#include "EnhancedInputComponent.h"
#include <EnhancedInputSubsystems.h>
#include "Player/PlayerCommands.h"
<<<<<<< Updated upstream
=======
#include "Player/PlayerCharacter.h"
>>>>>>> Stashed changes
#include "../Chat/GameClient.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "Skill/Skill_Explosion.h"
#include "UserController.generated.h"

<<<<<<< Updated upstream
class APlayerCharacter;
=======
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	virtual void OnPossess(APawn* InPawn) override;
=======
>>>>>>> Stashed changes

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;
<<<<<<< Updated upstream
	void OnMoveStarted();

private:
	void OnMoveCompleted();
	void OnMove();
	void OnCursorEffect();
	void InitBinding();
	FVector GetClickPosition();

	//bindingAction
	void OnJump();
	void OnAttack();
	void OnAttackEffect(int inputID);
	void OnConsumeItem(int inputID);
	void OnOpenUI(int inputID);


	UPROPERTY(EditAnywhere, Category = Input);
	UNiagaraSystem* Cursor;
=======

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
>>>>>>> Stashed changes

	APlayerCharacter* Player;

	UPROPERTY(EditAnywhere, Category = Input);
<<<<<<< Updated upstream
	UInputMappingContext* CurrentContext;
	
	UPROPERTY(VisibleAnywhere, Category = Input);
=======
	UInputMappingContext* currentContext;

	UPROPERTY(EditAnywhere, Category = Input);
	UInputAction* move;
	UPROPERTY(EditAnywhere, Category = Input);
	UInputAction* defalutAttack;
	
	UPROPERTY(EditAnywhere, Category = Input);
>>>>>>> Stashed changes
	APlayerCommands* Commands;

	UPROPERTY(EditAnywhere, Category = Input);
	UClass* CommandClass;
<<<<<<< Updated upstream

	void AssignPlayerSeq();

	UPROPERTY()
	AGameClient* GameClient;

	float deltaTime;
	float pressTime;
	float movePacketInterval;
	float timeSinceLastMovePacket;
	FVector lastSentPosition;

	bool IsMove();

	friend class APlayerCommands;
=======
	void AssignPlayerSeq();
	UPROPERTY()
	AGameClient* GameClient;
	float deltaTime;
	float pressTime;

>>>>>>> Stashed changes
};
