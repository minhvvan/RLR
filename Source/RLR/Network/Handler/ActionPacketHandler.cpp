// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/ActionPacketHandler.h"
#include "GameManager/GameManager.h"
#include "GameManager/MonsterManager.h"
#include "GameManager/OtherUserManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/NetworkManager.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"
#include "Structs/PlayerStructs.h"
#include "ClientPacketHandler.h"


bool Handle_ATTACK_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_AttackResponsePacket& pkt) {
    int skillSeq =  pkt.skill().skillseq();
    int userSeq = pkt.skill().userseq();
    // 남에꺼 소환하는 거 만들어주세요
	return true;
}

bool Handle_MOVE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_MoveResponsePacket& pkt) {
	return true;
}
bool Handle_MOVE_BROADCAST(TSharedPtr<PacketSession>& session, Protocol::SC_MoveBroadcastPacket& pkt) {

	UOtherUserManager* OtherManager = GameInstance->GetOtherUserManager();
	if (GameInstance->GetUserSeq() != pkt.userseq()) {
		if (OtherManager->GetPlayer(pkt.userseq())) {
			OtherManager->GetPlayer(pkt.userseq())->UpdateTransform(FVector(pkt.transx(), pkt.transy(), pkt.transz()));
		}
		else {

			Protocol::UserCharacter userCharacter;
			userCharacter.set_userseq(pkt.userseq());
			userCharacter.set_transx(pkt.transx());
			userCharacter.set_transy(pkt.transy());
			userCharacter.set_transz(pkt.transz());

			OtherManager->AddPlayer(userCharacter);
		}
	}

	//UIManager->UpdatedPlayerInfo.Broadcast(UserCharacter); 플레이어 매니저로 이전 
	return true;
}

bool Handle_ACTION_BROADCAST(TSharedPtr<PacketSession>& session, Protocol::SC_ActionBroadcastPacket& pkt)
{
	UOtherUserManager* otherManager = GameInstance->GetOtherUserManager();

	if (GameInstance->GetUserSeq() != pkt.userseq())
	{
		if (otherManager->GetPlayer(pkt.userseq()))
		{
			FActionResult actionResult;
			actionResult.UserSeq = pkt.userseq();
			actionResult.ActionSeq = pkt.actionseq();
			actionResult.TargetTransform = FVector(pkt.transx(), pkt.transy(), pkt.transz());

			otherManager->GetPlayer(pkt.userseq())->UpdateAction(actionResult);
		}
		else
		{
			Protocol::UserCharacter userCharacter;
			userCharacter.set_userseq(pkt.userseq());
			otherManager->AddPlayer(userCharacter);
			return true;
		}
	}

	return true;
}

bool Handle_MONSTER_ATTACK_REQUEST(TSharedPtr<PacketSession>& session, Protocol::SS_MonsterAttackRequestPacket& pkt) {

	return false;
}
bool Handle_MONSTER_MOVE_REQUEST(TSharedPtr<PacketSession>& session, Protocol::SC_MonsterMoveRequestPacket& pkt)
{
	// TODO :  몬스터 아이디를 통해 몬스터 매니저에있는 monster Data 중 Search하여 해당 몬스터의 좌표 변경 + 애니메이션 
	UE_LOG(LogTemp, Log, TEXT("monster Id : %lld"), pkt.monsterid());
	GameInstance->GetMonsterManager()->UpdateMonsterTransform(pkt.monsterid(), pkt.transx(), pkt.transy(), pkt.transz());

	return false;
}
bool Handle_DAMAGE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SS_DamageResponsePacket& pkt) {
	UE_LOG(LogTemp, Log, TEXT("Damage : %f"), pkt.damage());
	//UE_LOG(LogTemp, Log, TEXT("monster Id : %d"), pkt.monsterId());
	return true;
}

bool Handle_MONSTER_STATUS_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_MonsterStatusBroadcastPacket& pkt) {
	UE_LOG(LogTemp, Log, TEXT("monster Id : %lld"), pkt.monsterid());
	UE_LOG(LogTemp, Log, TEXT("monster hp : %f"), pkt.hp());
	GameInstance->GetMonsterManager()->UpdateMonsterHp(pkt.monsterid(), pkt.hp());

	return true;
}

bool Handle_MONSTER_DIE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_MonsterDieBroadcast& pkt)
{
	// 몬스터 매니저에 몬스터 스테이트랑 연결해서 monster 사망 처리 
	//GameInstance->GetMonsterManager()->UpdateMonsterState(pkt.monsterid(),1);

	return false;
}
