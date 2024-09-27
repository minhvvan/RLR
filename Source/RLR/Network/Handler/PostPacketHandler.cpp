// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Handler/PostPacketHandler.h"
#include "Structs/UtilStructs.h"
#include "GameManager/GameManager.h"
#include "GameManager/PostalManager.h"

bool Handle_POST_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_PostResponse& pkt)
{
	TArray<FPostResult> PostDataList;
	for (int32 i = 0; i < pkt.posts_size(); i++) {
		FPostResult postData;
		postData.MakePostData(pkt.posts().at(i));
		PostDataList.Add(postData);
	}
	// 우편 매니저에 우편 을 받는 것 구현 필요
	return false;
}
