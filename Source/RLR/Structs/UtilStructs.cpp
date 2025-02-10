// Fill out your copyright notice in the Description page of Project Settings.


#include "Structs/UtilStructs.h"

const FExpTable FExpTable::EmptyExpData;
const FAnimData FAnimData::EmptyAnimData = FAnimData(FGameplayTag::EmptyTag, nullptr);
const FActionResource FActionResource::EmptyActionResource = FActionResource();

void FAttackResult::MakeAttackData()
{
}

void FPostResult::MakePostData(const Protocol::Post& post, const Protocol::ItemList& items)
{
	ReceiverSeq = post.receiverseq();

	Title = UTF8_TO_TCHAR(post.title().c_str());

	SenderSeq = post.senderseq();

	Content = UTF8_TO_TCHAR(post.content().c_str());
	
	for (auto& itemId : post.itemid()) {
		ItemId.Add(itemId);
		ItemValues.FindOrAdd(itemId)++;
	}
	TotalMoney = post.totalmoney();

	IsRead = post.isread();

	IsReceived = post.isreceived();

	PostId = post.postid();
	for (const auto& item : items.items()) // itemList의 items() 순회
	{
		FItemData itemData;
		itemData.MakeItemData(item);
		ItemList.Add(itemData);
	}
	
	
	PostDate = UTF8_TO_TCHAR(post.makedate().c_str());

	SenderName = UTF8_TO_TCHAR(post.sendername().c_str());
	ReceiverName = UTF8_TO_TCHAR(post.receivername().c_str());
}

// group
void FFriendGroupResult::MakeGroupData(const Protocol::Group group)
{
	GroupSeq = group.groupseq();
	GroupName = UTF8_TO_TCHAR(group.groupname().c_str());

	for (auto& friendInfo : group.friends())
	{
		FriendSeq.Add(friendInfo.friendseq());
		FriendName.Add(UTF8_TO_TCHAR(friendInfo.friendname().c_str()));
	}
}

void FGuildResult::MakeGuildData(const Protocol::Guild guild)
{
	guildSeq = guild.guildseq();
	guildName = UTF8_TO_TCHAR(guild.guildname().c_str());
	guildLevel = guild.guildlevel();
	guildMaxExp = guild.guildmaxexp();
	guildExp = guild.guildexp();
	guildMaxUser = guild.guildmaxuser();

	GuildRanks.Empty();
	for (const auto& rank : guild.guildranks())
	{
		GuildRanks.Add(FGuildRank::MakeGuildRankData(rank));
	}
}

FGuildRank FGuildRank::MakeGuildRankData(const Protocol::GuildRank& guildRank)
{
	FGuildRank NewRank;
	NewRank.GuildRankSeq = (EGuildRole)guildRank.guildrankseq();
	NewRank.UserSeq = guildRank.userseq();
	NewRank.UserName = UTF8_TO_TCHAR(guildRank.username().c_str());
	
	return NewRank;
}