// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "CharacterListUI.generated.h"

/**
 * 
 */

class UCharacterListElement;
class UListView;
class UButton;
class ARLRCharacter;
struct FUserCharacter;

UCLASS()
class RLR_API UCharacterListUI : public UBaseUI
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;
	virtual void Clear() override;

	UFUNCTION(BlueprintCallable, Category = "Server")
	void SetSelectedElement(UCharacterListElement* Element);

	void SpawnSelectedElementCharacter(const FUserCharacter& Data);

	UFUNCTION(BlueprintCallable, Category = "Server")
	void OnClickedCreateCharacterButton();

	UFUNCTION(BlueprintCallable, Category = "Server")
	void OnClickedDeleteCharacterButton();

	void AddUserCharacter(FUserCharacter NewCharacter);

public:

	/*
		Bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UListView* CharacterListView;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* CharacterCreateButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* CharacterDeleteButton;

public:

	/*
		캐릭터 선택시 소환할 캐릭터의 위치.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnLocation = FVector(500, 500, 100);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator SpawnRotation = FRotator(0, 0 ,0);

private:
	UPROPERTY()
	TObjectPtr<ARLRCharacter> SelectedCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterListElement> SelectedElement;

	UPROPERTY()
	TMap<int32, FUserCharacter> UserCharacterList;

	UPROPERTY()
	TSubclassOf<UCharacterListElement> ListElementClass;

};
