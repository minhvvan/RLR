// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyManager.h"
#include <Kismet/GameplayStatics.h>



void ULobbyManager::SetUserData(TArray<FUserData>& UserArray) {

}

void ULobbyManager::SetMapData(int mapId)
{
	FString MapName = TEXT("HyeonSeokTest");
	FName MapFName(*MapName);
	if (mapId == 1) {
		UGameplayStatics::OpenLevel(this, MapFName);
	}
	

}
