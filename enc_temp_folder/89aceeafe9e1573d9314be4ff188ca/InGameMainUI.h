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

UCLASS()
class RLR_API UInGameMainUI : public UMainUI
{
	GENERATED_BODY()



public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	UChatUI* GetChatUI(){return ChatUI;}

	UFUNCTION(BlueprintCallable)
	UCharacterStatusUI*	GetCharacterStatusUI() {return CharacterStatusUI;}

	void SetActionSystemComponent(AActor* Owner) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UChatUI> ChatUI;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Meta = (BindWidget))
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

public:
	//virtual bool ToggleSubUI(int inputID);
	//virtual class USubUI* GetSubUI(int inputID);

protected:
	UFUNCTION()
	void OnChangedTotalStatus();

	UFUNCTION()
	void OnChangedSetStatus();	
	
	UFUNCTION()
	void OnChangedExp();

	UFUNCTION()
	void OnChangedLevel();
	virtual bool ToggleSubUI(FGameplayTag InputTag);
	virtual class USubUI* GetSubUI(FGameplayTag InputTag);
};