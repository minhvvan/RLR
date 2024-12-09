// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Option/AudioOption/AudioOption.h"
#include "UI/InGame/Option/OptionUI.h"

void UAudioOption::NativeConstruct()
{
}

void UAudioOption::Init()
{
}

void UAudioOption::RefreshUI()
{
}

void UAudioOption::OpenUI()
{
	UOptionUI* OptionUI = Cast<UOptionUI>(GetParent());
	if (IsValid(OptionUI) == false)
		return;
	OptionUI->ChangeTab(OptionUI_TabType::AudioOption);
	RefreshUI();
}

void UAudioOption::Clear()
{
}

void UAudioOption::CloseUI()
{
}
