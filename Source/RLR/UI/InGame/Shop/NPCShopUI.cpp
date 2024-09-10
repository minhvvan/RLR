// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Shop/NPCShopUI.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "UI/InGame/Shop/NPCPurchaseTab.h"
#include "Structs/ItemStructs.h"
#include "Structs/ObjectStructs.h"

void UNPCShopUI::NativeConstruct()
{
	Super::NativeConstruct();

	BtnPurchase->OnClicked.AddDynamic(this, &UNPCShopUI::OnPurchaseClicked);
	BtnSale->OnClicked.AddDynamic(this, &UNPCShopUI::OnSaleClicked);

	OnPurchaseClicked();
}

void UNPCShopUI::SetItemData(TArray<FItemData>& Items)
{
	ItemData = MakeShared<TArray<FItemData>>(Items);
	auto purchaseTab = Cast<UNPCPurchaseTab>(TabSwitcher->GetWidgetAtIndex(TabIndex::EPurchase));
	if (!purchaseTab) return;
	purchaseTab->SetItemList(ItemData.Get());
}

void UNPCShopUI::SetShopData(FNPCShop& Data)
{
	NPCShopData = MakeShared<FNPCShop>(Data);
}

void UNPCShopUI::SetPosition(FVector2D pos)
{
	if (auto slot = Cast<UCanvasPanelSlot>(Slot))
	{
		slot->SetPosition(pos);
	}
}

TWeakPtr<FNPCShop> UNPCShopUI::GetShopData()
{
	return NPCShopData.ToWeakPtr();
}

UPanelSlot* UNPCShopUI::AddChild(UUserWidget* Child)
{
	return Canvas->AddChild(Child);
}

void UNPCShopUI::OnPurchaseClicked()
{
	TabSwitcher->SetActiveWidgetIndex(TabIndex::EPurchase);
}

void UNPCShopUI::OnSaleClicked()
{
	TabSwitcher->SetActiveWidgetIndex(TabIndex::ESale);
}
