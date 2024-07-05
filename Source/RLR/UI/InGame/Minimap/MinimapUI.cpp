// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Minimap/MinimapUI.h"
#include "Components/RichTextBlock.h"
#include "Components/Image.h"



void UMinimapUI::SetMapName(FString MapName)
{

	FText MapNameText = FText::FromString(MapName);
	MapNameRichTextBlock->SetText(MapNameText);
}

void UMinimapUI::SetChannel(int32 ChannelNumber)
{
	
	FText ChannelText = FText::FromString(FString::FromInt(ChannelNumber));
	ChannelRichTextBlock->SetText(ChannelText);
}
