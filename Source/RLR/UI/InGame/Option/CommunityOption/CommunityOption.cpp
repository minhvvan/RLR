// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Option/CommunityOption/CommunityOption.h"
#include "UI/InGame/Option/OptionUI.h"

void UCommunityOption::NativeConstruct()
{
}

void UCommunityOption::Init()
{
}

void UCommunityOption::RefreshUI()
{
}

void UCommunityOption::OpenUI()
{
	UOptionUI* OptionUI = Cast<UOptionUI>(GetParent());
	if (IsValid(OptionUI) == false)
		return;
	OptionUI->ChangeTab(OptionUI_TabType::CommunityOption);
	RefreshUI();
}

void UCommunityOption::Clear()
{
}

void UCommunityOption::CloseUI()
{
}
