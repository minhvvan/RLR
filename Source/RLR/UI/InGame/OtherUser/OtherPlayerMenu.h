// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "Structs/PlayerStructs.h"
#include "OtherPlayerMenu.generated.h"

class UTextBlock;

UCLASS()
class RLR_API UOtherPlayerMenu : public USubUI
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtUserName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> BtnUserInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> BtnAddFriend;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> BtnAddParty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> BtnTrade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> BtnWhisper;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> BtnReport;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> BtnCancel;

public:
	virtual void NativeConstruct() override;

	void SetOtherUserData(TSharedPtr<FUserCharacter> Otheruser);

protected:
	UFUNCTION()
	void OnUserInfoClicked();

	UFUNCTION()
	void OnAddFriendClicked();

	UFUNCTION()
	void OnAddPartyClicked();

	UFUNCTION()
	void OnTradeClicked();

	UFUNCTION()
	void OnWhisperClicked();

	UFUNCTION()
	void OnReportClicked();

	UFUNCTION()
	void OnCancelClicked();

	void CloseUIByManager();

private:
	TSharedPtr<FUserCharacter> OtherUserData;
};
