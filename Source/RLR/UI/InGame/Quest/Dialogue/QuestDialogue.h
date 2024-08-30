// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/BaseUI.h"
#include "QuestDialogue.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestDialogueEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestAccept);

class UDialogueUI;

UCLASS()
class RLR_API UQuestDialogue : public UBaseUI
{
	GENERATED_BODY()

private:
	int32 CurrentNPCSeq;
	int32 CurrentQuestSeq;
protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	TObjectPtr<UButton> BtnDeny;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	TObjectPtr<UButton> BtnAccept;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	TObjectPtr<UTextBlock> TxtQuest;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	//TSubclassOf<UDialogueUI> DialogueUIWidgetClass;

protected:
	virtual void NativeConstruct();

	UFUNCTION()
	void OnQuestAccepted();

	UFUNCTION()
	void OnQuestDialogueEnded();

public:
	FOnQuestDialogueEnd OnQuestDialogueEnd;
	FOnQuestAccept OnQuestAccept;

	void SetDialogueData(FString QuestDialogueString, int32 NPCSeq, int32 QuestSeq);
};
