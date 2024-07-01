// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abnormal/Abnormal.h"
// Main
#include"Abnormal/AbnormalStun.h"
#include "Abnormal/AbnormalBind.h"
#include"Abnormal/AbnormalFreeze.h"
#include"Abnormal/AbnormalStiffen.h"
#include"Abnormal/AbnormalProvoke.h"
#include "Abnormal/AbnormalElectric.h"
#include"Abnormal/AbnormalSilence.h"
 //Sub
#include "Abnormal/AbnormalBleeding.h"
#include "Abnormal/AbnormalBurn.h"
#include"Abnormal/AbnormalPoison.h"
#include"Abnormal/AbnormalSlow.h"

#include "GameFramework/Actor.h"
#include "GameManager/RLRStruct.h"
#include "PlayerSkill.generated.h"

UCLASS(abstract)
class RLR_API APlayerSkill : public AActor
{
	GENERATED_BODY()

public:
	// TODO : UParticleSystem Change to Niagara System

	virtual void SkillAttack(FVector position) PURE_VIRTUAL(APlayerSkill::SkillAttack, );
	virtual void Init() PURE_VIRTUAL(APlayerSkill::Init, );
	
	int GetDamage() { return Data.Damage; };
	int GetCoolTime() { return Data.CoolTime; };
	int GetLevel() { return Data.Level; };
	int GetCost() { return Data.Cost; };
	int GetDuration() { return Data.Duration; };
	void SetIsHit(bool value) { bIsHit = value; };
	
	UPROPERTY(EditAnywhere, Category = Abnormal);
	UAbnormal* Abnormal;

protected:

	virtual void OnDestroty();
	void InitData();
	
	UPROPERTY()
	FTimerHandle Timer;
	
	FSkillData Data;
	bool bIsHit = false;
};
