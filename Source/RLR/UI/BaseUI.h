// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameManager/RLRStruct.h"
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

	void		SetUIType(EUIType Type) {UIType = Type;}
	EUIType		GetUIType() {return UIType;}
	void		SetParent(UBaseUI* UI){Parent = UI;}
	UBaseUI*	GetParent();

	virtual void SetActionSystemComponent(AActor* Owner);

	void ChangeInputModeGameAndUI();
	void ChangeInputModeGameOnly();
	void ChangeInputModeUIOnly();

public:
	EUIType	UIType;

	UUIManager*			GetUIManager();
	UGameManager*		GetGameManager();
	UNetworkManager*	GetNetworkManager();
	UPlayerManager*		GetPlayerManager();
	USkillManager*		GetSkillManager();
	UInventoryManager*	GetInventoryManager();
	UDataManager*		GetDataManager();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UActionSystemComponent> ActionSystemComponent;

public:

	TObjectPtr<UBaseUI> Parent;

	template<typename T>
	TSubclassOf<T> GetWidgetClass(FString Name);
};

template<typename T>
inline TSubclassOf<T> UBaseUI::GetWidgetClass(FString Name)
{
	return GetGameManager()->GetDataManager()->GetWidgetClass<T>(Name);
}
