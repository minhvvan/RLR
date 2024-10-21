// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/UtilStructs.h"
#include "Blueprint/DragDropOperation.h"
#include "FriendGroupDragDropOperation.generated.h"

class UGroupButtonUI;
/**
 * 
 */
UCLASS()
class RLR_API UFriendGroupDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	UFriendGroupDragDropOperation();

	void SetFriendGroupData(const FFriendGroupResult& NewGroupData);
	const FFriendGroupResult& GetFriendGroupData();

	virtual void	Clear();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFriendGroupResult GroupData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGroupButtonUI> DragReference;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D DragOffset;
};
