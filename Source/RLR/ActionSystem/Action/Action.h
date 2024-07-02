// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionSystem/ActionSystemTypes.h"
#include "Action.generated.h"

class UActionSystemComponent;

UCLASS()
class RLR_API UAction : public UObject
{
	GENERATED_BODY()
	
public:
	UAction();

protected:
	//TODO: InstancingPolicy 설정 유무 결정 필요
	//UPROPERTY(EditDefaultsOnly, Category = Instance)
	//TEnumAsByte<EGameplayAbilityInstancingPolicy::Type>	InstancingPolicy;

public:
	void TryActivateAction();
	virtual void CancelAction();
	virtual void EndAction();

protected:
	virtual void PreActivateAction();
	virtual void ActivateAction();

	virtual bool CanActivateAction();

	bool CanEndAction();

protected:
	UPROPERTY()
	bool bIsActive;

	UPROPERTY()
	bool bIsAbilityEnding;

	UPROPERTY()
	bool bIsCancelable;

	//mutable const FActionActorInfo* CurrentActorInfo;

	UPROPERTY(EditDefaultsOnly, Category = Tags)
	FGameplayTagContainer ActivationOwnedTags;
};
