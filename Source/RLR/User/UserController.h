// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <NiagaraFunctionLibrary.h>
#include "EnhancedInputComponent.h"
#include <EnhancedInputSubsystems.h>
#include "Player/PlayerCommands.h"
#include "../Chat/GameClient.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "Skill/Skill_Explosion.h"
#include "UserController.generated.h"

class APlayerCharacter;
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
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;
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

	APlayerCharacter* Player;

	UPROPERTY(EditAnywhere, Category = Input);
	UInputMappingContext* CurrentContext;
	
	UPROPERTY(VisibleAnywhere, Category = Input);
	APlayerCommands* Commands;

	UPROPERTY(EditAnywhere, Category = Input);
	UClass* CommandClass;

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
};
