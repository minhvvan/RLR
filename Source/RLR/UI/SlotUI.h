// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "BaseDragDropOperation.h"
#include "SlotUI.generated.h"

/**
 
	SlotUI
		인벤토리 슬롯
		장비창 슬롯
		스킬 퀵 슬롯
		아이템 퀵 슬롯

	SlotUI를 상속 받는 대상은 드래그 헀을 때, 끌려야 하며, 다른 슬롯으로 옮기면 옮겨져야 한다.


	UDraggableWidget
		드래그 했을 때 뭘 옮기고 있는지 임시적으로 보여줄 이미지 같은 것.

	UBaseDragDropOperation
		드래그해서 다른 슬롯에 옮길 때, 해당 슬롯에 넘겨줄 데이터.

 */

 class USizeBox;
 class UImage;
 class UDraggableWidget;
 class UBaseDragDropOperation;

UCLASS()
class RLR_API USlotUI : public UBaseUI
{
	GENERATED_BODY()


public:

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION(BlueprintCallable)
	virtual void Clear();

	UFUNCTION(BlueprintCallable)
	virtual bool	IsEmpty();


	/*
		
		DragType => Native On Drop에서 응답해줄 DragDropOperation의 타입.

		ex)InventorySlot을 옮겨서 드래그드랍을 했을 경우, DragType에는 EDragType::Inventory_Slot을 넣어준다.

		ex)ItemQuickSlot의 경우 인벤토리 슬롯에서 올 수도 있고, 동일한 아이템 퀵 슬롯에서도 올 수 있으므로,
			Drag Type은 NVENTORY_SLOT, ITEM_QUICK_SLOT,2가지를 확인해주고 있다.

	*/
	UBaseDragDropOperation* CheckValidAndType(UDragDropOperation* InOperation, EDragType DragType);
	UBaseDragDropOperation* CheckValidAndType(UDragDropOperation* InOperation, EDragType DragType, EDragType DragType2);


public:
	
	/*
			Bind Widget
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USizeBox> RootSizeBox;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UImage> SlotImage;


	/*
		슬롯 이미지
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> DefaultSlotImage;


	/*
		Drag And Drop
		슬롯을 다른 슬롯으로 옮길 때 쓰이는 것들
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDraggableWidget> DraggableWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDraggableWidget> DraggedWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseDragDropOperation> DragDropOperationClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBaseDragDropOperation> DragDropOperation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D DragOffset;


	/*
	
	*/

	int32 SlotIndex = 0;
};
