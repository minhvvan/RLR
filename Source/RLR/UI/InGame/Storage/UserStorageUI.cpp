// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Storage/UserStorageUI.h"
#include "GameManager/StorageManager.h"
#include "UI/InGame/Popup/ItemCountMessageBox.h"
#include "GameManager/UIManager.h"
#include "RLR.h"
#include "Components/WidgetSwitcher.h"

void UUserStorageUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!StorageManager) StorageManager = GetStorageManager();
	
	//창고 아이템 요청(info 초기화에서 뿌린다면 없어도 됨)
	StorageManager->RequestGetUserStorageItems();

	StorageManager->OnUserStorageAllItemUpdated.RemoveDynamic(this, &UStorageUI::SetStorageAllItems);
	StorageManager->OnUserStorageAllItemUpdated.AddUniqueDynamic(this, &UStorageUI::SetStorageAllItems);
		
	SetTitle(TEXT("유저 창고"));
}