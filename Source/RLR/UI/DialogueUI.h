// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "DialogueUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestDialogueBegin);

class UButton;
class UTextBlock;
class UQuestDialogue;

UCLASS()
class RLR_API UDialogueUI : public UBaseUI
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	TObjectPtr<UButton> BtnTest;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtTest;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	TObjectPtr<UButton> BtnQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UQuestDialogue> QuestDialogueWidgetClass;

protected:
	virtual void NativeConstruct();

public:
	FOnDialogueEnd OnDialogueEnd;
	FOnQuestDialogueBegin OnQuestDialogueBegin;
	//Test
	void SetDialogueData(FString DialogueString);

protected:
	UFUNCTION()
	void OnDialogueEnded();

	UFUNCTION()
	void OnQuestDialogueBegins();
};
