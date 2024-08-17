// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ASCWidgetComponent.h"
#include "UI/BaseUI.h"
#include "UI/InGame/CharacterDisplay/CharacterStatDisplay.h"
#include "RLR.h"

void UASCWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UBaseUI* ASCWidget = Cast<UBaseUI>(GetWidget());
	if (!ASCWidget)
	{
		RLR_LOG(LogRLR, Log, TEXT("ASCWidget is Null"));
		return;
	}

	ASCWidget->SetActionSystemComponent(GetOwner());
}
