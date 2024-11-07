// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendRequestUI.h"
#include "UI/InGame/FriendList/FriendButtonUI.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Structs/UtilStructs.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/GameManager.h"


void UFriendRequestUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (FriendNameText)
	{
		FriendNameText->OnTextChanged.AddUniqueDynamic(this, &UFriendRequestUI::OnFriendNameTextChanged);
	}
	if (SendRequestButton)
	{
		SendRequestButton->OnClicked.AddUniqueDynamic(this, &UFriendRequestUI::OnSendRequestClicked);
	}
	if (CancelRequestButton)
	{
		CancelRequestButton->OnClicked.AddUniqueDynamic(this, &UFriendRequestUI::OnCancelClicked);
	}
}

/* TODO : FriendName을 통해 FriendSeq를 찾도록 변경해야 한다 */ 
void UFriendRequestUI::OnFriendNameTextChanged(const FText& Text)
{
	FString FriendName = Text.ToString();
	AddFriendButtonIfExists(FriendName);
}

void UFriendRequestUI::OnSendRequestClicked()
{
	GameInstance->GetNetworkManager()->SendRequestFriend(FriendNameText->GetText().ToString());
}

void UFriendRequestUI::OnCancelClicked()
{
	//CloseUI();
	OnCloseRequestUISignature.Broadcast(true);
}

/* 유저가 존재하면 버튼 추가 */
void UFriendRequestUI::AddFriendButtonIfExists(const FString& NewFriendName)
{
	//if (CheckIfFriendExists(NewFriendName))
	//{
	//	AddFriendButton(NewFriendName);
	//}
}

/* 유저 존재 여부 확인 (여기서는 단순히 확인, 실제로는 서버나 데이터베이스 조회) */
bool UFriendRequestUI::CheckIfFriendExists(const FString& NewFriendName)
{
	/* TODO : NewFriendName인 플레이어가 존재하는지 확인 */
	int UserSeq = GameInstance->GetUserSeq();
	int FriendNameSeq = FCString::Atoi(*NewFriendName);
	/* TODO : 현재 userSeq로 userName을 가져오는 로직이 있는지 모름. 일단 userSeq가 1인 플레이어 불러오기 */
	if (UserSeq == FriendNameSeq)
	{
		FriendSeq = FriendNameSeq;
		return true;
	}

	return false;
}

/* 현재 string 입력하면 안됨. int타입 seq로 고정해뒀음 */
void UFriendRequestUI::AddFriendButton(const FString& NewFriendName)
{
	if (!FriendScrollBox || NewFriendName.IsEmpty())
		return;
	if(FriendButtons.Contains(FCString::Atoi(*NewFriendName))) return;
	if (UFriendButtonUIClass)
	{
		UFriendButtonUI* NewFriendButton = CreateWidget<UFriendButtonUI>(this, UFriendButtonUIClass);
		if (NewFriendButton)
		{
			NewFriendButton->SetFriendInfo(FriendSeq, NewFriendName);

			FriendScrollBox->AddChild(NewFriendButton);
			/* TODO : 나중에 String(UserName)으로 바꾸기 */
			FriendButtons.Add(FCString::Atoi(*NewFriendName), NewFriendButton);
		}
	}
}