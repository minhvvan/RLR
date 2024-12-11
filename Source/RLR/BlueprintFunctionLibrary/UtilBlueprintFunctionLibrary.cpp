// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Network/Proto/Packet.pb.h"

#include "GameManager/GameManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/MonsterManager.h"
#include "GameManager/OtherUserManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/RLRStruct.h"
#include "GameManager/SkillManager.h"

#include "Structs/SkillStructs.h"
#include "Structs/ItemStructs.h"
#include "Structs/MonsterStructs.h"

#include <Kismet/GameplayStatics.h>

#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Handler/CertificationPacketHandler.h"

#include "UI/Lobby/LobbyMainUI.h"
#include "UI/Title/TitleMainUI.h"
#include "UI/Title/ServerListElement.h"
#include "UI/InGame/Trade/TradeUI.h"

void UUtilBlueprintFunctionLibrary::DebugLog(FString string)
{
	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, *string);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *string);
	}
}

void UUtilBlueprintFunctionLibrary::DebugMessage(const char* FunctionName, const char* FileName, int32 LineNumber)
{
	if (GEngine == nullptr)
		return;

	FString Result = FString::Printf(TEXT("%s is Error %s line - %d"), ANSI_TO_TCHAR(FunctionName), ANSI_TO_TCHAR(FileName), LineNumber);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Result);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, *Result);
}

void UUtilBlueprintFunctionLibrary::NotifyFeatureIncomplete()
{
	
	DEBUG_LOG("아직 제작 중인 기능입니다.");

	/*
		나중에는 미완성 알림 UI 띄워주기.
	*/
}

void UUtilBlueprintFunctionLibrary::Checkf(UObject* Object, FString Message)
{
	if (GEngine)
	{
		checkf(Object, TEXT("%s"), *Message);
	}
}

bool UUtilBlueprintFunctionLibrary::CheckValid(UObject* Object, FString Message, const char* FunctionName, const char* FileName, int32 LineNumber)
{
	if (IsValid(Object) == true)
		return true;
	if (GEngine == nullptr)
		return false;

	FString Result = FString::Printf(TEXT("%s Error %s %d, %s is not valid"), ANSI_TO_TCHAR(FunctionName), ANSI_TO_TCHAR(FileName), LineNumber, *Message);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Result);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, *Result);

	return false;
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

	//Delegate 인자 참조자로 변경: error 발생할 수 있음
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

void UUtilBlueprintFunctionLibrary::TestCharacterList()
{

	GameInstance->GetNetworkManager()->SendPlayerPacket();
}

void UUtilBlueprintFunctionLibrary::TestSkillQuickSlot()
{
	TArray<FSkillData> TestArray;

	{
		FSkillData Data = GameInstance->GetDataManager()->GetSkillData(3);
		TestArray.Add(Data);
	}

	{
		FSkillData Data = GameInstance->GetDataManager()->GetSkillData(302);
		TestArray.Add(Data);
	}

	{
		FSkillData Data = GameInstance->GetDataManager()->GetSkillData(304);
		TestArray.Add(Data);
	}

	GameInstance->GetSkillManager()->SetLearnedSkills(TestArray);
}

void UUtilBlueprintFunctionLibrary::TestItemQuickSlot()
{
	TArray<FItemData> TestArray;

	for (int32 i = 1; i <= 3; i++)
	{
		FItemData Data = GameInstance->GetDataManager()->GetItemData(i);
		TestArray.Add(Data);
	}

	GameInstance->GetInventoryManager()->SetQuickSlotItems(TestArray);
}

void UUtilBlueprintFunctionLibrary::TestServerList()
{
	TArray<FString> TestString = {TEXT("서버1"), TEXT("서버2"), TEXT("서버3"), TEXT("서버4"), "글자 깨짐 테스트 서버 5"};

	UTitleMainUI* Title = GameInstance->GetUIManager()->GetPage<UTitleMainUI>(FGameplayTagManager::Get().Page_InGame);
	if (IsValid(Title) == false)
		return;

	for(int32 i = 0 ; i < 5; i++)
	{ 
		FServerData Data;
		Data.ServerSeq = i;
		Data.ServerName = TestString[i];
		Title->AddServerListElement(Data);
	};	
}

void UUtilBlueprintFunctionLibrary::Test_Handle_TRADE_USER_REQUEST()
{
	GameInstance->GetNetworkManager()->SendTradeUserRequest(2);

}

void UUtilBlueprintFunctionLibrary::Test_Handle_TRADE_START_REQUEST()
{
}

void UUtilBlueprintFunctionLibrary::Test_Handle_TRADE_ADD_ITEM_REQUEST()
{
}

void UUtilBlueprintFunctionLibrary::Test_Handle_TRADE_ADD_GOOD_REQUEST()
{
}

void UUtilBlueprintFunctionLibrary::Test_Handle_TRADE_LOCK_REQUEST()
{
}

void UUtilBlueprintFunctionLibrary::Test_Handle_TRADE_CANCEL_REQUEST()
{
}

/*
	치트
*/

void UUtilBlueprintFunctionLibrary::CreateItem(int32 ItemSeq)
{
	if(IsValid(GameInstance) == false)
		return;

	FItemData Data = GameInstance->GetDataManager()->GetItemData(ItemSeq);
	if (Data == FItemData::EmptyItemData)
	{
		DEBUG_LOG("데이터 테이블에 없는 아이템입니다.");
		return;
	}

	GameInstance->GetNetworkManager()->SendCreateItemCheatPacket(ItemSeq);
}

void UUtilBlueprintFunctionLibrary::CreateSkill(int32 SkillSeq)
{
	if (IsValid(GameInstance) == false)
		return;

	FSkillData Data = GameInstance->GetDataManager()->GetSkillData(SkillSeq);
	if (Data == FSkillData::EmptySkillData)
	{
		DEBUG_LOG("데이터 테이블에 없는 스킬입니다.");
		return;
	}

	GameInstance->GetNetworkManager()->SendCreateSkillCheatPacket(SkillSeq);
}

void UUtilBlueprintFunctionLibrary::CreateMonster(int32 MonsterSeq)
{
	if (IsValid(GameInstance) == false)
		return;

	FMonsterStatus Data = GameInstance->GetDataManager()->GetMonsterData(MonsterSeq);
	if (Data == FMonsterStatus::EmptyMonsterData)
	{
		DEBUG_LOG("데이터 테이블에 없는 스킬입니다.");
		return;
	}

	GameInstance->GetNetworkManager()->SendCreateMonsterCheatPacket(MonsterSeq);
}

