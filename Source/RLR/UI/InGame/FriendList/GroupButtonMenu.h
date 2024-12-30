// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "GroupButtonMenu.generated.h"

DECLARE_DELEGATE_OneParam(FGroupRemovedSignature, int32);
DECLARE_DELEGATE_OneParam(FGroupCreateSignature, bool);
DECLARE_DELEGATE_ThreeParams(FGroupRenameSignature, bool, FString, int32);

UCLASS()
class RLR_API UGroupButtonMenu : public USubUI
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void RemoveGroup();

	UFUNCTION()
	void CreateGroup();

	UFUNCTION()
	void RenameGroup();

	UFUNCTION()
	void SetGroupSeq(int CurrentFriendSeq) { groupSeq = CurrentFriendSeq; };

	UFUNCTION()
	int GetGroupSeq() const { return groupSeq; };

	void SetGroupName(FString CurrentGroupName); 

	FGroupRemovedSignature GroupRemovedSignature;
	FGroupCreateSignature GroupCreateSignature;
	FGroupRenameSignature GroupRenameSignature;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* RemoveGroupButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CreateGroupButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RenameGroupButton;

private:
	int groupSeq;
	FString groupName;
};
