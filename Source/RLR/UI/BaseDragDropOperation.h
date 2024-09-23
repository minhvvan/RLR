// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "GameManager/RLRStruct.h"
#include "UI/SlotUI.h"
#include "Structs/SkillStructs.h"
#include "Structs/ItemStructs.h"
#include "BaseDragDropOperation.generated.h"

/**
 
	슬롯을 드래그 해서 옮길 때, 전달할 데이터 클래스.

 */




 class USlotUI;

UCLASS()
class RLR_API UBaseDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UBaseDragDropOperation();

	void			SetItemData(const FItemData& NewItemData);
	void			SetItemResourceData(const FItemResource& NewItemResourceData);
	void			SetSkillData(const FSkillData& NewSkillData);

	const FItemData&		GetItemData();
	const FSkillData&		GetSkillData();
	const FItemResource&	GetItemResource();

	void			SetMaster(USlotUI* From) {Master = From;}
	USlotUI*		GetMaster(){return Master;}

	void			SetDragedSlotType(ESlotType Type){DragedSlotType = Type;}
	ESlotType		GetDragedSlotType(){return DragedSlotType;}


	virtual void	Clear();
	virtual bool	IsEmpty();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemResource ItemResourceData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData SkillData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USlotUI> Master;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D DragOffset;

	//옮기고 있는 슬롯의 타입.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESlotType DragedSlotType;
};
