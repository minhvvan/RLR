// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "GameManager/RLRStruct.h"
#include "Network/Proto/Packet.pb.h"

#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/MonsterManager.h"
#include "GameManager/OtherUserManager.h"


void UUtilBlueprintFunctionLibrary::DebugLog(FString string)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, *string);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *string);
	}
}

void UUtilBlueprintFunctionLibrary::MakeItemData()
{
	Protocol::Item TestItem;
	TestItem.set_rank(1);
	TestItem.set_type("CONSUMPTION");
	TestItem.set_rank(3);
	TestItem.set_text("테스트 텍스트입니다.");
	TestItem.mutable_equip()->set_equippart(4);

	FItemData TestItemData;
	TestItemData.MakeItemData(TestItem);
}

void UUtilBlueprintFunctionLibrary::TestUpdateStatus()
{

	Protocol::UserCharacter TestPlayerInfo;

	TestPlayerInfo.mutable_totalstatus()->set_usermaxhp(999);
	TestPlayerInfo.mutable_totalstatus()->set_userstrength(1231);

	FUserCharacter UserCharacter;
	UserCharacter.SetUserChracterData(TestPlayerInfo);
	GameInstance->GetUIManager()->UpdatedPlayerInfo.Broadcast(UserCharacter);
}

void UUtilBlueprintFunctionLibrary::TestAddPartyPlayer()
{
	Protocol::UserCharacter TestPlayerInfo;

	TestPlayerInfo.set_name("테스트 플레이어");

	TestPlayerInfo.mutable_totalstatus()->set_usermaxhp(100);
	TestPlayerInfo.mutable_totalstatus()->set_userhp(50);

	GameInstance->GetOtherUserManager()->AddPlayerToParty(TestPlayerInfo);
}

