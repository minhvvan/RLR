// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameManager/RLRStruct.h"
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

#define STAT_ACCESSORS(ClassName, PropertyName, PropertyType) \
		STAT_GETTER(PropertyName, PropertyType) \
		STAT_SETTER(PropertyName, PropertyType)


UCLASS()
class RLR_API UStatSet : public UObject
{
	GENERATED_BODY()
	
public:
	UStatSet();
};