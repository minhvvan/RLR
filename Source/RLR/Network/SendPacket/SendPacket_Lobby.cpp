// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/GameManager.h"

#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

#include "Network/LoadBalancerClient.h"
#include <Networking.h>
#include "Network/FNetworkReceiver.h"
#include <Network/Buffer.h>
#include "Network/Handler/ClientPacketHandler.h"
#include "Network/Proto/Packet.pb.h"
#include "Network/Proto/Skill.pb.h"
#include "Network/Proto/Item.pb.h"
#include "Structs/PlayerStructs.h"

/*

	Lobby.proto

*/


bool UNetworkManager::SendCharacterListReuest(int32 userSeq)
{
	/*
		로비에서 캐릭터 리스트창에 띄울 캐릭터 정보 요청
	*/

	DEBUG_INCOMPLETE;
	return false;
}

bool UNetworkManager::SendEnterGameFromLobbyReqeust(const FUserCharacter& Character)
{
	/*
		로비에서 선택한 캐릭터 입장
	*/
	
	GameInstance->GetNetworkManager()->SetUserSeq(Character.UserSeq);
	GameInstance->GetNetworkManager()->SetMapId(Character.MapId);
	GameInstance->GetNetworkManager()->SendEnterPacket(Character.UserSeq);
	return true;
}

bool UNetworkManager::SendCharacterDeleteRequest(const FUserCharacter& DeleteCharacter)
{
	/*
		로비에서 캐릭터 리스트에서 선택한 캐릭터 삭제
	*/

	DEBUG_INCOMPLETE;
	return false;
}


bool UNetworkManager::SendCreateCharacterRequest(const FText NewCharacterName, int32 NewCharacterID)
{
	/*
		캐릭터 생성 요청.
	*/
	DEBUG_INCOMPLETE;
	return false;
}