// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ActionSystemComponent.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FGameplayTagCountContainer
{
	GENERATED_BODY()

	FGameplayTagCountContainer()
	{}

	FORCEINLINE bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const
	{
		return GameplayTagCountMap.FindRef(TagToCheck) > 0;
	}

	FORCEINLINE bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
	{
		if (TagContainer.Num() == 0)
		{
			return true;
		}

		bool AllMatch = true;
		for (const FGameplayTag& Tag : TagContainer)
		{
			if (GameplayTagCountMap.FindRef(Tag) <= 0)
			{
				AllMatch = false;
				break;
			}
		}

		return AllMatch;
	}

	FORCEINLINE bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
	{
		if (TagContainer.Num() == 0)
		{
			return false;
		}

		bool AnyMatch = false;
		for (const FGameplayTag& Tag : TagContainer)
		{
			if (GameplayTagCountMap.FindRef(Tag) > 0)
			{
				AnyMatch = true;
				break;
			}
		}
		return AnyMatch;
	}

	FORCEINLINE void UpdateTagCount(const FGameplayTagContainer& Container, int CountDelta)
	{
		if (CountDelta != 0)
		{
			for (auto TagIt = Container.CreateConstIterator(); TagIt; ++TagIt)
			{
				UpdateTagMap(*TagIt, CountDelta);
			}
		}
	}

	FORCEINLINE void UpdateTagCount(const FGameplayTag& Tag, int CountDelta)
	{
		if (CountDelta != 0)
		{
			UpdateTagMap(Tag, CountDelta);
		}
	}

	FORCEINLINE void SetTagCount(const FGameplayTag& Tag, int NewCount)
	{
		int32 ExistingCount = 0;
		if (int32* Ptr = GameplayTagCountMap.Find(Tag))
		{
			ExistingCount = *Ptr;
		}

		int32 CountDelta = NewCount - ExistingCount;
		if (CountDelta != 0)
		{
			UpdateTagMap(Tag, CountDelta);
		}
	}

	FORCEINLINE void UpdateTagMap(const FGameplayTag& Tag, int NewCount)
	{
		if (!GameplayTagCountMap.Contains(Tag))
		{
			GameplayTagCountMap.Add(Tag, 0);
		}

		GameplayTagCountMap[Tag] += NewCount;
		if (GameplayTagCountMap[Tag] == 0)
		{
			GameplayTagCountMap.Remove(Tag);
		}
	}

	FORCEINLINE int GetTagCount(const FGameplayTag& Tag) const
	{
		if (const int* Ptr = GameplayTagCountMap.Find(Tag))
		{
			return *Ptr;
		}

		return 0;
	}

	FORCEINLINE void AddTag(const FGameplayTag& Tag, int Count)
	{
		UpdateTagMap(Tag, Count);
	}

	FORCEINLINE void RemoveTag(const FGameplayTag& Tag)
	{
		UpdateTagMap(Tag, -GameplayTagCountMap[Tag]);
	}

private:
	UPROPERTY(VisibleAnywhere)
	TMap<FGameplayTag, int> GameplayTagCountMap;
};


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
	//	void GiveAction(FGameplayTag Tag, TSubclassOf<class AAction> Action);
	//	void RemoveAction(FGameplayTag Tag);
	//	void TryActivateAction(FGameplayTag Tag);

private:
	//TODO: ActorInfo struct로 관리 필요
	TObjectPtr<AActor> OwnerActor;
	TObjectPtr<AActor> AvatarActor;

	//	//Action
//	TMap<FGameplayTag, class AAction> GrantedActions;

	//Tag
	UPROPERTY(VisibleAnywhere, Category=Tag, meta = (AllowPrivateAccess = "true"))
	FGameplayTagCountContainer OwnedTags;

public:
	//Tag
	bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const;

	void AddGameplayTag(const FGameplayTag& GameplayTag, int32 Count = 1);

	void RemoveGameplayTag(const FGameplayTag& GameplayTag, int32 Count = 1);
};