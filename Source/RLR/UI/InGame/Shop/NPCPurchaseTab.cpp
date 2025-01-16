// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCPurchaseTab.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "UI/InGame/Shop/NPCShopItemSlot.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/LiteralManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "Structs/ItemStructs.h"
#include "Structs/ObjectStructs.h"
#include "UI/InGame/Shop/NPCCartSlot.h"
#include "UI/InGame/Shop/NPCShopBundlePurchase.h"
#include "UI/InGame/Shop/NPCShopUI.h"
#include "RLR.h"

void UNPCPurchaseTab::NativeConstruct()
{
	Super::NativeConstruct();

	BtnBuy->OnClicked.AddUniqueDynamic(this, &UNPCPurchaseTab::OnBuyClicked);
	BtnEmpty->OnClicked.AddUniqueDynamic(this, &UNPCPurchaseTab::OnEmptyClicked);

	BtnFirst->OnClicked.AddUniqueDynamic(this, &UNPCPurchaseTab::OnFirstClicked);
	BtnPrev->OnClicked.AddUniqueDynamic(this, &UNPCPurchaseTab::OnPrevClicked);
	BtnNext->OnClicked.AddUniqueDynamic(this, &UNPCPurchaseTab::OnNextClicked);
	BtnLast->OnClicked.AddUniqueDynamic(this, &UNPCPurchaseTab::OnLastClicked);

	CurrentPage = 1;
	LastPage = Items.Num() / ItemNumPerPage + (Items.Num() % ItemNumPerPage ? 1 : 0);
	UpdatePage();
	UpdateLastPageText();
}

void UNPCPurchaseTab::SetItemList(const TArray<FItemData>* ItemData)
{
	Items = *ItemData;
	UpdatePage();
	UpdateCart();

	LastPage = Items.Num() / ItemNumPerPage + (Items.Num() % ItemNumPerPage ? 1 : 0);
	UpdateLastPageText();
}

void UNPCPurchaseTab::AddToCart(const FItemData& item)
{
	if (Cart.Num() == MaxCartNum) return;

	for (int i = 0 ; i < Cart.Num(); i++)
	{
		if (Cart[i].ITEM_SEQ == item.ITEM_SEQ)
		{
			Cart[i].ITEM_MAX_COUNT += item.ITEM_MAX_COUNT;

			auto entry = GetCartSlotWidget(i);
			if (!entry) return;

			entry->SetItemData(Cart[i]);

			PurchasePrice += item.SALE_PRICE * item.ITEM_QUANTITY;
			UpdatePrice();
			return;
		}
	}

	auto entry = GetCartSlotWidget(Cart.Num());
	if (!entry) return;

	Cart.Add(item);
	PurchasePrice += item.SALE_PRICE * item.ITEM_MAX_COUNT;
	UpdatePrice();
	entry->SetItemData(item);
}

void UNPCPurchaseTab::RemoveFromCart(const FItemData& item)
{
	Cart.Remove(item);
	PurchasePrice -= item.SALE_PRICE * item.ITEM_MAX_COUNT;
	UpdatePrice();
	UpdateCart();
}

void UNPCPurchaseTab::OnBuyClicked()
{
	auto NetworkManager = GetNetworkManager();
	if (NetworkManager)
	{
		auto shopUI = Cast<UNPCShopUI>(GetParent());
		if (!shopUI) return;

		/* shopData 가 null */
		auto shopData = shopUI->GetShopData();
		for (auto& item : Cart)
		{
			NetworkManager->SendBuyPacket(item.ITEM_SEQ, shopData.ShopSeq, item.ITEM_MAX_COUNT);
		}
	}

	//Cart 비우기
	OnEmptyClicked();
}

void UNPCPurchaseTab::OnEmptyClicked()
{
	for (int i = 0; i < Cart.Num(); i++)
	{
		auto entry = GetCartSlotWidget(i);
		if (!entry) return;

		entry->SetItemData(FItemData::EmptyItemData);
	}

	Cart.Empty();
	PurchasePrice = 0;
	UpdatePrice();
}

void UNPCPurchaseTab::OnFirstClicked()
{
	if (CurrentPage == 1) return;
	CurrentPage = 1;
	UpdatePage();
}

void UNPCPurchaseTab::OnPrevClicked()
{
	if (CurrentPage == 1) return;
	CurrentPage--;
	UpdatePage();
}

void UNPCPurchaseTab::OnNextClicked()
{
	if (CurrentPage == LastPage) return;
	CurrentPage++;
	UpdatePage();
}

void UNPCPurchaseTab::OnLastClicked()
{
	if (CurrentPage == LastPage) return;
	CurrentPage = LastPage;
	UpdatePage();
}

void UNPCPurchaseTab::UpdatePage()
{
	auto dataManager = GameInstance->GetDataManager();
	if (!dataManager) return;

	auto itemSlotClass = dataManager->GetWidgetClass<UNPCShopItemSlot>(RLRLITERAL.WBP_NPCItemSlot);
	if (!itemSlotClass) return;

	int idx = (CurrentPage - 1) * ItemNumPerPage;
	TVItem->ClearListItems();
	for (int i = idx; i < idx + ItemNumPerPage; i++)
	{
		if (!Items.IsValidIndex(i)) break;
		auto itemWidget = Cast<UNPCShopItemSlot>(CreateWidget<UNPCShopItemSlot>(GetWorld(), itemSlotClass));
		itemWidget->SetParent(this);
		itemWidget->SetItemData(Items[i]);
		TVItem->AddItem(itemWidget);
	}

	UpdateCurrentPageText();
}

void UNPCPurchaseTab::UpdateCurrentPageText()
{
	TxtCurrentPage->SetText(FText::AsNumber(CurrentPage));
}

void UNPCPurchaseTab::UpdateLastPageText()
{
	TxtLastPage->SetText(FText::AsNumber(LastPage));
}

void UNPCPurchaseTab::UpdatePrice()
{
	TxtPurchasePrice->SetText(FText::AsNumber(PurchasePrice));
	int safePrice =  GameInstance->GetPlayerManager()->GetPlayerGood().TotalMoney- PurchasePrice;
	TxtSafe->SetText(FText::AsNumber(safePrice));
}

void UNPCPurchaseTab::UpdateCart()
{
	auto dataManager = GameInstance->GetDataManager();
	if (!dataManager) return;

	auto cartSlotClass = dataManager->GetWidgetClass<UNPCCartSlot>(RLRLITERAL.WBP_NPCCartSlot);
	if (!cartSlotClass) return;

	TVCart->ClearListItems();
	for (int i = 0; i < MaxCartNum; i++)
	{
		auto newItem = CreateWidget<UNPCCartSlot>(GetWorld(), cartSlotClass);
		if (Cart.IsValidIndex(i))
		{
			newItem->SetItemData(Cart[i]);
		}
		else
		{
			newItem->SetItemData(FItemData::EmptyItemData);
		}
		newItem->OnCartClicked.AddDynamic(this, &UNPCPurchaseTab::RemoveFromCart);
		TVCart->AddItem(newItem);
	}
}

UNPCCartSlot* UNPCPurchaseTab::GetCartSlotWidget(int idx)
{
	auto listItem = TVCart->GetItemAt(idx);
	if (!listItem) return nullptr;

	auto entry = Cast<UNPCCartSlot>(TVCart->GetEntryWidgetFromItem(listItem));
	return entry;
}

void UNPCPurchaseTab::OpenBundlePurchase(const FItemData& item)
{
	auto dataManager = GameInstance->GetDataManager();
	if (!dataManager) return;

	auto bundlePurchaseClass = dataManager->GetWidgetClass<UNPCShopBundlePurchase>(RLRLITERAL.WBP_NPCBundlePurchase);
	if (!bundlePurchaseClass) return;

	auto bundleUI = CreateWidget<UNPCShopBundlePurchase>(GetWorld(), bundlePurchaseClass);
	bundleUI->SetItemData(item);
	bundleUI->OnConfirmPurchase.AddDynamic(this, &UNPCPurchaseTab::AddToCart);

	auto shopUI = Cast<UNPCShopUI>(GetParent()->GetOuter()->GetOuter());
	if (!shopUI) return;

	auto slot = Cast<UCanvasPanelSlot>(shopUI->AddChild(bundleUI));
	FVector2D panelSize(shopUI->RootSizeBox->WidthOverride, shopUI->RootSizeBox->HeightOverride);
	slot->SetSize(panelSize);
}