// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Structs/PlayerStructs.h"
#include "CharacterListElement.generated.h"

/**
 * 
 */
class UTextBlock; 
class UButton; 
class UCharacterListUI;
struct FUserCharacter;

UCLASS()
class RLR_API UCharacterListElement : public UBaseUI, public IUserObjectListEntry
{

	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;

	UFUNCTION()
	void		OnClickedConnectButton();
	UFUNCTION()
	void		OnClickedElementButton();

	void			SetUserCharacterData(FUserCharacter Data);
	FUserCharacter	GetUserCharacterData();

public:

	/*
		Bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CharacterNameText;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ConnectButton;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ElementButton;

public:

	UPROPERTY()
	TObjectPtr<UCharacterListUI> Parent;
	
	UPROPERTY()
	FUserCharacter UserCharacterData;
};
