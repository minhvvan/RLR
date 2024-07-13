// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "GameManager/RLRStruct.h"
#include "Network/Proto/Packet.pb.h"


void UUtilBlueprintFunctionLibrary::DebugLog(FString string)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, *string);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *string);
	}
}

void UUtilBlueprintFunctionLibrary::MakeItemData()
{
	Protocol::Item TestItem;
	TestItem.set_rank(1);
	TestItem.set_type("CONSUMPTION");
	TestItem.set_rank(3);
	TestItem.set_text("테스트 텍스트입니다.");
	TestItem.mutable_equip()->set_equippart(4);

	FItemData TestItemData;
	TestItemData.MakeItemData(TestItem);
}
