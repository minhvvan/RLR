// Fill out your copyright notice in the Description page of Project Settings.


#include "RLRObjects/Actors/RLRDropItem.h"
#include "Components/SphereComponent.h"
#include "GameManager/GameManager.h"
#include "GameManager/ObjectManager.h"

ARLRDropItem::ARLRDropItem()
{
}

void ARLRDropItem::BeginPlay()
{
	ARLRActor::BeginPlay();

	InteractionComp->OnComponentBeginOverlap.AddDynamic(this, &ARLRDropItem::OnBeginOverlap);
	InteractionComp->OnComponentEndOverlap.AddDynamic(this, &ARLRDropItem::OnEndOverlap);
}

void ARLRDropItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GameInstance->GetObjectManager()->RequestPickUpItem(ItemData);
}