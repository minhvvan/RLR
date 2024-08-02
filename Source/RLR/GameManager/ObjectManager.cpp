// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/ObjectManager.h"
#include "RLRObjects/Characters/RLRNonPlayerCharacter.h"
#include "RLR.h"

UObjectManager::UObjectManager()
{
    ConstructorHelpers::FClassFinder<ARLRNonPlayerCharacter> NPC(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Character/BP_NPC.BP_NPC_C'"));
    if (NPC.Succeeded())
    {
        NPCClass = NPC.Class;
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
