// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "../../../Network/Proto/Packet.pb.h"
#include "GameManager/RLRStruct.h"
#include "PartyUI.generated.h"



class ARLRPlayerCharacter;
class UPartyListElement;
class UScrollBox;
class UListView;

/**
	
	파티창에서는 뭘 보여줘야 하고, 뭘 가지고 있어야 할까?
	현재 기획이 나온게 없어서 껍데기만 만들어둠. 나중에 기획 추가되면 보완해줄 것.

	-------파티창-------
	1.Player [hp ----bar]
	2.Player
	3.Player
	4.Player


	파티 관련된 기능만을 관리하는 PartySystemComponent가 필요할까?
	
	일단 임시적으로 UI에서 파티 정보들 들고 있게 해둠. 아마 나중에는 높은 확률로 파티 정보를 따로 관리할수도.

 */

UCLASS()
class RLR_API UPartyUI : public USubUI
{
	GENERATED_BODY()

private:
	
	virtual void NativeConstruct() override;

	
public:

	virtual void RefreshUI() override;


	/*
		파티원은 한 명씩 추가 될 수도 있고, 여러명이 한 번에 추가될 수도 있다.
		ex)누군가가 나보다 늦게 들어오는 경우 한 명씩 추가.
		ex)내가 중간에 들어온 경우라면, 한 번에 여러명씩 추가.
	*/
	UFUNCTION()
	virtual void AddPlayer(FUserCharacter& NewPlayer);

	UFUNCTION()
	virtual void RemovePlayer(FUserCharacter& LeavePlayer);

public:

	/*
		bind
	*/


    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UListView> PlayerList;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, UPartyListElement*> PlayerMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPartyListElement> PartyListElementClass;

};
