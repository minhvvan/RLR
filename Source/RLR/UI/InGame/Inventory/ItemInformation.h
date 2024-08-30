// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/SubUI.h"
#include "ItemInformation.generated.h"

/**
 * 
 */

 class URichTextBlock;
 class UImage;
 class UBaseUI;

UCLASS()
class RLR_API UItemInformation : public USubUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	//Item정보 표시 창에서 GetData를 할 상황이 없을 것 같음
	//확인 이후 삭제 필요
	//UFUNCTION(BlueprintCallable, BlueprintPure)
	//FItemData GetItemData(){return *ItemData.Pin().Get();}

	UFUNCTION(BlueprintCallable)
	void SetItemData(const FItemData& NewData);

	//	Rich Text 때문에 블루프린트에서 함수 구현.
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetItemNameText(const FItemData& NewData);

	UFUNCTION(BlueprintCallable)
	void SetItemStatusText(const FItemData& NewData);

	void OpenItemInformation(UBaseUI* From);

	virtual void UpdateSlotState(class USlotUI* Target);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FVector2D	PositionOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemInformationText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemRarityAndTypeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemLevelText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> ItemStatusText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;

private:
	//Item정보 표시 창에서 Data를 저장할 상황이 없을 것 같음
	//확인 이후 삭제 필요
	//UPROPERTY()
	//TWeakPtr<FItemData> ItemData;

};
