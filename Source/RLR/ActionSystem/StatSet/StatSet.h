// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameManager/RLRStruct.h"
#include "ActionSystem/ActionSystemTypes.h"
#include "StatSet.generated.h"

//#define STAT_ACCESSORS(ClassName, PropertyName, PropertyType) \
//		STAT_GETTER(PropertyName, PropertyType) \
//		STAT_SETTER(PropertyName, PropertyType)

#define STAT_GETTER(PropertyName, PropertyType) \
	FORCEINLINE PropertyType Get##PropertyName() const \
	{ \
		return Stat.PropertyName; \
	}

#define STAT_SETTER(PropertyName, PropertyType) \
	FORCEINLINE void Set##PropertyName(PropertyType NewVal) \
	{ \
		Stat.PropertyName = NewVal; \
	}

#define ALL_STAT_SETTER(StructType) \
	FORCEINLINE void SetStatData(StructType NewStruct) \
	{ \
		Stat = NewStruct; \
	}

#define STAT_PROPERTY_GETTER(StructType, PropertyName) \
	static FStat Get##PropertyName##Stat() \
	{ \
		static UScriptStruct* StatStruct = StructType::StaticStruct(); \
		static FProperty* Prop = StatStruct->FindPropertyByName(TEXT(#PropertyName)); \
		return Prop; \
	}

#define STAT_ACCESSORS(ClassName, StructType, PropertyName, PropertyType) \
		STAT_PROPERTY_GETTER(StructType, PropertyName) \
		STAT_GETTER(PropertyName, PropertyType) \
		STAT_SETTER(PropertyName, PropertyType)


USTRUCT()
struct FAbnormalTimer
{
	GENERATED_BODY()

public:
	FTimerHandle AbnormalTimerHandle;
	FDateTime EndTime;
	bool bDisplayed;
	EAbnormalType AbnormalType;

	static FAbnormalTimer* MakeTimer(const FAbnormal& Abnormal);

	bool operator<(const FAbnormalTimer& Other) const
	{
		return EndTime > Other.EndTime;
	}
};

USTRUCT()
struct FAbnormalMark : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString AbnormalText;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* AbnoramlFX;
};

UCLASS()
class RLR_API UStatSet : public UObject
{
	GENERATED_BODY()
	
public:
	UStatSet();
	
	//Abnormal
	void ApplyAbnormal(const FAbnormal& abnormal);
	void ExpiredAbnormalTimer(FAbnormalTimer* ExpiredTimer);

	void AddAbnormalTimer(FAbnormalTimer* NewTimer);
	void RemoveAbnormalTimer(FAbnormalTimer* NewTimer);

	FAbnormalTimer* GetTimerTop();
	const FAbnormalMark* GetAbnormalMark(int AbnormalType);
	bool HasActivatedTimer();

protected:
	UPROPERTY()
	TObjectPtr<UDataTable> AbnoramlMarkTable;

private:
	TArray<FAbnormalTimer*> AbnoramlTimers;


	//--------------------------
	//사용법
	//--------------------------
	//자식 클래스에서 구현 필요(특수화 사용 가능)
	//template<typename T>
	//void ApplyChangeStat(FStatChangeSpec<T>& ChangeSpec)
	//{
	//};
	//변경할 곳(e.g. Manager)에서 StatSet을 받아와 FStatChangeSpec 전달
	//FStatChangeSpec{ChangedStat, NewValue}
};