// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"


void UUtilBlueprintFunctionLibrary::DebugLog(FString string)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, *string);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *string);
	}
}