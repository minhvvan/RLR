// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildManagement/GuildIconImage.h"

#include "Components/Image.h"

void UGuildIconImage::NativeConstruct()
{
	Super::NativeConstruct();

	if (Image)
	{
		Image->OnMouseButtonDownEvent.BindUFunction(this, FName("OnImageClicked"));
	}
}

void UGuildIconImage::OnImageClicked()
{
	if (Image)
	{
		IconTexture = Cast<UTexture2D>(Image->GetBrush().GetResourceObject());
	}
	GuildIconImageClicked.Broadcast(this);
}

void UGuildIconImage::SetImage(UTexture2D* NewIconImage)
{
	Image->SetBrushFromTexture(NewIconImage);
}

UTexture2D* UGuildIconImage::GetIconTexture()
{
	return IconTexture;
}

void UGuildIconImage::Highlight()
{
    if (!Image) return;

    FLinearColor HighlightColor = FLinearColor(1.0f, 1.0f, 0.0f, 1.0f); 
    Image->SetColorAndOpacity(HighlightColor);
}

void UGuildIconImage::UnHighlight()
{
    if (!Image) return;

    FLinearColor DefaultColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
    Image->SetColorAndOpacity(DefaultColor);
}