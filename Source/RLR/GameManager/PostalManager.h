// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Structs/CommunicationStructs.h"
#include "Structs/ItemStructs.h"
#include "PostalManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdatePostalManager);


UCLASS()
class RLR_API UPostalManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    void Update();

    UFUNCTION(BlueprintCallable)
    void AddItem(const FItemData& NewItem);

    UFUNCTION(BlueprintCallable)
    void AddItemList(const TArray<FItemData>& NewItemList, const TArray<FItemResource>& NewItemResourceList);

    UFUNCTION(BlueprintCallable)
    void AddItemResourceList(const TArray<FItemResource>& NewItemResourceList);

    UFUNCTION(BlueprintCallable)
    FItemData GetItem(int32 ItemSeq);

    UFUNCTION(BlueprintCallable)
    void RemoveItem(int32 ItemSeq);

    UFUNCTION(BlueprintCallable)
    void ChangeItemSlot(int32 Item_Seq, int32 NewSlotIndex);

    UFUNCTION(BlueprintCallable)
    void GetItemList(UPARAM(ref) TArray<FItemData>& ItemArray);

    UFUNCTION(BlueprintCallable)
    void GetItemResourceList(UPARAM(ref) TArray<FItemResource>& ItemResourceArray);

    UFUNCTION(BlueprintCallable)
    const FItemResource GetItemResource(int32 ItemSeq) const;

    UFUNCTION(BlueprintCallable)
    bool TryGetItemResource(int32 ItemSeq, FItemResource& OutItemResource) const;

    void SetItemList(TArray<FItemData>& ItemArray);

    //UFUNCTION(BlueprintCallable)
    //bool SetPost(const FString& RecipientName, const FString& Content, const TArray<FItemData>& AttachedItems, int32 TransactionCost, bool bIsSpecialPost);

public:
    UPROPERTY(BlueprintAssignable, Category = "Postal")
    FUpdatePostalManager OnUpdatePostalDelegate;

    void OnUpdatePostalDelegateBroadcast();

public:
    //<DB Key , FItemData>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TMap<int32, FItemData> ItemData;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TMap<int32, FItemResource> ItemResourceData;

    /* 우편 목록 */
    TArray<FPost> PostList;

private:
    // 우편 아이템 키값을 위한 임시용. 나중에 서버에서 아이템 패킷을 쏴주면 필요없어질 예정.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    int32 PostalItemKey = 0;
};
