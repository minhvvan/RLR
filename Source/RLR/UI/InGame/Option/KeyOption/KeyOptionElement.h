// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "Player/PlayerCommands.h"
#include "GameManager/GameplayTagManager.h"
#include "KeyOptionElement.generated.h"

/**
 * 
 */


 class UTextBlock;
 class UInputAction;
 class UInputKeySelector;

UCLASS()
class RLR_API UKeyOptionElement : public UBaseUI
{
	GENERATED_BODY()



public:

	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;

	UFUNCTION(BlueprintCallable)
	void ApplyInputTagOptions();

	UFUNCTION(BlueprintCallable)
	void SetInputTag(FGameplayTag NewTag) {InputTag = NewTag;};


public:

	/*

		각 Element들은 KeyOption UI에서 고정된 KeyOptionName과 ActionTag를 가짐.

		ex) 스킬 슬롯 1
				KeyOptionName = 스킬 1
				ActionTag = Action_Skill_1_Anim

				인벤토리 열기
				KeyOptionName = 인벤토리
				ActionTag = UI_Inventory.

			이렇게 값이 고정된 상태에서 InputTag만 바꿔준다.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText KeyOptionName = FText();

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputType InputType = EInputType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag InputTag = FGameplayTagManager::Get().None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ActionTag = FGameplayTagManager::Get().None;

	UFUNCTION(BlueprintCallable)
	void SetKeyOption(UInputAction* Action, EInputType Type, FGameplayTag TargetKeyTag, FGameplayTag TargetActionTag);


public:

	/*
		Bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> KeyOptionNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInputKeySelector>  InputTagKeySelector_1;

	
	/*
		세컨드 키는 현재 X. 필요하면 나중에 이어서 만들것.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputKeySelector>  InputTagKeySelector_2;
};
