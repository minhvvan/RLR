// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/ObjectManager.h"
#include "RLRObjects/Characters/RLRNonPlayerCharacter.h"
#include "RLRObjects/Actors/RLRInteractableActor.h"
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
	//TODO: Add NPCDatas
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
        for (auto data : NPCData)
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
            for (auto data : InteractObjectData)
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
