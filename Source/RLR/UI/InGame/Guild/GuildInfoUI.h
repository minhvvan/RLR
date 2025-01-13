// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/UtilStructs.h"
#include "GuildInfoUI.generated.h"

class UTextBlock;
/**
 *  길드 정보
 */
UCLASS()
class RLR_API UGuildInfoUI : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;
	void RefreshUI();

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GuildLevelText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GuildRankText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GuildCreatedDateText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GuildMasterNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GuildMemberCountText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GuildMaxUserText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GuildPointText;
private:
	int32 guildMemberCount = 0;
};
