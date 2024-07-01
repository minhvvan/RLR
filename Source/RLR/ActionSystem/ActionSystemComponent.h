// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ActionSystemComponent.generated.h"

class AAction;
struct FGameplayTagCountContainer
{
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

	FORCEINLINE bool UpdateTagCount(const FGameplayTag& Tag, int CountDelta)
	{
		if (CountDelta != 0)
		{
			return UpdateTagMap(Tag, CountDelta);
		}

		return false;
	}

	FORCEINLINE bool SetTagCount(const FGameplayTag& Tag, int NewCount)
	{
		int32 ExistingCount = 0;
		if (int32* Ptr = GameplayTagCountMap.Find(Tag))
		{
			ExistingCount = *Ptr;
		}

		int32 CountDelta = NewCount - ExistingCount;
		if (CountDelta != 0)
		{
			return UpdateTagMap(Tag, CountDelta);
		}

		return false;
	}

	FORCEINLINE bool UpdateTagMap(const FGameplayTag& Tag, int NewCount)
	{
		if (NewCount > 0)
		{
			GameplayTagCountMap[Tag] += NewCount;
		}
		else
		{
			return false;
		}

		return true;
	}

	FORCEINLINE int GetTagCount(const FGameplayTag& Tag) const
	{
		if (const int* Ptr = GameplayTagCountMap.Find(Tag))
		{
			return *Ptr;
		}

		return 0;
	}

	//FORCEINLINE void AddTag(const FGameplayTag& Tag, int Count) const
	//{
	//	UpdateTagMap(Tag, Count);
	//}

private:
	/** Map of tag to active count of that tag */
	TMap<FGameplayTag, int> GameplayTagCountMap;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
	TObjectPtr<AActor> OwnerActor;
	TObjectPtr<AActor> AvatarActor;

	//	//Action
//	TMap<FGameplayTag, class AAction> GrantedActions;

	//Tag
	FGameplayTagCountContainer OwnedTags;

public:
	//Tag

	//Tag를 count로 쓸건지 아닌지...
	//사실 count로 쓰는게 좋긴함 -> 스택 가능
	//근데 countContainer쓰려면 GAS플러그인 깔아야함
	//아니면 직접 만들어야 함 

	//or 그냥 container쓰기

	FORCEINLINE bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const
	{
		return OwnedTags.HasMatchingGameplayTag(TagToCheck);
	}

	FORCEINLINE void AddGameplayTag(const FGameplayTag& GameplayTag, int32 Count = 1)
	{
		//OwnedTags.AddTag(GameplayTag);
		//UpdateTagMap(GameplayTag, Count);
	}

	FORCEINLINE void RemoveGameplayTag(const FGameplayTag& GameplayTag, int32 Count = 1)
	{
		//OwnedTags.RemoveTag(GameplayTag);
		//UpdateTagMap(GameplayTag, -Count);
	}
};