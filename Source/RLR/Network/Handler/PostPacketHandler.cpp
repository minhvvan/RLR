// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/PostPacketHandler.h"
#include "Structs/UtilStructs.h"
#include "GameManager/GameManager.h"
#include "GameManager/PostalManager.h"

bool Handle_POST_SEND_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_PostSendResponse& pkt)
{
	FPostResult postData;
	postData.MakePostData(pkt.posts());
	// 우편 매니저에 우편 받는 것 구현 필요
	 GameInstance->GetPostalManager()->SetAlertPostData(postData);
	return false;
}
bool Handle_POST_GET_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_PostGetResponse& pkt) {


	TArray<FPostResult> sendPostDataList;
	TArray<FPostResult> recvPostDataList;
	for (int32 i = 0; i < pkt.sendposts_size(); i++) {
		FPostResult postData;
		postData.MakePostData(pkt.sendposts().at(i));
		sendPostDataList.Add(postData);
	}
	for (int32 i = 0; i < pkt.recvposts_size(); i++) {
		FPostResult postData;
		postData.MakePostData(pkt.recvposts().at(i));
		recvPostDataList.Add(postData);
	}
	// 우편 매니저에 우편 메시지 조회 구현 필요
	GameInstance->GetPostalManager()->SetSentPostData(sendPostDataList);
	GameInstance->GetPostalManager()->SetRecvPostData(recvPostDataList);
	return true;
}