// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCSaleTab.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/LiteralManager.h"
#include "GameManager/UIManager.h"
#include "UI/InGame/Shop/NPCShopUI.h"
#include "UI/InGame/Shop/NPCShopItemSlot.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "Structs/ItemStructs.h"
#include "Structs/ObjectStructs.h"


void UNPCSaleTab::NativeConstruct()
{
	Super::NativeConstruct();

	UpdatePage();
	BtnSell->OnClicked.AddUniqueDynamic(this, &UNPCSaleTab::OnSellClicked);
	BtnEmpty->OnClicked.AddUniqueDynamic(this, &UNPCSaleTab::OnEmptyClicked);
}

void UNPCSaleTab::OnSellClicked()
{
	auto NetworkManager = GetNetworkManager();
	auto UIManager = GetUIManager();
	if (NetworkManager && UIManager)
	{
		auto shopUI = Cast<UNPCShopUI>(GetParent()->GetOuter()->GetOuter());
		if (!shopUI) return;

		auto shopData = shopUI->GetShopData();
		AsyncTask(ENamedThreads::GameThread, [this, shopData, NetworkManager]()
			{
				for (auto& item : Cart)
				{
					NetworkManager->SendSellPacket(item.ITEM_ID, shopData.ShopSeq, item.ITEM_QUANTITY);
				}
			});

		OnEmptyClicked();
	}
}

void UNPCSaleTab::OnEmptyClicked()
{
	UInventoryUI* Inventory = GetUIManager()->GetSubUI<UInventoryUI>(RLRTAG.UI_Inventory);
	if (!Inventory)
	{
		RLR_LOG(LogRLR, Log, TEXT("InventoryUI Is Null"));
		return;
	}

	for (auto item : Cart)
	{
		Inventory->CancelSelectSlot(item);
	}

	Cart.Empty();
	SellPrice = 0;
	UpdatePrice();
	UpdatePage();
}

void UNPCSaleTab::AddToCart(const FItemData& item)
{
	if (Cart.Num() == MaxCartNum) return;

	for (int i = 0; i < Cart.Num(); i++)
	{
		//TODO: ITEM_ID vs ITEM_SEQ 어떤걸로 비교????
		if (Cart[i].ITEM_ID == item.ITEM_ID)
		{
			Cart[i].ITEM_QUANTITY += item.ITEM_QUANTITY;

			auto entry = GetItemSlotWidget(i);
			if (!entry) return;

			entry->SetItemData(Cart[i]);
			entry->SetItemAmountShow(true);
			SellPrice += item.SALE_PRICE * item.ITEM_QUANTITY;
			UpdatePage();
			UpdatePrice();
			return;
		}
	}

	auto entry = GetItemSlotWidget(Cart.Num());
	if (!entry) return;

	Cart.Add(item);
	SellPrice += item.SALE_PRICE * item.ITEM_QUANTITY;
	UpdatePage();
	UpdatePrice();
	entry->SetItemData(item);
	entry->SetItemAmountShow(true);
}

void UNPCSaleTab::RemoveFromCart(const FItemData& item)
{
	Cart.Remove(item);
	SellPrice -= item.ITEM_QUANTITY * item.SALE_PRICE;
	UpdatePrice();
}

void UNPCSaleTab::UpdatePage()
{
	auto dataManager = GameInstance->GetDataManager();
	if (!dataManager) return;

	auto itemSlotClass = dataManager->GetWidgetClass<UNPCShopItemSlot>(RLRLITERAL.WBP_NPCItemSlot);
	if (!itemSlotClass) return;

	TVItem->ClearListItems();
	for (int i = 0; i < Cart.Num(); i++)
	{
		auto itemWidget = Cast<UNPCShopItemSlot>(CreateWidget<UNPCShopItemSlot>(GetWorld(), itemSlotClass));
		itemWidget->SetItemData(Cart[i]);
		itemWidget->SetParent(this);
		TVItem->AddItem(itemWidget);
	}

	for (int i = 0; i < MaxCartNum - Cart.Num(); i++)
	{
		auto itemWidget = Cast<UNPCShopItemSlot>(CreateWidget<UNPCShopItemSlot>(GetWorld(), itemSlotClass));
		itemWidget->SetItemData(FItemData::EmptyItemData);
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