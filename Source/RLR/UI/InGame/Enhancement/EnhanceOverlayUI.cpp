// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Enhancement/EnhanceOverlayUI.h"

#include "GameManager/UIManager.h"

void UEnhanceOverlayUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetUITag(RLRTAG.UI_Enhance);
}