// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameManager/DataManager.h"
#include "ItemInformation.generated.h"

/**
 * 
 */

 class URichTextBlock;
 class UImage;

UCLASS()
class RLR_API UItemInformation : public UUserWidget
{
	GENERATED_BODY()
	

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemInformationText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;


public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FItemData	GetItemData(){return ItemData;}

	UFUNCTION(BlueprintCallable)
	void				SetItemData(FItemData NewData);


private:

	UPROPERTY()
	FItemData ItemData;

};
