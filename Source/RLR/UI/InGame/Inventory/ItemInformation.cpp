// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Inventory/ItemInformation.h"
#include "Components/RichTextBlock.h"
#include "Components/Image.h"
#include "ItemInformation.h"
#include "UI/BaseUI.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"

void UItemInformation::NativeConstruct()
{
	Super::NativeConstruct();	

}

void UItemInformation::SetItemData(FItemData NewData)
{
	ItemData = NewData;

	ItemInformationText->SetText(FText::FromString(ItemData.TEXT));
	//ItemNameText->SetText(FText::FromString(ItemData.NAME));
	SetItemNameText(NewData);
	SetItemStatusText(NewData);
	ItemImage->SetBrushFromTexture(ItemData.ItemImage);
}

void UItemInformation::SetItemStatusText(FItemData NewData)
{

	FStatus ItemStatus = NewData.ITEM_STATUS;

	/*
		0이면 넣지 않고, 수치가 있으면 설명에 넣는다.
	*/

	ItemStatusText->SetText(FText::FromString( ItemStatus.ToString()));


}

void UItemInformation::OpenItemInformation(UBaseUI* From)
{
	OpenUI();

	//아이템 정보창은 슬롯 옆에서 열어준다.
	FVector2D V1 =	UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	V1	-= PositionOffset;
	Cast<UCanvasPanelSlot>(Slot)->SetPosition(V1);
}

