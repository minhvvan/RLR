// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/InGame/BaseUI.h"
#include "SubUI.generated.h"

/**
 
	SubUI는 InGameUI가 생성되면 같이 생성되어, 
	사용되지 않을 때는 Hidden 상태로 있다가 사용될 때 Visible로 바뀌어 보이게 된다.

 */
UCLASS()
class RLR_API USubUI : public UBaseUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void Init();
	virtual void CloseUI();
	
};
