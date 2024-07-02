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

	virtual void InitializeComponent();

	void InitActorInfo(AActor* Owner, AActor* Avatar);

	//	//Action
	void GiveAction(FGameplayTag Tag, const FActionSpec& Spec);
	void RemoveAction(FGameplayTag Tag);
	void TryActivateAction(FGameplayTag Tag);

	void NotifyActionEnded(UAction* EndedAction);

	UAction* CreateNewInstanceOfAction(FActionSpec& Spec);

	FActionActorInfo* GetActionActorInfo();

private:
	//Actor Info
	TSharedPtr<FActionActorInfo> ActorInfo;

	//Action
	UPROPERTY(VisibleAnywhere, Category = Action, meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, FActionSpec> GrantedActions;

	//Tag
	UPROPERTY(VisibleAnywhere, Category=Action, meta = (AllowPrivateAccess = "true"))
	FGameplayTagCountContainer OwnedTags;

public:
	//Tag
	bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const;

	void AddGameplayTag(const FGameplayTag& GameplayTag, int32 Count = 1);

	void RemoveGameplayTag(const FGameplayTag& GameplayTag, int32 Count = 1);
};