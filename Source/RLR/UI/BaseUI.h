// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUI.generated.h"

/**
	인게임 Main UI 안에 들어가는, 드래그 가능한 UI들의 부모가 될 예정.
 */

 class UUIManager;

UCLASS()
class RLR_API UBaseUI : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void CloseUI();

public:

	UUIManager* GetUIManager();
};
