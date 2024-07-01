// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameManager/DataManager.h"
#include "UI/SubUI.h"
#include "ItemInformation.generated.h"

/**
 * 
 */

 class URichTextBlock;
 class UImage;
 class UBaseUI;

UCLASS()
class RLR_API UItemInformation : public USubUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FItemData	GetItemData(){return ItemData;}

	UFUNCTION(BlueprintCallable)
	void				SetItemData(FItemData NewData);

	//	Rich Text 때문에 블루프린트에서 함수 구현.
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void				SetItemNameText(FItemData NewData);

	UFUNCTION(BlueprintCallable)
	void				SetItemStatusText(FItemData NewData);


	 void				OpenItemInformation(UBaseUI* From);

	 virtual void UpdateSlotState(class USlotUI* Target);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FVector2D	PositionOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemInformationText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemRarityAndTypeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemLevelText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemStatusText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;

private:

	UPROPERTY()
	FItemData ItemData;

};
