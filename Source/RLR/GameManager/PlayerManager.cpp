// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/PlayerManager.h"
#include "GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/LiteralManager.h"

#include "Kismet/GameplayStatics.h"
#include "RLRObjects/Characters/RLRPlayerCharacter.h"

#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/StatSet/StatSetPlayer.h"

#include "RLR.h"
#include "Structs/PlayerStructs.h"
#include "Structs/UtilStructs.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include <Player/RLRPlayerController.h>

UPlayerManager::UPlayerManager()
{
	// PlayerCharacterClass에 기본 캐릭터 클래스 설정
	static ConstructorHelpers::FClassFinder<ARLRPlayerCharacter> PlayerCharacterBPClass(*RLRLITERAL.RLRPlayerCharacter_Path);
	if (PlayerCharacterBPClass.Succeeded())
	{
		PlayerCharacterClass = PlayerCharacterBPClass.Class;
	}
	else
	{
		RLR_LOG(LogRLR, Error, TEXT("Failed to load BP_Player character class"));
	}
}

void UPlayerManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UpdatePlayerManagerDelegate.Clear();
}

ARLRPlayerCharacter* UPlayerManager::GetPlayerCharacter()
{
	if (IsValid(PlayerCharacter) == false)
	{
		DEBUG_LOG("GetPlayerCharacter Error. Player Character Is Null");
		return nullptr;
	}

	return PlayerCharacter;
}

FUserCharacter UPlayerManager::GetPlayerData()
{
	return UserData;
}

void UPlayerManager::SetPlayerData(FUserCharacter PlayerData)
{
	if (UWorld* World = GetWorld())
	{
		// 기존에 스폰된 캐릭터가 없으면 새로 스폰
		if (!PlayerCharacter)
		{
			
			ARLRPlayerCharacter* Player = Cast<ARLRPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));
			if (!Player)
			{
				AsyncTask(ENamedThreads::GameThread, [this, PlayerData, World]()
					{
				UserData = PlayerData;
				// 스폰할 위치와 회전 값이 PlayerData에 있다고 가정
				FVector SpawnLocation(PlayerData.Transform);
				FRotator SpawnRotation(0.0f, 0.0f, 0.0f);  // 정면 회전
				// 플레이어 캐릭터 스폰
				FActorSpawnParameters SpawnParams;
				ARLRPlayerCharacter* SpawnedCharacter = World->SpawnActor<ARLRPlayerCharacter>(PlayerCharacterClass, SpawnLocation, SpawnRotation, SpawnParams);
				if (SpawnedCharacter)
				{
					PlayerCharacter = SpawnedCharacter;

					// 플레이어 컨트롤러로 빙의 처리
					ARLRPlayerController* PlayerController = Cast<ARLRPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
					if (PlayerController)
					{
						PlayerController->Possess(SpawnedCharacter);
					}
				}
					});
			}
			else
			{
				PlayerCharacter = Player;
			}
			
		}

		// 플레이어 캐릭터가 유효하다면 데이터를 설정
		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->SetStat(PlayerData);
		}
	}
}

void UPlayerManager::UpdatePlayerTotalStatus(const FTotalStatus& NewTotalStatus)
{
	UStatSetPlayer* statSet = GetStatSet();
	if (!statSet) return;

	FStatChangeSpec<FTotalStatus> spec;
	spec.ChangedStat = statSet->GetTotalStatusStat();
	spec.NewValue = NewTotalStatus;


	statSet->ApplyChangeStat<FTotalStatus>(spec);
}

void UPlayerManager::UpdatePlayerSetStatus(const FSetStatus& NewSetStatus)
{
	UStatSetPlayer* statSet = GetStatSet();
	if (!statSet) return;

	FStatChangeSpec<FSetStatus> spec;
	spec.ChangedStat = statSet->GetSetStatusStat();
	spec.NewValue = NewSetStatus;

	statSet->ApplyChangeStat<FSetStatus>(spec);
}

void UPlayerManager::UpdatePlayerExp(int32 NewExp)
{
	AsyncTask(ENamedThreads::GameThread, [this, NewExp]()
		{
			UStatSetPlayer* statSet = GetStatSet();
			if (!statSet) return;

			FStatChangeSpec<int32> spec;
			spec.ChangedStat = statSet->GetExpStat();
			spec.NewValue = NewExp;

			statSet->ApplyChangeStat(spec);
		});
}

void UPlayerManager::UpdatePlayerLevel(int32 NewLevel)
{
	AsyncTask(ENamedThreads::GameThread, [this, NewLevel]()
		{
	UStatSetPlayer* statSet = GetStatSet();
	if (!statSet) return;

	FStatChangeSpec<int32> spec;
	spec.ChangedStat = statSet->GetLevelStat();
	spec.NewValue = NewLevel;

	statSet->ApplyChangeStat(spec);
		});
}

void UPlayerManager::UpdateTalent(const FTalent& NewTalent)
{
	UStatSetPlayer* statSet = GetStatSet();
	if (!statSet) return;

	FStatChangeSpec<FTalent> spec;
	spec.ChangedStat = statSet->GetTalentStat();
	spec.NewValue = NewTalent;

	statSet->ApplyChangeStat(spec);
}

void UPlayerManager::ApplyAbnormal(const FAbnormal& Abnormal)
{
	UStatSetPlayer* statSet = GetStatSet();
	if (!statSet) return;

	statSet->ApplyAbnormal(Abnormal);
}

bool UPlayerManager::RequestMove(const FMoveResult& MoveResult)
{
	return GameInstance->GetNetworkManager()->SendMovePacket(MoveResult.TargetTransform);
}

void UPlayerManager::UpdatePlayerTransform(const FVector& NewTransform)
{
	if (!PlayerCharacter)
	{
		ARLRPlayerCharacter* player = Cast<ARLRPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (player)
		{
			PlayerCharacter = player;
		}
	}

	PlayerCharacter->UpdateTransform(NewTransform);
}
void UPlayerManager::SpawnPlayerTransform(const FVector& NewTransform)
{
	if (!PlayerCharacter)
	{
		ARLRPlayerCharacter* player = Cast<ARLRPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (player)
		{
			PlayerCharacter = player;
		}
	}

	PlayerCharacter->SpawnTransform(NewTransform);
}

bool UPlayerManager::RequestTalent(int TalentOrder)
{
	//TODO: TalentOrder에 맞는 재능 변경 요청

	return false;
}

void UPlayerManager::UpdateUserGood(FUserGoods userGood)
{
	UserGood.Contribution = userGood.Contribution;
	UserGood.Reputation = userGood.Reputation;
}
void UPlayerManager::UpdatePlayerGood(FPlayerGoods playerGood)
{
	PlayerGood.TotalMoney = playerGood.TotalMoney;
	PlayerGood.Diamond = playerGood.Diamond;
}
FUserGoods UPlayerManager::GetUserGood() const
{
	return UserGood;
}
FPlayerGoods UPlayerManager::GetPlayerGood() const
{
	return PlayerGood;
}
UStatSetPlayer* UPlayerManager::GetStatSet()
{
	if (UWorld* world = GetWorld())
	{
		if (!PlayerCharacter)
		{
			ARLRPlayerCharacter* player = Cast<ARLRPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(world, 0));
			if (player)
			{
				PlayerCharacter = player;
			}
		}

		//찾지 못하는 경우도 있어서 안전검사 추가.
		if (IsValid(PlayerCharacter) == false)
			return nullptr;

		UActionSystemComponent* ASC = PlayerCharacter->GetActionSystemComponent();
		if (!ASC) return nullptr;

		UStatSetPlayer* statSet = ASC->GetStatSet<UStatSetPlayer>();
		if (!statSet) return nullptr;

		return statSet;
	}

	return nullptr;
}

void UPlayerManager::UpdatePlayerManagerBroadcast()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			// 유효성 검사 추가
			if (!IsValid(this))
			{
				DEBUG_MESSAGE;
				return;
			}
			UpdatePlayerManagerDelegate.Broadcast();
		});
}
