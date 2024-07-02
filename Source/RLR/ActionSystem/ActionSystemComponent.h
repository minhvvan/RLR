// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionSystem/ActionSystemTypes.h"
#include "ActionSystemComponent.generated.h"

class UAction;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RLR_API UActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActionSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitActorInfo(AActor* Owner, AActor* Avatar);

	//	//Action
	void GiveAction(FGameplayTag Tag, FActionSpec Spec);
	void RemoveAction(FGameplayTag Tag);
	void TryActivateAction(FGameplayTag Tag);

private:
	//TODO: ActorInfo struct로 관리 필요
	TObjectPtr<AActor> OwnerActor;
	TObjectPtr<AActor> AvatarActor;

	//	//Action
	TMap<FGameplayTag, FActionSpec> GrantedActions;

	//Tag
	UPROPERTY(VisibleAnywhere, Category=Tag, meta = (AllowPrivateAccess = "true"))
	FGameplayTagCountContainer OwnedTags;

public:
	//Tag
	bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const;

	void AddGameplayTag(const FGameplayTag& GameplayTag, int32 Count = 1);

	void RemoveGameplayTag(const FGameplayTag& GameplayTag, int32 Count = 1);
};