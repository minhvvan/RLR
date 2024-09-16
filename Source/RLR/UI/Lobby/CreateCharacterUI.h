// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "CreateCharacterUI.generated.h"

/**
 * 
 */

UCLASS()
class RLR_API UCreateCharacterUI : public UBaseUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void Init();
	virtual void RefreshUI() override;
	virtual void Clear() override;

public:

	/*
		Bind
	*/

};
