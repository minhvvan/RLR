// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRObjects/Actors/RLRDropItem.h"
#include "Components/SphereComponent.h"
#include "GameManager/GameManager.h"
#include "GameManager/ObjectManager.h"
#include "GameManager/MonsterManager.h"
#include "Structs/ObjectStructs.h"
#include "Engine/AssetManager.h"

ARLRDropItem::ARLRDropItem()
{
}

void ARLRDropItem::SetDropItemData(const FDropItem& Data)
{
	ItemData = MakeShared<FDropItem>(Data);

	//SetMesh
	if (ItemMeshes.IsEmpty() || Data.ObjectSeq >= ItemMeshes.Num()) return;
	ItemMeshHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(ItemMeshes[Data.ObjectSeq], FStreamableDelegate::CreateUObject(this, &ARLRDropItem::ItemMeshLoadCompleted));
}

int ARLRDropItem::GetObjectId()
{
	if (!ItemData.IsValid()) return -1;
	return ItemData->ObjectId;
}

void ARLRDropItem::BeginPlay()
{
	ARLRActor::BeginPlay();

	InteractionComp->OnComponentBeginOverlap.AddDynamic(this, &ARLRDropItem::OnBeginOverlap);
	InteractionComp->OnComponentEndOverlap.AddDynamic(this, &ARLRDropItem::OnEndOverlap);
}

void ARLRDropItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!ItemData.IsValid()) return;
	GameInstance->GetObjectManager()->RequestPickUpItem(*ItemData);
}

void ARLRDropItem::ItemMeshLoadCompleted()
{
	if (ItemMeshHandle.IsValid())
	{
		UStaticMesh* itemMesh = Cast<UStaticMesh>(ItemMeshHandle->GetLoadedAsset());
		if (itemMesh && Mesh)
		{
			Mesh->SetStaticMesh(itemMesh);
		}
	}

	ItemMeshHandle->ReleaseHandle();
	OnLoadComplete.Broadcast();
}

