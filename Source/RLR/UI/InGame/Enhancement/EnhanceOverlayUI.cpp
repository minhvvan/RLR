// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Enhancement/EnhanceOverlayUI.h"
#include "UI/InGame/Enhancement/EnhanceResultUI.h"
#include "UI/InGame/Enhancement/EquipmentList.h"
#include "UI/InGame/Enhancement/EnhanceSlot.h"
#include "UI/InGame/Enhancement/EnhanceUI.h"
#include "UI/InGame/Popup/ConfirmMessageBox.h"

#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/EnhanceManager.h"
#include "GameManager/LiteralManager.h"

#include "Components/WidgetSwitcher.h"


void UEnhanceOverlayUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetUITag(RLRTAG.UI_Enhance);
	GameInstance->GetEnhanceManager()->EnhanceOverlayUI = this;

	if (EnhanceUI)
	{
		EnhanceUI->EnhanceButtonClicked.AddUniqueDynamic(this, &UEnhanceOverlayUI::OnEnhanceButtonClicked);
		if (EquipmentList)
		{
			EquipmentList->EnhanceUI = EnhanceUI;
		}
	}

	if (EnhanceResultUI)
	{
		EnhanceResultUI->OnConfirmButotnClicked.AddUniqueDynamic(this, &UEnhanceOverlayUI::ResultConfirmButtonClicked);
		EnhanceResultUI->EnhanceUI = EnhanceUI;
	}
}

void UEnhanceOverlayUI::RefreshUI()
{
	Super::RefreshUI();

	for (FItemData itemData : GameInstance->GetEnhanceManager()->EquipItemList)
	{
		EquipmentList->AddEquipButton(itemData);
	}
}
/* 강화창에서 강화 버튼 클릭 */
void UEnhanceOverlayUI::OnEnhanceButtonClicked()
{
	ConfirmMessageBox->SetVisibility(ESlateVisibility::Visible);
	ConfirmMessageBox->Clear();

	//클릭, 취소 버튼 콜백 함수 등록
	ConfirmMessageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, RLRLITERAL.Enhance_OnClickedAcceptButton);
	ConfirmMessageBox->OnCancelButtonClickedDelegate.BindUFunction(this, RLRLITERAL.Enhance_OnClickedCancelButton);


	FText MessageText = FSTRING_TO_FTEXT(RLRLITERAL.Enhance_EnhancePrompt);

	ConfirmMessageBox->SetMessageText(MessageText);
}
/* 강화 진행 */
void UEnhanceOverlayUI::OnClickedAcceptButton()
{
	int32 itemID = EnhanceUI->EnhanceSlot_Equip->GetItemData().ITEM_ID;
	int32 userSeq = GameInstance->GetUserSeq();

	int32 enhanceMaterialSeq = EnhanceUI->EnhanceSlot_Item1->GetItemData().ITEM_SEQ;
	/* 강화재료 물약, 3개 필요한 것으로 임시 설정 */
	GameInstance->GetNetworkManager()->SendEnhancePacket(itemID, userSeq, enhanceMaterialSeq, 3);

	ConfirmMessageBox->SetVisibility(ESlateVisibility::Hidden);
}
/* 강화 취소 */
void UEnhanceOverlayUI::OnClickedCancelButton()
{
	ConfirmMessageBox->SetVisibility(ESlateVisibility::Hidden);
}

void UEnhanceOverlayUI::ResultConfirmButtonClicked()
{
	EnhanceResultUI->SetVisibility(ESlateVisibility::Hidden);
}

void UEnhanceOverlayUI::OpenSuccessUI()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			EnhanceResultUI->SetVisibility(ESlateVisibility::Visible);
			EnhanceResultUI->ShowEnhanceResult(true);
		});
}

void UEnhanceOverlayUI::OpenFailUI()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
	{
		EnhanceResultUI->SetVisibility(ESlateVisibility::Visible);
		EnhanceResultUI->ShowEnhanceResult(false);
	});
}