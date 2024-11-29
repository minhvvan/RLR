// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Enhancement/EnhanceResultUI.h"
#include "UI/InGame/Enhancement/EnhanceSlot.h"
#include "UI/InGame/Enhancement/EnhanceUI.h"

#include "GameManager/RLRStruct.h"
#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/RichTextBlock.h"
#include "Components/WidgetSwitcher.h"

void UEnhanceResultUI::NativeConstruct()
{
	if (FailureVerticalBox)
	{
		Message1 = STRING_TO_FTEXT("제련 성공 스택 +");
		Message2 = STRING_TO_FTEXT("상승");
	}

	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddUniqueDynamic(this, &UEnhanceResultUI::ConfirmButtonClicked);
	}
}

void UEnhanceResultUI::ShowEnhanceResult(bool bIsSuccess)
{
	itemData = EnhanceUI->EnhanceSlot_Equip->GetItemData();
	if (itemData.ITEM_ID != -1)
	{
		enhancedItemData = GameInstance->GetInventoryManager()->GetItemBySlotIndex(itemData.ITEM_SLOT_IDX);
	}

	if (ResultSwitcher)
	{
		if (bIsSuccess)
		{
			// 성공 UI 활성화
			ResultSwitcher->SetActiveWidget(SuccessVerticalBox);
			UpdateTextAsResult(bIsSuccess);
		}
		else
		{
			// 실패 UI 활성화
			ResultSwitcher->SetActiveWidget(FailureVerticalBox);
			UpdateTextAsResult(bIsSuccess);
		}
	}
}

void UEnhanceResultUI::UpdateTextAsResult(bool bIsSuccess)
{
	if (bIsSuccess)
	{
		/* 성공 이벤트 처리 */
		if (EnhanceSlot_Success)
		{
			/* TODO : ITEM_SEQ->ITEM_ID로 바꾸기 */
			EnhanceSlot_Success->SetSlot(enhancedItemData.ITEM_SEQ);
		}

		StrengthText->SetText(FText::AsNumber(itemData.ITEM_STATUS.STRENGTH));
		EnhancedStrengthText->SetText(FText::AsNumber(enhancedItemData.ITEM_STATUS.STRENGTH));

		HealthText->SetText(FText::AsNumber(itemData.ITEM_STATUS.HEALTH));
		EnhancedHealthText->SetText(FText::AsNumber(enhancedItemData.ITEM_STATUS.HEALTH));
	}
	else
	{
		/* 실패 이벤트 처리 */
		if (EnhanceSlot_Fail)
		{
			/* TODO : ITEM_SEQ->ITEM_ID로 바꾸기 */
			EnhanceSlot_Fail->SetSlot(itemData.ITEM_SEQ);
		}

		/* TODO : 서버로부터 스택 받아오기 */
		enhanceFailStack = 1;
		adjustedStack = FText::AsNumber(enhanceFailStack);

		FText FailureTextFormat = FText::Format(
			FText::FromString(TEXT("{0}{1}{2}")),
			Message1,
			adjustedStack,
			Message2
		);
		AdjustedStackText->SetText(FailureTextFormat);
	}
}

void UEnhanceResultUI::ConfirmButtonClicked()
{
	OnConfirmButotnClicked.Broadcast();
}