// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatTabWidget.h"

void UChatTabWidget::SetTabName(const FText& InTabName)
{
    if (ChattingTabText)
    {
        ChattingTabText->SetText(InTabName);
    }
}

void UChatTabWidget::ClickButton(int32 ButtonIndex) const
{
    FMyButtonClickedSignature.Broadcast(ButtonIndex);
}