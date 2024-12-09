// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "AudioOption.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API UAudioOption : public UBaseUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void Init() override;
	virtual void RefreshUI() override;
	UFUNCTION()
	virtual void OpenUI() override;
	virtual void Clear() override;
	virtual void CloseUI() override;
};
