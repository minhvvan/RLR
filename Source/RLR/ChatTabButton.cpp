// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatTabButton.h"


void UChatTabButton::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    OnClicked.AddDynamic(this, &UChatTabButton::HandleOnClicked);
}

void UChatTabButton::SetIndex(int32 NewIndex)
{
   
    Tabindex = NewIndex;
}

int32 UChatTabButton::GetIndex() const
{
    return Tabindex;
}

void UChatTabButton::HandleOnClicked()
{
    OnMyButtonClicked.Broadcast(this);
}
