// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameplayTagsManager.h"
#include "GameOptionData.generated.h"

/**
	게임 옵션을 저장하기 위한 클래스.
 */

UENUM(BlueprintType)
enum class EChatType : uint8
{
    General = 0,
    Whisper= 1,
    Country = 2,
    World = 3,
    Guild = 4,
    Raid = 5,
    Party = 6,
    Continent = 7,
    Nearby = 8,
    None = 9,
};

USTRUCT(BlueprintType)
struct FChatOption
{
    GENERATED_BODY()
	//채팅 필터

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EChatType, bool> bVisibleChatOption;

    void Init();
};

USTRUCT(BlueprintType)
struct FSkillQuickSlotOption
{
    GENERATED_BODY()
    /*
      옵션 정보에 스킬 퀵 슬롯을 저장하기 위한 구조체.

      <Skill Action Tag, Skill Seq> 
      만약 Skill ID가 -1이면 없는 걸로 친다.

  
      이제 서버에서 스킬 퀵 슬롯 정보를 관리할거라서 추후 삭제할 수도 있음. 
      하지만 일단 클라이언트 자체에서 스킬 옵션 정보를 가지고 있어서 나쁠 건 없으니,
      가지고 있는 걸로.
    */

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FGameplayTag, int32> SkillQuickSlotList;

    void Init();

    bool IsEquippedSkill(int32 Id);

};

UCLASS()
class RLR_API UGameOptionData : public USaveGame
{
	GENERATED_BODY()

public:
    
    UFUNCTION(BlueprintCallable)
    void Init();

    FSkillQuickSlotOption& GetSkillQuickSlotOption();

public:

	//채팅 옵션.
    UPROPERTY();
	FChatOption ChatOption;

    //스킬 퀵 슬롯
    UPROPERTY()
    FSkillQuickSlotOption SkillQuickSlotOption;

    static const FString SlotName; 
};
