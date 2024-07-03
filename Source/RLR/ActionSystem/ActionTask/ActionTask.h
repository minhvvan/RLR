// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "ActionSystem/Action/Action.h"
#include "ActionTask.generated.h"

UCLASS()
class RLR_API UActionTask : public UGameplayTask
{
	GENERATED_BODY()
	
public:
	virtual void OnDestroy(bool bInOwnerFinished) override;
	virtual void BeginDestroy() override;

	template <class T>
	static T* NewActionTask(UAction* Action, FName InstanceName = FName())
	{
		check(Action);

		T* MyObj = NewObject<T>();
		MyObj->InitTask(*Action, Action->GetGameplayTaskDefaultPriority());

		MyObj->InstanceName = InstanceName;
		return MyObj;
	}

	void SetActionSystemComponent(UActionSystemComponent* InASC);
	virtual void InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent) override;

public:
	UPROPERTY()
	TObjectPtr<UAction> Action;

	UPROPERTY()
	TWeakObjectPtr<UActionSystemComponent> ActionSystemComponent;
};