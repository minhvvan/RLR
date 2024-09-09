// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/UtilStructs.h"
#include "Structs/ObjectStructs.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "UI/SubUI.h"
#include "QuestListUI.generated.h"

class UQuestButtonUI;

UCLASS()
class RLR_API UQuestListUI : public USubUI
{
	GENERATED_BODY()
	

protected:
	virtual void NativeConstruct();
	void UpdateQuestDetails(const FQuest& Quest);
	void SetBackgroundHitTestVisible(bool bIsHitTestVisible);
	void OnQuestButtonClicked(const FQuest& ClickedQuest);

	UFUNCTION()
	void OnCompleteButtonClicked();
	UFUNCTION()
	void OnDeclineButtonClicked();

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* QuestListContainer;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SelectedQuestTitle;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestDescription;

	/* TODO : 나중에 위젯으로 따로 빼놓을 것*/
	UPROPERTY(meta = (BindWidget))
	UButton* DeclineButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CompleteButton;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UQuestButtonUI> QuestButtonUIClass;

private:
	void ClearQuestList();
	void AddQuestButton(const FQuest& Quest);

	FQuest SelectedQuest;

public:
	void UpdateQuestList(const TArray<FQuest>& Quests);

};
