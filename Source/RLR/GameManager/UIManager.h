// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIManager.generated.h"

/**
 
	UI를 관리할 매니저.

 */

 class UBaseUI;
 class UMainUI;
class USubUI;

UCLASS()
class RLR_API UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	
	void ShowMainUI(TSubclassOf<UMainUI> UIClass);
	void ShowSubUI(USubUI* Target);
	void SetZOderUI(USubUI* Target);

	void CloseSubUI(USubUI* Target);
	void CloseSubUI();
	void CloseAllSubUI();

	UMainUI* GetMainUI();


private:

	TObjectPtr<UMainUI> MainUI;	
	TArray<USubUI*> SubUIStack;
	int32 ZOrder = 0;
};
