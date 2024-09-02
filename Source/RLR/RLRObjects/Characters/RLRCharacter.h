// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ActionSystem/ActionSystemInterface.h"
#include "GameplayTagContainer.h"
#include "RLRCharacter.generated.h"

class UAction;
class UActionSystemComponent;
struct FAbnormalMark;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS(Blueprintable)
class ARLRCharacter : public ACharacter, public IActionSystemInterface
{
	GENERATED_BODY()

public:
	ARLRCharacter();

	virtual UActionSystemComponent* GetActionSystemComponent() const;
	virtual void Tick(float DeltaSeconds) override;

	void DisplayAbnormalText(const FString AbnormalText);
	void DisplayAbnormalFX(UNiagaraSystem* AbnormalFX);

	UFUNCTION()
	virtual void SetDead();

	UFUNCTION()
	virtual void SetRevive();

protected:
	virtual void BeginPlay() override;
	void PlayDeadAnimation();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UASCWidgetComponent> StatDisplay;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UNiagaraComponent* AbnormalNiagaraComp;

protected:
	UPROPERTY(VisibleAnywhere, Category=Action , meta=( AllowPrivateAccess="true" ));
	TObjectPtr<UActionSystemComponent> ASC;

	UPROPERTY(EditAnywhere , Category=Action)
	TMap<FGameplayTag , TSubclassOf<UAction>> DefaultActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Anim, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;
};