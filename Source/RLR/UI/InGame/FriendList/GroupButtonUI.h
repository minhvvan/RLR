// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/UtilStructs.h"
#include "Blueprint/UserWidget.h"
#include "GroupButtonUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGroupButtonDropped, UGroupButtonUI*, DroppedButton, UGroupButtonUI*, TargetButton);

DECLARE_DELEGATE_TwoParams(FOnGroupRightClickedSignature, FVector2D, UGroupButtonUI*);
DECLARE_DELEGATE_OneParam(FGroupClickedOnList,UGroupButtonUI*);

class UButton;
class UTextBlock;
class UVerticalBox;
class UFriendListUI;
class UFriendGroupDragDropOperation;

/**
 * 그룹 추가 시 추가되는 Button
 */
UCLASS()
class RLR_API UGroupButtonUI : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    void SetGroupData(const FFriendGroupResult& NewGroupData) {GroupData = NewGroupData;};
    void SetGroupInfo(int NewGroupSeq, FString NewGroupName);
    FString GetGroupName();

    UFUNCTION()
    int32 GetGroupSeq() const { return GroupSeq; }

    UFUNCTION()
    void OnGroupButtonClicked();

    virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
    virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    FOnGroupRightClickedSignature OnGroupRightClicked;
    FGroupClickedOnList GroupClickedOnList;

public:
    /* TODO : 친구목록의 플레이어 정보 더 추가하기 */
    UPROPERTY(meta = (BindWidget))
    UButton* GroupButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* GroupNameText;

    UPROPERTY(meta = (BindWidgetOptional))
    UVerticalBox* GroupContainer;

    UPROPERTY()
    UFriendListUI* FriendListUI;
    
    UPROPERTY(BlueprintAssignable)
    FOnGroupButtonDropped OnGroupButtonDropped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UFriendGroupDragDropOperation> DragDropOperationClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D DragOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group")
    bool bIsInGroupList = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group")
    bool bIsInGroupOrderList = false;

private:
    int GroupSeq;
    FString GroupName;

    FFriendGroupResult GroupData;
};
