// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/ItemInformation.h"
#include "Components/RichTextBlock.h"
#include "Components/Image.h"
#include "ItemInformation.h"

void UItemInformation::SetItemData(FItemData NewData)
{
	ItemData = NewData;


	ItemInformationText->SetText(FText::FromString(ItemData.TEXT));
	ItemNameText->SetText(FText::FromString(ItemData.NAME));
	ItemImage->SetBrushFromTexture(ItemData.ItemImage);
}
