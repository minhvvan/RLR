// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Inventory/ItemInformation.h"
#include "Components/RichTextBlock.h"
#include "Components/Image.h"
#include "ItemInformation.h"
#include "UI/BaseUI.h"
#include "UI/SlotUI.h"
#include "UI/InGame/Inventory/InventorySlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Structs/PlayerStructs.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "GameManager/DataManager.h"
#include "Structs/ItemStructs.h"
#include "Structs/UtilStructs.h"

void UItemInformation::NativeConstruct()
{
	Super::NativeConstruct();	
	SetUIType(EUIType::ITEMINFOMATION);
}

void UItemInformation::SetItemData(const FItemData& NewData)
{
	ItemInformationText->SetText(NewData.TEXT);
	ItemNameText->SetText(NewData.NAME);
	SetItemNameText(NewData);
	SetItemStatusText(NewData);
	ItemImage->SetBrushFromTexture(NewData.ItemImage);
}

void UItemInformation::SetItemStatusText(const FItemData& NewData)
{

	FItemStatus ItemStatus = NewData.ITEM_STATUS;

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

void UItemInformation::UpdateSlotState(USlotUI* Target)
{
	SetItemData(Target->GetItemData());

	auto geo = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld());
	FVector2D position = geo.AbsoluteToLocal(Target->GetCachedGeometry().GetAbsolutePosition()) + Target->GetCachedGeometry().GetLocalSize() / 2.f;

	position.X += (RootSizeBox->WidthOverride / 2.f) + (Target->RootSizeBox->WidthOverride / 2.f);
	position.Y += (RootSizeBox->HeightOverride / 2.f) - (Target->RootSizeBox->HeightOverride / 2.f);

	//띄우려는 창의 크기를 고려해서 위치를 조정해준다.
	FVector2D viewportSize = geo.GetLocalSize();
	
	if (position.X + RootSizeBox->WidthOverride / 2.f > viewportSize.X)
	{
		position.X -= (Target->RootSizeBox->WidthOverride + RootSizeBox->WidthOverride);
	}

	if (position.Y + RootSizeBox->HeightOverride / 2.f > viewportSize.Y)
	{
		position.Y -= ((position.Y + RootSizeBox->HeightOverride / 2.f) - viewportSize.Y);
	}

	//pos = center pos
	Cast<UCanvasPanelSlot>(Slot)->SetPosition(position);
	Cast<UCanvasPanelSlot>(Slot)->SetZOrder(1);
}