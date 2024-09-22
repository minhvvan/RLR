// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/Proto/Struct.pb.h"
#include "Network/Proto/Player_2.pb.h"
#include "Network/Proto/User_2.pb.h"
#include "ItemStructs.generated.h"

enum class ECharacterMainJobType : uint8;
enum class ECharacterSubJobType : uint8;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EQUIPMENT,
	CONSUMPTION,
	ETC,
	NONE,
};

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	//무기, 방어구
	WEAPON,
	SUBWEAPON,
	HELMET,
	UPPERBODYARMOR,
	LOWERBODYARMOR,
	SHOES,
	GLOVES,
	//장신구

	NECKLACE,
	EARRING,
	RING,
	BRACELET,
	NONE,
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	COMMON,
	UNCOMMON,
	RARE,
	UNIQUE,
	EPIC,
	LEGEND,
	NONE,
};

UENUM(BlueprintType)
enum class EStatusType : uint8
{
	HP,
	MP,
	STR,
	AGI,
	INT,
	NONE,
};

UENUM(BlueprintType)
enum class EConsumptionType : uint8
{
	/*
		프로토에도 딱히 정보 없어서 일단 만들어만 둠.

	*/

	COMMON,
	POTION,
	NONE,
};

UENUM(BlueprintType)
enum class EETCType : uint8
{
	NORMAL,
	QUEST,
	NONE,
};

UENUM(BlueprintType)
enum class EGoodsType : uint8	//재화 타입
{
	Total,
	Diamond,
	Reputation,
	Contribution,
	SIZE
};

USTRUCT(Atomic, BlueprintType)
struct FItemStatus
{
	GENERATED_BODY()
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float HP = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float HP_ABSORB = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MP = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MP_ABSORB = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float HEALTH = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MAGIC = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float STRENGTH = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float AGILITY = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float INTELLIGENCE = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MAX_HP = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MAX_MP = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float ATTACK = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float DEFENCE = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float ATTACK_SPEED = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MOVE_SPEED = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float EVASION = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float LIFE_STEAL = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float CRITICAL_CHANCE = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float CRITICAL_DAMAGE = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float AVOID = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float COOLDOWN_REDUCTION = 0;

	FString ToString() const
	{
		FString ItemString;

		auto AppendStat = [&ItemString](const FString& StatName, float StatValue)
			{
				if (StatValue != 0)
				{
					if (!ItemString.IsEmpty())
					{
						ItemString.Append(TEXT("\n"));
					}
					ItemString.Append(FString::Printf(TEXT("%s = %.2f"), *StatName, StatValue));
				}
			};

		AppendStat(TEXT("HP"), HP);
		AppendStat(TEXT("HP_ABSORB"), HP_ABSORB);
		AppendStat(TEXT("MP"), MP);
		AppendStat(TEXT("MP_ABSORB"), MP_ABSORB);
		AppendStat(TEXT("HEALTH"), HEALTH);
		AppendStat(TEXT("MAGIC"), MAGIC);
		AppendStat(TEXT("STRENGTH"), STRENGTH);
		AppendStat(TEXT("AGILITY"), AGILITY);
		AppendStat(TEXT("INTELLIGENCE"), INTELLIGENCE);
		AppendStat(TEXT("MAX_HP"), MAX_HP);
		AppendStat(TEXT("MAX_MP"), MAX_MP);
		AppendStat(TEXT("ATTACK"), ATTACK);
		AppendStat(TEXT("DEFENCE"), DEFENCE);
		AppendStat(TEXT("ATTACK_SPEED"), ATTACK_SPEED);
		AppendStat(TEXT("MOVE_SPEED"), MOVE_SPEED);
		AppendStat(TEXT("EVASION"), EVASION);
		AppendStat(TEXT("LIFE_STEAL"), LIFE_STEAL);
		AppendStat(TEXT("CRITICAL_CHANCE"), CRITICAL_CHANCE);
		AppendStat(TEXT("CRITICAL_DAMAGE"), CRITICAL_DAMAGE);
		AppendStat(TEXT("AVOID"), AVOID);
		AppendStat(TEXT("COOLDOWN_REDUCTION"), COOLDOWN_REDUCTION);

		return ItemString;
	}
};

USTRUCT(Atomic, BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	//슬롯에 있는 아이템 데이터가 ITEM_ID == -1 이면 비어 있는 슬롯으로 처리 중.
	FItemData()
	{
		ITEM_SEQ = -1;
		ITEM_ID = -1;
		QUANTITY = 1;
		ItemImage = nullptr;
		TYPE = EItemType::NONE;
		EQUIPMENT_TYPE = EEquipmentType::NONE;
		IsEquiped = false;
	}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 ITEM_SEQ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NAME;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECharacterMainJobType> MainJobType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECharacterSubJobType> SubJobType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemType> TYPE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EEquipmentType> EQUIPMENT_TYPE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemRarity> RANK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EQUIPMENT_LEVEL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemStatus ITEM_STATUS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SALE_PRICE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 USE_PERIOD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TEXT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ITEM_VALUE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ITEM_MAX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 QUANTITY; 

	/*
		Consumption
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float COOLDOWN;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CONSUMPTION_VALUE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CONSUMPTION_DURATION;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EStatusType> CONSUMPTION_STATUS_TYPE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EConsumptionType> CONSUMPTION_TYPE;

	/*
		Etc
	*/


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EETCType> ETC_TYPE;

	//아이템 리소스 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemImage;

	//DB에 저장되어야할 정보
	int32 ITEM_SLOT_IDX;
	int64 ITEM_ID;
	bool IsEquiped;

	//나중에 패킷 날라오면, 그 정보로 FItemData를 만들어준다.
	void MakeItemData(const Protocol::Item itemData);
	void MakeItemData(const Protocol::Equip EquipData);
	Protocol::Item MakeItemPacket();
	Protocol::Equip MakeEquipPacket();
	static const FItemData EmptyItemData;

	void SetItemSlotIndex(int32 Id) { ITEM_SLOT_IDX = Id; }

	/** Operators */
	FORCEINLINE bool operator==(FItemData const& Other) const
	{
		if (ITEM_SEQ != Other.ITEM_SEQ)
			return false;
		return true;
	}
};

USTRUCT(Atomic, BlueprintType)
struct FPlayerGoods
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int TotalMoney;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int Diamond;

	FString ToString() const
	{
		FString PlayerGoodsString;

		auto AppendInt = [&PlayerGoodsString](const FString& StatName, int32 StatValue)
			{
				if (!PlayerGoodsString.IsEmpty()) PlayerGoodsString.Append(TEXT("\n"));
				PlayerGoodsString.Append(FString::Printf(TEXT("%s = %d"), *StatName, StatValue));
			};

		AppendInt(TEXT("TOTALMONEY"), TotalMoney);
		AppendInt(TEXT("DIAMOND"), Diamond);

		return PlayerGoodsString;
	}

	void MakePlayerGoods(const Protocol::PlayerGood playerGood);
};

USTRUCT(Atomic, BlueprintType)
struct FUserGoods
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int Reputation;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int Contribution;

	FString ToString() const
	{
		FString UserGoodsString;

		auto AppendInt = [&UserGoodsString](const FString& StatName, int32 StatValue)
			{
				if (!UserGoodsString.IsEmpty()) UserGoodsString.Append(TEXT("\n"));
				UserGoodsString.Append(FString::Printf(TEXT("%s = %d"), *StatName, StatValue));
			};

		AppendInt(TEXT("REPUTATION"), Reputation);
		AppendInt(TEXT("CONTRIBUTION"), Contribution);

		return UserGoodsString;
	}

	void MakeUserGoods(const Protocol::UserGood userGood);
};