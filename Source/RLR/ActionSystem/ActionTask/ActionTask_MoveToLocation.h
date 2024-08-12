// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/ActionTask/ActionTask.h"
#include "Navigation/PathFollowingComponent.h"
#include "ActionTask_MoveToLocation.generated.h"

class UAction;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMoveResultDelegate, bool, bSuccess);

UCLASS()
class RLR_API UActionTask_MoveToLocation : public UActionTask
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FMoveResultDelegate	OnMoveFinish;

	UFUNCTION(Category = "Action|Tasks")
	static UActionTask_MoveToLocation* CreateMoveTask(UAction* OwningAction, FName TaskInstanceName, APawn* Pawn, FVector Location, bool bStopWhenActionEnds = true);

	virtual void Activate() override;

	/** Called when the ability is asked to cancel from an outside node. What this means depends on the individual task. By default, this does nothing other than ending the task. */
	virtual void ExternalCancel() override;

protected:
	virtual void OnDestroy(bool ActionEnded) override;

	void TryMove();

protected:
	UPROPERTY()
	TObjectPtr<APawn> Pawn;

	UPROPERTY()
	FVector GoalLocation;
	FDelegateHandle InterruptedHandle;

	UPROPERTY()
	bool bStopWhenActionEnds;

	UPROPERTY()
	TObjectPtr<UPathFollowingComponent> PFollowComp;

protected:
	void OnMoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result);
};
