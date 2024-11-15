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


bool UNetworkManager::SendCharacterListReuest(int32 playerSeq)
{
	// 로비 ui로 이동 필요
	Protocol::CS_CharacterRequestPacket packet;
	packet.set_playerseq(playerSeq);

	TSharedPtr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
	bool bSuccess = SendToLobbySocket(sendBuffer);
	if (!bSuccess) {
		UE_LOG(LogTemp, Error, TEXT("Enter 패킷 송신 실패"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Enter 패킷 송신 성공"));
	}

	DEBUG_INCOMPLETE;

	return bSuccess;

}

bool UNetworkManager::SendEnterGameFromLobbyReqeust(const FUserCharacter& Character)
{
	/*
		로비에서 선택한 캐릭터 입장
	*/
	
	GameInstance->SetUserSeq(Character.UserSeq);
	GameInstance->GetNetworkManager()->SendEnterPacket(Character.UserSeq);
	DEBUG_INCOMPLETE;
	return false;
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