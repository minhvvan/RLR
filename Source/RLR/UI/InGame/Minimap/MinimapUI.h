// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "MinimapUI.generated.h"

/**
		TODO   .
		현재는 틀만 구현. 나중에 몬스터랑 플레이어가 제대로 구현이 될 경우 이어서 작업할 예정.
 */

 class URichTextBlock;
 class UImage;

UCLASS()
class RLR_API UMinimapUI : public UBaseUI
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void SetMapName(FString MapName);

	UFUNCTION(BlueprintCallable)
	void SetChannel(int32 ChannelNumber);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<URichTextBlock> MapNameRichTextBlock;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<URichTextBlock> ChannelRichTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UImage> MiniMapImage;

};
