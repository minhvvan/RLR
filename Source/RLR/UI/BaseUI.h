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

UCLASS()
class RLR_API UBaseUI : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void RefreshUI(){};
	virtual void OpenUI();
	virtual void Clear(){};
	virtual void CloseUI();

	void SetUIType(EUIType Type) {UIType = Type;}
	EUIType GetUIType() {return UIType;}

	virtual void SetActionSystemComponent(AActor* Owner);

public:
	EUIType	UIType = EUIType::NONE;

	/*UI Cpp에서 구현할 떄마다 Manager 헤더 파일 추가하기 귀찮아서 만듬.*/
	UUIManager*			GetUIManager();
	UGameManager*		GetGameManager();
	UNetworkManager*	GetNetworkManager();
	UPlayerManager*		GetPlayerManager();
	USkillManager*		GetSkillManager();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UActionSystemComponent> ActionSystemComponent;

public:

	template<typename T>
	TSubclassOf<T> GetWidgetClass(FString Name);
};

template<typename T>
inline TSubclassOf<T> UBaseUI::GetWidgetClass(FString Name)
{
	return GetGameManager()->GetDataManager()->GetWidgetClass<T>(Name);
}
