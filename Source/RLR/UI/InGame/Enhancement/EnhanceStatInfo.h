// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnhanceStatInfo.generated.h"

class URichTextBlock;

/**
 * 강화 전/후 스탯
 */
UCLASS()
class RLR_API UEnhanceStatInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(meta = (BindWidget))
	URichTextBlock* ItemStatusText;
};
