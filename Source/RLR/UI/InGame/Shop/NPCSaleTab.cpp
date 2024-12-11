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
				for (auto& [slotIndex, item] : Cart)
				{
					NetworkManager->SendSellPacket(item.ITEM_ID, shopData.ShopSeq, item.ITEM_VALUE);
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

	for (auto& [slotIndex, item] : Cart)
	{
		Inventory->CancelSelectSlot(slotIndex);
	}

	Cart.Empty();
	SellPrice = 0;
	UpdatePrice();
	UpdatePage();
}

void UNPCSaleTab::AddToCart(const FItemData& newItem, int32 InventorySlotIndex)
{
	UNPCShopItemSlot* entry = GetItemSlotWidget(Cart.Num());
	if (entry == nullptr)
	{
		RLR_LOG(LogRLR, Log, TEXT("entry is nullptr"));
		return;
	}
	
	Cart.Add({InventorySlotIndex, newItem});
	SellPrice += newItem.SALE_PRICE * newItem.QUANTITY;
	UpdatePage();
	UpdatePrice();
	entry->SetItemData(newItem);
	entry->SetItemAmountShow(true);

	UInventoryUI* Inventory = GetUIManager()->GetSubUI<UInventoryUI>(RLRTAG.UI_Inventory);
	if (!Inventory) return;

	Inventory->SelectSlot(InventorySlotIndex);
}

void UNPCSaleTab::RemoveFromCart(const FItemData& item)
{
	int removeIndex = -1;
	for (int i = 0; i < Cart.Num(); i++)
	{
		if (item != Cart[i].Value) continue;

		removeIndex = i;
		SellPrice -= item.ITEM_VALUE * item.SALE_PRICE;
		UpdatePrice();
		break;
	}

	if (removeIndex != -1)
	{
		UInventoryUI* Inventory = GetUIManager()->GetSubUI<UInventoryUI>(RLRTAG.UI_Inventory);
		if (!Inventory)
		{
			RLR_LOG(LogRLR, Log, TEXT("InventoryUI Is Null"));
			return;
		}

		Inventory->CancelSelectSlot(Cart[removeIndex].Key);
		Cart.RemoveAt(removeIndex);
	}
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
		itemWidget->SetItemData(Cart[i].Value);
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
	auto DisplayedWidget = TVItem->GetEntryWidgetFromItem(TVItem->GetItemAt(idx));
	return Cast<UNPCShopItemSlot>(DisplayedWidget);
}

void UNPCSaleTab::UpdatePrice()
{
	TxtSellPrice->SetText(FText::AsNumber(SellPrice));
}