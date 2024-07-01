// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "SubUI.generated.h"

/**
 
	SubUI는 InGameUI가 생성되면 같이 생성되어, 
	사용되지 않을 때는 Hidden 상태로 있다가 사용될 때 Visible로 바뀌어 보이게 된다.

 */

 class UButton;
 class UCanvasPanelSlot;
 class UMainUI;
 class USizeBox;
 class USlotUI;

UCLASS()
class RLR_API USubUI : public UBaseUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	virtual void SetVisibilityToggle();
	virtual void OpenUI();

	virtual void CloseUI();
	virtual void UpdateSlotState(class USlotUI* Target) {};
	
	UFUNCTION()
    void OnDragStarted();

    UFUNCTION()
    void UpdateLocation();

	UFUNCTION()
	void UpdateLocationStop();

    UFUNCTION()
    void OnDragEnded();

	UFUNCTION(BlueprintCallable)
	UMainUI* GetMainUI() {return MainUI;}
	UFUNCTION(BlueprintCallable)
	void			SetMainUI(UMainUI* UI){MainUI = UI;}

	template<typename T>
	T*				GetMainUI(){return Cast<T>(MainUI);}

public:

	FVector2D ClickedFirstPoint;
	FVector2D ClickedCurrentPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> DragButton;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USizeBox> RootSizeBox;

private:

	UMainUI* MainUI;
	FTimerHandle DragTimer;
};
