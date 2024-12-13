// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Storage/PlayerStorageUI.h"
#include "GameManager/StorageManager.h"
#include "GameManager/UIManager.h"

void UPlayerStorageUI::NativeConstruct()
{
	Super::NativeConstruct();

	//창고 아이템 요청(info 초기화에서 뿌린다면 없어도 됨)
	StorageManager->RequestGetPlayerStorageItems();
	
	StorageManager->OnPlayerStorageAllItemUpdated.RemoveDynamic(this, &UStorageUI::SetStorageAllItems);
	StorageManager->OnPlayerStorageAllItemUpdated.AddUniqueDynamic(this, &UStorageUI::SetStorageAllItems);
	SetTitle(TEXT("플레이어 창고"));
}