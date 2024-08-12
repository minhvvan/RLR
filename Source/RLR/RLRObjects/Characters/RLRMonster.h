// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLRObjects/Characters/RLRCharacter.h"
#include "GameManager/RLRStruct.h"
#include "RLRMonster.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API ARLRMonster : public ARLRCharacter
{
	GENERATED_BODY()
	
public:
	ARLRMonster();
	void SetStat(FMonsterStatus& Stat);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UASCWidgetComponent> HpBar;

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
};
 