// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/ActionPacketHandler.h"
#include "GameManager/GameManager.h"
#include "GameManager/MonsterManager.h"
#include "ClientPacketHandler.h"


bool Handle_ATTACK_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::AttackResponsePacket& pkt) {
    int skillSeq =  pkt.skill().skillseq();
    // 남에꺼 소환하는 거 만들어주세요
	return true;
}

bool Handle_MOVE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::MoveResponsePacket& pkt) {
    return true;
}
bool Handle_MOVE_BROADCAST(TSharedPtr<PacketSession>& session, Protocol::MoveBroadcastPacket& pkt) {
    // TODO : OTHERUSERMAGER 연결하여 다른 유저의 위치 연동
    UE_LOG(LogTemp, Log, TEXT("User seq : %d"), pkt.userseq());
    UE_LOG(LogTemp, Log, TEXT("User Trans X : %d"), pkt.transx());
    UE_LOG(LogTemp, Log, TEXT("User Trans Y : %d"), pkt.transy());
    UE_LOG(LogTemp, Log, TEXT("User Trans Z : %d"), pkt.transz());
    return true;
}

bool Handle_MONSTER_ATTACK_REQUEST(TSharedPtr<PacketSession>& session, Protocol::MonsterAttackRequestPacket& pkt) {

    return false;
}
bool Handle_MONSTER_MOVE_REQUEST(TSharedPtr<PacketSession>& session, Protocol::MonsterMoveRequestPacket& pkt)
{
    // TODO :  몬스터 아이디를 통해 몬스터 매니저에있는 monster Data 중 Search하여 해당 몬스터의 좌표 변경 + 애니메이션 
    GameInstance->GetMonsterManager()->UpdateMonsterTransform(pkt.monsterid(), pkt.transx(), pkt.transy(), pkt.transz());

    return false;
}
bool Handle_DAMAGE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::DamageResponsePacket& pkt) {
    UE_LOG(LogTemp, Log, TEXT("Damage : %f"), pkt.damage());
    //UE_LOG(LogTemp, Log, TEXT("monster Id : %d"), pkt.monsterId());
    return true;
}

bool Handle_MONSTER_STATUS_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::MonsterStatusBroadcastPacket& pkt) {
    UE_LOG(LogTemp, Log, TEXT("monster Id : %lld"), pkt.monsterid());
    UE_LOG(LogTemp, Log, TEXT("monster hp : %f"), pkt.hp());
    GameInstance->GetMonsterManager()->UpdateMonsterHp(pkt.monsterid(), pkt.hp());
    
    return true;
}