// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MessageBoxUI.h"
#include "AddFriendMessageBox.generated.h"

class UComboBoxString;
class UEditableText;
/**
 * 친구 추가 시 뜨는 팝업
 */
UCLASS()
class RLR_API UAddFriendMessageBox : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* GroupListDropDownBox;

	UPROPERTY(meta = (BindWidget))
	UEditableText* PlayerNameInputText;
};
