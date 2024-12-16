// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendButtonMenu.h"
#include "UI/InGame/FriendList/FriendListUI.h"
#include "UI/InGame/FriendList/FriendTabWidget.h"
#include "UI/InGame/FriendList/Popup/MoveGroupMessageBox.h"
#include "Structs/UtilStructs.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/FriendManager.h"

void UFriendButtonMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayerInfoButton)
	{
		PlayerInfoButton->OnClicked.AddUniqueDynamic(this, &UFriendButtonMenu::OpenFriendInfoUI);
	}
	if (RemoveFriendButton)
	{
		RemoveFriendButton->OnClicked.AddUniqueDynamic(this, &UFriendButtonMenu::RemoveFriend);
	}
	if (MoveGroupButton)
	{
		MoveGroupButton->OnClicked.AddUniqueDynamic(this, &UFriendButtonMenu::MoveGroup);
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
	GameInstance->GetFriendManager()->FriendListUI->OpenFriendMenuUI(true);
}
// 그룹 이동(그룹 리스트 Open)
void UFriendButtonMenu::MoveGroup()
{
	OnMoveGroupClicked.Broadcast();
}