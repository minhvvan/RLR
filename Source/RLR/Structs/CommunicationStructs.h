// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	FString Title;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString SenderName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString Content;

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

		AppendInt(TEXT("PostId"), PostId);
		AppendInt(TEXT("SenderSeq"), SenderSeq);
		AppendInt(TEXT("ReceiverSeq"), ReceiverSeq);
		AppendInt(TEXT("itemId"), itemId);
		AppendString(TEXT("Title"), Title);
		AppendString(TEXT("SenderName"), SenderName);
		AppendString(TEXT("Content"), Content);

		return PostString;
	}
};