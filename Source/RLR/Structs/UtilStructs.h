// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/Proto/Post.pb.h"
#include "GameplayTagContainer.h"
#include "Network/Proto/Friend.pb.h"
#include "Network/Proto/Guild.pb.h"
#include "UtilStructs.generated.h"

class UAction;

UENUM(BlueprintType)
enum class ESlotType : uint8
{
	INVENTORY_SLOT,
	EQUIPMENT_SLOT,
	ITEM_QUICK_SLOT,
	SKILL_QUICK_SLOT,
	SKILL_SETTING_QUICK_SLOT,
	SKILL_SETTING_LIST_SLOT,
	TRADE_LIST_SLOT,
	POST_ITEM_SLOT,
	USER_STORAGE_ITEM_SLOT,
	PLAYER_STORAGE_ITEM_SLOT,
	STORAGE_INVENTORY_SLOT,
	NPCSHOP_INVENTORY_SLOT,
	POST_INVENTORY_SLOT,
	TRADE_INVENTORY_SLOT,
	ENHANCE_ITEM_SLOT,
	NONE,
};

UENUM(BlueprintType)
enum class EGuildRole : uint8 
{
	NONE = 0,
	MEMBER = 1,
	OFFICER = 2,
	VICEMASTER = 3,
	MASTER = 4
};

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
	int32 ActionSeq = -1;

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

	/* ItemId, Value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int64, int64> ItemValues;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PostDate;

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
	/* 길드 내 직급 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TEnumAsByte<EGuildRole> GuildRankSeq;

  /* UserSeq */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 UserSeq;
	/* UserName */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString UserName;
	/* 길드 명성치 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int guildReputation;
	/* 개인 길드 포인트 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int userGuildPoint;

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
	/* 길드 이름 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString  guildName;
	/* 길드 레벨 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int guildLevel;
	/* 길드 최대 획득 가능 경험치 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int guildMaxExp;
	/* 길드 경험치 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int guildExp;
	/* 길드 최대 수용가능 인원 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int guildMaxUser;
	/* 길드 포인트 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int guildPoint;
	/* 길드 랭크 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int guildRank;
	/* 길드 신설일 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int guildCreationDate;
	/* 길드 기여도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int guildContribution;
	
	// GuildRank : 길드 각 멤버 정보, 배열 길이 == 길드 멤버 수
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