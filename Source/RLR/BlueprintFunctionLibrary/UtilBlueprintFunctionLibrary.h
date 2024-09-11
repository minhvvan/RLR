// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilBlueprintFunctionLibrary.generated.h"


/**
 
	모두가 돌려 쓸만한 기타 잡다한 함수들 모음.

 */


 using Util = UUtilBlueprintFunctionLibrary;

#define DEBUG_LOG(Message)	UUtilBlueprintFunctionLibrary::DebugLog(TEXT(Message))
#define DEBUG_MESSAGE		UUtilBlueprintFunctionLibrary::DebugMessage(__FUNCTION__, __FILE__, __LINE__)
#define CHECK_VALID(Object) UUtilBlueprintFunctionLibrary::CheckValid(Object,TEXT(#Object),__FUNCTION__, __FILE__, __LINE__)
#define DEBUG_INCOMPLETE	UUtilBlueprintFunctionLibrary::NotifyFeatureIncomplete()


UCLASS()
class RLR_API UUtilBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "RLRBlueprintLibrary | Utils")
	static void DebugLog(FString string);
	static void DebugMessage(const char* FunctionName, const char* FileName, int32 LineNumber);
	
	UFUNCTION(BlueprintCallable, Category = "RLRBlueprintLibrary | Utils")
	static void NotifyFeatureIncomplete();

	UFUNCTION(BlueprintCallable, Category = "RLRBlueprintLibrary | Utils")
	static void Checkf(UObject* Object, FString Message);

	static bool CheckValid(UObject* Object, FString Message, const char* FunctionName, const char* FileName, int32 LineNumber);

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

	UFUNCTION(BlueprintCallable, Category = "RLRBlueprintLibrary | Utils")
	static void TestCharacterList();

	/*
		Cheat Code
	*/
	
	UFUNCTION(BlueprintCallable, Category = "RLRBlueprintLibrary | Cheat")
	static void CreateItem(int32 ItemSeq);

	UFUNCTION(BlueprintCallable, Category = "RLRBlueprintLibrary | Cheat")
	static void CreateSkill(int32 SkillSeq);

	UFUNCTION(BlueprintCallable, Category = "RLRBlueprintLibrary | Cheat")
	static void CreateMonster(int32 MonsterSeq);

};

