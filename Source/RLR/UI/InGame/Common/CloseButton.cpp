// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Common/CloseButton.h"
#include "UI/BaseUI.h"

#include "Components/Button.h"

void UCloseButton::NativeConstruct()
{
	Super::NativeConstruct();

}

void UCloseButton::Init()
{
	Super::Init();
	CloseButton->OnClicked.AddUniqueDynamic(this, &UCloseButton::OnClickedCloseButton);
}

void UCloseButton::OnClickedCloseButton()
{
	if(IsValid(GetParent()) == false)
		return;

	GetParent()->CloseUI();
}
