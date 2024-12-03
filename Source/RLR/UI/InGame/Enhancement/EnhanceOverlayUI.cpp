// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Enhancement/EnhanceOverlayUI.h"
#include "UI/InGame/Enhancement/EquipmentList.h"
#include "UI/InGame/Enhancement/EnhanceUI.h"
#include "UI/InGame/Popup/ConfirmMessageBox.h"

#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/EnhanceManager.h"
#include "GameManager/LiteralManager.h"

void UEnhanceOverlayUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetUITag(RLRTAG.UI_Enhance);

	
	if (EnhanceUI)
	{
		EnhanceUI->EnhanceButtonClicked.AddUniqueDynamic(this, &UEnhanceOverlayUI::OnEnhanceButtonClicked);
		if (EquipmentList)
		{
			EquipmentList->EnhanceUI = EnhanceUI;
		}
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
/* 강화창에서 장비 목록에 있는 장비 클릭 */
void UEnhanceOverlayUI::OnEnhanceButtonClicked()
{
	UConfirmMessageBox* ConfirmMessageBox = OpenOtherUI<UConfirmMessageBox>(FGameplayTagManager::Get().UI_Popup_ConfirmMessageBox);
	if (IsValid(ConfirmMessageBox) == false) return;

	ConfirmMessageBox->Clear();

	//클릭, 취소 버튼 콜백 함수 등록
	ConfirmMessageBox->OnConfirmButtonClickedDelegate.BindUFunction(this, RLRLITERAL.Enhance_OnClickedAcceptButton);
	ConfirmMessageBox->OnCancelButtonClickedDelegate.BindUFunction(this, RLRLITERAL.Enhance_OnClickedCancelButton);


	FText MessageText = STRING_TO_FTEXT(RLRLITERAL.Enhance_EnhancePrompt);

	ConfirmMessageBox->SetMessageText(MessageText);
}
/* 강화 진행 */
void UEnhanceOverlayUI::OnClickedAcceptButton()
{
}
/* 강화 취소 */
void UEnhanceOverlayUI::OnClickedCancelButton()
{
}