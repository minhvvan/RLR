// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Structs/UtilStructs.h"
#include "FriendManager.generated.h"

class UFriendListUI;

/**
 * Friend 패킷을 FriendUI와 연결해주는 매니저
 */
UCLASS()
class RLR_API UFriendManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    void InitializeFriendManager();
    virtual void SetFriendData(const TArray<FFriendGroupResult>& NewGroupData);

    const TArray<FFriendGroupResult>& GetFriendData() const;
    
    void SetRequestFriendData(int NewFriendSeq, FString NewFriendName);
    const TMap<int32, FString>& GetRequestFriendData() const;

    void AddToFriendDeletionList(const int32& NewFriendData);
    TArray<FFriendGroupResult> GetAndClearFriendDeletionList();

    void DeleteFromRequestList(int friendSeq);

    void SetFriendMemo(int32 FriendSeq, const FString& Memo);
    FString GetFriendMemo(int32 FriendSeq) const;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FFriendGroupResult> FriendDeletionList;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TObjectPtr<UFriendListUI> FriendListUI;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FFriendGroupResult> GroupData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<int32, FString> RequestFriendData;

private:
    TMap<int32, FString> FriendMemoMap;
};
