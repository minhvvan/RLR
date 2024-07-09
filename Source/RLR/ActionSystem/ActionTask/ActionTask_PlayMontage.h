// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/ActionTask/ActionTask.h"
#include "ActionTask_PlayMontage.generated.h"

class UAction;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMontageWaitSimpleDelegate);

UCLASS()
class RLR_API UActionTask_PlayMontage : public UActionTask
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable)
	FMontageWaitSimpleDelegate	OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FMontageWaitSimpleDelegate	OnBlendOut;

	UPROPERTY(BlueprintAssignable)
	FMontageWaitSimpleDelegate	OnInterrupted;

	UPROPERTY(BlueprintAssignable)
	FMontageWaitSimpleDelegate	OnCancelled;

	UFUNCTION()
	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnActionCancelled();

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION(Category = "Action|Tasks")
	static UActionTask_PlayMontage* CreatePlayMontageTask(UAction* OwningAction, FName TaskInstanceName,
		UAnimMontage* MontageToPlay, float Rate = 1.f, FName StartSection = NAME_None, bool bStopWhenAbilityEnds = true, float AnimRootMotionTranslationScale = 1.f, float StartTimeSeconds = 0.f, bool bAllowInterruptAfterBlendOut = false);

	virtual void Activate() override;

	/** Called when the ability is asked to cancel from an outside node. What this means depends on the individual task. By default, this does nothing other than ending the task. */
	virtual void ExternalCancel() override;

protected:

	virtual void OnDestroy(bool ActionEnded) override;

	/** Checks if the ability is playing a montage and stops that montage, returns true if a montage was stopped, false if not. */
	bool StopPlayingMontage();

	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;
	FDelegateHandle InterruptedHandle;

	UPROPERTY()
	TObjectPtr<UAnimMontage> MontageToPlay;

	UPROPERTY()
	float Rate;

	UPROPERTY()
	FName StartSection;

	UPROPERTY()
	float AnimRootMotionTranslationScale;

	UPROPERTY()
	float StartTimeSeconds;

	UPROPERTY()
	bool bStopWhenAbilityEnds;

	UPROPERTY()
	bool bAllowInterruptAfterBlendOut;
};
