// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/RLRStruct.h"
#include "../Network/Packet.pb.h"
void FItemData::MakeItemData(const Protocol::Item itemData)
{
    
    ITEM_SEQ = itemData.itemseq();
   ITEM_ID = itemData.itemid();
    ITEM_SLOT_IDX = itemData.itemslotidx();
    
  /*  NAME = itemData.name();
    TYPE = itemData.type();
    RANK = itemData.rank();
    EQUIP_LEVEL = itemData.equiplevel();
    SALE_PRICE = itemData.saleprice();
    USE_PERIOD = itemData.useperiod();
    TEXT = itemData.text();
    ITEM_VALUE = itemData.itemvalue();
    ITEM_MAX = itemData.itemmax();*/
    
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
        //ITEM_STATUS.EQUIP_PART = equipData.equippart();
    }
    if (itemData.has_consumption()) {
        auto consumptionData = itemData.consumption();
        /* ITEM_CONSUMPTION.COOLDOWN = consumptionData.cooldown();
   ITEM_CONSUMPTION.VALUE = consumptionData.value();
   ITEM_CONSUMPTION.DURATION = consumptionData.duration();
   ITEM_CONSUMPTION.STATUS_TYPE = consumptionData.statustype();
   ITEM_CONSUMPTION.CON_TYPE = consumptionData.contype();*/
    }
    if (itemData.has_etcitem()) {
        auto etcItemData = itemData.etcitem();
        /*ITEM_ETC.ETC_TYPE = etcItemData.etctype();*/
    }

  

   
}
