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
		InventoryManager
			서버에서 소유한 아이템 정보를 보내주면 관리할 매니저.
		UIManager
			UI를 열고 닫기를 관리할 매니저.
		SkillManager
			Skill 관리 매니저(등록, 실행)
		MonsterManager
			Monster 관리 매니저
		OtherUserManager
			다른 플레이어 관리.
		PlayerUserManager
			플레이어 관리.
		ObjectManager
			NPC, 오브젝트 관리.
 */


class UDataManager;
class UUIManager;
class UInventoryManager;
class USkillManager;
class UGameOptionData;
class UNetworkManager;
class UMonsterManager;
class UOtherUserManager;
class UPlayerManager;
class UObjectManager;


UCLASS()
class RLR_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;

	

	UFUNCTION(BlueprintCallable)
	UDataManager* GetDataManager();

	UFUNCTION(BlueprintCallable)
	UUIManager* GetUIManager();

	UFUNCTION(BlueprintCallable)
	UInventoryManager* GetInventoryManager();

	UFUNCTION(BlueprintCallable)
	USkillManager* GetSkillManager();

	UFUNCTION(BlueprintCallable)
	UNetworkManager* GetNetworkManager();

	UFUNCTION(BlueprintCallable)
	UMonsterManager* GetMonsterManager();

	UFUNCTION(BlueprintCallable)
	UOtherUserManager* GetOtherUserManager();

	UFUNCTION(BlueprintCallable)
	UPlayerManager* GetPlayerManager();
	
	UFUNCTION(BlueprintCallable)
	UObjectManager* GetObjectManager();

	UFUNCTION(BlueprintCallable)
	UGameOptionData* GetGameOptionData();

	

	UFUNCTION(BlueprintCallable)
	void SaveGameOption();

	UFUNCTION(BlueprintCallable)
	void LoadGameOption();

private:
	/*
		게임 옵션 데이터
	*/
	UPROPERTY();
	TObjectPtr<UGameOptionData> GameOptionData;

	
};
extern  UGameManager* GameInstance;