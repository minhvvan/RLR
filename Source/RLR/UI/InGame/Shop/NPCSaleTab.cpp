// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCSaleTab.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/UIManager.h"
#include "UI/InGame/Shop/NPCShopUI.h"
#include "Structs/ItemStructs.h"
#include "Structs/ObjectStructs.h"
#include "UI/InGame/Shop/NPCShopItemSlot.h"

void UNPCSaleTab::NativeConstruct()
{
	Super::NativeConstruct();

	UpdatePage();
	BtnSell->OnClicked.AddDynamic(this, &UNPCSaleTab::OnSellClicked);
	BtnEmpty->OnClicked.AddDynamic(this, &UNPCSaleTab::OnEmptyClicked);
}

void UNPCSaleTab::OnSellClicked()
{
	auto NetworkManager = GetNetworkManager();
	auto UIManager = GetUIManager();
	if (NetworkManager && UIManager)
	{
		auto shopUI = Cast<UNPCShopUI>(GetParent()->GetOuter()->GetOuter());
		if (!shopUI) return;

		auto shopData = shopUI->GetShopData().Pin();
		AsyncTask(ENamedThreads::GameThread, [this, shopData, NetworkManager]()
			{
				for (auto& item : Cart)
				{
					NetworkManager->SendSellPacket(item.ITEM_ID, shopData->ShopSeq, item.ITEM_VALUE);
				}
			});

		OnEmptyClicked();
	}
}

void UNPCSaleTab::OnEmptyClicked()
{
	Cart.Empty();
	CartResources.Empty();
	SellPrice = 0;
	UpdatePrice();
	UpdatePage();
}

void UNPCSaleTab::AddToCart(const FItemData& item, const FItemResource& itemResource)
{
	if (Cart.Num() == MaxCartNum) return;

	for (int i = 0; i < Cart.Num(); i++)
	{
		if (Cart[i].ITEM_ID == item.ITEM_ID)
		{
			Cart[i].ITEM_VALUE += item.ITEM_VALUE;

			auto entry = GetItemSlotWidget(i);
			if (!entry) return;

			entry->SetItemData(Cart[i]);
			entry->SetSlotItemResourceData(CartResources[i]);
			entry->SetItemAmountShow(true);
			SellPrice += item.SALE_PRICE * item.ITEM_VALUE;
			UpdatePage();
			UpdatePrice();
			return;
		}
	}

	auto entry = GetItemSlotWidget(Cart.Num());
	if (!entry) return;

	Cart.Add(item);
	CartResources.Add(itemResource);
	SellPrice += item.SALE_PRICE * item.ITEM_VALUE;
	UpdatePage();
	UpdatePrice();
	entry->SetItemData(item);
	entry->SetSlotItemResourceData(itemResource);
	entry->SetItemAmountShow(true);
}

void UNPCSaleTab::RemoveFromCart(const FItemData& item, const FItemResource& itemResource)
{
	Cart.Remove(item);
	CartResources.Remove(itemResource);
	SellPrice -= item.ITEM_VALUE * item.SALE_PRICE;
	UpdatePrice();
}

void UNPCSaleTab::UpdatePage()
{
	auto dataManager = GameInstance->GetDataManager();
	if (!dataManager) return;

	auto itemSlotClass = dataManager->GetWidgetClass<UNPCShopItemSlot>(TEXT("WBP_NPCItemSlot"));
	if (!itemSlotClass) return;

	TVItem->ClearListItems();
	for (int i = 0; i < Cart.Num(); i++)
	{
		auto itemWidget = Cast<UNPCShopItemSlot>(CreateWidget<UNPCShopItemSlot>(GetWorld(), itemSlotClass));
		itemWidget->SetItemData(Cart[i]);
		itemWidget->SetSlotItemResourceData(CartResources[i]);
		itemWidget->SetParent(this);
		TVItem->AddItem(itemWidget);
	}

	for (int i = 0; i < MaxCartNum - Cart.Num(); i++)
	{
		auto itemWidget = Cast<UNPCShopItemSlot>(CreateWidget<UNPCShopItemSlot>(GetWorld(), itemSlotClass));
		itemWidget->SetItemData(FItemData::EmptyItemData);
		itemWidget->SetSlotItemResourceData(FItemResource::EmptyItemResource);
		itemWidget->SetParent(this);
		TVItem->AddItem(itemWidget);
	}
}

UNPCShopItemSlot* UNPCSaleTab::GetItemSlotWidget(int idx)
{
	auto listItem = TVItem->GetItemAt(idx);
	if (!listItem) return nullptr;

	auto entry = Cast<UNPCShopItemSlot>(TVItem->GetEntryWidgetFromItem(listItem));
	return entry;
}

void UNPCSaleTab::UpdatePrice()
{
	TxtSellPrice->SetText(FText::AsNumber(SellPrice));
}