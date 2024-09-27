// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/InputTransactionCost.h"
#include "Components/EditableText.h"

void UInputTransactionCost::OnTransactionCostChanged(const FText& NewText)
{
	/* 금화(골드) */
    FString NewTextString = NewText.ToString();

    // 숫자가 아닌 문자는 제거
    for (int32 i = 0; i < NewTextString.Len(); ++i)
    {
        if (!FChar::IsDigit(NewTextString[i]))
        {
            NewTextString.RemoveAt(i);
            --i;
        }
    }

    FText FilteredText = FText::FromString(NewTextString);

	/* 재화 차감 로직 작성 */
}