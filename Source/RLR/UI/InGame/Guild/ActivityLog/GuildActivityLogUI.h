// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GuildActivityLogUI.generated.h"

/**
 * 길드 활동 관련 (주간 획득 길드포인트/개인 포인트, 보유중인 개인 포인트, 활동로그)
 */
UCLASS()
class RLR_API UGuildActivityLogUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void RefreshUI();
};
