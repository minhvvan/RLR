// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/Popup/RenameGroupMessageBox.h"
#include "UI/InGame/FriendList/FriendTabWidget.h"
#include "UI/InGame/FriendList/GroupButtonUI.h"
#include "UI/InGame/FriendList/FriendListUI.h"
#include "GameManager/FriendManager.h"
#include "GameManager/GameManager.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void URenameGroupMessageBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddUniqueDynamic(this, &URenameGroupMessageBox::ConfirmButtonClicked);
	}
	if (CancelButton)
	{
		CancelButton->OnClicked.AddUniqueDynamic(this, &URenameGroupMessageBox::CancelButtonClicked);
	}
	if (GroupNameText)
	{
		GroupNameText->OnTextChanged.AddUniqueDynamic(this, &URenameGroupMessageBox::OnGroupNameTextChanged);
	}
}

void URenameGroupMessageBox::ConfirmButtonClicked()
{
	if (!GroupNameText->GetText().IsEmpty())
	{
		FString NewGroupName = GroupNameText->GetText().ToString();
		UGroupButtonUI* GroupButtonUI = GameInstance->GetFriendManager()->FriendListUI->FriendTabWidget->GroupButtons.FindRef(groupSeq);
		
		/* 
			TODO : 아래 내용 지우고 서버에 요청하는 방식으로 변경하기, 
				   현재 서버에서는 변경되지 않아서 그룹이동/친구추가에서 변경전 이름으로 뜸 -> 누르면 오류남 
		*/
		GroupButtonUI->SetGroupInfo(groupSeq, NewGroupName);
	}
	OnCloseRenameGroupSignature.Broadcast(true);
}

void URenameGroupMessageBox::CancelButtonClicked()
{
	OnCloseRenameGroupSignature.Broadcast(true);
}

void URenameGroupMessageBox::OnGroupNameTextChanged(const FText& NewGroupName)
{
	FString NewGroupNameString = NewGroupName.ToString();
	if (NewGroupNameString.Len() > maxCharacters)
	{
		GroupNameText->SetText(FText::FromString(NewGroupNameString.Left(maxCharacters)));
	}
}

void URenameGroupMessageBox::SetCurrentGroupName(const FText& CurrentGroupName)
{
	CurrentGroupNameText->SetText(CurrentGroupName);
}

void URenameGroupMessageBox::SetGroupSeq(int32 CurrentGroupSeq)
{
	groupSeq = CurrentGroupSeq;
}