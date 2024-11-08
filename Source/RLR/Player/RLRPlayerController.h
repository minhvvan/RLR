// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "GameFramework/PlayerController.h"
#include "Player/RLRBasePlayerController.h"
#include "GameplayTagContainer.h"
#include "RLRPlayerController.generated.h"

class ARLRPlayerCharacter;
class UPlayerManager;
class APlayerCommands;
class UInputMappingContext;

UCLASS()
class RLR_API ARLRPlayerController : public ARLRBasePlayerController
{
	GENERATED_BODY()

public:
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSoundEvent);
	
	ARLRPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	FVector GetClickPosition();

	void InitBinding();

private:
	void OnInput();
	void OnMoveStarted(FGameplayTag TriggerTag);
	void OnMove(FGameplayTag TriggerTag);
	void OnMoveCompleted(FGameplayTag TriggerTag);

	void OnUserClick();
	void OnTest();

	//bindingAction
	void OnDefaultAction(FGameplayTag TriggerTag);
	void OnSkillStarted(FGameplayTag TriggerTag);
	void OnSkillCompleted(FGameplayTag TriggerTag);
	void OnSkillHeld(FGameplayTag TriggerTag);
	void OnConsumeItem(int inputID);
	void OnConsumeItem(FGameplayTag InputTag);
	void OnOpenUI(FGameplayTag InputTag);
	void OnCloseUI();
	void OnActionStart(FGameplayTag InputTag);

	UPROPERTY(VisibleAnywhere, Category = Character);
	TObjectPtr<ARLRPlayerCharacter> PlayerCharacter;

	UPROPERTY(EditAnywhere, Category = Input);
	UInputMappingContext* CurrentContext;

	UPROPERTY(VisibleAnywhere, Category = Input);
	TObjectPtr<APlayerCommands> Commands;

	UPROPERTY(EditAnywhere, Category = Input);
	TSubclassOf<APlayerCommands> CommandClass;

	UPROPERTY()
	TObjectPtr<UPlayerManager> PlayerManager;

	UPROPERTY(BlueprintAssignable, Category = "SoundEvent");
	FSoundEvent soundEvent;

	float movePacketInterval;
	float timeSinceLastMovePacket;
	FVector lastSentPosition;

	bool IsMove();

	friend class APlayerCommands;
};
