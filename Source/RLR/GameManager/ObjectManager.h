// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager/RLRStruct.h"
#include "ObjectManager.generated.h"

class ARLRNonPlayerCharacter;

UCLASS()
class RLR_API UObjectManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    UObjectManager();

    //NPC
    UFUNCTION()
    void SetNPCData(TArray<FNPCData> Data);

    UFUNCTION()
    void SpawnNPC();

private:
    //NPC
    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    TArray<FNPCData> NPCData;

    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    TArray<TObjectPtr<ARLRNonPlayerCharacter>> NPCInstances;

    TSubclassOf<ARLRNonPlayerCharacter> NPCClass;

    FCriticalSection NPCDataMutex;

    //Other Actor

};
