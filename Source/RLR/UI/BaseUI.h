// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameManager/RLRStruct.h"
#include "BaseUI.generated.h"

/**

 */

 class UUIManager;
 class UGameManager;

UCLASS()
class RLR_API UBaseUI : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void RefreshUI(){};
	virtual void CloseUI();

	void SetUIType(EUIType Type) {UIType = Type;}
	EUIType GetUIType() {return UIType;}

public:


	EUIType			UIType = EUIType::NONE;
	UUIManager* GetUIManager();
	UGameManager* GetGameManager();
};
