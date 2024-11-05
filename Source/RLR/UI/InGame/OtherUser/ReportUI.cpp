// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/OtherUser/ReportUI.h"
#include "Components/ComboBoxString.h"
#include "Components/MultiLineEditableText.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Structs/UtilStructs.h"
#include "RLR.h"

void UReportUI::NativeConstruct()
{
	Super::NativeConstruct();

	BtnSubmit->OnClicked.AddUniqueDynamic(this, &UReportUI::OnSubmitClicked);
	BtnExit->OnClicked.AddUniqueDynamic(this, &UReportUI::CloseUIByManager);
}

void UReportUI::OnSubmitClicked()
{
	//TODO: Submit
	auto text = EdtDetail->GetText().ToString();
	auto type = CboxReportType->GetSelectedOption();

	RLR_LOG(LogRLR, Log, TEXT("Report: %s"), *text);
	RLR_LOG(LogRLR, Log, TEXT("RepotType: %s"), *type);

	CloseUIByManager();
}

void UReportUI::OpenUI()
{
	CboxReportType->ClearSelection();
	EdtDetail->SetText(FText::FromString(TEXT("")));

	Super::OpenUI();
}

void UReportUI::SetUserName(FString NickName)
{
	TxtUserName->SetText(FText::FromString(NickName));
}

void UReportUI::SetUserSeq(int Seq)
{
	UserSeq = Seq;
}
