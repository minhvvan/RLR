// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCShopUI.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include "UI/InGame/Shop/NPCPurchaseTab.h"
#include "UI/InGame/Shop/NPCSaleTab.h"
#include "UI/InGame/Inventory/InventoryUI.h"
#include "Structs/ItemStructs.h"
#include "Structs/ObjectStructs.h"
#include "GameManager/GameManager.h"
#include "GameManager/ObjectManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/UIManager.h"

void UNPCShopUI::NativeConstruct()
{
	Super::NativeConstruct();

	BtnPurchase->OnClicked.AddUniqueDynamic(this, &UNPCShopUI::OnPurchaseClicked);
	BtnSale->OnClicked.AddUniqueDynamic(this, &UNPCShopUI::OnSaleClicked);

	OnPurchaseClicked();
}

void UNPCShopUI::SetItemData(const TArray<FItemData>& Items)
{
	ItemData = MakeShared<TArray<FItemData>>(Items);

	auto purchaseTab = Cast<UNPCPurchaseTab>(TabSwitcher->GetWidgetAtIndex(TabIndex::EPurchase));
	if (!purchaseTab) return;
	purchaseTab->SetItemList(ItemData.Get());
}

void UNPCShopUI::SetShopData(const FNPCShop& Data)
{
	NPCShopData = Data;
}

FNPCShop& UNPCShopUI::GetShopData()
{
	return NPCShopData;
}

UPanelSlot* UNPCShopUI::AddChild(UUserWidget* Child)
{
	return Canvas->AddChild(Child);
}

void UNPCShopUI::AddSaleItem(const FItemData& Item)
{
	if (TabSwitcher->GetActiveWidgetIndex() != TabIndex::ESale) return;
	auto saleTab = Cast<UNPCSaleTab>(TabSwitcher->GetActiveWidget());
	if (!saleTab) return;

	UInventoryUI* Inventory = GetUIManager()->GetSubUI<UInventoryUI>(RLRTAG.UI_Inventory);
	if (!Inventory) return;

	Inventory->SelectSlot(Item);
	saleTab->AddToCart(Item);
}

void UNPCShopUI::OnPurchaseClicked()
{
	TabSwitcher->SetActiveWidgetIndex(TabIndex::EPurchase);
	GetInventoryManager()->OnInventorySlotClickedDelegate.Clear();
}

void UNPCShopUI::OnSaleClicked()
{
	TabSwitcher->SetActiveWidgetIndex(TabIndex::ESale);
	GetInventoryManager()->OnInventorySlotClickedDelegate.BindUFunction(this, FName("AddSaleItem"));
}