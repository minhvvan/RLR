// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
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


	드래그 드랍이 진행되는 과정.

	1.NativeOnDragDetected
		드래그를 감지 후, 질질 끌고 다닐 임시적인 위젯 생성.
		UWidgetBlueprintLibrary::CreateDragDropOperation을 사용하며,
		어떤 위젯을 만들어야 하는지 알려줘야 할 설계도, DragDropOperationClass에 값을 할당해둘 필요가 있다.

	2.NativeOnDrop
		이름 그대로 끌고왔던 위젯을 드랍했을 때 실행되는 함수.

	만약 드래그 드랍 기능을 만들고 싶다면, NativeOnDragDetected, NativeOnDrop 기능을 잘 만들어주자.

 */



 class USizeBox;
 class UImage;
 class UButton;
 class UDraggableWidget;
 class UBaseDragDropOperation;

 
 UENUM(BlueprintType)
enum class ESlotType : uint8
{
	INVENTORY_SLOT,
	EQUIPMENT_SLOT,
	ITEM_QUICK_SLOT,
	SKILL_QUICK_SLOT,
	SKILL_SETTING_QUICK_SLOT,
	SKILL_SETTING_LIST_SLOT,
	NONE,
};

UCLASS()
class RLR_API USlotUI : public UBaseUI
{
	GENERATED_BODY()


public:

	virtual void NativeConstruct() override;

	//드래그 드랍
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	UFUNCTION()
	virtual void OnClickedSlotButton();
		
	UFUNCTION()
	virtual void OnHoveredSlotButton();
		
	UFUNCTION()
	virtual void OnUnHoveredSlotButton();

	UFUNCTION()
	virtual void SetSlotImage(UTexture2D* NewImage);


	UFUNCTION(BlueprintCallable)
	virtual void Clear();

	UFUNCTION(BlueprintCallable)
	virtual bool IsEmpty();

	virtual UBaseDragDropOperation* GetSlotData();
	virtual void					SetItemData(FItemData& NewItemData);
	virtual	const FItemData&		GetItemData();

	virtual void					SetSkillData(FSkillData NewSkillData);
	virtual const FSkillData&		GetSkillData();

	virtual void					SetSlotType(ESlotType Type){SlotType = Type;}
	virtual const ESlotType			GetSlotType(){return SlotType;}

	void							SetSlotIndex(int32 NewIndex){SlotIndex = NewIndex;}
	int32							GetSlotIndex(){return SlotIndex;}

	TSubclassOf<UDraggableWidget>	GetDraggableWidgetClass(FString Name = FString());
	TSubclassOf<UBaseDragDropOperation> GetDragDropOperationClass(FString Name = FString());

	/*
		CheckValidAndType.

		슬롯을 다른 슬롯한테 드래그 드랍했을 때, 이게 유효한 방법인지 판단하기 위한 부분. 

		ex)InventorySlot을 옮겨서 드래그드랍을 했을 경우, DragType에는 EDragType::Inventory_Slot을 넣어준다.
			인벤토리 슬롯은 같은 인벤토리 슬롯에서만 정보를 받아야 한다.

		ex)ItemQuickSlot의 경우 인벤토리 슬롯에서 올 수도 있고, 동일한 아이템 퀵 슬롯에서도 올 수 있으므로,
			Drag Type은 NVENTORY_SLOT, ITEM_QUICK_SLOT,2가지를 확인해주고 있다.

	*/
	UBaseDragDropOperation* CheckValidAndType(UDragDropOperation* InOperation, ESlotType DragType);
	UBaseDragDropOperation* CheckValidAndType(UDragDropOperation* InOperation, ESlotType DragType, ESlotType DragType2);


public:
	
	/*
			Bind Widget
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USizeBox> RootSizeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UImage> SlotImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> SlotButton;


	/*
		슬롯 이미지
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> DefaultSlotImage = nullptr;

	UTexture2D*				GetDefaultSlotImage();


	/*
		Drag And Drop
		슬롯을 다른 슬롯으로 옮길 때 쓰이는 것들
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDraggableWidget> DraggableWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDraggableWidget> DraggedWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseDragDropOperation> DragDropOperationClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBaseDragDropOperation> DragDropOperation = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESlotType SlotType = ESlotType::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D DragOffset;


	/*
	
	*/

	int32 SlotIndex = 0;
};
