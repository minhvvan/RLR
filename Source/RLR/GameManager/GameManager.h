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
		EffectManager
			이펙트
		LevelManager
			레벨 이동 관리
		QuestManager
			Quest 관리
		LobbyManager
			Lobby 관리
		PartyManager
			Party 관리(생성, 조회, 참가, 탈퇴)
 */

class UDataManager;
class UUIManager;
class UInventoryManager;
class USkillManager;
class UGameOptionData;
class UQuestManager;
class UNetworkManager;
class UMonsterManager;
class UOtherUserManager;
class UPlayerManager;
class UObjectManager;
class UEffectManager;
class ULevelManager;
class ULobbyManager;
class UPostalManager;
class UFriendManager;
class UPartyManager;
class UGuildManager;

UCLASS()
class RLR_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;
	virtual void LoadComplete(const float LoadTime, const FString& MapName);
	
	void SetUserSeq(int32 userSeq);
	void SetPlayerSeq(int32 playerSeq);

	int32 GetUserSeq() { return UserSeq; }
	int32 GetPlayerSeq() { return PlayerSeq; }

	UFUNCTION(BlueprintCallable)
	UDataManager*		GetDataManager();

	UFUNCTION(BlueprintCallable)
	UUIManager*			GetUIManager();

	UFUNCTION(BlueprintCallable)
	UInventoryManager*	GetInventoryManager();

	UFUNCTION(BlueprintCallable)
	USkillManager*		GetSkillManager();

	UFUNCTION(BlueprintCallable)
	UNetworkManager*	GetNetworkManager();

	UFUNCTION(BlueprintCallable)
	UMonsterManager*	GetMonsterManager();

	UFUNCTION(BlueprintCallable)
	UOtherUserManager*	GetOtherUserManager();

	UFUNCTION(BlueprintCallable)
	UPlayerManager*		GetPlayerManager();
	
	UFUNCTION(BlueprintCallable)
	UObjectManager*		GetObjectManager();

	UFUNCTION(BlueprintCallable)
	UGameOptionData*	GetGameOptionData();

	UFUNCTION(BlueprintCallable)
	UEffectManager*		GetEffectManager();

	UFUNCTION(BlueprintCallable)
	ULevelManager*		GetLevelManager();

	UFUNCTION(BlueprintCallable)
	UQuestManager*		GetQuestManager();

	UFUNCTION(BlueprintCallable)
	UPostalManager*		GetPostalManager();	
	
	UFUNCTION(BlueprintCallable)
	UPartyManager*		GetPartyManager();

	UFUNCTION(BlueprintCallable)
	UFriendManager*		GetFriendManager();

	UFUNCTION(BlueprintCallable)
	UGuildManager*		GetGuildManager();

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

	UPROPERTY()
    int32 PlayerSeq;
    UPROPERTY()
    int32 UserSeq;
};
extern  UGameManager* GameInstance;