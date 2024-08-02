// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLRObjects/Characters/RLRCharacter.h"
#include "GameManager/RLRStruct.h"
#include "RLRNonPlayerCharacter.generated.h"

class USphereComponent;
class UDialogueUI;

UCLASS()
class RLR_API ARLRNonPlayerCharacter : public ARLRCharacter
{
	GENERATED_BODY()
	
public:
	ARLRNonPlayerCharacter();

	void SetNPCData(const FNPCData& Data);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> InteractionComp;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere, Category = Action)
	TMap<FGameplayTag, TSubclassOf<UAction>> GiveToPlayerActions;

	UPROPERTY(EditAnywhere, Category = Action)
	TSubclassOf<UDialogueUI> DialogueUI;

	FNPCData NPCData;
};