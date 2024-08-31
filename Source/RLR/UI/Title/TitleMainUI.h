// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MainUI.h"
#include "TitleMainUI.generated.h"

/**
 * 
 */

 class UServerList;
 class UButton;
 class UEditableTextBox;

  /*
	민환님이 지금 정리 중이니 임시 배치. 나중에 머지되면 RLRStruct 어딘가에 옮겨줄 예정. 
 */

 USTRUCT(Atomic, BlueprintType)
struct FServerData
{
	GENERATED_BODY()

	/*
		나중에 현석님한테 서버 리스트에서 채울 데이터 어떻게 구성할지 물어보기.
	*/

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 ServerSeq;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString ServerName;
};

UCLASS()
class RLR_API UTitleMainUI : public UMainUI
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;
	virtual void Clear() override;

	//서버 목록 추가.
	virtual void AddServerListElement(FServerData NewServerData);

	void OnClickedConnectServerButton();

public:

	/*
		bind
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UServerList> ServerList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> IDEditableTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> PWEditableTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ConnectServerButton;


};
