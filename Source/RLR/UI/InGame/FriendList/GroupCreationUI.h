// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "GroupCreationUI.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGroupAddSignature, FString, GroupName);

class UEditableText;
class UButton;

/**
 *  그룹 추가 위젯
 */
UCLASS()
class RLR_API UGroupCreationUI : public USubUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ConfirmButtonClicked();

	UFUNCTION()
	void CancelButtonClicked();

	UFUNCTION()
	bool GetVisibilityStatus() {return bIsOpen;};

	UFUNCTION()
	void SetVisibilityStatus(bool status) {bIsOpen = status;};

public:
	UPROPERTY(meta = (BindWidget))
	UEditableText* GroupNameText;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

private:
	bool bIsOpen;	
};
