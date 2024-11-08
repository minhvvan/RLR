// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GuildCreationUI.generated.h"

class UButton;

/**
 * 길드 생성 UI
 */
UCLASS()
class RLR_API UGuildCreationUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void CreateGuild();

public:
	UPROPERTY(meta = (BindWidget))
	UButton* CreateGuildButton;
};
