// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "GameManager/RLRStruct.h"
#include "Network/Proto/Packet.pb.h"
#include "CharacterStatusUI.generated.h"


 using FPlayerInfo = FUserCharacter;

 class UEquipmentUI;

UCLASS()
class RLR_API UCharacterStatusUI : public USubUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void RefreshUI() override;

	void UpdateTotalStat(const FTotalStatus& NewTotalStat);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UEquipmentUI> EquipmentUI;
};
