// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/WidgetSwitcherButton.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "blueprint/WidgetTree.h"

void UWidgetSwitcherButton::PostLoad()
{
	Super::PostLoad();

	OnClicked.AddUniqueDynamic(this, &UWidgetSwitcherButton::OnClickCallBack);
}

void UWidgetSwitcherButton::OnClickCallBack()
{
	//Find WidgetSwitcher
	UWidgetTree* ParentWidgetTree = GetTypedOuter<UWidgetTree>();
	if (!ParentWidgetTree) return;

	auto widgetSwitcher = Cast<UWidgetSwitcher>(ParentWidgetTree->FindWidget("WidgetSwitcher"));
	if (!widgetSwitcher) return;

	widgetSwitcher->SetActiveWidgetIndex(WidgetIndex);
}