// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTasksComponent.h"
#include "ActionSystem/ActionSystemTypes.h"
#include "GameManager/RLRStruct.h"
#include "ActionSystemComponent.generated.h"

class UAction;
class UStatSet;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RLR_API UActionSystemComponent : public UGameplayTasksComponent
{
	GENERATED_BODY()

public:
	UActionSystemComponent(const FObjectInitializer& ObjectInitializer);

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
	virtual float PlayMontage(UAction* AnimatingAction, UAnimMontage* Montage, float InPlayRate, FName StartSectionName = NAME_None, float StartTimeSeconds = 0.0f);

	UAction* GetAnimatingAction();
	UAnimMontage* GetCurrentMontage();

	void CurrentMontageStop(float OverrideBlendOutTime = -1.0f);
	virtual void ClearAnimatingAction(UAction* Action);

	//Stat
	template<typename T>
	void CreateStatSet()
	{
		AActor* OwningActor = GetOwner();
		const T* MyStat = nullptr;
		if (OwningActor && T::StaticClass())
		{
			T* NewStatSet = NewObject<T>(OwningActor, T::StaticClass());
			StatSet = NewStatSet;
		}
	}

	template <class T>
	T* GetStatSet() const
	{
		T* ResultStatSet = nullptr;
		if (StatSet.IsA(T::StaticClass()))
		{
			ResultStatSet = Cast<T>(StatSet.Get());
		}

		return ResultStatSet;
	}

	void AddActionData(FGameplayTag Tag, FActionData& Data);
	void GetActionData(FGameplayTag Tag, FActionData& Data);

	bool ActivateWaitAction();

private:
	//Actor Info
	TSharedPtr<FActionActorInfo> ActorInfo;

	//Action
	UPROPERTY(VisibleAnywhere, Category = Action, meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, FActionSpec> GrantedActions;

	//Tag
	UPROPERTY(EditAnywhere, Category=Action, meta = (AllowPrivateAccess = "true"))
	FGameplayTagCountContainer OwnedTags;

	UPROPERTY(VisibleAnywhere, Category = Anim, meta = (AllowPrivateAccess = "true"))
	FActionAnimMontage LocalAnimMontageInfo;

	UPROPERTY(VisibleAnywhere, Category=Stat)
	TObjectPtr<UStatSet> StatSet;

	//Action Data
	UPROPERTY(VisibleAnywhere, Category = Action, meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, FActionData> StoredActionData;

public:
	//Tag
	bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const;

	void AddGameplayTag(const FGameplayTag& GameplayTag, int32 Count = 1);

	void RemoveGameplayTag(const FGameplayTag& GameplayTag, int32 Count = 1);
};