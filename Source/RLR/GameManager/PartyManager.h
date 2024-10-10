// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PartyManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSuccessCreateParty);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSuccessJoinParty);

UCLASS()
class RLR_API UPartyManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/*--------------------
		Client Interface
	--------------------*/
	//생성
	void CreateParty();

	//조회
	bool GetHasParty();

	//참가
	void JoinParty(int PartyId);

	//탈퇴
	void LeaveParty();

	//참가 요청
	void InviteParty(int OtherUserSeq);


	/*--------------------
	Server Interface
	--------------------*/
	//Create Callback
	void SuccessCreateParty(int PartyId);

	//Join Callback
	void SuccessJoinParty(int PartyId);

public:
	FOnSuccessCreateParty SuccessCreate;
	FOnSuccessJoinParty SuccessJoin;

private:
	const int INVAILD_PARTY_ID = -1;
	int CurrentPartyId = INVAILD_PARTY_ID;

	void SetCurrentPartyId(int PartyId);
};
