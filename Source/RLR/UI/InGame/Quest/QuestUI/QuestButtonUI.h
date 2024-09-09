// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Structs/ObjectStructs.h"
#include "QuestButtonUI.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestButtonClick, const FQuest&);

UCLASS()
class RLR_API UQuestButtonUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetQeustInfo(const FQuest& InQuest);

	FOnQuestButtonClick OnQuestButtonClick;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* QuestButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestNameText;

private:
	UFUNCTION()
	void OnQuestButtonClicked();

	FQuest QuestInfo;
};
