// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/Proto/Post.pb.h"
#include "GameplayTagContainer.h"
#include "Network/Proto/Friend.pb.h"
#include "Network/Proto/Guild.pb.h"
#include "UtilStructs.generated.h"

class UAction;

USTRUCT(Atomic, BlueprintType)
struct FAttackResult
{
	GENERATED_BODY()

	FAttackResult() :
		SkillSeq(-1),
		Level(0),
		Timestamp(0),
		UserSeq(0)
	{}

	UPROPERTY(EditAnyWhere)
	int32 SkillSeq;

	UPROPERTY(EditAnyWhere)
	int32 Level;

	UPROPERTY(EditAnyWhere)
	uint64 Timestamp;

	UPROPERTY(EditAnyWhere)
	uint32 UserSeq;

	UPROPERTY(EditAnyWhere)
	TArray<uint32> TargetSeq;

	FString ToString() const
	{
		FString AttackString;

		auto AppendStatInt = [&AttackString](const FString& StatName, float StatValue)
			{
				if (!AttackString.IsEmpty()) AttackString.Append(TEXT("\n"));
				AttackString.Append(FString::Printf(TEXT("%s = %.2f"), *StatName, StatValue));
			};

		AppendStatInt(TEXT("SkillSEQ"), SkillSeq);
		AppendStatInt(TEXT("Level"), Level);
		AppendStatInt(TEXT("Timestamp"), Timestamp);
		AppendStatInt(TEXT("UserSeq"), UserSeq);
		for (auto target : TargetSeq)
		{
			AppendStatInt(TEXT("Target"), target);
		}

		return AttackString;
	}

	void MakeAttackData(/*const Protocol::Item itemData*/);
};

USTRUCT(Atomic, BlueprintType)
struct FActionResource : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 ActionSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FGameplayTag ActionTag;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UAction> ActionClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> ActionImage;

	FORCEINLINE bool operator==(FActionResource const& Other) const
	{
		if (ActionSeq != Other.ActionSeq)
			return false;
		return true;
	}
	static const FActionResource EmptyActionResource;
};

USTRUCT(Atomic, BlueprintType)
struct FActionResult : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 ActionSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 ChannelId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector TargetTransform;
};

USTRUCT(Atomic, BlueprintType)
struct FPostResult
{
	GENERATED_BODY()

	FPostResult() :
	ReceiverSeq(0),
	ReceiverName(""),
	Title(""),
	SenderSeq(0),
	Content(""),
	TotalMoney(0),
	IsRead(false),
	PostId(-1),
	SenderName("")
	{}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 ReceiverSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString ReceiverName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString Title;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 SenderSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString Content;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<int64> ItemId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 TotalMoney;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool IsRead;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool IsReceived;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 PostId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString SenderName;

	void MakePostData(const Protocol::Post post);
};

USTRUCT(Atomic, BlueprintType)
struct FMoveResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 UserSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 MapId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 ChannelId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector TargetTransform;
};

USTRUCT(Atomic, BlueprintType)
struct FExpTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 MaxExp = -1;

	static const FExpTable EmptyExpData;

	/** Operators */

	FORCEINLINE bool operator==(FExpTable const& Other) const
	{
		if (MaxExp != Other.MaxExp)
			return false;

		return true;
	}
};

USTRUCT(Atomic, BlueprintType)
struct FResourceData : public FTableRowBase
{
	GENERATED_BODY()
	int32 ResourceID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;
};

USTRUCT(Atomic, BlueprintType)
struct FClassData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UObject> RLRClass;

	//무슨 용도로 쓰는지 메모용.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DataInfo;
};

USTRUCT(Atomic, BlueprintType)
struct FEffectData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite);
	int32 PlayerSkillSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite);
	int32 MonsterSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite);
	FVector HitTransform;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite);
	FString EffectPath;
};

//잡동사니 데이터 저장용 구조체
USTRUCT(BlueprintType)
struct FEtcPropertyData
{
	GENERATED_BODY()
	UPROPERTY()
	TMap<FString, UObject*> EtcObjectMap;
	UPROPERTY()
	TMap<FString, FString> EtcStringMap;
	UPROPERTY()
	TMap<FString, int32> EtcIntMap;
};

USTRUCT(Atomic, BlueprintType)
struct FFriendGroupResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> FriendSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FString> FriendName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 GroupSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString GroupName;

  void MakeGroupData(const Protocol::Group group);
};

USTRUCT(BlueprintType)
struct FGuildRank
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 GuildRankSeq;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 UserSeq;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString UserName;

    FGuildRank()
        : GuildRankSeq(0), UserSeq(0), UserName(TEXT("")) {}

	static FGuildRank MakeGuildRankData(const Protocol::GuildRank& guildRank);
};

USTRUCT(Atomic, BlueprintType)
struct FGuildResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int guildSeq;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString  guildName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int guildLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int guildMaxExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int guildExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int guildMaxUser;

	// GuildRank 배열 추가
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FGuildRank> GuildRanks;

	FGuildResult()
		: guildSeq(0), guildName(TEXT("")), guildLevel(0), guildMaxExp(0), guildExp(0), guildMaxUser(0) {}


	void MakeGuildData(const Protocol::Guild guild);	
};

USTRUCT(Atomic, BlueprintType)
struct FAnimData : public FTableRowBase
{
	GENERATED_BODY()

	FAnimData() = default;

	FAnimData(FGameplayTag tag, UAnimMontage* anim) :
		Tag(tag),
		Anim(anim)
	{};

	UPROPERTY(EditAnyWhere, BlueprintReadWrite);
	FGameplayTag Tag;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite);
	UAnimMontage* Anim;

	static const FAnimData EmptyAnimData;

	bool operator==(const FAnimData& rhs)
	{
		return Tag == rhs.Tag;
	}
};