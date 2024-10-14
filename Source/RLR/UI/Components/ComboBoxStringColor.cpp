// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/ComboBoxStringColor.h"

void UComboBoxStringColor::SetDefaultOptionColor(FSlateColor Color)
{
	auto children = ComboBoxContent->GetAllChildren();

	for (int i = 0; i < children->Num(); i++)
	{
		auto& child = static_cast<STextBlock&>(children->GetChildAt(i).Get());
		child.SetColorAndOpacity(Color);
	}
}