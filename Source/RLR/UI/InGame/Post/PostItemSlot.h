// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SlotUI.h"
#include "UI/BaseUI.h"
#include "PostItemSlot.generated.h"

class UTextBlock;
class UTImage;
class UPostWriteTabWidget;
class UPostOverlayUI;


UCLASS()
class RLR_API UPostItemSlot : public USlotUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void RefreshUI() override;

	virtual void NativeOnMouseEnter( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual void NativeOnMouseLeave( const FPointerEvent& InMouseEvent ) override;
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;

	// 인벤토리에서 드래그된 아이템을 처리하는 함수
	bool HandleInventoryItemDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	UFUNCTION()
	void SetSlot(int64 NewitemId);

	virtual void Clear() override;
public:

	/*
		슬롯 이미지
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UImage> ItemRarityImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

	UPROPERTY(EditAnywhere)
	int64 itemId;

public:
	UPostOverlayUI* PostUI;
};
