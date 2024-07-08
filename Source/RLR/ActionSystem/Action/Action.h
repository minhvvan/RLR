// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTaskOwnerInterface.h"
#include "ActionSystem/ActionSystemTypes.h"
#include "Action.generated.h"

class UActionSystemComponent;

DECLARE_MULTICAST_DELEGATE(FOnGameplayAbilityCancelled);

UCLASS(Blueprintable)
class RLR_API UAction : public UObject, public IGameplayTaskOwnerInterface
{
	GENERATED_BODY()
	
public:
	UAction();

	// --------------------------------------
	//	IGameplayTaskOwnerInterface
	// --------------------------------------	
	virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const override;
	virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const override;
	virtual AActor* GetGameplayTaskAvatar(const UGameplayTask* Task) const override;
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

public:
	void TryActivateAction();
	virtual void CancelAction();
	virtual void EndAction();

	void InitCurrentActorInfo();
	const FActionActorInfo* GetCurrentActorInfo() const;

	void SetTriggerTag(FGameplayTag Tag);
	FGameplayTag GetTriggerTag() { return TriggerTag; }

	EActionInstancingPolicy GetInstancingPolicy() const;

	UActionSystemComponent* GetASCFromActorInfo();
	AActor* GetAvatarActorFromActorInfo() const;

	virtual void SetCurrentMontage(class UAnimMontage* InCurrentMontage);
	virtual UAnimMontage* GetCurrentMontage();

protected:
	virtual void PreActivateAction();
	virtual void ActivateAction();

	virtual bool CanActivateAction();

	bool CanEndAction();

public:
	FOnGameplayAbilityCancelled OnGameplayAbilityCancelled;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Instance)
	EActionInstancingPolicy InstancingPolicy;

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

	UPROPERTY()
	TArray<TObjectPtr<UGameplayTask>> ActiveTasks;

	UPROPERTY()
	TObjectPtr<class UAnimMontage> CurrentMontage;
};
