// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "ReportUI.generated.h"

class UTextBlock;
class UMultiLineEditableText;
class UComboBoxString;

UCLASS()
class RLR_API UReportUI : public USubUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UButton> BtnExit;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> TxtUserName;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UComboBoxString> CboxReportType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UMultiLineEditableText> EdtDetail;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidgetOptional))
	TObjectPtr<UButton> BtnSubmit;

protected:
	UFUNCTION()
	void OnSubmitClicked();

	void OpenUI() override;

public:
	void SetUserName(FString NickName);
	void SetUserSeq(int Seq);

private:
	int UserSeq;
};
