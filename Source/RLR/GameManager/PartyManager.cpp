// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/PartyManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"

void UPartyManager::CreateParty()
{
	GameInstance->GetNetworkManager()->SendCreateParty();
	SuccessCreateParty(1);
}

bool UPartyManager::GetHasParty()
{
	return CurrentPartyId != INVAILD_PARTY_ID;
}

void UPartyManager::JoinParty(int PartyId)
{
	GameInstance->GetNetworkManager()->SendJoinParty(PartyId);
}

void UPartyManager::LeaveParty()
{
	if (CurrentPartyId == INVAILD_PARTY_ID) return;
	GameInstance->GetNetworkManager()->SendLeaveParty(CurrentPartyId);
}

void UPartyManager::InviteParty(int OtherUserSeq)
{
	if (CurrentPartyId == INVAILD_PARTY_ID) return;
	//TODO: SendInviteParty(OtherUserSeq, CurrentPartyId);
}

void UPartyManager::SuccessCreateParty(int PartyId)
{
	SetCurrentPartyId(PartyId);
	SuccessCreate.Broadcast();
}

void UPartyManager::SuccessJoinParty(int PartyId)
{
	SetCurrentPartyId(PartyId);
	SuccessJoin.Broadcast();
}

void UPartyManager::SetCurrentPartyId(int PartyId)
{
	CurrentPartyId = PartyId;
}
