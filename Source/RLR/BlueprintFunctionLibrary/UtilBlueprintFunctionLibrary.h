// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilBlueprintFunctionLibrary.generated.h"

/**
 
	모두가 돌려 쓸만한 기타 잡다한 함수들 모음.

 */
UCLASS()
class RLR_API UUtilBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "RLRBlueprintLibrary | Utils")
	static void DebugLog(FString string);
	
};
