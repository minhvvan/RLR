// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/PageSwitcher.h"
#include "UI/BaseUI.h"
#include "Components/WidgetSwitcherSlot.h"

void UPageSwitcher::SetWidgetAtIndex(int index, UWidget* newWidget)
{
    if (Slots.IsValidIndex(index))
    {
        if (Slots.IsValidIndex(index))
        {
            RemoveChildAt(index);
            InsertChildAt(index, newWidget);
        }
    }
}