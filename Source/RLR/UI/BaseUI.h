// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameManager/RLRStruct.h"
#include "Structs/ItemStructs.h"
#include "GameplayTagContainer.h"
#include "BaseUI.generated.h"

/**

 */

 class UUIManager;
 class UGameManager;
 class UNetworkManager;
 class UActionSystemComponent;
 class UPlayerManager;
 class USkillManager;
 class UDataManager;
 class UPartyManager;
 class UInventoryManager;

UCLASS()
class RLR_API UBaseUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void Init(){};
	virtual void RefreshUI(){};
	virtual void OpenUI();
	virtual void Clear(){};
	virtual void CloseUI();
	virtual void BindWidget();

	virtual void SetInputMode();

	void		SetUIType(EUIType Type);
	EUIType		GetUIType() {return UIType;}
	void		SetParent(UBaseUI* UI){Parent = UI;}
	UBaseUI*	GetParent();

	virtual void SetActionSystemComponent(AActor* Owner);

	void ChangeInputModeGameAndUI();
	void ChangeInputModeGameOnly();
	void ChangeInputModeUIOnly();

	//하이라이트 효과. 필요한 UI에 그때그때 구현해주기
	UFUNCTION(BlueprintImplementableEvent)
	void Highlight();
	UFUNCTION(BlueprintImplementableEvent)
	void UnHighlight();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUIType	UIType;

	UUIManager*			GetUIManager();
	UGameManager*		GetGameManager();
	UNetworkManager*	GetNetworkManager();
	UPlayerManager*		GetPlayerManager();
	USkillManager*		GetSkillManager();
	UInventoryManager*	GetInventoryManager();
	UDataManager*		GetDataManager();
	UPartyManager*		GetPartyManager();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UActionSystemComponent> ActionSystemComponent;

public:
	TObjectPtr<UBaseUI> Parent;

	template<typename T>
	TSubclassOf<T> GetWidgetClass(FString Name);

	void OpenOtherUI(FGameplayTag Tag);

	template<typename T>
	TObjectPtr<T> GetSubUI(FGameplayTag Tag);

	UPROPERTY(EditAnywhere, Category = "Tag")
	FGameplayTag UITag = FGameplayTag();
};

template<typename T>
inline TSubclassOf<T> UBaseUI::GetWidgetClass(FString Name)
{
	return GetGameManager()->GetDataManager()->GetWidgetClass<T>(Name);
}

template<typename T>
inline TObjectPtr<T> UBaseUI::GetSubUI(FGameplayTag Tag)
{
	return GetUIManager()->GetSubUI<T>(Tag);
}