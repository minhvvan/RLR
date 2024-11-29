// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ItemStructs.h"
#include "EnhanceResultUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConfirmButotnClicked);

class UEnhanceSlot;
class UEnhanceUI;
class UWidgetSwitcher;
class URichTextBlock;
class UVerticalBox;
class UTextBlock;
class UButton;

UCLASS()
class RLR_API UEnhanceResultUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void ShowEnhanceResult(bool bIsSuccess);
	void UpdateTextAsResult(bool bIsSuccess);

	UFUNCTION()
	void ConfirmButtonClicked();
	FOnConfirmButotnClicked OnConfirmButotnClicked;
public:
	/* 강화 성공 : 0, 강화 실패 : 1*/
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* ResultSwitcher;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* SuccessVerticalBox;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* FailureVerticalBox;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* ConfirmButton;

	/* 강화 성공 시 띄울 TextBlock들 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEnhanceSlot> EnhanceSlot_Success;

	/* 물리 방어력 */
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* PhysicalDefenseText;
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* EnhancedPhysicalDefenseText;
	/* 마법 방어력 */
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* MagicalDefenseText;
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* EnhancedMagicalDefenseText;
	/* 힘 */
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* StrengthText;
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* EnhancedStrengthText;
	/* 체력*/
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* HealthText;
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* EnhancedHealthText;

	/* 강화 실패 시 띄울 TextBlock */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEnhanceSlot> EnhanceSlot_Fail;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* AdjustedStackText;

	TObjectPtr<UEnhanceUI> EnhanceUI;
private:
	FItemData itemData;
	/* 강화된 장비 정보 */
	FItemData enhancedItemData;
	
	/* 실패 후 조정된 강화 성공률 */
	FText Message1;
	FText adjustedStack;
	int32 enhanceFailStack;
};
