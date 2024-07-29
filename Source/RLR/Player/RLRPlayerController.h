// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "../Chat/GameClient.h"
#include "GameplayTagContainer.h"
#include "RLRPlayerController.generated.h"

class ARLRPlayerCharacter;
class UPlayerManager;
class UNiagaraSystem;
class APlayerCommands;
class UInputMappingContext;

UCLASS()
class RLR_API ARLRPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARLRPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;
	void OnMoveStarted();

	FVector GetClickPosition();

	void InitBinding();

private:
	void OnMoveCompleted();
	void OnMove();
	void OnCursorEffect();

	//bindingAction
	void OnDefaultAction(FGameplayTag TriggerTag);
	void OnSkillStarted(FGameplayTag TriggerTag);
	void OnSkillCompleted(FGameplayTag TriggerTag);
	void OnSkillHeld(FGameplayTag TriggerTag);
	void OnConsumeItem(int inputID);
	void OnConsumeItem(FGameplayTag InputTag);
	void OnOpenUI(FGameplayTag InputTag);

	UPROPERTY(EditAnywhere, Category = Input);
	TObjectPtr<UNiagaraSystem> Cursor;

	UPROPERTY(VisibleAnywhere, Category = Character);
	TObjectPtr<ARLRPlayerCharacter> PlayerCharacter;

	UPROPERTY(EditAnywhere, Category = Input);
	UInputMappingContext* CurrentContext;
	
	UPROPERTY(VisibleAnywhere, Category = Input);
	TObjectPtr<APlayerCommands> Commands;

	UPROPERTY(EditAnywhere, Category = Input);
	TSubclassOf<APlayerCommands> CommandClass;

	//void AssignPlayerSeq();

	//UPROPERTY()
	//AGameClient* GameClient;

	UPROPERTY()
	TObjectPtr<UPlayerManager> PlayerManager;

	float deltaTime;
	float pressTime;
	float movePacketInterval;
	float timeSinceLastMovePacket;
	FVector lastSentPosition;

	bool IsMove();

	friend class APlayerCommands;
};
