// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "EnhanceOverlayUI.generated.h"

class UConfirmMessageBox;
class UEnhanceResultUI;
class UEquipmentList;
class UEnhanceUI;

UCLASS()
class RLR_API UEnhanceOverlayUI : public USubUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;

	UFUNCTION()
	void OnEnhanceButtonClicked();

	UFUNCTION()
	void OnClickedAcceptButton();

	UFUNCTION()
	void OnClickedCancelButton();

	UFUNCTION()
	void ResultConfirmButtonClicked();

	void OpenSuccessUI();
	void OpenFailUI();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquipmentList> EquipmentList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEnhanceUI> EnhanceUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEnhanceResultUI> EnhanceResultUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UConfirmMessageBox> ConfirmMessageBox;
};
