// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "SubUI.generated.h"

/**
 
	SubUI는 InGameUI가 생성되면 같이 생성되어, 
	사용되지 않을 때는 Hidden 상태로 있다가 사용될 때 Visible로 바뀌어 보이게 된다.

 */

class UTextBlock;
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
	virtual void OpenUI() override;
	virtual void CloseUI() override;

	UFUNCTION(BlueprintCallable)
	virtual void SetVisibilityToggle();

	virtual void UpdateSlotState(class USlotUI* Target) {};
	
	UFUNCTION()
    void OnDragStarted();

    UFUNCTION()
    void UpdateLocation();

	UFUNCTION()
	void UpdateLocationStop();

    UFUNCTION()
    void OnDragEnded();

    UFUNCTION()
	void SetPosition(FVector2D pos);

	UFUNCTION(BlueprintCallable)
	UMainUI*					GetMainUI() {return MainUI;}
	UFUNCTION(BlueprintCallable)
	void							SetMainUI(UMainUI* UI){MainUI = UI;}

	template<typename T>
	T*								GetMainUI(){return Cast<T>(MainUI);}

	UFUNCTION(BlueprintCallable)
	void							SetUITag(FGameplayTag Tag) {UITag = Tag;}
	UFUNCTION(BlueprintCallable)
	FGameplayTag		GetUITag(){return UITag;}

	UFUNCTION()
	void CloseUIByManager();

	void SetTitle(const FString& Title) const;

public:
	FVector2D ClickedFirstPoint;
	FVector2D ClickedCurrentPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UButton> DragButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> TxtTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<USizeBox> RootSizeBox;

private:

	UMainUI* MainUI;
	FTimerHandle DragTimer;

public:
	/*
		Input Binding
	*/


};
