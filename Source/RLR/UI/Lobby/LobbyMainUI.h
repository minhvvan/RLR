// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MainUI.h"
#include "Structs/PlayerStructs.h"
#include "LobbyMainUI.generated.h"

/**
 * 
 */

 class UCharacterListUI;
 class UCharacterListElement;
 class UCreateCharacterUI;

UCLASS()
class RLR_API ULobbyMainUI : public UMainUI
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct();
	virtual void RefreshUI() override;
	virtual void Clear() override;
	virtual void SetInputMode() override;

	void AddUserCharacter(FUserCharacter NewCharacter);

	void OpenCreateCharacterUI();

	UCharacterListUI*		GetCharacterListUI() {return CharacterListUI;};
	UCreateCharacterUI*		GetCreateCharacterUI(){return CreateCharacterUI;};

public:

	/*
		Bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCharacterListUI> CharacterListUI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCreateCharacterUI> CreateCharacterUI;

};
