// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCPurchaseTab.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/Overlay.h"
#include "UI/InGame/Shop/NPCShopItemSlot.h"
#include "GameManager/DataManager.h"
#include "GameManager/GameManager.h"
#include "Structs/ItemStructs.h"
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

void UNPCPurchaseTab::SetItemList(const TArray<FItemData>* ItemData)
{
	Items = *ItemData;
	UpdatePage();

	auto dataManager = GameInstance->GetDataManager();
	if (!dataManager) return;

	auto cartSlotClass = dataManager->GetWidgetClass<UNPCCartSlot>(TEXT("WBP_NPCCartSlot"));
	if (!cartSlotClass) return;

	for (int i = 0; i < 10; i++)
	{
		auto newItem = CreateWidget<UNPCCartSlot>(GetWorld(), cartSlotClass);
		TVCart->AddItem(newItem);
	}

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
			Cart[i].ITEM_VALUE += item.ITEM_VALUE;

			auto entry = GetCartSlotWidget(i);
			if (!entry) return;

			entry->SetItemData(Cart[i]);
			return;
		}
	}

	auto entry = GetCartSlotWidget(Cart.Num());
	if (!entry) return;

	Cart.Add(item);
	entry->SetItemData(item);
}

void UNPCPurchaseTab::OnBuyClicked()
{
	//TODO: Buy
}

void UNPCPurchaseTab::OnEmptyClicked()
{
	//TODO: 장바구니 비우기
	RLR_LOG(LogRLR, Log, TEXT("OnEmptyClicked"));
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
		itemWidget->SetItemData(Items[i]);
		itemWidget->SetParent(this);
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

	auto bundlePurchaseClass = dataManager->GetWidgetClass<UNPCShopBundlePurchase>(TEXT("WBP_NPCBundlePurchase"));
	if (!bundlePurchaseClass) return;

	auto bundleUI = CreateWidget<UNPCShopBundlePurchase>(GetWorld(), bundlePurchaseClass);
	bundleUI->SetItemData(item);

	auto shopUI = Cast<UNPCShopUI>(GetParent()->GetOuter()->GetOuter());
	if (!shopUI) return;

	FVector2D panelSize(shopUI->RootSizeBox->WidthOverride, shopUI->RootSizeBox->HeightOverride);
	auto slot = Cast<UCanvasPanelSlot>(shopUI->Canvas->AddChild(bundleUI));
	slot->SetSize(panelSize);
}