// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MessageBoxUI.h"
#include "NotificationMessageBox.generated.h"

/**
 * 
 */

 class UTextBlock;

UCLASS()
class RLR_API UNotificationMessageBox : public UMessageBoxUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void Init() override;
	virtual void RefreshUI() override;
	virtual void OpenUI() override;
	virtual void Clear() override;
	virtual void CloseUI() override;

public:

	virtual void OnClickedConfirmButton() override;

public:

	virtual void SetText(FString MessageString) override;

public:

	/*
		bind
	*/
};
