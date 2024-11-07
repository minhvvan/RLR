// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Structs/UtilStructs.h"
#include "GuildManager.generated.h"

class UGuildUI;

UCLASS()
class RLR_API UGuildManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	/* Guild Struct 만들어야 함 */
	void SetGuildInfo(const FGuildResult& guildData);	
	FGuildResult GetGuildInfo();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuildResult GuildData;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TObjectPtr<UGuildUI> GuildOverlayUI;

private:
	bool bBelongToGuild;
};
