// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "GameManager/RLRStruct.h"
#include "GameManager/GameplayTagManager.h"

#include "Structs/UtilStructs.h"
#include "MainUI.generated.h"

/**
 * 
 */

 class USubUI;
 class USlotUI;
 class UCanvasPanel;

UCLASS()
class RLR_API UMainUI : public UBaseUI
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Canvas;

public:

	virtual void NativeConstruct() override;
	virtual void BindSubUI();
	virtual void RefreshUI() override;
	virtual void CloseUI() {};

	bool IsOpenSubUI(FGameplayTag InputTag);
	void ToggleSubUI(FGameplayTag InputTag);
	template<typename T = USubUI>
	T* GetSubUI(FGameplayTag InputTag);
	virtual USubUI* OpenSubUI(FGameplayTag InputTag);
	virtual void CloseSubUI(FGameplayTag InputTag);
	void CloseFrontSubUI();
	void CloseAllSubUI();

	void AdjustZOrder();
	void SetZOrderToTop(FGameplayTag Tag);
	void SetSubUIPosition(FGameplayTag Tag, FVector2D NewPos);
	void OpenSubUINearTargetSlot(USlotUI* Target, FGameplayTag Tag);		//해당 슬롯 옆에 Sub UI를 띄운다.

	virtual void OnPageActivated() {};

protected:
	TMap<FGameplayTag, USubUI*>		SubUIMap;
	TArray<USubUI*>					SubUIStack;
};

template<typename T>
inline T* UMainUI::GetSubUI(FGameplayTag InputTag)
{
	if (!SubUIMap.Contains(InputTag)) return nullptr;
	return Cast<T>(SubUIMap[InputTag]);
}
