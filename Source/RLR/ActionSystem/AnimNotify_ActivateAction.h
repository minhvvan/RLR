// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AnimNotify_ActivateAction.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UAnimNotify_ActivateAction : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_ActivateAction();

	virtual void Notify(USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference);

protected:
	UPROPERTY(EditAnywhere, Category=Action)
	FGameplayTag TriggerActionTag;
};
