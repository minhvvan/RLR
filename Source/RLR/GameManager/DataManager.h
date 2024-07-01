// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager/RLRStruct.h"
#include "DataManager.generated.h"

/**
 * 
 */



UCLASS()
class RLR_API UDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:

	virtual void Initialize(FSubsystemCollectionBase& Collection);
	

	UFUNCTION(BlueprintCallable)
	FItemData GetItemData(int32 Id);

	//등급에 따른 배경색
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EItemRarity, TObjectPtr<UTexture2D>> RarityImage;


private:
	UPROPERTY()
	TObjectPtr<UDataTable> ItemDataTable;

};
