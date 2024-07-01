// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI.h"
#include "UI/SubUI.h"
#include "Blueprint/WidgetTree.h"

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();
	BindSubUI();

}

void UMainUI::BindSubUI()
{
	TArray<UWidget*> Array;
	WidgetTree->GetAllWidgets(Array);

	for (auto Widget : Array)
	{
		if (USubUI* SubUI = Cast<USubUI>(Widget))
		{
			SubUI->SetMainUI(this);
		}
	}

}

void UMainUI::CloseUI()
{
}
