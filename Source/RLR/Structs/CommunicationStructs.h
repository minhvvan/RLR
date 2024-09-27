// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStructs.h"
#include "CommunicationStructs.generated.h"


USTRUCT(Atomic, BlueprintType)
struct FPost : public FTableRowBase
{
	GENERATED_BODY()

	FPost()
	{
		PostId = -1;
	}
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int PostId;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int SenderSeq;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int ReceiverSeq;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int itemId;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int TransactionCost;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString Title;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString ReceiverName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString SenderName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString Content;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FDateTime SendTime;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TMap<int, FItemArray> AttachedItems;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bIsSpecialPost;

	// ToString 함수 추가
	FString ToString() const
	{
        FString PostString;
        auto AppendInt = [&PostString](const FString& StatName, int32 StatValue)
            {
                if (!PostString.IsEmpty()) PostString.Append(TEXT("\n"));
                PostString.Append(FString::Printf(TEXT("%s = %d"), *StatName, StatValue));
            };
        auto AppendString = [&PostString](const FString& StatName, const FString& StatValue)
            {
                if (!PostString.IsEmpty()) PostString.Append(TEXT("\n"));
                PostString.Append(FString::Printf(TEXT("%s = %s"), *StatName, *StatValue));
            };
        auto AppendDateTime = [&PostString](const FString& StatName, const FDateTime& StatValue)
            {
                if (!PostString.IsEmpty()) PostString.Append(TEXT("\n"));
                PostString.Append(FString::Printf(TEXT("%s = %s"), *StatName, *StatValue.ToString()));
            };

        AppendInt(TEXT("PostId"), PostId);
        AppendInt(TEXT("SenderSeq"), SenderSeq);
        AppendInt(TEXT("ReceiverSeq"), ReceiverSeq);
        AppendInt(TEXT("ItemId"), itemId);
        AppendInt(TEXT("TransactionCost"), TransactionCost);
        AppendString(TEXT("Title"), Title);
        AppendString(TEXT("ReceiverName"), ReceiverName);
        AppendString(TEXT("SenderName"), SenderName);
        AppendString(TEXT("Content"), Content);
        AppendDateTime(TEXT("SendTime"), SendTime);

		return PostString;
	}
	// TODO : 완성하기
	//void MakePostData(const Protocol::Post post);
};