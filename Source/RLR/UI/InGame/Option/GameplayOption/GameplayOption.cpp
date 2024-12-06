// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Option/GameplayOption/GameplayOption.h"
#include "UI/InGame/Option/OptionUI.h"

void UGameplayOption::NativeConstruct()
{
}

void UGameplayOption::Init()
{
}

void UGameplayOption::RefreshUI()
{
}

void UGameplayOption::OpenUI()
{
	UOptionUI* OptionUI = Cast<UOptionUI>(GetParent());
	if (IsValid(OptionUI) == false)
		return;
	OptionUI->ChangeTab(OptionUI_TabType::GameplayOption);
	RefreshUI();
}

void UGameplayOption::Clear()
{
}

void UGameplayOption::CloseUI()
{
}
