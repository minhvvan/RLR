// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueDynamicButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClickedSendType, int32, ButtonType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClickedSendIndex, int32, ButtonIndex);

class UButton;
class UTextBlock;

/**
 * DialogueUI에서 NPC의 Quest, Post, Shop 유무에 따라 동적 생성되는 버튼 클래스
 */
UCLASS()
class RLR_API UDialogueDynamicButton : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;	
	void SetButtonText(FString buttonText);

	void SetButtonIndex(int32 index);
	void SetButtonType(int32 type);
	
	int32 GetButtonIndex();
	int32 GetButtonType();

	UFUNCTION()
	void OnButtonClicked();

	void SetQuestSeq(int32 NewQuestSeq) { questSeq = NewQuestSeq;};
	int32 GetQuestSeq() {return questSeq;};
public:
	UPROPERTY(meta = (BindWidget))
	UButton* DynamicButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;

	FOnButtonClickedSendType OnButtonClickedSendType;
	FOnButtonClickedSendIndex OnButtonClickedSendIndex;

private:
	int32 buttonIdx;
	/* 
		Type
		0 : Shop
		1 : Post
		2 : Quest
		3 : Enhance
	*/
	int32 buttonType;

	int32 questSeq;
};
