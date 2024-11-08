// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendInformation.h"
#include "Structs/UtilStructs.h"
#include "Components/TextBlock.h"

void UFriendInformation::NativeConstruct()
{
	Super::NativeConstruct();
}

void UFriendInformation::SetFriendDetails(int FriendSeq)
{
	FriendName->SetText(FText::FromString(FString::FromInt(FriendSeq)));
}