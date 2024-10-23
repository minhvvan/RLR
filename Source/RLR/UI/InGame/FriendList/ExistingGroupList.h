// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "ExistingGroupList.generated.h"

class UGroupButtonUI;
class UVerticalBox;

/**
 *  존재하는 친구 그룹 리스트
 */
UCLASS()
class RLR_API UExistingGroupList : public USubUI
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* GroupListBox;
};
