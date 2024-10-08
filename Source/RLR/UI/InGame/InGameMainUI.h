// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameManager/RLRStruct.h"
#include "GameManager/GameplayTagManager.h"

#include "UI/MainUI.h"
#include "InGameMainUI.generated.h"

/**
 * 
 */

 class UChatUI;
 class UInventoryUI;
 class UChatOptionUI;
 class UEquipmentUI;
 class UItemInformation;
 class UCharacterStatusUI;
 class UMinimapUI;
 class UStatusDisplay;
 class UInGameMenuUI;
 class UPartyUI;
 class UKeyOption;
 class USkillUI;
 class USkillUpgrade;
 class UQuestListUI;
 class UPostOverlayUI;
 class UOtherPlayerMenu;
 class UReportUI;
 class UCanvasPanel;

UCLASS()
class RLR_API UInGameMainUI : public UMainUI
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void SetActionSystemComponent(AActor* Owner) override;


public:

	UChatUI*			GetChatUI(){return ChatUI;}
	UChatOptionUI*		GetChatOptionUI(){return ChatOptionUI;}
	UInventoryUI*		GetInventoryUI(){return InventoryUI;}
	UCharacterStatusUI*	GetCharacterStatusUI() {return CharacterStatusUI;}
	UItemInformation*	GetItemInformation(){return ItemInformation;}
	UMinimapUI*			GetMinimapUI(){return Minimap;}
	UStatusDisplay*		GetStatusDisplayUI(){return StatusDisplayUI;}
	UInGameMenuUI*		GetInGameMenuUI(){return InGameMenuUI;}
	UPartyUI*			GetPartyUI(){return PartyUI;}
	UKeyOption*			GetKeyOptionUI(){return KeyOptionUI;}
	USkillUI*			GetSkillUI(){return SkillUI;}
	USkillUpgrade*		GetSkillUpgradeUI(){return SkillUpgrade;}
	UQuestListUI*		GetQuestListUI() {return QuestListUI;}
	UPostOverlayUI*		GetPostOverlayUI() {return PostOverlayUI;}
	UOtherPlayerMenu*	GetOtherPlayerMenu() {return OtherPlayerMenu;}
	
public:
	//나중에 Private로 닫아주자. 지금은 블루프린트로 테스트할 때가 있으니 편하게 다 열어준다.
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UChatUI> ChatUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UChatOptionUI> ChatOptionUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UInventoryUI> InventoryUI;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UCharacterStatusUI> CharacterStatusUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UItemInformation> ItemInformation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UMinimapUI> Minimap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UStatusDisplay> StatusDisplayUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UInGameMenuUI> InGameMenuUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UPartyUI> PartyUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UKeyOption> KeyOptionUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<USkillUI> SkillUI;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<USkillUpgrade> SkillUpgrade;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UQuestListUI> QuestListUI;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UPostOverlayUI> PostOverlayUI;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UOtherPlayerMenu> OtherPlayerMenu;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UCharacterStatusUI> OtherPlayerStatusUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UReportUI> ReportUI;

public:


protected:
	UFUNCTION()
	void OnChangedTotalStatus();

	UFUNCTION()
	void OnChangedSetStatus();	
	
	UFUNCTION()
	void OnChangedExp();	
	
	UFUNCTION()
	void OnChangedTalent();

	UFUNCTION()
	void OnChangedLevel();
	virtual bool ToggleSubUI(FGameplayTag InputTag);
	virtual void OpenSubUI(FGameplayTag InputTag) override;
	virtual void CloseSubUI(FGameplayTag InputTag) override;
	virtual bool IsOpenSubUI(FGameplayTag InputTag) override;
	virtual class USubUI* GetSubUI(FGameplayTag InputTag);
};