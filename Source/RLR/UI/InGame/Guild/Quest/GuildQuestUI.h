// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/UtilStructs.h"
#include "GuildQuestUI.generated.h"

class UGuildQuestCardUI;
class UProgressBar;
class UTextBlock;
class USizeBox;
/**
 * 길드 의뢰
 */
UCLASS()
class RLR_API UGuildQuestUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void RefreshUI();
	void InitQuestBoard();

public:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGuildQuestCardUI> GuildQuestCardUI;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> GuildQuestExpProgressBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GuildQuestTierText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> WeeklyCompleteQuestCountText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> WeeklyAcquirePoints;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CustomNicknameText;

	TObjectPtr<USizeBox> QuestBoard;

private:
	TArray<TObjectPtr<UGuildQuestCardUI>> CreatedQuestCards;
};
