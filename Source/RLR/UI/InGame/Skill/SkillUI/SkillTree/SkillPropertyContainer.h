// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "Structs/SkillStructs.h"
#include "SkillPropertyContainer.generated.h"

class USkillPropertySlot;
class UImage;
/**
 * 
 */
UCLASS()
class RLR_API USkillPropertyContainer : public UBaseUI
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void RefreshUI();
	virtual void SetSkillData(FSkillData NewSkillData);
	void SetSkillLearned(bool Learned);

private:
	void SetPropertiesUnlock(int UnlockNum);

private:
	UPROPERTY(VisibleAnywhere, Meta = (BindWidget))
	TObjectPtr<UImage> ImgSkill;
	
	UPROPERTY(VisibleAnywhere, Meta = (BindWidget))
	TObjectPtr<USkillPropertySlot> SkillPropertySlot_1;
	
	UPROPERTY(VisibleAnywhere, Meta = (BindWidget))
	TObjectPtr<USkillPropertySlot> SkillPropertySlot_2;

	UPROPERTY(VisibleAnywhere, Meta = (BindWidget))
	TObjectPtr<USkillPropertySlot> SkillPropertySlot_3;
	
	UPROPERTY(VisibleAnywhere, Meta = (BindWidget))
	TObjectPtr<USkillPropertySlot> SkillPropertySlot_4;

	UPROPERTY(VisibleAnywhere, Meta = (BindWidget))
	TObjectPtr<USkillPropertySlot> SkillPropertySlot_5;
	
public:
	FSkillData SkillData;

private:
	TArray<TObjectPtr<USkillPropertySlot>> SkillPropertySlots;
	bool bLearned;
};