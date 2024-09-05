// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCShopUI.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "UI/InGame/Shop/NPCPurchaseTab.h"
#include "Structs/ItemStructs.h"

void UNPCShopUI::NativeConstruct()
{
	Super::NativeConstruct();

	BtnPurchase->OnClicked.AddDynamic(this, &UNPCShopUI::OnPurchaseClicked);
	BtnSale->OnClicked.AddDynamic(this, &UNPCShopUI::OnSaleClicked);

	OnPurchaseClicked();
}

void UNPCShopUI::SetItemData(TMap<int, FItemData>& Items)
{
	ItemData = MakeShared<TMap<int, FItemData>>(Items);
	auto purchaseTab = Cast<UNPCPurchaseTab>(TabSwitcher->GetWidgetAtIndex(TabIndex::EPurchase));
	if (!purchaseTab) return;
	purchaseTab->SetItemList(ItemData.Get());
}

void UNPCShopUI::OnPurchaseClicked()
{
	TabSwitcher->SetActiveWidgetIndex(TabIndex::EPurchase);
}

void UNPCShopUI::OnSaleClicked()
{
	TabSwitcher->SetActiveWidgetIndex(TabIndex::ESale);
}
