// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/GroupButtonMenu.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameManager.h"
#include "Structs/UtilStructs.h"
#include "Components/Button.h"

void UGroupButtonMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (RemoveGroupButton)
	{
		RemoveGroupButton->OnClicked.AddUniqueDynamic(this, &UGroupButtonMenu::RemoveGroup);
	}
}

void UGroupButtonMenu::RemoveGroup()
{
	GameInstance->GetNetworkManager()->SendRemoveFriendGroup(GroupSeq);
	GroupRemovedSignature.Execute(GroupSeq);
}