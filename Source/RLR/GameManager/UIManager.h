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
class USlotUI;

UCLASS()
class RLR_API UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void OpenMainUI(TSubclassOf<UMainUI> UIClass);
	void OpenSubUINearTargetSlot(USlotUI* Target);
	void CloseSubUINearTargetSlot();
	void SetZOrderToTop(USubUI* Target);

	void CloseFrontSubUI ();
	void CloseAllSubUI();

	UMainUI* GetMainUI();

	void ToggleSubUI(int inputID);
	void AdjustZOrder();

private:

	TObjectPtr<UMainUI> MainUI;	
	TArray<USubUI*> SubUIStack;
	int32 ZOrder = 0;

};
