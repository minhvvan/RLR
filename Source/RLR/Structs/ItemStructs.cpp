// Fill out your copyright notice in the Description page of Project Settings.


#include "Structs/ItemStructs.h"
#include "Network/Proto/Packet.pb.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/RLRStruct.h"

const FItemData     FItemData::EmptyItemData;
const FItemResource FItemResource::EmptyItemResource;

void FItemData::MakeItemData(const Protocol::Item itemData)
{
    ITEM_SEQ = itemData.itemseq();
    ITEM_ID = itemData.itemid();
    ITEM_SLOT_IDX = itemData.itemslotidx();
    UE_LOG(LogTemp, Log, TEXT("ITEM_SEQ : %d"), ITEM_SEQ);
    UE_LOG(LogTemp, Log, TEXT("ITEM_ID : %lld"), ITEM_ID);
    UE_LOG(LogTemp, Log, TEXT("ITEM_SLOT_IDX : %d"), ITEM_SLOT_IDX);

    NAME = STRING_TO_FTEXT(itemData.name().c_str());

    FString ItemType = UTF8_TO_TCHAR(itemData.type().c_str());
    TYPE = StringToEItemType(ItemType);

    /*Rank는 int 형?*/
    RANK = (EItemRarity)itemData.rank();
    EQUIPMENT_LEVEL = itemData.equiplevel();
    SALE_PRICE = itemData.saleprice();
    USE_PERIOD = itemData.useperiod();
    TEXT = STRING_TO_FTEXT(itemData.text().c_str());

    ITEM_VALUE = itemData.itemvalue();
    ITEM_MAX = itemData.itemmax();

    if (itemData.has_equip()) {
        auto equipData = itemData.equip();

        ITEM_STATUS.HP = equipData.hp();
        ITEM_STATUS.HP_ABSORB = equipData.hpabsorb();
        ITEM_STATUS.MP = equipData.mp();
        ITEM_STATUS.MP_ABSORB = equipData.mpabsorb();
        ITEM_STATUS.STRENGTH = equipData.strength();
        ITEM_STATUS.AGILITY = equipData.agility();
        ITEM_STATUS.INTELLIGENCE = equipData.intelligence();
        ITEM_STATUS.ATTACK = equipData.attack();
        UE_LOG(LogTemp, Log, TEXT("itemData 공격력 : %f"), equipData.attack());
        ITEM_STATUS.DEFENCE = equipData.defence();
        ITEM_STATUS.ATTACK_SPEED = equipData.attackspeed();
        ITEM_STATUS.MOVE_SPEED = equipData.movespeed();
        ITEM_STATUS.CRITICAL_CHANCE = equipData.criticalchance();
        ITEM_STATUS.CRITICAL_DAMAGE = equipData.criticaldamage();
        ITEM_STATUS.AVOID = equipData.avoid();
        ITEM_STATUS.COOLDOWN_REDUCTION = equipData.cooldownreduction();
        EQUIPMENT_TYPE = (EEquipmentType)equipData.equippart();
    }

    if (itemData.has_consumption()) {
        auto consumptionData = itemData.consumption();
        COOLDOWN = consumptionData.cooldown();
        CONSUMPTION_VALUE = consumptionData.value();
        CONSUMPTION_DURATION = consumptionData.duration();
        CONSUMPTION_STATUS_TYPE = (EStatusType)consumptionData.statustype();
        CONSUMPTION_TYPE = (EConsumptionType)consumptionData.contype();
    }

    if (itemData.has_etcitem()) {
        auto etcItemData = itemData.etcitem();
        ETC_TYPE = (EETCType)etcItemData.etctype();
    }
}

void FItemData::MakeItemData(const Protocol::Equip EquipData)
{
    MakeItemData(EquipData.base());
}

Protocol::Item FItemData::MakeItemPacket()
{
    Protocol::Item itemData;

    itemData.set_itemseq(ITEM_SEQ);
    itemData.set_itemid(ITEM_ID);
    itemData.set_itemslotidx(ITEM_SLOT_IDX);
    itemData.set_name(TCHAR_TO_UTF8(*NAME.ToString()));  // FString -> std::string

    // ItemType 변환 (EItemType -> string)
    FString ItemTypeStr = EItemTypeToString(TYPE);
    itemData.set_type(TCHAR_TO_UTF8(*ItemTypeStr));

    itemData.set_rank(RANK.GetIntValue());
    itemData.set_equiplevel(EQUIPMENT_LEVEL);
    itemData.set_saleprice(SALE_PRICE);
    itemData.set_useperiod(USE_PERIOD);
    itemData.set_text(TCHAR_TO_UTF8(*TEXT.ToString()));

    itemData.set_itemvalue(ITEM_VALUE);
    itemData.set_itemmax(ITEM_MAX);

    if (EQUIPMENT_TYPE != EEquipmentType::NONE) {
        auto* equipData = itemData.mutable_equip();

        equipData->set_hp(ITEM_STATUS.HP);
        equipData->set_hpabsorb(ITEM_STATUS.HP_ABSORB);
        equipData->set_mp(ITEM_STATUS.MP);
        equipData->set_mpabsorb(ITEM_STATUS.MP_ABSORB);
        equipData->set_strength(ITEM_STATUS.STRENGTH);
        equipData->set_agility(ITEM_STATUS.AGILITY);
        equipData->set_intelligence(ITEM_STATUS.INTELLIGENCE);
        equipData->set_attack(ITEM_STATUS.ATTACK);
        equipData->set_defence(ITEM_STATUS.DEFENCE);
        equipData->set_attackspeed(ITEM_STATUS.ATTACK_SPEED);
        equipData->set_movespeed(ITEM_STATUS.MOVE_SPEED);
        equipData->set_criticalchance(ITEM_STATUS.CRITICAL_CHANCE);
        equipData->set_criticaldamage(ITEM_STATUS.CRITICAL_DAMAGE);
        equipData->set_avoid(ITEM_STATUS.AVOID);
        equipData->set_cooldownreduction(ITEM_STATUS.COOLDOWN_REDUCTION);
        equipData->set_equippart(EQUIPMENT_TYPE.GetIntValue());
    }

    if (CONSUMPTION_TYPE != EConsumptionType::NONE) {  // 소비 아이템 데이터가 있는지 확인하는 변수
        auto* consumptionData = itemData.mutable_consumption();

        consumptionData->set_cooldown(COOLDOWN);
        consumptionData->set_value(CONSUMPTION_VALUE);
        consumptionData->set_duration(CONSUMPTION_DURATION);
        consumptionData->set_statustype(CONSUMPTION_STATUS_TYPE.GetIntValue());
        consumptionData->set_contype(CONSUMPTION_TYPE.GetIntValue());
    }

    if (ETC_TYPE != EETCType::NONE) {  // 기타 아이템 데이터가 있는지 확인하는 변수
        auto* etcItemData = itemData.mutable_etcitem();

        etcItemData->set_etctype(ETC_TYPE.GetIntValue());
    }
    return itemData;
}

Protocol::Equip FItemData::MakeEquipPacket()
{
    Protocol::Equip EquipData;
    Protocol::Item* Equip_Item = EquipData.mutable_base();

    Equip_Item->set_itemseq(ITEM_SEQ);
    Equip_Item->set_itemid(ITEM_ID);
    Equip_Item->set_itemslotidx(ITEM_SLOT_IDX);
    Equip_Item->set_name(TCHAR_TO_UTF8(*NAME.ToString()));  // FString -> std::string

    // ItemType 변환 (EItemType -> string)
    FString ItemTypeStr = EItemTypeToString(TYPE);
    Equip_Item->set_type(TCHAR_TO_UTF8(*ItemTypeStr));

    Equip_Item->set_rank(RANK.GetIntValue());
    Equip_Item->set_equiplevel(EQUIPMENT_LEVEL);
    Equip_Item->set_saleprice(SALE_PRICE);
    Equip_Item->set_useperiod(USE_PERIOD);
    Equip_Item->set_text(TCHAR_TO_UTF8(*TEXT.ToString()));

    Equip_Item->set_itemvalue(ITEM_VALUE);
    Equip_Item->set_itemmax(ITEM_MAX);

    if (EQUIPMENT_TYPE != EEquipmentType::NONE) {
        EquipData.set_hp(ITEM_STATUS.HP);
        EquipData.set_hpabsorb(ITEM_STATUS.HP_ABSORB);
        EquipData.set_mp(ITEM_STATUS.MP);
        EquipData.set_mpabsorb(ITEM_STATUS.MP_ABSORB);
        EquipData.set_strength(ITEM_STATUS.STRENGTH);
        EquipData.set_agility(ITEM_STATUS.AGILITY);
        EquipData.set_intelligence(ITEM_STATUS.INTELLIGENCE);
        EquipData.set_attack(ITEM_STATUS.ATTACK);
        EquipData.set_defence(ITEM_STATUS.DEFENCE);
        EquipData.set_attackspeed(ITEM_STATUS.ATTACK_SPEED);
        EquipData.set_movespeed(ITEM_STATUS.MOVE_SPEED);
        EquipData.set_criticalchance(ITEM_STATUS.CRITICAL_CHANCE);
        EquipData.set_criticaldamage(ITEM_STATUS.CRITICAL_DAMAGE);
        EquipData.set_avoid(ITEM_STATUS.AVOID);
        EquipData.set_cooldownreduction(ITEM_STATUS.COOLDOWN_REDUCTION);
        EquipData.set_equippart(EQUIPMENT_TYPE.GetIntValue());
    }
    return EquipData;
}

void FPlayerGoods::MakePlayerGoods(const Protocol::PlayerGood playerGood)
{
    //TODO: PlayerGoods 생성
    TotalMoney = playerGood.totalmoney();
    Diamond = playerGood.diamond();
}

void FUserGoods::MakeUserGoods(const Protocol::UserGood userGood)
{
    //TODO: UserGoods 생성
    Reputation = userGood.reputation();
    Contribution = userGood.contribution();
}

void FItemResource::MakeItemResource(const Protocol::Item itemData)
{
    ITEM_SEQ = itemData.itemseq();
    const FItemResource& OriginData = GameInstance->GetDataManager()->GetItemResource(ITEM_SEQ);

    ItemImage = OriginData.ItemImage;
    Model = OriginData.Model;
}

void FItemResource::MakeShopItemResource(const FItemData itemData)
{
    ITEM_SEQ = itemData.ITEM_SEQ;
    const FItemResource& OriginData = GameInstance->GetDataManager()->GetItemResource(ITEM_SEQ);

    ItemImage = OriginData.ItemImage;
    Model = OriginData.Model;
}
