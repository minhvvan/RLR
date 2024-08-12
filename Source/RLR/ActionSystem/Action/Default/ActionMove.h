// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Action/Action.h"
#include "ActionMove.generated.h"


class UActionSystemComponent;
class ARLRPlayerCharacter;
class ARLRPlayerController;
class UActionTask_MoveToLocation;
class UNiagaraSystem;

UCLASS()
class RLR_API UActionMove : public UAction
{
	GENERATED_BODY()

public:
	UActionMove();

protected:
	virtual bool PreActivateAction() override;
	virtual void ActivateAction() override;

public:
	virtual void CancelAction() override;
	virtual void EndAction() override;

protected:
	void StartMove();
	void AddMovementInput();
	void MoveToLocation();

protected:
	UPROPERTY(EditAnywhere, Category = FX);
	TObjectPtr<UNiagaraSystem> Cursor;

	UPROPERTY(EditAnywhere, Category = FX);
	int CursorPeriod; /*Tick Count*/

	static int SpawnCursorCnt;

	TObjectPtr<UActionSystemComponent> ASC;
	TObjectPtr<ARLRPlayerCharacter> PlayerCharacter;
	TObjectPtr<ARLRPlayerController> Controller;
	FActionData ActionData;

	TObjectPtr<UActionTask_MoveToLocation> MoveTask;

	UFUNCTION()
	void OnMoveComplete(bool bSuccess);
};
