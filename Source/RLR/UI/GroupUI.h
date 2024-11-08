// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "GroupUI.generated.h"

class USubUI;

UCLASS()
class RLR_API UGroupUI : public UBaseUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void BindSubUI();

	TArray<USubUI*> GetSubUIs();

private:
	TArray<USubUI*> SubUIs;
};
