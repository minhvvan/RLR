// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/CharacterStatus/Equipment/EquipmentUI.h"
#include "UI/InGame/CharacterStatus/Equipment/EquipmentSlot.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

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


	DetailStatButton->OnClicked.AddUniqueDynamic(this, &UEquipmentUI::ToggleShowDetailStatUI);
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

void UEquipmentUI::ToggleShowDetailStatUI()
{
	ESlateVisibility State = DetailStatSizeBox->GetVisibility();

	if (State == ESlateVisibility::Hidden)
	{
		/*
			TODO 
			패킷 연결 및 Player Data 관리하는 클래스 완성되면 그쪽이랑 연결하는 방향으로 수정해줄 것. 
		*/

		FStatus TestStats;
		TestStats.ATTACK = 999;
		RefreshStatUI(TestStats);
		DetailStatSizeBox->SetVisibility(ESlateVisibility::Visible);
	}
	else if (State == ESlateVisibility::Visible)
	{
		DetailStatSizeBox->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UEquipmentUI::RefreshStatUI(FStatus NewStatus)
{
	HPStatText->SetText(FText::FromString(FString::SanitizeFloat(NewStatus.MAX_HP)));
	MPStatText->SetText(FLOAT_TO_FTEXT(NewStatus.MAX_MP));
	StrengthStatText->SetText(FLOAT_TO_FTEXT(NewStatus.STRENGTH));
	AgilityStatText->SetText(FLOAT_TO_FTEXT(NewStatus.AGILITY));
	INTStatText->SetText(FLOAT_TO_FTEXT(NewStatus.INTELLIGENCE));
	DamageStatText->SetText(FLOAT_TO_FTEXT(NewStatus.ATTACK));
	DefenceStatText->SetText(FLOAT_TO_FTEXT(NewStatus.DEFENCE));
	AttackSpeedStatText->SetText(FLOAT_TO_FTEXT(NewStatus.ATTACK_SPEED));
	CoolTimeStatText->SetText(FLOAT_TO_FTEXT(NewStatus.COOLDOWN_REDUCTION));
	MoveSpeedStatText->SetText(FLOAT_TO_FTEXT(NewStatus.MOVE_SPEED));
	LifeStealStatText->SetText(FLOAT_TO_FTEXT(NewStatus.LIFE_STEAL));
	CriticalChanceStatText->SetText(FLOAT_TO_FTEXT(NewStatus.CRITICAL_CHANCE));
	CriticalDamageStatText->SetText(FLOAT_TO_FTEXT(NewStatus.CRITICAL_DAMAGE));
}
