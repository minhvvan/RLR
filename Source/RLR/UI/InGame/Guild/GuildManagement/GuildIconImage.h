// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GuildIconImage.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGuildIconImageClicked, UGuildIconImage*, IconClass);

class UImage;
/**
 * 길드 관리 - 길드 이름 및 아이콘 변경
 */
UCLASS()
class RLR_API UGuildIconImage : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnImageClicked();

	void SetImage(UTexture2D* NewIconImage);
	UTexture2D* GetIconTexture();

	void Highlight();
	void UnHighlight();

	FGuildIconImageClicked GuildIconImageClicked;
public:
	UPROPERTY(meta = (BindWidget))
	UImage* Image;

private:
	UTexture2D* IconTexture;
};