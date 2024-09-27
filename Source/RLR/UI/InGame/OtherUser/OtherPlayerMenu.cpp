// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/OtherUser/OtherPlayerMenu.h"
#include "Structs/UtilStructs.h"

void UOtherPlayerMenu::NativeConstruct()
{
	Super::NativeConstruct();

	SetUIType(EUIType::OTHER_PLAYER_MENU);
}
