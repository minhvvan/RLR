// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameManager.generated.h"

/**
 
 GameManager에 다른 매니저를 붙일 때는 UGameInstanceSubsystem 상속 받는 매니저로 생성할 것을 추천

	GameManager.
		DataManager
			아이템 데이터. 
			스킬 데이터
			데이터 관련된 정보를 들고 있을 매니저.
		ObjectManager
			프로그램 위에 올라와 있는 몬스터, 아이템, NPC 관련들을 관리할 매니저.

 */


 class UDataManager;

UCLASS()
class RLR_API UGameManager : public UGameInstance
{
	GENERATED_BODY()
	

	UFUNCTION(BlueprintCallable)
	UDataManager* GetDataManager();
};
