// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ASCWidgetComponent.h"
#include "UI/InGame/Monster/MonsterHpBar.h"
#include "RLR.h"

void UASCWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UMonsterHpBar* MonsterHpBar = Cast<UMonsterHpBar>(GetWidget());
	if (!MonsterHpBar)
	{
		RLR_LOG(LogRLR, Log, TEXT("MonsterHpBar is Null"));
		return;
	}

	MonsterHpBar->SetActionSystemComponent(GetOwner());
}
