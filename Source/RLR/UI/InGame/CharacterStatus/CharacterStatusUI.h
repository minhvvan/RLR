// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "GameManager/RLRStruct.h"
#include "Network/Proto/Packet.pb.h"
#include "CharacterStatusUI.generated.h"

/**
 
	일단 Proto 구조체를 썡으로 써보다가, 나중에 수정이 필요할 것 같으면 바꿔줄 예정

 */


 using FPlayerInfo = FUserCharacter;

 class UEquipmentUI;

UCLASS()
class RLR_API UCharacterStatusUI : public USubUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void RefreshUI() override;
	
	UFUNCTION()
	void SetPlayerInfo(FUserCharacter NewPlayerInfo);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UEquipmentUI> EquipmentUI;

public:

	FUserCharacter PlayerInfo;

};
