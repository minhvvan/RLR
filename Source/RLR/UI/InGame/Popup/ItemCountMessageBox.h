// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MessageBoxUI.h"
#include "Structs/ItemStructs.h"
#include "ItemCountMessageBox.generated.h"

/**
 
	아이템 갯수 입력 UI

 */

 class UEditableTextBox;

UCLASS()
class RLR_API UItemCountMessageBox : public UMessageBoxUI
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
	virtual void OnClickedCancelButton() override;

	FItemData	GetItemData() {return ItemData;}
	void		SetItemData(const FItemData& Data){ItemData = Data;}
	
	int32		GetItemCount();

public:

	/*
		bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UEditableTextBox> InputEditableTextBox;

public:

	UPROPERTY()
	FItemData ItemData;
};
