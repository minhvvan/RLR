// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MainUI.h"
#include "LobbyMainUI.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API ULobbyMainUI : public UMainUI
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct();
	virtual void RefreshUI() override;
	virtual void Clear() override;
	virtual void SetInputMode() override;


};
