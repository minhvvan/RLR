// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Title/TitleRegisterUI.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

void UTitleRegisterUI::NativeConstruct()
{
	Super::NativeConstruct();

	ConfirmButton->OnClicked.AddUniqueDynamic(this, &UTitleRegisterUI::OnConfirmButtonClicked);
	CancelButton->OnClicked.AddUniqueDynamic(this, &UTitleRegisterUI::OnCancelButtonClicked);
}

void UTitleRegisterUI::OnCancelButtonClicked()
{
	/* 회원가입 취소 전달 */
	OnRegisterCancelButtonClicked.Broadcast();
}

void UTitleRegisterUI::OnConfirmButtonClicked()
{
	if (IDEditableTextBox->GetText().IsEmpty() || PWEditableTextBox->GetText().IsEmpty()) return;
	FString signFString = IDEditableTextBox->GetText().ToString();

	// FString을 std::string으로 변환
	std::string signStdString(TCHAR_TO_UTF8(*signFString));
	GameInstance->GetNetworkManager()->SendSignRequest(signStdString);
	/* 회원가입 완료 전달 */
	OnRegisterConfirmButtonClicked.Broadcast();
}