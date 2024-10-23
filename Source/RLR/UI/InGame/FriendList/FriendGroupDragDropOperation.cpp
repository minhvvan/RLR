// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/FriendList/FriendGroupDragDropOperation.h"

UFriendGroupDragDropOperation::UFriendGroupDragDropOperation() :
	GroupData(FFriendGroupResult())
{
}

void UFriendGroupDragDropOperation::SetFriendGroupData(const FFriendGroupResult& NewGroupData)
{
	GroupData = NewGroupData;
}

const FFriendGroupResult& UFriendGroupDragDropOperation::GetFriendGroupData()
{
	return GroupData;
}

void UFriendGroupDragDropOperation::Clear()
{
    SetFriendGroupData(FFriendGroupResult());
}