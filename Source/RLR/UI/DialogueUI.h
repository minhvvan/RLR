// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotUI.h"
#include "UI/MainUI.h"
#include "Structs/ItemStructs.h"
#include "Structs/ObjectStructs.h"
#include "DialogueUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestDialogueBegin);

class UDialogueDynamicButton;
class UButton;
class UTextBlock;
class UHorizontalBox;
class UQuestDialogue;
class UPostOverlayUI;
class UNPCShopUI;
class UCanvasPanel;
class UNPCShopUI;
class UItemInformation;
class UInventoryUI;
class USlotUI;

UCLASS()
class RLR_API UDialogueUI : public UMainUI
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	TObjectPtr<UButton> BtnExit;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* BtnBox;

	/* 버튼 동적 생성 */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDialogueDynamicButton> BtnQuest;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDialogueDynamicButton> PostButton;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDialogueDynamicButton> BtnShop;	
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtNPCName;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtNPCTalk;	

protected:
	virtual void NativeConstruct();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UQuestDialogue> QuestDialogueWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UDialogueDynamicButton> DialogueDynamicButtonClass;

public:
	FOnDialogueEnd OnDialogueEnd;
	FOnQuestDialogueBegin OnQuestDialogueBegin;
	void UpdateNPCFunctionality();
	//Test
	void SetDialogueData(FString DialogueString);
	void SetNPCData(int32 NPCSeq);

	void OpenItemInfo(USlotUI* Target);
	void CloseItemInfo();

	void CreateShopButtons(const TArray<FNPCShop>& ShopData);
	void CreateQuestButtons(const TArray<FQuest>& QuestData);
	UDialogueDynamicButton* CreateDynamicButton();
	
	virtual void OnPageActivated() override;

	void ToggleNpcButtons(bool bOpen);

	void RemoveQuestButton(int32 QuestSeq);
	void ReAddQuestButton(int32 QuestSeq);

protected:
	UFUNCTION()
	void OnDialogueEnded();

	UFUNCTION()
	void OnQuestDialogueBegins(int32 ButtonIndex);
	
	UFUNCTION()
	void OnShopClicked(int32 ButtonIndex);

	UFUNCTION()
	void OnPostClicked();

	void SetInventorySlotType(ESlotType SlotType);
	
	UFUNCTION()
	void OnStorageClicked();

	UFUNCTION()
	void HandleButtonClicked(int32 ButtonType);
	
  UFUNCTION()
  void OnEnhanceClicked();

	UFUNCTION()
	void HandleButtonClicked(int32 ButtonType, int32 ButtonIdx);

	UFUNCTION()
	void CloseQuestDialogue();
	
	UFUNCTION()
	void RemoveFromHorizontalBox();

	void OpenInventory(FVector2D InventoryPosition);

private:
	UPROPERTY(EditAnywhere, Category = DynamicButton)
	TMap<ENPCFunctionality, FString> ButtonText;
	TArray<UDialogueDynamicButton*> QuestButtons;

	int32 CurrentNPCSeq;
	int32 CurrentOpenQuest;

	bool bOpenShop;
	bool bOpenPost;
	bool bOpenEnhance;
	bool bOpenQuestDialogue;
};
