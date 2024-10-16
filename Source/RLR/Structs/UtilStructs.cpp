// Fill out your copyright notice in the Description page of Project Settings.


#include "Structs/UtilStructs.h"

const FExpTable FExpTable::EmptyExpData;
const FAnimData FAnimData::EmptyAnimData = FAnimData(FGameplayTag::EmptyTag, nullptr);

void FAttackResult::MakeAttackData()
{
}

void FPostResult::MakePostData(const Protocol::Post post)
{
	ReceiverSeq = post.receiverseq();

	Title = UTF8_TO_TCHAR(post.title().c_str());

	SenderSeq = post.senderseq();

	Content = UTF8_TO_TCHAR(post.content().c_str());

	for (auto& itemId : post.itemid()) {
		ItemId.Add(itemId);
	}

	TotalMoney = post.totalmoney();

	IsRead = post.isread();

	IsReceived = post.isreceived();

	PostId = post.postid();

	SenderName = UTF8_TO_TCHAR(post.sendername().c_str());
	ReceiverName = UTF8_TO_TCHAR(post.receivername().c_str());
}
