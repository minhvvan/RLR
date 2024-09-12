// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager/RLRStruct.h"
#include "ObjectManager.generated.h"

class ARLRNonPlayerCharacter;
class ARLRInteractableActor;
class ARLRDropItem;

UCLASS()
class RLR_API UObjectManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    UObjectManager();

    //NPC
    UFUNCTION()
    void SetNPCData(TArray<FNPCData> Data);

    const FNPCData& GetNPCDataBySeq(int NPCSeq);

    //Object
    UFUNCTION()
    void SetObjectData(TArray<FInteractData> Data);

    //DropItem
    UFUNCTION()
    void SetDropItemData(TArray<FDropItem> Data);

    //아이템 획득 요청
    UFUNCTION()
    void RequestPickUpItem(const FDropItem& Dropitem);

    //아이템 획득 요청 결과 처리
    UFUNCTION()
    void ResponePickUpItem(int ObjectId, bool bSuccess);

protected:
    UFUNCTION()
    void SpawnNPC();

    UFUNCTION()
    void SpawnObejct();

    UFUNCTION()
    void SpawnDropItem();

    TObjectPtr<ARLRDropItem> GetObjectInstanceById(int ObjectId);

private:
    //NPC
    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    TArray<FNPCData> NPCData;

    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    TArray<TObjectPtr<ARLRNonPlayerCharacter>> NPCInstances;

    TSubclassOf<ARLRNonPlayerCharacter> NPCClass;

    FCriticalSection NPCDataMutex;

    //Object
    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    TArray<FInteractData> InteractObjectData;

    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    TArray<TObjectPtr<ARLRInteractableActor>> ObjectInstances;

    TMap<EInteractObjectType,TSubclassOf<ARLRInteractableActor>> ObjectClasses;

    FCriticalSection ObjectDataMutex;

    //Item
    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    TArray<FDropItem> DropItemData;

    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    TArray<TObjectPtr<ARLRDropItem>> DropItemInstances;

    FCriticalSection ItemDataMutex;
};
