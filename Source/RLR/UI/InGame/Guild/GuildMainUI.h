// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GuildMainUI.generated.h"

class UGuildInfoUI;
class UGuildDetailUI;

/**
 * 길드 MainUI
 */
UCLASS()
class RLR_API UGuildMainUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void RefreshUI();

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UGuildInfoUI> GuildInfoUI;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UGuildDetailUI> GuildDetailUI;

};
