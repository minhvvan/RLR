// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "SkillPropertyContainer.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API USkillPropertyContainer : public UBaseUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	virtual void OpenUI();
	virtual void CloseUI();
	virtual void RefreshUI();
	virtual void SetSkillData(FSkillData NewSkillData);

public:

	FSkillData SkillData;
};
