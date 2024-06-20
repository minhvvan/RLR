// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "MainUI.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UMainUI : public UBaseUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void BindSubUI();
	virtual void CloseUI();
};
