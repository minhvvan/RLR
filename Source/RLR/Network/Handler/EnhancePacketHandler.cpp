#include "EnhancePacketHandler.h"

bool Handle_ENHANCE_SUCCESS_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EnhanceSuccessResponse& pkt)
{
	int userSeq = pkt.userseq();

	// 성공 UI 오픈
	return true;
}
bool Handle_ENHANCE_FAILURE_RESPONSE(TSharedPtr<PacketSession>& session, Protocol::SC_EnhanceFailureResponse& pkt)
{
	int userSeq = pkt.userseq();
	// 실패 UI 오픈
	
	return true;
}