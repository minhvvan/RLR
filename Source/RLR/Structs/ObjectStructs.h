// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/Proto/Struct.pb.h"
#include "Network/Proto/NPCStruct.pb.h"
#include "Network/Proto/Drop.pb.h"
#include "Structs/ItemStructs.h"
#include "ObjectStructs.generated.h"

UENUM(BlueprintType)
enum class EInteractObjectType : uint8
{
	COLLECT = 0,
	MINING,
	LOGGING,
	FISHING,
	SWIMMING,
	NONE
};

UENUM(BlueprintType)
enum class ENPCFunctionality : uint8
{
	POST = 0,
	STORAGE,
	ENHNACE,
	SIZE
};


USTRUCT(Atomic, BlueprintType)
struct FObjectMap
{
	GENERATED_BODY()
	TMap<int, int> Map;

	FString ToString() const
	{
		FString OutString;

		auto AppendStatInt = [&OutString](int key, int value)
			{
				if (!OutString.IsEmpty()) OutString.Append(TEXT(", "));
				OutString.Append(FString::Printf(TEXT("{%d:%d}"), key, value));
			};

		for (const auto& [seq, amount] : Map)
		{
			AppendStatInt(seq, amount);
		}

		return OutString;
	}

	void Add(int key, int value)
	{
		Map.Add(key, value);
	}
};


USTRUCT(Atomic, BlueprintType)
struct FQuest
{
	GENERATED_BODY()

	FQuest()
	{}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int QuestSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int NPCSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString QuestTitle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString QuestText;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString QuestDescription;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int QuestKind;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool IsProgress;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool IsClear;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TMap<FString, FObjectMap> Rewards;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TMap<FString, FObjectMap> Needs;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FPlayerGoods PlayerGoods;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FUserGoods UserGoods;

	FString ToString() const
	{
		FString QuestString;

		auto AppendQuestInt = [&QuestString](const FString& StatName, int32 StatValue)
			{
				if (!QuestString.IsEmpty()) QuestString.Append(TEXT("\n"));
				QuestString.Append(FString::Printf(TEXT("%s = %d"), *StatName, StatValue));
			};

		auto AppendQuestString = [&QuestString](const FString& StatName, FString StatValue)
			{
				if (!QuestString.IsEmpty()) QuestString.Append(TEXT("\n"));
				QuestString.Append(FString::Printf(TEXT("%s = %s"), *StatName, *StatValue));
			};

		auto AppendQuestBool = [&QuestString](const FString& StatName, bool StatValue)
			{
				if (!QuestString.IsEmpty()) QuestString.Append(TEXT("\n"));
				FString str = StatValue ? TEXT("TRUE") : TEXT("FALSE");
				QuestString.Append(FString::Printf(TEXT("%s = %s"), *StatName, *str));
			};

		AppendQuestInt(TEXT("SEQ"), QuestSeq);
		AppendQuestInt(TEXT("NPCSEQ"), NPCSeq);
		AppendQuestString(TEXT("QUESTTITLE"), QuestTitle);
		AppendQuestString(TEXT("QUESTTEXT"), QuestText);
		AppendQuestString(TEXT("QUESTDECRIPTION"), QuestDescription);
		AppendQuestInt(TEXT("QUESTKIND"), QuestKind);
		AppendQuestBool(TEXT("ISPROGRESS"), IsProgress);
		AppendQuestBool(TEXT("ISCLEAR"), IsClear);

		QuestString.Append(FString::Printf(TEXT("\n---------------\n")));
		QuestString.Append(FString::Printf(TEXT("\nREWARDS\n")));
		for (const auto& [type, rewards] : Rewards)
		{
			AppendQuestString(type, rewards.ToString());
		}

		QuestString.Append(FString::Printf(TEXT("\n---------------\n")));
		QuestString.Append(FString::Printf(TEXT("\nNEEDS\n")));
		for (const auto& [type, need] : Needs)
		{
			AppendQuestString(type, need.ToString());
		}
		 
		QuestString.Append(FString::Printf(TEXT("\nPLAYERGOODS\n")));
		QuestString.Append(PlayerGoods.ToString());
		QuestString.Append(FString::Printf(TEXT("\nUSERGOODS\n")));
		QuestString.Append(UserGoods.ToString());

		return QuestString;
	}

	void MakeQuestData(const Protocol::Quest quest);
};

USTRUCT(Atomic, BlueprintType)
struct FNPCShop
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 ShopSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString ShopName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FItemData> Items;

	void MakeNPCShopData(const Protocol::Shop shop);
};


USTRUCT(Atomic, BlueprintType)
struct FNPCData
{
	GENERATED_BODY()

	FNPCData() :
		NPCSeq(-1),
		NPCTransform(FVector::ZeroVector)
	{}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int NPCSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString NPCName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString NPCTalk;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int NPCType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString NPCConcept;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector NPCTransform;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 MapId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FQuest> NPCQuests;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FNPCShop> Shop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Functionality;

	FString ToString() const
	{
		FString NPCString;

		auto AppendFloat = [&NPCString](const FString& StatName, float StatValue)
			{
				if (!NPCString.IsEmpty()) NPCString.Append(TEXT("\n"));
				NPCString.Append(FString::Printf(TEXT("%s = %.2f"), *StatName, StatValue));
			};

		auto AppendInt = [&NPCString](const FString& StatName, int32 StatValue)
			{
				if (!NPCString.IsEmpty()) NPCString.Append(TEXT("\n"));
				NPCString.Append(FString::Printf(TEXT("%s = %d"), *StatName, StatValue));
			};

		auto AppendString = [&NPCString](const FString& StatName, FString StatValue)
			{
				if (!NPCString.IsEmpty()) NPCString.Append(TEXT("\n"));
				NPCString.Append(FString::Printf(TEXT("%s = %s"), *StatName, *StatValue));
			};

		auto AppendVector = [&NPCString](const FString& StatName, FVector StatValue)
			{
				if (!NPCString.IsEmpty()) NPCString.Append(TEXT("\n"));
				NPCString.Append(FString::Printf(TEXT("%s = %s"), *StatName, *StatValue.ToString()));
			};

		AppendInt(TEXT("SEQ"), NPCSeq);
		AppendString(TEXT("NAME"), NPCName);
		AppendString(TEXT("TALK"), NPCTalk);
		AppendInt(TEXT("TYPE"), NPCType);
		AppendString(TEXT("CONCEPT"), NPCConcept);
		AppendVector(TEXT("TRANSFORM"), NPCTransform);
		AppendInt(TEXT("MAPID"), MapId);

		NPCString.Append(TEXT("\nQUESTS\n"));
		for (auto quest : NPCQuests)
		{
			NPCString.Append(TEXT("--------------\n"));
			NPCString.Append(quest.ToString());
			NPCString.Append(TEXT("\n--------------\n"));
		}

		return NPCString;
	}

	void MakeNPCData(const Protocol::NPC npc);
	const static FNPCData EmptyNPCData;
};

USTRUCT(Atomic, BlueprintType)
struct FInteractData
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	EInteractObjectType InteractType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector ObjectTransform;

	void MakeObjectData();
	//TODO:MakeData 구현 후 삭제
	static int testID;
};

USTRUCT(Atomic, BlueprintType)
struct FDropItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 ObjectId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int64 ObjectSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int Num;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector ObjectTransform;

	void MakeDropItemData(int64 objectId, int32 value, int64 monsterId);
};
