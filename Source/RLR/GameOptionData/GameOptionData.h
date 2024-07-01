// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
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
};

UCLASS()
class RLR_API UGameOptionData : public USaveGame
{
	GENERATED_BODY()

public:
    
    UFUNCTION(BlueprintCallable)
    void Init();

public:

	//채팅 옵션.
    UPROPERTY();
	FChatOption ChatOption;

    static const FString SlotName; 
};
