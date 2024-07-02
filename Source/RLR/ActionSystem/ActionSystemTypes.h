// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ActionSystemTypes.generated.h"

class UAction;
class UActionSystemComponent;

USTRUCT(Atomic, BlueprintType)
struct RLR_API FGameplayTagCountContainer
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

USTRUCT(Atomic, BlueprintType)
struct RLR_API FActionSpec
{
	GENERATED_BODY()

public:
	FActionSpec()
		: Action(nullptr), Level(1), InputID(INDEX_NONE)
	{ }

	FActionSpec(TSubclassOf<UAction> ActionClass, int32 InLevel, int32 InInputID);

	UPROPERTY()
	TObjectPtr<UAction> Action;

	/** What level to grant this ability at */
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	int32 Level;

	/** Input ID to bind this ability to */
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	int32 InputID;

	UPROPERTY(VisibleAnywhere, Category = "Action")
	TArray<TObjectPtr<UAction>> ActionInstances;
};

USTRUCT(Atomic, BlueprintType)
struct RLR_API FActionActorInfo
{
	GENERATED_BODY()

public:
	virtual ~FActionActorInfo() {}

	UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")
	TWeakObjectPtr<AActor>	OwnerActor;

	UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")
	TWeakObjectPtr<AActor>	AvatarActor;

	UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")
	TWeakObjectPtr<UActionSystemComponent>	ActionSystemComponent;

	virtual void InitFromActor(AActor* Owner, AActor* Avatar, UActionSystemComponent* InASC);

	virtual void SetAvatarActor(AActor* Avatar);

	virtual void ClearActorInfo();
};

UENUM(BlueprintType)
namespace EActionInstancingPolicy
{
	enum Type : int
	{
		NonInstanced,
		InstancedPerActor,
		InstancedPerExecution,
	};
}