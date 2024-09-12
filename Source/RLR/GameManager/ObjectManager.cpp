// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/ObjectManager.h"
#include "RLRObjects/Characters/RLRNonPlayerCharacter.h"
#include "RLRObjects/Actors/RLRInteractableActor.h"
#include "RLRObjects/Actors/RLRDropItem.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/DataManager.h"
#include "Structs/ObjectStructs.h"
#include "RLR.h"

UObjectManager::UObjectManager()
{
    //NPC 
    ConstructorHelpers::FClassFinder<ARLRNonPlayerCharacter> NPC(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Character/BP_NPC.BP_NPC_C'"));
    if (NPC.Succeeded())
    {
        NPCClass = NPC.Class;
    }   
    
    //Object
    {
        ConstructorHelpers::FClassFinder<ARLRInteractableActor> Object(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Actors/BP_Interactable_Tree.BP_Interactable_Tree_C'"));
        if (Object.Succeeded())
        {
            ObjectClasses.Add(EInteractObjectType::LOGGING, Object.Class);
        }
    }
}

void UObjectManager::SetNPCData(TArray<FNPCData> Data)
{
	FScopeLock Lock(&NPCDataMutex);

	for (auto& data : Data)
	{
        NPCData.Add(data);
	}

	SpawnNPC();
}

void UObjectManager::SpawnNPC()
{
	auto world = GetWorld();
	if (!world) return;
    if (!NPCClass) return;

	AsyncTask(ENamedThreads::GameThread, [this, world]()
	{
        for (auto& data : NPCData)
        {
            FTransform SpawnTransform;
            SpawnTransform.SetLocation(FVector(data.NPCTransform.X, data.NPCTransform.Y, data.NPCTransform.Z));

            ARLRNonPlayerCharacter* npc = world->SpawnActorDeferred<ARLRNonPlayerCharacter>(NPCClass, FTransform::Identity);
            if (!npc)
            {
                RLR_LOG(LogRLR, Log, TEXT("Failed to spawn NPC"));
                continue;
            }

            npc->SetNPCData(data);
            npc->FinishSpawning(SpawnTransform);

            NPCInstances.Add(npc);
        }
	});
}

void UObjectManager::SetObjectData(TArray<FInteractData> Data)
{
    //TODO: Add NPCDatas
    FScopeLock Lock(&ObjectDataMutex);

    for (auto& data : Data)
    {
        InteractObjectData.Add(data);
    }

    SpawnObejct();
}

void UObjectManager::SpawnObejct()
{
    auto world = GetWorld();
    if (!world) return;

    AsyncTask(ENamedThreads::GameThread, [this, world]()
        {
            for (auto& data : InteractObjectData)
            {
                if (!ObjectClasses.Contains(data.InteractType)) continue;
                auto objectClass = ObjectClasses[data.InteractType];
                if (!objectClass) continue;

                FTransform SpawnTransform;
                SpawnTransform.SetLocation(FVector(data.ObjectTransform.X, data.ObjectTransform.Y, data.ObjectTransform.Z));

                ARLRInteractableActor* object = world->SpawnActorDeferred<ARLRInteractableActor>(objectClass, FTransform::Identity);
                if (!object)
                {
                    RLR_LOG(LogRLR, Log, TEXT("Failed to spawn Object"));
                    continue;
                }

                object->SetInteractData(data);
                object->FinishSpawning(SpawnTransform);

                ObjectInstances.Add(object);
            }
        });
}

void UObjectManager::SetDropItemData(TArray<FDropItem> Data)
{
    FScopeLock Lock(&ItemDataMutex);

    for (auto& data : Data)
    {
        DropItemData.Add(data);
    }

    SpawnDropItem();
}

void UObjectManager::SpawnDropItem()
{
    auto world = GetWorld();
    if (!world) return;

    auto* dataManager = GameInstance->GetDataManager();
    if (!dataManager) return;
    
    AsyncTask(ENamedThreads::GameThread, [this, world, dataManager]()
        {

            for (auto& data : DropItemData)
            {
                RLR_LOG(LogRLR, Warning, TEXT("DropItemData Size: %d"), DropItemData.Num());
                RLR_LOG(LogRLR, Warning, TEXT("DropItemInstances Size: %d"), DropItemInstances.Num());
                TSubclassOf<ARLRDropItem> itemClass = dataManager->GetObjectClass<ARLRDropItem>(TEXT("BP_DropItem"));
                if (!itemClass) continue;

                FTransform SpawnTransform;
                SpawnTransform.SetLocation(data.ObjectTransform);

                ARLRDropItem* object = world->SpawnActorDeferred<ARLRDropItem>(itemClass, FTransform::Identity);
                if (!object)
                {
                    RLR_LOG(LogRLR, Log, TEXT("Failed to spawn DropItem"));
                    continue;
                }

                object->SetDropItemData(data);
                object->FinishSpawning(SpawnTransform);
                DropItemInstances.Add(object);

                //object->OnLoadComplete.AddLambda([object, SpawnTransform, this]()
                //{
                //    object->FinishSpawning(SpawnTransform);
                //    DropItemInstances.Add(object);
                //});
            }
            DropItemData.Empty();
        });
}

TObjectPtr<ARLRDropItem> UObjectManager::GetObjectInstanceById(int ObjectId)
{
    TObjectPtr<ARLRDropItem> result = nullptr;

    for (auto dropItem : DropItemInstances)
    {
        if (dropItem->GetObjectId() == ObjectId)
        {
            result = dropItem;
            break;
        }
    }

    return result;
}

void UObjectManager::RequestPickUpItem(const FDropItem& Dropitem)
{
    //TODO: 아이템 획득 pkt보내기
    GameInstance->GetNetworkManager()->SendAddItemPacket(Dropitem.ObjectId, Dropitem.Num);
    //클라 -> 서버(아이템 요청)
    RLR_LOG(LogRLR, Log, TEXT("Called RequestPickUpItem"));
    ResponePickUpItem(Dropitem.ObjectId, true);
}

void UObjectManager::ResponePickUpItem(int ObjectId, bool bSuccess)
{
    if (!bSuccess) return;

    AsyncTask(ENamedThreads::GameThread, [ObjectId, this]()
        {
            auto dropItemInstance = GetObjectInstanceById(ObjectId);
            if (!dropItemInstance) return;
            
            float DelayTime = 1.0f;
            FTimerHandle TimerHandle;

            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, dropItemInstance]()
                {
		            DropItemInstances.Remove(dropItemInstance);
		            dropItemInstance->Destroy();
                }, DelayTime, false);
        });
}