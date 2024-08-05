// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Action/Action.h"
#include "ActionInteract.generated.h"

class UTimerProgressBar;

UCLASS()
class RLR_API UActionInteract : public UAction
{
	GENERATED_BODY()
	
public:
	UActionInteract();

protected:
	virtual bool PreActivateAction() override;
	virtual void ActivateAction() override;

public:
	virtual void CancelAction() override;
	virtual void EndAction() override;

protected:
	void PlayInteractMontage();

	UFUNCTION()
	virtual void OnCompletePlayMontage();

protected:
	//Interac Anim
	UPROPERTY(EditAnywhere, Category = Anim)
	TObjectPtr<UAnimMontage> InteractAnim;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UTimerProgressBar> InteractTimerClass;

	UPROPERTY(VisibleAnywhere, Category = UI)
	TObjectPtr<UTimerProgressBar> InteractTimerUI;
};
