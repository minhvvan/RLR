// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "Structs/ItemStructs.h"
#include "DialogueUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestDialogueBegin);

class UButton;
class UTextBlock;
class UQuestDialogue;
class UNPCShopUI;
class UCanvasPanel;
class UNPCShopUI;
class UItemInformation;
class UInventoryUI;
class USlotUI;

UCLASS()
class RLR_API UDialogueUI : public UBaseUI
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Canvas;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	TObjectPtr<UButton> BtnExit;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	TObjectPtr<UButton> BtnQuest;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> BtnShop;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtNPCName;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtNPCTalk;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UNPCShopUI> NPCShopUI;		
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UInventoryUI> InventoryUI;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UItemInformation> ItemInformationUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UQuestDialogue> QuestDialogueWidgetClass;


protected:
	virtual void NativeConstruct();

public:
	FOnDialogueEnd OnDialogueEnd;
	FOnQuestDialogueBegin OnQuestDialogueBegin;
	//Test
	void SetDialogueData(FString DialogueString);
	void SetNPCData(int32 NPCSeq, int32 QuestSeq);

	void OpenItemInfo(USlotUI* Target);
	void CloseItemInfo();

	void AddSaleItem(const FItemData& Item, const FItemResource& NewItemResource);
	void RemoveSaleItem(const FItemData& Item);

protected:
	UFUNCTION()
	void OnDialogueEnded();

	UFUNCTION()
	void OnQuestDialogueBegins();	
	
	UFUNCTION()
	void OnShopClicked();


private:
	int32 CurrentNPCSeq;
	int32 CurrentQuestSeq;

	bool bOpenShop;
};
