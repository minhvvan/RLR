// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LobbyManager.generated.h"

/**
 * 
 */
UCLASS()
class RLR_API ULobbyManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:


	void SetUserData(TArray<FUserData>& UserArray);
	void SetMapData(int mapId);

private:
	TArray<FUserData> Users;

};
