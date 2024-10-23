// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "FriendInformation.generated.h"

class UTextBlock;

/**
 *  친구 목록에서 친구 우클릭 -> 유저 정보 선택시 뜨는 UI
 */
UCLASS()
class RLR_API UFriendInformation : public USubUI
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetFriendDetails(int FriendSeq);

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FriendName;
};
