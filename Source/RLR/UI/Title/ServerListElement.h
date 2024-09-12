// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "UI/Title/TitleMainUI.h"
#include "ServerListElement.generated.h"

/**
 * 
 */


 class UTextBlock;
 class UButton;
 class UServerList;

UCLASS()
class RLR_API UServerListElement : public UBaseUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;
	virtual void Clear() override;
	void			SetServerData(FServerData NewServerData);
	FServerData		GetServerData();

	UFUNCTION()
	void OnClickedServerSelectButton();

public:

	/*
		bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock>	ServerNameText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton>		ServerSelectButton;

public:
	UPROPERTY()
	FServerData ServerData;	
};
