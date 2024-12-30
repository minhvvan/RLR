// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RenameGroupMessageBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCloseRenameGroupSignature, bool, bIsClosed);

class UEditableText;
class UTextBlock;
class UButton;
/**
 * 그룹 이름 변경 시 뜨는 UI
 */
UCLASS()
class RLR_API URenameGroupMessageBox : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ConfirmButtonClicked();
	UFUNCTION()
	void CancelButtonClicked();

	UFUNCTION()
	void OnGroupNameTextChanged(const FText& NewGroupName);

	void SetCurrentGroupName(const FText& CurrentGroupName);
	void SetGroupSeq(int32 CurrentGroupSeq);

	FOnCloseRenameGroupSignature OnCloseRenameGroupSignature;
public:
	UPROPERTY(meta = (BindWidget))
	UEditableText* GroupNameText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentGroupNameText;

	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;
private:
	int32 maxCharacters = 12;
	/* TODO : 서버에 그룹이름 변경하는 내용 생기면 아래 삭제 */
	int32 groupSeq;
};
