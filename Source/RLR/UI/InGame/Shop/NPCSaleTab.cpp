// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCSaleTab.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/Button.h"
#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/LiteralManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/PlayerManager.h"
#include "UI/InGame/Shop/NPCShopUI.h"
#include "UI/InGame/Shop/NPCShopBundleSell.h"
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
	UE_LOG(LogTemp, Log, TEXT("Sell Packet Request Start 1!!"));
	if (NetworkManager && UIManager)
	{
		auto shopUI = GetSubUI<UNPCShopUI>(RLRTAG.UI_NPCShop);
		UE_LOG(LogTemp, Log, TEXT("Sell Packet Request Start 2!!"));
		if (!shopUI) return;

		auto shopData = shopUI->GetShopData();
		UE_LOG(LogTemp, Log, TEXT("Sell Packet Request Start 3!!"));
		/*AsyncTask(ENamedThreads::GameThread, [this, shopData, NetworkManager]()
			{*/
				for (auto& [slotIndex, item] : Cart)
				{
					NetworkManager->SendSellPacket(item.ITEM_ID, shopData.ShopSeq, item.ITEM_QUANTITY);
				}
			//});

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
	FItemData newPriceItem = newItem;
	newPriceItem.SALE_PRICE /= 10;
	Cart.Add({InventorySlotIndex, newPriceItem});
	SellPrice += (newPriceItem.SALE_PRICE) * newPriceItem.ITEM_QUANTITY ;

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

		FItemData newPriceItem = item;
		newPriceItem.SALE_PRICE /= 10;

		removeIndex = i;
		SellPrice -= item.ITEM_QUANTITY * (newPriceItem.SALE_PRICE);
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

	auto itemSlotClass = dataManager->GetWidgetClass<UNPCShopItemSlot>(RLRLITERAL.WBP_NPCItemSlot);
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
	if (!IsValid(TxtSellPrice) || !IsValid(TxtSafe)) return;

	TxtSellPrice->SetText(FText::AsNumber(SellPrice));

	FPlayerGoods PlayerGood = GameInstance->GetPlayerManager()->GetPlayerGood();

	int safePrice = SellPrice + GameInstance->GetPlayerManager()->GetPlayerGood().TotalMoney;
	TxtSafe->SetText(FText::AsNumber(safePrice));
}

void UNPCSaleTab::OpenBundleSell(const FItemData& item, int32 InventorySlotIndex)
{
	auto dataManager = GameInstance->GetDataManager();
	if (!dataManager) return;

	auto bundleSellClass = dataManager->GetWidgetClass<UNPCShopBundleSell>(RLRLITERAL.WBP_NPCBundleSell);
	if (!bundleSellClass) return;

	auto bundleUI = CreateWidget<UNPCShopBundleSell>(GetWorld(), bundleSellClass);
	bundleUI->SetSlotIndex(InventorySlotIndex);
	bundleUI->SetItemData(item);
	bundleUI->OnConfirmSell.AddUniqueDynamic(this, &UNPCSaleTab::AddToCart);

	auto shopUI = Cast<UNPCShopUI>(GetParent());
	if (!shopUI) return;

	auto slot = Cast<UCanvasPanelSlot>(shopUI->AddChild(bundleUI));
	FVector2D panelSize(shopUI->RootSizeBox->WidthOverride, shopUI->RootSizeBox->HeightOverride);
	slot->SetSize(panelSize);
}