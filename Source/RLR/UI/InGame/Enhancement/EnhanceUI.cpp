// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Enhancement/EnhanceUI.h"

#include "Components/Button.h"

void UEnhanceUI::NativeConstruct()
{
	Super::NativeConstruct();

	if(EnhanceButton)
	{
		EnhanceButton->OnClicked.AddUniqueDynamic(this, &UEnhanceUI::OnEnhanceButtonClicked);
	}

}
/* 강화 버튼 클릭 */
void UEnhanceUI::OnEnhanceButtonClicked()
{
	EnhanceButtonClicked.Broadcast();
}