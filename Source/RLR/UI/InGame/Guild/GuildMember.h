// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/InGame/Guild/BaseGuildMember.h"
#include "GuildMember.generated.h"

/**
 * 길드원 탭에 속한 Guild Member Button (직급, 이름, 레벨, 직업, 현재 위치, 명성치, 접속상태가 표시됨)
 */
UCLASS()
class RLR_API UGuildMember : public UBaseGuildMember
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	FString GetGuildRankText(EGuildRole Rank);
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GuildRankText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentLocation;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GuildReputation;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> OnlineStatusText;
};
