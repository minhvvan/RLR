// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataManager.generated.h"

/**
 * 
 */

 
UENUM(BlueprintType)
enum class EItemType : uint8
{
	EQUIPMENT,
	CONSUMPTION,
	ETC,
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
};

USTRUCT(Atomic, BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()


	FItemData()
	{
		ITEM_ID = -1;
		ItemImage = nullptr;
	}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 ITEM_SEQ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NAME;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemType> TYPE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemRarity> RANK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EQUIPMENT_LEVEL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SALE_PRICE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 USE_PERIOD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TEXT;

	//아이템 리소스 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemImage;

	//DB에 저장되어야할 정보
	int32 ITEM_SLOT_IDX;
	int32 ITEM_ID;

	//나중에 패킷 날라오면, 그 정보로 FItemData를 만들어준다.
	void MakeItemData();

	void SetItemSlotIndex(int32 Id){ITEM_SLOT_IDX = Id;}
};


UCLASS()
class RLR_API UDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:

	virtual void Initialize(FSubsystemCollectionBase& Collection);
	

	UFUNCTION(BlueprintCallable)
	FItemData GetItemData(int32 Id);


private:
	UPROPERTY()
	TObjectPtr<UDataTable> ItemDataTable;

};
