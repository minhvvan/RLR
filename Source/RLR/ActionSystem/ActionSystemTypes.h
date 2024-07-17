// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ActionSystemTypes.generated.h"

class UAction;
class UActionSystemComponent;
class APlayerController;
class UAnimInstance;
class UAnimMontage;
class UMovementComponent;
class USkeletalMeshComponent;


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
	UPROPERTY(EditAnywhere, Category = Action, meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, int> GameplayTagCountMap;
};

USTRUCT(Atomic, BlueprintType)
struct RLR_API FActionSpec
{
	GENERATED_BODY()

public:
	FActionSpec()
		: Action(nullptr), Level(1), InputID(INDEX_NONE), bCancelable(false)
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

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool bCancelable;

	/** Chain ActionTag (e.g. AttackCheck) */
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FGameplayTag FollowActionTag;

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

	UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")
	TWeakObjectPtr<UAnimInstance>	AnimInstance;

	UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")
	TWeakObjectPtr<USkeletalMeshComponent>	SkeletalMeshComponent;

	UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")
	TWeakObjectPtr<UMovementComponent>	MovementComponent;

	UAnimInstance* GetAnimInstance() const;
	
	virtual void InitFromActor(AActor* Owner, AActor* Avatar, UActionSystemComponent* InASC);

	virtual void SetAvatarActor(AActor* Avatar);

	virtual void ClearActorInfo();
};

USTRUCT(Atomic, BlueprintType)
struct RLR_API FActionData
{
	GENERATED_BODY()

public:
	virtual ~FActionData() {}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorInfo")
	FVector	MousePos;
};

UENUM(BlueprintType)
enum class EActionInstancingPolicy : uint8
{
	NonInstanced ,
	InstancedPerActor ,
	InstancedPerExecution ,
};

USTRUCT()
struct RLR_API FActionAnimMontage
{
	GENERATED_BODY()

	FActionAnimMontage()
		: AnimMontage(nullptr), AnimatingAction(nullptr)
	{
	}

	/** What montage is being played */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAnimMontage> AnimMontage;

	/** The ability, if any, that instigated this montage */
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<UAction> AnimatingAction;
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	STATE_INIT						UMETA(DisplayName = "Init"),
	STATE_ACTIVATE					UMETA(DisplayName = "Activate"),
	STATE_END						UMETA(DisplayName = "End"),
	STATE_WAIT_ACTIVATE				UMETA(DisplayName = "Wait_Activate"),
	STATE_WAIT_ADDTIONAL_INPUT		UMETA(DisplayName = "Wait_Input"),
	SIZE
};