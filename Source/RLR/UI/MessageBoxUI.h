// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/PopupUI.h"
#include "Structs/UtilStructs.h"
#include "MessageBoxUI.generated.h"

/**
	메시지 박스 UI 
	ex) 아이템 갯수 입력 UI.

 */

class UTextBlock;
class UButton;

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnButtonClicked, class UMessageBoxUI*, MessageBox);

UCLASS()
class RLR_API UMessageBoxUI : public UPopupUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void Init() override;
	virtual void RefreshUI() override;
	virtual void OpenUI();
	virtual void Clear() override;
	virtual void CloseUI();

public:

	UFUNCTION()
	virtual void OnClickedConfirmButton();
	UFUNCTION()
	virtual void OnClickedCancelButton();

public:

	virtual void SetMessageText(FString Message);
	virtual void SetMessageText(FText Message);

public:
	/*
		bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> MessageText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UButton> ConfirmButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UButton> CancelButton;

public:
	
	UPROPERTY()
	FOnButtonClicked OnConfirmButtonClickedDelegate;

	UPROPERTY()
	FOnButtonClicked OnCancelButtonClickedDelegate;

public:

	//기타 정보 저장용
	//ex 거래창에서 상대방 정보를 저장할 필요가 있는데, 그런거 임시 저장
	UPROPERTY()
	TMap<FString, FEtcPropertyData>	EtcPropertyMap;
};
