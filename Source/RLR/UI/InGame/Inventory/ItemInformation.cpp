// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Inventory/ItemInformation.h"
#include "Components/RichTextBlock.h"
#include "Components/Image.h"
#include "ItemInformation.h"
#include "UI/BaseUI.h"
#include "UI/SlotUI.h"
#include "UI/InGame/Inventory/InventorySlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
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
	UInventorySlot* TargetSlot = Cast<UInventorySlot>(Target);
	if (!TargetSlot) return;

	SetItemData(TargetSlot->GetItemData());

	//마우스 커서 위치를 가져온다.
	FVector2D V1 = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	//슬롯의 크기: 슬롯의 크기는 같으니까 임의의 슬롯으로 설정했는데
	//슬롯 크기가 변하지 않거나 특정 값으로 설정을 한다면 static함수로 크기 받아오게 하고 싶음
	V1.X -= TargetSlot->RootSizeBox->GetWidthOverride() * 2;

	float SubUIRootBoxWidth = RootSizeBox->GetWidthOverride();
	//띄우려는 창의 크기를 고려해서 위치를 조정해준다.
	if (V1.X > SubUIRootBoxWidth)
	{
		V1.X -= SubUIRootBoxWidth / 2;
	}
	else
	{
		V1.X += SubUIRootBoxWidth / 2 + TargetSlot->RootSizeBox->GetWidthOverride() * 4;
	}

	Cast<UCanvasPanelSlot>(Slot)->SetPosition(V1);
}