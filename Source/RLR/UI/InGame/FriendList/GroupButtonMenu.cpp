// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/GroupButtonMenu.h"
#include "UI/InGame/FriendList/FriendTabWidget.h"
#include "UI/InGame/FriendList/GroupButtonUI.h"
#include "UI/InGame/FriendList/FriendListUI.h"
#include "GameManager/LiteralManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/FriendManager.h"
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
	if (CreateGroupButton)
	{
		CreateGroupButton->OnClicked.AddUniqueDynamic(this, &UGroupButtonMenu::CreateGroup);
	}
	if (RenameGroupButton)
	{
		RenameGroupButton->OnClicked.AddUniqueDynamic(this, &UGroupButtonMenu::RenameGroup);
	}
}

void UGroupButtonMenu::RemoveGroup()
{
	GameInstance->GetNetworkManager()->SendRemoveFriendGroup(groupSeq);
	GroupRemovedSignature.Execute(groupSeq);
}

void UGroupButtonMenu::CreateGroup()
{	
	GroupCreateSignature.Execute(false);
}

void UGroupButtonMenu::RenameGroup()
{
	/* default group일 경우, 그룹명 변경 불가 */
	if(groupName == RLRLITERAL.Friend_DefaultGroup) return;
	GroupRenameSignature.Execute(false, groupName, groupSeq);
}

void UGroupButtonMenu::SetGroupName(FString CurrentGroupName)
{
	groupName = CurrentGroupName;
}