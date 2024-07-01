// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOptionData/GameOptionData.h"


const FString UGameOptionData::SlotName =  FString(TEXT("GameOptionData"));

void UGameOptionData::Init()
{
	ChatOption.bVisibleChatOption.Add(EChatType::General, true);
	ChatOption.bVisibleChatOption.Add(EChatType::Whisper, true);
	ChatOption.bVisibleChatOption.Add(EChatType::Country, true);
	ChatOption.bVisibleChatOption.Add(EChatType::World, true);
	ChatOption.bVisibleChatOption.Add(EChatType::Guild, true);
	ChatOption.bVisibleChatOption.Add(EChatType::Raid, true);
	ChatOption.bVisibleChatOption.Add(EChatType::Party, true);
	ChatOption.bVisibleChatOption.Add(EChatType::Continent, true);
	ChatOption.bVisibleChatOption.Add(EChatType::Nearby, true);

}
