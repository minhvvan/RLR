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

            //Slot 할당
            AddChild(newWidget);
            int32 CurrentIndex = GetChildIndex(newWidget);
            Slots.RemoveAt(CurrentIndex);

            //추가
            Slots.Insert(newWidget->Slot, FMath::Clamp(index, 0, Slots.Num()));
        }
    }
}