// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI.h"
#include "UI/SubUI.h"
#include "Blueprint/WidgetTree.h"
#include "Structs/UtilStructs.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

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
			EUIType Type = SubUI->GetUIType();
			FGameplayTag Tag = SubUI->GetUITag();

			if (Type == EUIType::NONE)
			{
				DEBUG_LOG("BIndSubUI Error. UIType이 설정이 안된 SubUI가 있습니다. 확인 바랍니다.");
			}

			UserActionSubUI.Add(Tag, SubUI);
			SubUIMap.Add(Type, SubUI);
		}
	}

}

void UMainUI::RefreshUI()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			Super::RefreshUI();
			TArray<UWidget*> Array;
			WidgetTree->GetAllWidgets(Array);
			for (auto Widget : Array)
			{
				if (UBaseUI* ChildUI = Cast<UBaseUI>(Widget))
				{
					ChildUI->RefreshUI();
				}
			}
		});
	
}

void UMainUI::CloseUI()
{
}

void UMainUI::SetInputMode()
{
	//특별한 경우가 없다면 그냥 Game And UI 모드.
	ChangeInputModeGameAndUI();
}
