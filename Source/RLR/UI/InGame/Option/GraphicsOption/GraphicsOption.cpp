// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Option/GraphicsOption/GraphicsOption.h"
#include "UI/InGame/Option/OptionUI.h"

void UGraphicsOption::NativeConstruct()
{
}

void UGraphicsOption::Init()
{
}

void UGraphicsOption::RefreshUI()
{
}

void UGraphicsOption::OpenUI()
{
	UOptionUI* OptionUI = Cast<UOptionUI>(GetParent());
	if (IsValid(OptionUI) == false)
		return;
	OptionUI->ChangeTab(OptionUI_TabType::GraphicsOption);
	RefreshUI();
}

void UGraphicsOption::Clear()
{
}

void UGraphicsOption::CloseUI()
{
}
