// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "GameManager/RLRStruct.h"
#include "BaseDragDropOperation.generated.h"

/**
 
	슬롯을 드래그 해서 옮길 때, 전달할 데이터 클래스.

 */


 UENUM(BlueprintType)
enum class EDragType : uint8
{
	INVENTORY_SLOT,
	EQUIPMENT_SLOT,
	ITEM_QUICK_SLOT,
	SKILL_QUICK_SLOT,
	NONE,
};



 class USlotUI;

UCLASS()
class RLR_API UBaseDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData ItemData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USlotUI> Master;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D DragOffset;

	//슬
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDragType StartingDragType = EDragType::NONE;
};
