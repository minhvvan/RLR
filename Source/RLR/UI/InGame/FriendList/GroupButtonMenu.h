// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "GroupButtonMenu.generated.h"

DECLARE_DELEGATE_OneParam(FGroupRemovedSignature, int32);

UCLASS()
class RLR_API UGroupButtonMenu : public USubUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void RemoveGroup();

	UFUNCTION()
	void SetGroupSeq(int CurrentFriendSeq) { GroupSeq = CurrentFriendSeq;};

	UFUNCTION()
	int GetGroupSeq() const {return GroupSeq;};

	FGroupRemovedSignature GroupRemovedSignature;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* RemoveGroupButton;

private:
	int GroupSeq;
};
