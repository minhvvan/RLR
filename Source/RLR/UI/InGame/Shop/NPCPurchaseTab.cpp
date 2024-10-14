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
#include "GameManager/NetworkManager.h"
#include "Structs/ItemStructs.h"
#include "Structs/ObjectStructs.h"
#include "UI/InGame/Shop/NPCCartSlot.h"
#include "UI/InGame/Shop/NPCShopBundlePurchase.h"
#include "UI/InGame/Shop/NPCShopUI.h"
#include "RLR.h"

void UNPCPurchaseTab::NativeConstruct()
{
	Super::NativeConstruct();

	BtnBuy->OnClicked.AddDynamic(this, &UNPCPurchaseTab::OnBuyClicked);
	BtnEmpty->OnClicked.AddDynamic(this, &UNPCPurchaseTab::OnEmptyClicked);

	BtnFirst->OnClicked.AddDynamic(this, &UNPCPurchaseTab::OnFirstClicked);
	BtnPrev->OnClicked.AddDynamic(this, &UNPCPurchaseTab::OnPrevClicked);
	BtnNext->OnClicked.AddDynamic(this, &UNPCPurchaseTab::OnNextClicked);
	BtnLast->OnClicked.AddDynamic(this, &UNPCPurchaseTab::OnLastClicked);

	CurrentPage = 1;
	LastPage = Items.Num() / ItemNumPerPage + (Items.Num() % ItemNumPerPage ? 1 : 0);
	UpdatePage();
	UpdateLastPageText();
}

void UNPCPurchaseTab::SetItemList(const TArray<FItemData>* ItemData, const TArray<FItemResource>* ItemResourceData)
{
	Items = *ItemData;
	ItemResources = *ItemResourceData;
	UpdatePage();
	UpdateCart();

	LastPage = Items.Num() / ItemNumPerPage + (Items.Num() % ItemNumPerPage ? 1 : 0);
	UpdateLastPageText();
}

void UNPCPurchaseTab::AddToCart(const FItemData& item, const FItemResource& itemResource)
{
	if (Cart.Num() == MaxCartNum) return;

	for (int i = 0 ; i < Cart.Num(); i++)
	{
		if (Cart[i].ITEM_SEQ == item.ITEM_SEQ)
		{
			Cart[i].ITEM_VALUE += item.ITEM_VALUE;

			auto entry = GetCartSlotWidget(i);
			if (!entry) return;

			entry->SetItemData(Cart[i]);
			entry->SetSlotItemResourceData(CartResources[i]);

			PurchasePrice += item.SALE_PRICE * item.ITEM_VALUE;
			UpdatePrice();
			return;
		}
	}

	auto entry = GetCartSlotWidget(Cart.Num());
	if (!entry) return;

	Cart.Add(item);
	CartResources.Add(itemResource);
	PurchasePrice += item.SALE_PRICE * item.ITEM_VALUE;
	UpdatePrice();
	entry->SetItemData(item);
	entry->SetSlotItemResourceData(itemResource);
}

void UNPCPurchaseTab::RemoveFromCart(const FItemData& item, const FItemResource& itemResource)
{
	Cart.Remove(item);
	CartResources.Remove(itemResource);
	PurchasePrice -= item.SALE_PRICE * item.ITEM_VALUE;
	UpdatePrice();
	UpdateCart();
}

void UNPCPurchaseTab::OnBuyClicked()
{
	auto NetworkManager = GetNetworkManager();
	if (NetworkManager)
	{
		auto shopUI = Cast<UNPCShopUI>(GetParent()->GetOuter()->GetOuter());
		if (!shopUI) return;

		auto shopData = shopUI->GetShopData().Pin();
		AsyncTask(ENamedThreads::GameThread, [this, shopData, NetworkManager]()
		{
			for (auto& item : Cart)
			{
				NetworkManager->SendBuyPacket(item.ITEM_SEQ, shopData->ShopSeq, item.ITEM_VALUE);
			}
		});
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
		entry->SetSlotItemResourceData(FItemResource::EmptyItemResource);
	}

	Cart.Empty();
	CartResources.Empty();
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

	auto itemSlotClass = dataManager->GetWidgetClass<UNPCShopItemSlot>(TEXT("WBP_NPCItemSlot"));
	if (!itemSlotClass) return;

	int idx = (CurrentPage - 1) * ItemNumPerPage;
	TVItem->ClearListItems();
	for (int i = idx; i < idx + ItemNumPerPage; i++)
	{
		if (!Items.IsValidIndex(i)) break;
		auto itemWidget = Cast<UNPCShopItemSlot>(CreateWidget<UNPCShopItemSlot>(GetWorld(), itemSlotClass));
		itemWidget->SetParent(this);
		itemWidget->SetItemData(Items[i]);
		itemWidget->SetSlotItemResourceData(ItemResources[i]);
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
	//TODO: 잔액 update
}

void UNPCPurchaseTab::UpdateCart()
{
	auto dataManager = GameInstance->GetDataManager();
	if (!dataManager) return;

	auto cartSlotClass = dataManager->GetWidgetClass<UNPCCartSlot>(TEXT("WBP_NPCCartSlot"));
	if (!cartSlotClass) return;

	TVCart->ClearListItems();
	for (int i = 0; i < MaxCartNum; i++)
	{
		auto newItem = CreateWidget<UNPCCartSlot>(GetWorld(), cartSlotClass);
		if (Cart.IsValidIndex(i))
		{
			newItem->SetItemData(Cart[i]);
			newItem->SetSlotItemResourceData(CartResources[i]);
		}
		else
		{
			newItem->SetItemData(FItemData::EmptyItemData);
			newItem->SetSlotItemResourceData(FItemResource::EmptyItemResource);
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

void UNPCPurchaseTab::OpenBundlePurchase(const FItemData& item, const FItemResource& itemResource)
{
	auto dataManager = GameInstance->GetDataManager();
	if (!dataManager) return;

	auto bundlePurchaseClass = dataManager->GetWidgetClass<UNPCShopBundlePurchase>(TEXT("WBP_NPCBundlePurchase"));
	if (!bundlePurchaseClass) return;

	auto bundleUI = CreateWidget<UNPCShopBundlePurchase>(GetWorld(), bundlePurchaseClass);
	bundleUI->SetItemData(item, itemResource);
	bundleUI->OnConfirmPurchase.AddDynamic(this, &UNPCPurchaseTab::AddToCart);

	auto shopUI = Cast<UNPCShopUI>(GetParent()->GetOuter()->GetOuter());
	if (!shopUI) return;

	auto slot = Cast<UCanvasPanelSlot>(shopUI->AddChild(bundleUI));
	FVector2D panelSize(shopUI->RootSizeBox->WidthOverride, shopUI->RootSizeBox->HeightOverride);
	slot->SetSize(panelSize);
}