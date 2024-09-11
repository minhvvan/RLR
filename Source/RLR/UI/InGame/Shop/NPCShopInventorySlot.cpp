// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCShopInventorySlot.h"
#include "RLR.h"

//void UNPCShopInventorySlot::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
//{
//	UUserWidget::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
//}
//
//void UNPCShopInventorySlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
//{
//	UUserWidget::NativeOnDragLeave(InDragDropEvent, InOperation);
//}

FReply UNPCShopInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = UUserWidget::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		//TODO:판매탭에 추가
		RLR_LOG(LogRLR, Log, TEXT("right"));
	}

	return result;
}
