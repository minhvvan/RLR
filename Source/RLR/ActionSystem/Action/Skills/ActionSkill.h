// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Action/Action.h"
#include "GameManager/RLRStruct.h"
#include "ActionSystem/ActionSystemTypes.h"
#include "ActionSkill.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSkillExpired);

class UTimerProgressBar;

UCLASS()
class RLR_API UActionSkill : public UAction
{
	GENERATED_BODY()
	
public:
	UActionSkill();

protected:
	void PlaySkillMontage();

	virtual bool PreActivateAction();
	virtual void ActivateAction();

	UFUNCTION()
	virtual void OnCompletePlayMontage();	
	
public:
	FOnSkillExpired OnSkillExpired;

	void SetSkillData();

protected:
	const FSkillData* SkillData;

	//Action 유효 시간 타이머 핸들
	FTimerHandle SkillValidTimerHandle;

	//표시 클래스(지점이나 방향)
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARLRReticle> ReticleClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTimerProgressBar> TimerWidgetClass;

	//Timer Widget
	UPROPERTY(VisibleAnywhere, Category = Timer)
	TObjectPtr<UTimerProgressBar> TimerWidget;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;
};
