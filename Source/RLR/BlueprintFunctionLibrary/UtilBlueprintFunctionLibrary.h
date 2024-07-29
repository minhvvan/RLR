// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilBlueprintFunctionLibrary.generated.h"


/**
 
	모두가 돌려 쓸만한 기타 잡다한 함수들 모음.

 */


 using Util = UUtilBlueprintFunctionLibrary;

#define DEBUG_LOG(Message) UUtilBlueprintFunctionLibrary::DebugLog(TEXT(Message))

UCLASS()
class RLR_API UUtilBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "RLRBlueprintLibrary | Utils")
	static void DebugLog(FString string);

	UFUNCTION(BlueprintCallable, Category = "RLRBlueprintLibrary | Utils")
	static void Checkf(UObject* Object, FString Message);


	/*
	
			TEST CODE. 
			블루프린트에서 이것저것 실험하려면 추가.
	*/

	UFUNCTION(BlueprintCallable, Category = "RLRBlueprintLibrary | Utils")
	static void MakeItemData();

	UFUNCTION(BlueprintCallable, Category = "RLRBlueprintLibrary | Utils")
	static void TestUpdateStatus();

	UFUNCTION(BlueprintCallable, Category = "RLRBlueprintLibrary | Utils")
	static void TestAddPartyPlayer();
	
};
