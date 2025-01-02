// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "SkillPropertySlot.generated.h"

class UImage;

UCLASS()
class RLR_API USkillPropertySlot : public USlotUI
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Meta = (BindWidget))
	TObjectPtr<UImage> SkillLockImage;

public:
	void SetPropertyImage();
	
	void UnLock() const;
	void Lock() const;
};
