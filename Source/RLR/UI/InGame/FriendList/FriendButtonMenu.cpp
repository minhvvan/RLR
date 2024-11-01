// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendButtonMenu.h"
#include "UI/InGame/FriendList/ExistingGroupList.h"
#include "Structs/UtilStructs.h"
#include "Components/Button.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"

void UFriendButtonMenu::NativeConstruct()
{
	Super::NativeConstruct();

	SetUIType(EUIType::FRIEND_MENU_UI);

	if (PlayerInfoButton)
	{
		PlayerInfoButton->OnClicked.AddDynamic(this, &UFriendButtonMenu::OpenFriendInfoUI);
	}
	if (RemoveFriendButton)
	{
		RemoveFriendButton->OnClicked.AddDynamic(this, &UFriendButtonMenu::RemoveFriend);
	}
	if (MoveGroupButton)
	{
		MoveGroupButton->OnClicked.AddDynamic(this, &UFriendButtonMenu::MoveGroup);
	}
}

// TODO : 프로필 보기
void UFriendButtonMenu::OpenFriendInfoUI()
{
	OnFriendInfoClicked.Broadcast(FriendSeq);
}
// 친구 삭제
void UFriendButtonMenu::RemoveFriend()
{
	GameInstance->GetNetworkManager()->SendRemoveFriend(FriendSeq);
	// TODO : 친구 삭제 friendListUI에 전달하기

}
// 그룹 이동(그룹 리스트 Open)
void UFriendButtonMenu::MoveGroup()
{
	if (bIsGroupListOpen)
	{
		bIsGroupListOpen = false;
		GroupListUI->CloseUI();
	}
	else
	{
		bIsGroupListOpen = true;
		if (GroupListUI)
		{
			GroupListUI->OpenUI();
		}
	}
}