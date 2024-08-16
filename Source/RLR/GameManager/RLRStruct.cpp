// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/RLRStruct.h"

#include "Network/Proto/Packet.pb.h"

const FItemData     FItemData::EmptyItemData;
const FSkillData    FSkillData::EmptySkillData;

void FTotalStatus::MakeStatus(Protocol::UserTotalStatus Status)
{
    HP = Status.userhp();
    HP_ABSORB = Status.userhpabsorb();
    MP = Status.usermp();
	MP_ABSORB = Status.usermpabsorb();

    STRENGTH = Status.userstrength();
    AGILITY = Status.useragility();
    INTELLIGENCE = Status.userintelligence();

    MAX_HP = Status.usermaxhp();
    MAX_MP = Status.usermaxmp();

    ATTACK = Status.userattack();
    DEFENCE = Status.userdefence();
    ATTACK_SPEED = Status.userattackspeed();
    MOVE_SPEED = Status.usermovespeed();
    CRITICAL_CHANCE = Status.usercriticalchance();
    CRITICAL_DAMAGE = Status.usercriticaldamage();
    AVOID = Status.useravoid();
    COOLDOWN_REDUCTION = Status.usercooldownreduction();
}


void FItemData::MakeItemData(const Protocol::Item itemData)
{
    ITEM_SEQ = itemData.itemseq();
   ITEM_ID = itemData.itemid();
    ITEM_SLOT_IDX = itemData.itemslotidx();
    UE_LOG(LogTemp, Log, TEXT("ITEM_SEQ : %d"), ITEM_SEQ);
    UE_LOG(LogTemp, Log, TEXT("ITEM_ID : %lld"), itemData.itemid());
    UE_LOG(LogTemp, Log, TEXT("ITEM_SLOT_IDX : %d"), ITEM_SLOT_IDX);

	NAME = UTF8_TO_TCHAR(itemData.name().c_str());

    FString ItemType = UTF8_TO_TCHAR(itemData.type().c_str());
	TYPE = StringToEItemType(ItemType);

    /*Rank는 int 형?*/
	RANK = (EItemRarity) itemData.rank();
    EQUIPMENT_LEVEL = itemData.equiplevel();
	SALE_PRICE = itemData.saleprice();
	USE_PERIOD = itemData.useperiod();
	TEXT = UTF8_TO_TCHAR(itemData.text().c_str());

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
        EQUIPMENT_TYPE = (EEquipmentType) equipData.equippart();
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
        ETC_TYPE =  (EETCType)etcItemData.etctype();
    }
}

Protocol::Item FItemData::MakeItemPacket()
{
    Protocol::Item itemData;

    itemData.set_itemseq(ITEM_SEQ);
    itemData.set_itemid(ITEM_ID);
    itemData.set_itemslotidx(ITEM_SLOT_IDX);
    itemData.set_name(TCHAR_TO_UTF8(*NAME));  // FString -> std::string

    // ItemType 변환 (EItemType -> string)
    FString ItemTypeStr = EItemTypeToString(TYPE);  
    itemData.set_type(TCHAR_TO_UTF8(*ItemTypeStr));

    itemData.set_rank(RANK.GetIntValue());
    itemData.set_equiplevel(EQUIPMENT_LEVEL);
    itemData.set_saleprice(SALE_PRICE);
    itemData.set_useperiod(USE_PERIOD);
    itemData.set_text(TCHAR_TO_UTF8(*TEXT));

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

void FMonsterStatus::MakeMonsterData(const Protocol::Monster monsterData)
{
    //(X=1250.000000,Y=1930.000000,Z=96.000000)
    MonsterSeq = monsterData.monsterseq();
    MonsterName = UTF8_TO_TCHAR(monsterData.monstername().c_str());
    MonsterLevel = monsterData.monsterlevel();
    MontserExp = monsterData.monsterexp();
    MonsterAttackRate = monsterData.monsterdamage();
    MonsterDefence = monsterData.monsterdefence();
    MonsterHp = monsterData.monsterhp();
    MonsterAttackRange = 10;  // Packet 추가 예정
    MonsterTransform = { monsterData.monstertransx(), monsterData.monstertransy(), monsterData.monstertransz() };
    MonsterId = monsterData.monsterid();
    MonsterMapId = monsterData.monstermapid();
}

void FUserCharacter::MakeUserCharacter(Protocol::UserCharacter Data)
{
    UserSeq = Data.userseq();
    PlayerSeq = Data.playerseq();
    Name = UTF8_TO_TCHAR(Data.name().c_str());
    Level = Data.level();
    NobilityRank = Data.nobilityrank();

    MainJob = (ECharacterMainJobType)Data.mainjob();
    SubJob = (ECharacterSubJobType)Data.subjob();

    Exp = Data.exp();
    AdventureRank = Data.adventurerrank();

    TotalStatus.MakeStatus(Data.totalstatus());
    SetStatus.MakeSetStatus(Data.setstatus());
    Talent.MakeTalent(Data.talent());

}

void FSetStatus::MakeSetStatus(Protocol::UserSetStatus Data)
{
    UserHP = Data.userhp();
    UserMP = Data.usermp();
    UserSTR = Data.userstr();
    UserAGI =Data.useragi();
    UserINT =Data.userint();
}

void FAttackResult::MakeAttackData()
{
}
void FSkillData::MakeSkillData(Protocol::SkillInfo skill) {
    
    SkillSeq = skill.skillseq();

    Name = UTF8_TO_TCHAR(skill.skillname().c_str());

    Level = skill.skilllevel();

    Cost = skill.cost();

    CoolTime = skill.cooltime();

    Cind = skill.skillkind();

    Damage = skill.skillactivestatus().skilldamage();

    Duration = skill.skillactivestatus().skillduration();

    //ActivityTime = skill.mutable_skillactivestatus()->

    SkillId = skill.skillid();


    SkillType = static_cast<ESkillType>(skill.skillactivestatus().skilltype());
}

FString FSkillData::ToString() const
{
    {
        FString SkillString;

        auto AppendFloat = [&SkillString](const FString& Name, float Value)
            {
                if (!SkillString.IsEmpty())
                    SkillString.Append(TEXT("\n"));

                SkillString.Append(FString::Printf(TEXT("%s = %.2f"), *Name, Value));
            };

        auto AppendInt = [&SkillString](const FString& Name, int32 Value)
            {
                if (!SkillString.IsEmpty())
                    SkillString.Append(TEXT("\n"));

                SkillString.Append(FString::Printf(TEXT("%s = %d"), *Name, Value));
            };

        auto AppendString = [&SkillString](const FString& Name, FString Value)
            {
                if (!SkillString.IsEmpty())
                    SkillString.Append(TEXT("\n"));

                SkillString.Append(FString::Printf(TEXT("%s = %s"), *Name, *Value));
            };

        /*
            지금은 스킬 디테일 정보를 띠워주는데 사용 중.
            나중에 UI에서 보여줄 정보에 따라 코드를 수정할 예정
        */

        AppendString(TEXT("Name"), Name);
        AppendString(TEXT("Job"), ECharacterMainJobTypeToString(MainJobType));
        AppendInt(TEXT("Level"), Level);
        AppendInt(TEXT("Cost"), Cost);
        AppendFloat(TEXT("CoolTime"), CoolTime);


        return SkillString;
    }
}


/*
Enum 변환 관련된 건, 찾아보기 좋게 맨 아래에 배치.
*/

// 문자열을 EItemRarity으로 변환하는 함수
EItemRarity StringToEItemRarity(const FString& RarityString)
{
    if (RarityString.Equals(TEXT("COMMON"), ESearchCase::IgnoreCase))
    {
        return EItemRarity::COMMON;
    }
    else if (RarityString.Equals(TEXT("UNCOMMON"), ESearchCase::IgnoreCase))
    {
        return EItemRarity::UNCOMMON;
    }
    else if (RarityString.Equals(TEXT("RARE"), ESearchCase::IgnoreCase))
    {
        return EItemRarity::RARE;
    }
    else if (RarityString.Equals(TEXT("UNIQUE"), ESearchCase::IgnoreCase))
    {
        return EItemRarity::UNIQUE;
    }
    else if (RarityString.Equals(TEXT("EPIC"), ESearchCase::IgnoreCase))
    {
        return EItemRarity::EPIC;
    }
    else if (RarityString.Equals(TEXT("LEGEND"), ESearchCase::IgnoreCase))
    {
        return EItemRarity::LEGEND;
    }
    else if (RarityString.Equals(TEXT("NONE"), ESearchCase::IgnoreCase))
    {
        return EItemRarity::NONE;
    }
    else
    {
        // 잘못된 문자열 입력 처리, 예: 디폴트 값 반환 또는 에러 처리
        return EItemRarity::NONE; // 기본값을 NONE으로 설정
    }
}


EItemType StringToEItemType(const FString& ItemTypeString)
{
    if (ItemTypeString.Equals(TEXT("EQUIPMENT"), ESearchCase::IgnoreCase))
    {
        return EItemType::EQUIPMENT;
    }
    else if (ItemTypeString.Equals(TEXT("CONSUMPTION"), ESearchCase::IgnoreCase))
    {
        return EItemType::CONSUMPTION;
    }
    else if (ItemTypeString.Equals(TEXT("ETC"), ESearchCase::IgnoreCase))
    {
        return EItemType::ETC;
    }
    else if (ItemTypeString.Equals(TEXT("NONE"), ESearchCase::IgnoreCase))
    {
        return EItemType::NONE;
    }
    else
    {
        return EItemType::NONE; // 기본값
    }
}


ECharacterMainJobType StringToECharacterMainJobType(const FString& MainJobTypeString)
{
    if (MainJobTypeString.Equals(TEXT("SWORDSMAN"), ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::SWORDSMAN;
    }
    else if (MainJobTypeString.Equals(TEXT("THIEF"), ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::THEIF;
    }
    else if (MainJobTypeString.Equals(TEXT("MAGE"), ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::MAGE;
    }
    else if (MainJobTypeString.Equals(TEXT("ARCHER"), ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::ARCHER;
    }
    else if (MainJobTypeString.Equals(TEXT("PRIEST"), ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::PRIEST;
    }
    else if (MainJobTypeString.Equals(TEXT("NONE"), ESearchCase::IgnoreCase))
    {
        return ECharacterMainJobType::NONE;
    }
    else
    {
        return ECharacterMainJobType::NONE; // 기본값
    }
}

ECharacterSubJobType StringToECharacterSubJobType(const FString& SubJobTypeString)
{
    if (SubJobTypeString.Equals(TEXT("NONE"), ESearchCase::IgnoreCase))
    {
        return ECharacterSubJobType::NONE;
    }
    else
    {
        return ECharacterSubJobType::NONE; // 기본값
    }
}

EEquipmentType StringToEEquipmentType(const FString& EquipmentTypeString)
{
    if (EquipmentTypeString.Equals(TEXT("WEAPON"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::WEAPON;
    }
    else if (EquipmentTypeString.Equals(TEXT("SUBWEAPON"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::SUBWEAPON;
    }
    else if (EquipmentTypeString.Equals(TEXT("HELMET"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::HELMET;
    }
    else if (EquipmentTypeString.Equals(TEXT("UPPERBODYARMOR"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::UPPERBODYARMOR;
    }
    else if (EquipmentTypeString.Equals(TEXT("LOWERBODYARMOR"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::LOWERBODYARMOR;
    }
    else if (EquipmentTypeString.Equals(TEXT("SHOES"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::SHOES;
    }
    else if (EquipmentTypeString.Equals(TEXT("GLOVES"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::GLOVES;
    }
    else if (EquipmentTypeString.Equals(TEXT("NECKLACE"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::NECKLACE;
    }
    else if (EquipmentTypeString.Equals(TEXT("EARRING"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::EARRING;
    }
    else if (EquipmentTypeString.Equals(TEXT("RING"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::RING;
    }
    else if (EquipmentTypeString.Equals(TEXT("BRACELET"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::BRACELET;
    }
    else if (EquipmentTypeString.Equals(TEXT("NONE"), ESearchCase::IgnoreCase))
    {
        return EEquipmentType::NONE;
    }
    else
    {
        return EEquipmentType::NONE; // 기본값
    }
}



// EItemType을 문자열로 변환하는 함수
FString EItemTypeToString(EItemType ItemType)
{
    uint8 Index = static_cast<uint8>(ItemType);
    if (Index < UE_ARRAY_COUNT(EItemTypeStrings))
    {
        return EItemTypeStrings[Index];
    }
    return TEXT("UNKNOWN"); // 알 수 없는 값 처리
}

// ECharacterMainJobType을 문자열로 변환하는 함수
FString ECharacterMainJobTypeToString(ECharacterMainJobType MainJobType)
{
    uint8 Index = static_cast<uint8>(MainJobType);
    if (Index < UE_ARRAY_COUNT(ECharacterMainJobTypeStrings))
    {
        return ECharacterMainJobTypeStrings[Index];
    }
    return TEXT("UNKNOWN"); // 알 수 없는 값 처리
}

// ECharacterSubJobType을 문자열로 변환하는 함수
FString ECharacterSubJobTypeToString(ECharacterSubJobType SubJobType)
{
    uint8 Index = static_cast<uint8>(SubJobType);
    if (Index < UE_ARRAY_COUNT(ECharacterSubJobTypeStrings))
    {
        return ECharacterSubJobTypeStrings[Index];
    }
    return TEXT("UNKNOWN"); // 알 수 없는 값 처리
}

// EEquipmentType을 문자열로 변환하는 함수
FString EEquipmentTypeToString(EEquipmentType EquipmentType)
{
    uint8 Index = static_cast<uint8>(EquipmentType);
    if (Index < UE_ARRAY_COUNT(EEquipmentTypeStrings))
    {
        return EEquipmentTypeStrings[Index];
    }
    return TEXT("UNKNOWN"); // 알 수 없는 값 처리
}

// EItemRarity을 문자열로 변환하는 함수
FString EItemRarityToString(EItemRarity ItemRarity)
{
    uint8 Index = static_cast<uint8>(ItemRarity);
    if (Index < UE_ARRAY_COUNT(EItemRarityStrings))
    {
        return EItemRarityStrings[Index];
    }
    return TEXT("UNKNOWN"); // 알 수 없는 값 처리
}

// EStatusType을 문자열로 변환하는 함수
FString EStatusTypeToString(EStatusType StatusType)
{
    uint8 Index = static_cast<uint8>(StatusType);
    if (Index < UE_ARRAY_COUNT(EStatusTypeStrings))
    {
        return EStatusTypeStrings[Index];
    }
    return TEXT("UNKNOWN"); // 알 수 없는 값 처리
}

FString ESkillGroupToString(ESkillGroup SkillGroup)
{
    uint8 Index = static_cast<uint8>(SkillGroup);
    if (Index < UE_ARRAY_COUNT(ESkillGroups))
    {
        return ESkillGroups[Index];
    }
    return TEXT("UNKNOWN"); // 알 수 없는 값 처리
}

void FTalent::MakeTalent(Protocol::Talent Data)
{
    Talents.Add(TPair<int32,int32>(Data.firsttalent(), Data.firsttalent()));
    Talents.Add(TPair<int32,int32>(Data.secondtalent(), Data.secondlevel()));
    Talents.Add(TPair<int32,int32>(Data.thirdtalent(), Data.thirdlevel()));
}
void FQuest::MakeQuestData(const Protocol::Quest quest)
{
    //TODO: QuestData 생성
    QuestSeq = quest.questseq();
    NPCSeq = quest.npcseq();
    QuestTitle = UTF8_TO_TCHAR(quest.questtitle().c_str());
    QuestText = UTF8_TO_TCHAR(quest.questtext().c_str());
    QuestDescription = UTF8_TO_TCHAR(quest.questdescription().c_str());
    QuestKind = quest.questkind();
    IsProgress = false;
    IsClear = false;

   
    for (const auto& questReward : quest.rewardseqs()) {
        FString rewardKey = UTF8_TO_TCHAR(questReward.first.c_str());  // rewardSeqs의 key
        FObjectMap reward;
        for (const auto& rewardMap : questReward.second.values()) {
        
            // 맵에 추가
            reward.Add(rewardMap.first, rewardMap.second);
        }
        Rewards.Add(rewardKey, reward);
    }

    for (const auto& questNeed : quest.needseqs()) {
        FString needKey = UTF8_TO_TCHAR(questNeed.first.c_str());  // needSeqs의 key
        FObjectMap need;
        for (const auto& needMap : questNeed.second.values()) {

            // 맵에 추가
            need.Add(needMap.first, needMap.second);
        }
        Needs.Add(needKey, need);
    }
    FPlayerGoods pGoods;
    pGoods.MakePlayerGoods(quest.rewardplayergoods());
    PlayerGoods = pGoods;

    FUserGoods uGoods;  
    uGoods.MakeUserGoods(quest.rewardusergoods());
    UserGoods = uGoods;
}

void FNPCData::MakeNPCData(const Protocol::NPC npc)
{
    //TODO: NPCData 생성
    NPCSeq = npc.npcseq();
    NPCName = UTF8_TO_TCHAR(npc.npcname().c_str());
    NPCTalk = UTF8_TO_TCHAR(npc.npctalk().c_str());
    NPCType = npc.npctype();
    NPCConcept = UTF8_TO_TCHAR(npc.npcconcept().c_str());
    NPCTransform = FVector(npc.npctransform().x(), npc.npctransform().y(), npc.npctransform().z());
    MapId = npc.mapid();

    FQuest quest;
    for (auto&& npcQuest : npc.quests()) {
        quest.MakeQuestData(npcQuest);
        NPCQuests.Add(quest);
    }
    
}

int FInteractData::testID = 0;
void FInteractData::MakeObjectData()
{
    //TODO: ObjectData 생성
    InteractType = EInteractObjectType::LOGGING;
    ObjectTransform = FVector(1400.f, 1500.f + 500 * testID++, 96);
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
