// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "UI/SubUI.h"
#include "SkillUpgrade.generated.h"

/**
 * 
 */

 class UButton;

UCLASS()
class RLR_API USkillUpgrade : public USubUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;
	virtual void OpenUI() override;
	virtual void CloseUI() override;


	void SetSkillData(FSkillData NewSkillData);




public:

/*
	Binding
*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

public:

	UPROPERTY()
	FSkillData SkillData;
};
