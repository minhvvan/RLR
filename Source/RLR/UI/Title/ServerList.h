// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "UI/Title/TitleMainUI.h"
#include "ServerList.generated.h"

/**
 * 
 */

 class UServerListElement;
 class UScrollBox;

UCLASS()
class RLR_API UServerList : public UBaseUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void Init() override;
	virtual void RefreshUI() override;
	virtual void Clear() override;


	virtual void AddServerListElement(FServerData NewServerData);

	void					SetSelectedServer(UServerListElement* Element);
	UServerListElement*		GetSelectedServer();

public:

	/*
		Bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UScrollBox> ServerListScrollBox;


private:

	UPROPERTY()
	TObjectPtr<UServerListElement> SelectedElement;

	UPROPERTY()
	TMap<int32, UServerListElement*> ServerListElementMap;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ServerListMaxCount = 8;

};
