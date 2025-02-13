// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Structs/UtilStructs.h"
#include "Structs/ItemStructs.h"
#include "PostalManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdatePostalManager);

class UPostItemSlot;
class UPostOverlayUI;

UCLASS()
class RLR_API UPostalManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    void Update();

    virtual void SetRecvPostData(const TArray<FPostResult>& NewPostResult);
    virtual void SetSentPostData(const TArray<FPostResult>& NewPostResult);
    virtual void SetAlertPostData(const FPostResult& NewPostResult);
    void CreateAlertPost();

    const TArray<FPostResult>& GetSentPostData() const;
    const TArray<FPostResult>& GetReceivedPostData() const;
    const FPostResult& GetAlertPostData() const;
    FItemData GetItemDataById(int64 ItemId);
    //void SetItemData(int64 ItemId, const FItemData& ItemData);

    void AddToPostDeletionList(const FPostResult& PostData, bool IsSent);
    void ClearPostDeletionList(bool IsSent);
    TArray<FPostResult> GetAndClearPostDeletionList(bool IsSent);

	UFUNCTION()
	void OnPostItemSlotClicked(int32 InventorySlotIndex, int32 PostSlotIndex, const FItemData& itemData, ESlotType SlotType);
    UPostItemSlot* GetPostWriteTabItemSlot(int32 PostItemSlotIndex);


public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPostResult> SentPostDeletionList;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPostResult> RecvPostDeletionList;

    UPROPERTY(BlueprintAssignable, Category = "Postal")
    FUpdatePostalManager OnUpdatePostalDelegate;

    void OnUpdatePostalDelegateBroadcast();

    void SetItemData(int32 itemId);

public:
    //<DB Key , FItemData>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TMap<int32, FItemData> ItemData;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TMap<int64, int64> ItemValues;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TMap<int32, FItemResource> ItemResourceData;

    /* 우편 목록 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FPostResult> PostRecvData;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FPostResult> PostSentData;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FPostResult PostAlertData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FPostResult> SentPostList;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FPostResult> ReceivedPostList;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TObjectPtr<UPostItemSlot>> PostSlotList;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TObjectPtr<UPostOverlayUI> PostUIClass;

private:
    // 우편 아이템 키값을 위한 임시용. 나중에 서버에서 아이템 패킷을 쏴주면 필요없어질 예정.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    int32 PostalItemKey = 0;
};
