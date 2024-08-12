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
 class UActionSystemComponent;

UCLASS()
class RLR_API UBaseUI : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void RefreshUI(){};
	virtual void OpenUI();
	virtual void Clear(){};
	virtual void CloseUI();

	void SetUIType(EUIType Type) {UIType = Type;}
	EUIType GetUIType() {return UIType;}

	virtual void SetActionSystemComponent(AActor* Owner);

public:
	EUIType			UIType = EUIType::NONE;
	UUIManager* GetUIManager();
	UGameManager* GetGameManager();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UActionSystemComponent> ActionSystemComponent;
};
