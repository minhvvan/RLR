// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/Proto/Post.pb.h"
#include "GameplayTagContainer.h"
#include "Network/Proto/Friend.pb.h"
#include "UtilStructs.generated.h"

class UAction;

UENUM(BlueprintType)
enum class EUIType : uint8
{
	//Title
	TITLE_MAIN_UI,
	SERVER_LIST,

	//Lobby
	LOBBY_MAIN_UI,
	CHARACTER_LIST_UI,
	CREATE_CHARACTER_UI,

	//InGame
	INGAME_MAIN_UI,
	ABNORMAL_DISPLAY,
	INVENTORY_UI,
	CHARACTER_STATUS_UI,
	CHAT_OPTION_UI,
	CHAT_UI,
	ITEM_INFOMATION,
	MINIMAP,
	STATUS_DISPLAY,
	INGAME_MENU,
	PARTY,
	QUEST_DIALOGUE,
	KEY_OPTION,
	SKILL_UI,
	SKILL_SETTING,
	SKILL_TREE,
	SKILL_UPGRADE,
	TIME_PROGRESS_BAR,
	EXP_PROGRESS_BAR,
	BADGE_UI,
	QUEST,
	TRADE_UI,
	//Popup
	ITEM_COUNT_MESSAGE_BOX,
	NOTIFICATION_MESSAGE_BOX,
	POST_UI,
	OTHER_PLAYER_MENU,
	FRIEND_LIST_UI,
	FRIEND_REQUEST_UI,
	FRIEND_INFORMATION_UI,
	FRIEND_MENU_UI,
	GROUP_CREATION_UI,
	GROUP_MENU_UI,
	NONE,
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
struct FPostResult
{
	GENERATED_BODY()

	FPostResult() :
	ReceiverSeq(0),
	SenderSeq(0),
	TotalMoney(0),
	PostId(-1),
	ReceiverName(""),
	SenderName(""),
	Title(""),
	Content(""),
	IsRead(false)
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