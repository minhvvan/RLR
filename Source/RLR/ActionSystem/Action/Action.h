// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionSystem/ActionSystemTypes.h"
#include "Action.generated.h"

class UActionSystemComponent;

UCLASS(Blueprintable)
class RLR_API UAction : public UObject
{
	GENERATED_BODY()
	
public:
	UAction();

public:
	void TryActivateAction();
	virtual void CancelAction();
	virtual void EndAction();

	void InitCurrentActorInfo();
	void SetTriggerTag(FGameplayTag Tag);
	FGameplayTag GetTriggerTag() { return TriggerTag; }

	EActionInstancingPolicy::Type GetInstancingPolicy() const;

protected:
	virtual void PreActivateAction();
	virtual void ActivateAction();

	virtual bool CanActivateAction();

	bool CanEndAction();

protected:
	UPROPERTY(EditDefaultsOnly, Category = Instance)
	TEnumAsByte<EActionInstancingPolicy::Type> InstancingPolicy;

	UPROPERTY()
	bool bIsActive;

	UPROPERTY()
	bool bIsAbilityEnding;

	UPROPERTY()
	bool bIsCancelable;

	UPROPERTY(VisibleAnywhere)
	FGameplayTag TriggerTag;

	mutable const FActionActorInfo* CurrentActorInfo;

	UPROPERTY(EditDefaultsOnly, Category = Tags)
	FGameplayTagContainer ActivationOwnedTags;
};
