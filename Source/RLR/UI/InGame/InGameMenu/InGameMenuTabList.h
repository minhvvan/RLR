// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "InGameMenuTabList.generated.h"

/**
 

 */

 class UListView;
 class UButton;
 class UInGameMenuTab;

UCLASS()
class RLR_API UInGameMenuTabList : public UBaseUI
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
public:

	void Open();
	void Close();


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UListView> MenuTabListView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInGameMenuTab> InGameMenuTab;
};
