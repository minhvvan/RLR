// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GroupUI.h"
#include "Blueprint/WidgetTree.h"
#include "UI/SubUI.h"
#include "UI/InGame/InGameMainUI.h"

void UGroupUI::NativeConstruct()
{
	Super::NativeConstruct();
	BindSubUI();
}

void UGroupUI::BindSubUI()
{
	TArray<UWidget*> Array;
	WidgetTree->GetAllWidgets(Array);

	for (auto Widget : Array)
	{
		if (USubUI* SubUI = Cast<USubUI>(Widget))
		{
			SubUIs.Add(SubUI);
		}
	}
}

TArray<USubUI*> UGroupUI::GetSubUIs()
{
	return SubUIs;
}