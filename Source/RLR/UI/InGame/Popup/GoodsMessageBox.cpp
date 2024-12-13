// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Popup/GoodsMessageBox.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"

void UGoodsMessageBox::NativeConstruct()
{
	Super::NativeConstruct();

	BtnMax->OnClicked.AddUniqueDynamic(this, &UGoodsMessageBox::OnMaxClicked);
	EdtAmount->OnTextCommitted.AddUniqueDynamic(this, &UGoodsMessageBox::OnTextCommitted);
	EdtAmount->OnTextChanged.AddUniqueDynamic(this, &UGoodsMessageBox::OnTextChanged);
}

int UGoodsMessageBox::GetAmount()
{
	return amount;
}

void UGoodsMessageBox::OpenUI()
{
	SetAmountText();
	Super::OpenUI();
}

void UGoodsMessageBox::SetAmountText()
{
	EdtAmount->SetText(FText::AsNumber(amount));
	EdtAmount->SynchronizeProperties();
}

void UGoodsMessageBox::OnMaxClicked()
{
	//TODO: 입금인지 출금인지 따져서 알맞은 값을 가져와야 함
	amount = 10000;
	SetAmountText();
}

void UGoodsMessageBox::OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	OnTextChanged(Text);
	if (CommitMethod == ETextCommit::OnEnter)
	{
		OnClickedConfirmButton();
	}
}

void UGoodsMessageBox::OnTextChanged(const FText& Text)
{
	FString str = EdtAmount->GetText().ToString();
	FString onlyDigit;
	for (int i = 0; i < str.Len(); i++)
	{
		if (0 <= str[i] - '0' && str[i] - '0' <= 9)
		{
			onlyDigit += str[i];
		}
	}

	amount = FCString::Atoi(*onlyDigit);
	SetAmountText();
}
