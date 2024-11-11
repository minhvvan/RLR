// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendRequestMessageBox.generated.h"

class UTextBlock;

UCLASS()
class RLR_API UFriendRequestMessageBox : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void InitializeWidget(const FString& SenderName);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SenderNameText;
};
