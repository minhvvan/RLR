// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildMainUI.h"
#include "UI/InGame/Guild/GuildInfoUI.h"

void UGuildMainUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGuildMainUI::RefreshUI()
{
	GuildInfoUI->RefreshUI();
}