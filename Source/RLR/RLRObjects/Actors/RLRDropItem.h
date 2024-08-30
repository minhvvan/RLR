// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLRObjects/Actors/RLRInteractableActor.h"
#include "Engine/StreamableManager.h"
#include "RLRDropItem.generated.h"



DECLARE_MULTICAST_DELEGATE(FOnLoadComplete);

UCLASS(config = RLR)
class RLR_API ARLRDropItem : public ARLRInteractableActor
{
	GENERATED_BODY()
	
public:
	ARLRDropItem();

	void SetDropItemData(const FDropItem& Data);
	int GetObjectId();

	FOnLoadComplete OnLoadComplete;

protected:
	virtual void BeginPlay() override;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {}

	void ItemMeshLoadCompleted();

private:
	UPROPERTY(config)
	TArray<FSoftObjectPath> ItemMeshes;
	TSharedPtr<FStreamableHandle> ItemMeshHandle;

	TWeakPtr<FDropItem> ItemData;
};
