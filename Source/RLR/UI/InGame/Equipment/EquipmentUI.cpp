// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Equipment/EquipmentUI.h"
#include "UI/InGame/Equipment/EquipmentSlot.h"

void UEquipmentUI::NativeConstruct()
{
	Super::NativeConstruct();

	EquipmentSlotList.Add(WeaponSlot);
	EquipmentSlotList.Add(SubWeaponSlot);
	EquipmentSlotList.Add(HelmetSlot);
	EquipmentSlotList.Add(UpperBodyArmorSlot);
	EquipmentSlotList.Add(LowerBodyArmorSlot);
	EquipmentSlotList.Add(ShoesSlot);
	EquipmentSlotList.Add(GlovesSlot);
	EquipmentSlotList.Add(NecklaceSlot);
	EquipmentSlotList.Add(EarringSlot_1);
	EquipmentSlotList.Add(EarringSlot_2);
	EquipmentSlotList.Add(RingSlot_1);
	EquipmentSlotList.Add(RingSlot_2);
	EquipmentSlotList.Add(BraceletSlot);

	WeaponSlot->SlotType = EEquipmentType::WEAPON;
	SubWeaponSlot->SlotType = EEquipmentType::SUBWEAPON;
	HelmetSlot->SlotType = EEquipmentType::HELMET;
	UpperBodyArmorSlot->SlotType = EEquipmentType::UPPERBODYARMOR;
	LowerBodyArmorSlot->SlotType = EEquipmentType::LOWERBODYARMOR;
	ShoesSlot->SlotType = EEquipmentType::SHOES;
	GlovesSlot->SlotType = EEquipmentType::GLOVES;
	NecklaceSlot->SlotType = EEquipmentType::NECKLACE;
	EarringSlot_1->SlotType = EEquipmentType::EARRING;
	EarringSlot_2->SlotType = EEquipmentType::EARRING;
	RingSlot_1->SlotType = EEquipmentType::RING;
	RingSlot_2->SlotType = EEquipmentType::RING;
	BraceletSlot->SlotType = EEquipmentType::BRACELET;

}

void UEquipmentUI::EquipItem(FItemData ItemData)
{

	//장비 아이템이 아니면 리턴한다.
	if(ItemData.TYPE != EItemType::EQUIPMENT)
		return;

	EEquipmentType EquipType = ItemData.EQUIPMENT_TYPE;

	//귀걸이나 반지 같이 2개씩 낄 수 있는 아이템을 구분해준다.

	if (EquipType == EEquipmentType::EARRING)
	{
		if (EarringSlot_1->IsEmpty())
		{
			EarringSlot_1->SetItemData(ItemData);
			return;
		}

		if (EarringSlot_2->IsEmpty())
		{
			EarringSlot_2->SetItemData(ItemData);
			return;
		}
		//둘다 비어 있지 않다면, 
		EarringSlot_1->SetItemData(ItemData);
		return;
	}

	if (EquipType == EEquipmentType::RING)
	{

		if (RingSlot_1->IsEmpty())
		{
			RingSlot_1->SetItemData(ItemData);
			return;
		}

		if (RingSlot_2->IsEmpty())
		{
			RingSlot_2->SetItemData(ItemData);
			return;
		}
		//둘다 비어 있지 않다면, 
		RingSlot_2->SetItemData(ItemData);
		return;
	}

	for (UEquipmentSlot* EquipSlot : EquipmentSlotList)
	{
		if (EquipSlot->SlotType == ItemData.EQUIPMENT_TYPE)
		{
			EquipSlot->SetItemData(ItemData);
		}
	}
}
