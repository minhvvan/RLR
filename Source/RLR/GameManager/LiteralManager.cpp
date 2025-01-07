// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/LiteralManager.h"

#include "Structs/SkillStructs.h"

LiteralManager LiteralManager::LiteralMessages;

LiteralManager::LiteralManager()
    :   DT_EffectData_Path(TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_EffectData.DT_EffectData'")),
        TransitionVolume_VolumeName(FName("TransitionVolume")),
        TransitionVolume_OverlapOnlyPawn(FName("OverlapOnlyPawn")),
        InteractableActor_InteractionComp(FName("InteractionComp")),
        InteractableActor_Mesh(FName("Mesh")),
        InteractableActor_InteractUI(FName("InteractUI")),
        Projectile_CollisionComponent(FName("CollisionComponent")),
        Projectile_Mesh(FName("Mesh")),
        Projectile_Movement(FName("ProjectileMovement")),
        RLRNonPlayerCharacter_Path(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Character/BP_NPC.BP_NPC_C'")),
        RLRInteractableActor_Path(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Actors/BP_Interactable_Tree.BP_Interactable_Tree_C'")),
        RLRPlayerCharacter_Path(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Player/BP/BP_Player.BP_Player_C'")),
        DT_AbnormalMark_Path(TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_AbnormalMark.DT_AbnormalMark'")),
        RLRReticle_Decal(FName("Decal"))
{
}

void LiteralManager::Init()
{
    /* Trade */
    LiteralMessages.TradeUI_Nickname = TEXT("Nickname");
    LiteralMessages.TradeUI_UserSeq = TEXT("UserSeq");
    LiteralMessages.TradeUI_From = TEXT("From");
    LiteralMessages.TradeUI_Gold = TEXT("골드");
    LiteralMessages.TradeUI_TradeRequest = TEXT("가 거래를 신청했습니다.");
    LiteralMessages.TradeUI_TradeSuccess = TEXT("거래를 성공했습니다.");
    LiteralMessages.TradeUI_TradeCanceled = TEXT("상대가 거래를 취소했습니다.");
    LiteralMessages.TradeUI_TradeDenied = TEXT("거래를 거절했습니다.");
    LiteralMessages.TradeUI_InputExceedsCurrentQuantity = TEXT("입력된 값이 현재 플레이어가 보유한 수량보다 많습니다");
    LiteralMessages.TradeUI_OnClickedInventorySlot = FName("OnClickedInventorySlot");
    LiteralMessages.TradeUI_OnClickedAcceptButton = FName("OnClickedAcceptButton");
    LiteralMessages.TradeUI_OnClickedCancelButton = FName("OnClickedCancelButton");
    LiteralMessages.TradeUI_OnConfirmItemCountMessageBox = FName("OnConfirmItemCountMessageBox");
    LiteralMessages.TradeUI_OnCancelItemCountMessageBox = FName("OnCancelItemCountMessageBox");
    
    /* Enhance */
    LiteralMessages.Enhance_EnhancePrompt = TEXT("강화를 진행하겠습니까?");
    LiteralMessages.Enhance_OnClickedAcceptButton = FName("OnClickedAcceptButton");
    LiteralMessages.Enhance_OnClickedCancelButton = FName("OnClickedCancelButton");

    /* PostOverlayUI */
    LiteralMessages.PostUI_ReceivedPost = TEXT("받은 우편함");
    LiteralMessages.PostUI_SentPost = TEXT("보낸 우편함");
    LiteralMessages.PostUI_RemovePrompt = TEXT("정말 삭제하시겠습니까? 다시 되돌릴 수 없습니다.");
    LiteralMessages.PostUI_ExitPrompt = TEXT("작성중인 우편이 있습니다. 창을 종료하면 작성 중이던 편지가 삭제됩니다.");
    LiteralMessages.PostUI_OnClickedDeletePostsConfirmButton = FName("OnClickedDeletePostsConfirmButton");
    LiteralMessages.PostUI_OnClickedAcceptButtonWhileWriting = FName("OnClickedAcceptButton");
    LiteralMessages.PostUI_OnClickedCancelButton = FName("OnClickedCancelButton");
	
	/* SKillUI */
	LiteralMessages.SkillUI_Learn = TEXT("스킬 배우기");
	LiteralMessages.SkillUI_Upgrade = TEXT("스킬 업그레이드");
	LiteralMessages.SkillType_Normal = TEXT("일반");
	LiteralMessages.SkillType_Area = TEXT("지역");
	LiteralMessages.SkillType_Holding = TEXT("홀딩");
	LiteralMessages.SkillType_Casting = TEXT("캐스팅");
	LiteralMessages.SkillType_Mobility = TEXT("이동");
	LiteralMessages.SkillType_Targeting = TEXT("타게팅");
	LiteralMessages.SkillType_Chain = TEXT("연계");
	LiteralMessages.CostType_MP = TEXT("MP");
	LiteralMessages.CostType_HP = TEXT("HP");

    /* DataManager */
    LiteralMessages.DT_ItemData_Path = TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ItemData.DT_ItemData'");
    LiteralMessages.DT_ItemResource_Path = TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ItemResource.DT_ItemResource'");
    LiteralMessages.DT_MonsterDataTable_Path = TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_MonsterDataTable.DT_MonsterDataTable'");
    LiteralMessages.DT_SkillData_Path = TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_SkillData.DT_SkillData'");
    LiteralMessages.DT_ActionResource_Path = TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ActionResource.DT_ActionResource'");
    LiteralMessages.RLRInputConfig_Path = TEXT("/Script/RLR.RLRInputConfig'/Game/Blueprints/Player/Input/RLRInputConfig.RLRInputConfig'");
    LiteralMessages.DT_ResourceData_Path = TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ResourceData.DT_ResourceData'");
    LiteralMessages.DT_WidgetClassData_Path = TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_WidgetClassData.DT_WidgetClassData'");
    LiteralMessages.DT_CharacterClassData_Path = TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_CharacterClassData.DT_CharacterClassData'");
    LiteralMessages.DT_ObjectClassData_Path = TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ObjectClassData.DT_ObjectClassData'");
    LiteralMessages.DT_LevelData_Path = TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_LevelData.DT_LevelData'");
    LiteralMessages.DT_MonsterClassData_Path = TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_MonsterClassData.DT_MonsterClassData'");
    LiteralMessages.DT_ExpTable_Path = TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_ExpTable.DT_ExpTable'");
    LiteralMessages.DT_AnimData_Path = TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_AnimData.DT_AnimData'");
    LiteralMessages.DataManager_SearchingByItemSeq = TEXT("Searching By ITEM_SEQ");
    LiteralMessages.DataManager_SearchingByTag = TEXT("Searching by Tag");
    LiteralMessages.DataManager_EmptyString = TEXT("");

    /* Player Commands */
    LiteralMessages.Playercommands_InputConfigNull = TEXT("InputConfig is nullptr. 값을 할당해주세요.");
    LiteralMessages.Playercommands_URLREnhancedInputComponentNull = TEXT("URLREnhancedInputComponent  is nullptr.");

    /* UItemCountMessageBox */
    LiteralMessages.ItemCountMsg_InputQuantity = TEXT("갯수 입력");

    /* LevelManager */
	LiteralMessages.LevelName_Lobby     = FName("Lobby");
    LiteralMessages.LevelName_Title     = FName("Title");
    LiteralMessages.LevelName_InGame    = FName("InGame");
    LiteralMessages.LevelName_Dungeon   = FName("Dungeon");
    LiteralMessages.LevelName_TestMap2  = FName("TestMap2");
    LiteralMessages.LevelPath_Lobby     = TEXT("/Game/Map/Lobby/{0}");
    LiteralMessages.LevelPath_Title     = TEXT("/Game/Map/Title/{0}");
    LiteralMessages.LevelPath_InGame    = TEXT("/Game/Map/InGame/{0}");
    LiteralMessages.LevelPath_Dungeon   = TEXT("/Game/Map/Dungeon/{0}");
    LiteralMessages.LevelPath_TestMap2  = TEXT("/Game/StylizedProvencal/Maps/TestMap2");
    /* NetworkManager */
    LiteralMessages.Network_LoginServerSocket           = TEXT("LoginServerSocket");
    LiteralMessages.Network_LoginServerReceiverThread   = TEXT("LoginServerReceiverThread");
    LiteralMessages.Network_LobbyServerSocket           = TEXT("LobbyServerSocket");
    LiteralMessages.Network_LobbyServerReceiverThread   = TEXT("LobbyServerReceiverThread");
    LiteralMessages.Network_MainServerSocket            = TEXT("MainServerSocket");
    LiteralMessages.Network_MainServerReceiverThread    = TEXT("MainServerReceiverThread");
    LiteralMessages.Network_MonsterServerSocket         = TEXT("MonsterServerSocket");
    LiteralMessages.Network_MonsterServerReceiverThread = TEXT("MonsterServerReceiverThread");
    /* PostalManager */
    LiteralMessages.WBP_PostAlertUI = TEXT("WBP_PostAlertUI");
    /* RLRStruct */
    LiteralMessages.ItemRarity_Common       = TEXT("COMMON");
    LiteralMessages.ItemRarity_Uncommon     = TEXT("UNCOMMON");
    LiteralMessages.ItemRarity_Rare         = TEXT("RARE");
    LiteralMessages.ItemRarity_Unique       = TEXT("UNIQUE");
    LiteralMessages.ItemRarity_Epic         = TEXT("EPIC");
    LiteralMessages.ItemRarity_Legend       = TEXT("LEGEND");
    LiteralMessages.ItemRarity_None         = TEXT("NONE");

    LiteralMessages.ItemType_Equipment      = TEXT("EQUIPMENT");
    LiteralMessages.ItemType_Consumption    = TEXT("CONSUMPTION");
    LiteralMessages.ItemType_Etc            = TEXT("ETC");
    LiteralMessages.ItemType_None           = TEXT("NONE");

    LiteralMessages.CharacterMainJobType_Swordsman  = TEXT("SWORDSMAN");
    LiteralMessages.CharacterMainJobType_Thief      = TEXT("THIEF");
    LiteralMessages.CharacterMainJobType_Mage       = TEXT("MAGE");
    LiteralMessages.CharacterMainJobType_Archer     = TEXT("ARCHER");
    LiteralMessages.CharacterMainJobType_Priest     = TEXT("PRIEST");
    LiteralMessages.CharacterMainJobType_None       = TEXT("NONE");

    LiteralMessages.CharacterSubJobType_None        = TEXT("NONE");

    LiteralMessages.EquipmentType_Weapon            = TEXT("WEAPON");
    LiteralMessages.EquipmentType_SubWeapon         = TEXT("SUBWEAPON");
    LiteralMessages.EquipmentType_Helmet            = TEXT("HELMET");
    LiteralMessages.EquipmentType_UpperbodyArmor    = TEXT("UPPERBODYARMOR");
    LiteralMessages.EquipmentType_LowerboddyArmor   = TEXT("LOWERBODYARMOR");
    LiteralMessages.EquipmentType_Shoes             = TEXT("SHOES");
    LiteralMessages.EquipmentType_Gloves            = TEXT("GLOVES");
    LiteralMessages.EquipmentType_Necklace          = TEXT("NECKLACE");
    LiteralMessages.EquipmentType_Earring           = TEXT("EARRING");
    LiteralMessages.EquipmentType_Ring              = TEXT("RING");
    LiteralMessages.EquipmentType_Bracelet          = TEXT("BRACELET");
    LiteralMessages.EquipmentType_None              = TEXT("NONE");

    LiteralMessages.Unknown = TEXT("UNKNOWN");
    /* PlayerStructs */
    LiteralMessages.TotalStatus_HP                  = TEXT("HP");
    LiteralMessages.TotalStatus_HP_Absorb           = TEXT("HP_ABSORB");
    LiteralMessages.TotalStatus_MP                  = TEXT("MP");
    LiteralMessages.TotalStatus_MP_Absorb           = TEXT("MP_ABSORB");
    LiteralMessages.TotalStatus_Strength            = TEXT("STRENGTH");
    LiteralMessages.TotalStatus_Agility             = TEXT("AGILITY");
    LiteralMessages.TotalStatus_Intelligence        = TEXT("INTELLIGENCE");
    LiteralMessages.TotalStatus_MaxHP               = TEXT("MAX_HP");
    LiteralMessages.TotalStatus_MaxMP               = TEXT("MAX_MP");
    LiteralMessages.TotalStatus_Attack              = TEXT("ATTACK");
    LiteralMessages.TotalStatus_Defence             = TEXT("DEFENCE");
    LiteralMessages.TotalStatus_Attack_Speed        = TEXT("ATTACK_SPEED");
    LiteralMessages.TotalStatus_Move_Speed          = TEXT("MOVE_SPEED");
    LiteralMessages.TotalStatus_Life_Steal          = TEXT("LIFE_STEAL");
    LiteralMessages.TotalStatus_Critical_Chance     = TEXT("CRITICAL_CHANCE");
    LiteralMessages.TotalStatus_Critical_Damage     = TEXT("CRITICAL_DAMAGE");
    LiteralMessages.TotalStatus_Avoid               = TEXT("AVOID");
	LiteralMessages.TotalStatus_Cooldown_Reduction  = TEXT("COOLDOWN_REDUCTION");

    /* UIManager */
    LiteralMessages.LevelName_Main = TEXT("Main");
    /* ChatClient */
    LiteralMessages.ChatType_General    = TEXT("일반");
    LiteralMessages.ChatType_Whisper    = TEXT("귓속말");
    LiteralMessages.ChatType_Country    = TEXT("국가");
    LiteralMessages.ChatType_World      = TEXT("세계");
    LiteralMessages.ChatType_Guild      = TEXT("길드");
    LiteralMessages.ChatType_Raid       = TEXT("레이드");
    LiteralMessages.ChatType_Party      = TEXT("파티");
    LiteralMessages.ChatType_Continent  = TEXT("대륙");
    LiteralMessages.ChatType_Fellow     = TEXT("동료");
    LiteralMessages.ChatType_Nearby     = TEXT("근처");

	LiteralMessages.ChatType_En_General     = TEXT("General");
	LiteralMessages.ChatType_En_Whisper     = TEXT("Whisper");
	LiteralMessages.ChatType_En_Guild       = TEXT("Guild");
	LiteralMessages.ChatType_En_Party       = TEXT("Party");
	LiteralMessages.ChatType_En_Continent   = TEXT("Continent");
	LiteralMessages.ChatType_En_Raid        = TEXT("Raid");
	LiteralMessages.ChatType_En_Country     = TEXT("Country");
	LiteralMessages.ChatType_En_Nearby      = TEXT("Nearby");
	LiteralMessages.ChatType_En_World       = TEXT("World");
    /* ActionPlayMontage */
    LiteralMessages.ActionPlayMontage_PlayAnim = FName("PlayAnim");
    /* ActionInteract */
    LiteralMessages.ActionInteract_PlayInteractAnim = FName("PlayInteractAnim");
    /* ActionSkill_Holding */
    LiteralMessages.ActionSkill_Holding_HoldingLoop = FName("HoldingLoop");
    LiteralMessages.ActionSkill_Holding_EndSection  = FName("EndSection");
    /* ActionAttack */
    LiteralMessages.ActionAttack_PlayAttackAnim = FName("PlayAttackAnim");
    /* StatSet */
    LiteralMessages.StatSet_EmptyString = TEXT("");
    /* LoadBalancer */
    LiteralMessages.LoadBalancerClient_LoadBalancerSocket = TEXT("LoadBalancerSocket");
    /* SkillStructs */
    LiteralMessages.SkillStructs_Name           = TEXT("Name");
    LiteralMessages.SkillStructs_Job            = TEXT("Job");
    LiteralMessages.SkillStructs_Level          = TEXT("Level");
    LiteralMessages.SkillStructs_CostType       = TEXT("CostType");
    LiteralMessages.SkillStructs_Cost           = TEXT("Cost");
    LiteralMessages.SkillStructs_CoolTime       = TEXT("CoolTime");
    LiteralMessages.SkillStructs_SkillInfo      = TEXT("SkillInfo");
    /* ItemQuickSlotContainer */
    LiteralMessages.WBP_ItemQuickSlot = TEXT("WBP_ItemQuickSlot");
    /* SkillQuickSlot */
    LiteralMessages.SkillQuickSlot_Prefix = TEXT("Input.");
    /* SkillQuickSlotContainer */
    LiteralMessages.WBP_SkillQuickSlot = TEXT("WBP_SkillQuickSlot");
    /* ChatUI */
	LiteralMessages.ChatUI_General  = TEXT("전체");
    LiteralMessages.ChatUI_Guild    = TEXT("길드");
    LiteralMessages.ChatUI_Party    = TEXT("파티");
    LiteralMessages.ChatUI_GeneralCommand   = TEXT("");
    LiteralMessages.ChatUI_ChatCommand      = TEXT("/chat");
    LiteralMessages.ChatUI_WhisperCommand   = TEXT("/w");
    LiteralMessages.WBP_ChatTabWidget       = TEXT("/Game/Blueprints/ChatTabWidget.ChatTabWidget_C");
    /* FriendTabWidget */
    LiteralMessages.Friend_DefaultGroup = TEXT("Default Group");
    /* InventoryUI */
    LiteralMessages.WBP_InventorySlot = TEXT("WBP_InventorySlot");
    /* KeyOption */
    LiteralMessages.AssetName   = TEXT("MyPrimaryDataAsset");
    LiteralMessages.PackageName = TEXT("/Game/");
    /* KeyOptionElement */
    LiteralMessages.FirstKey_InputFormat = TEXT("Input.{0}");
    /* ItemCountMessageBox */
    LiteralMessages.MessageTextFormat = TEXT("[{0}] {1}");
    /* PostDetailUI */
    LiteralMessages.HasReadStatus      = TEXT("");
    LiteralMessages.ReadStatusNotExist = TEXT("Read");
    /* NPCPurchaseTab */
    LiteralMessages.WBP_NPCItemSlot = TEXT("WBP_NPCItemSlot");
    LiteralMessages.WBP_NPCCartSlot = TEXT("WBP_NPCCartSlot");
    LiteralMessages.WBP_NPCBundlePurchase = TEXT("WBP_NPCBundlePurchase");
    /* NPCShopUI */
    LiteralMessages.FunctionName_AddSaleItem = FName("AddSaleItem");
    /* SkillSetting */
    LiteralMessages.FirstKey_LoadSkill_Format = TEXT("Action.Skill.{0}");
    /* SkillSettingListSlotContainer */
    LiteralMessages.WBP_SkillSettingListSlot = TEXT("WBP_SkillSettingListSlot");
    /* Skill SettingQuickSlotContainer */
    LiteralMessages.WBP_SkillSettingQuickSlot = TEXT("WBP_SkillSettingQuickSlot");
    /* SkillTreeSlotcontainer */
    LiteralMessages.WBP_SkillTreeSlot = TEXT("WBP_SkillTreeSlot");
    /* TradeList */
    LiteralMessages.WBP_TradeListElement = TEXT("WBP_TradeListElement");
    /* CharacterListUI */
    LiteralMessages.WBP_CharacterListElement = TEXT("WBP_CharacterListElement");
    LiteralMessages.BP_DefaultPlayer = TEXT("BP_DefaultPlayer");
    /* ServerList */
    LiteralMessages.WBP_ServerListElement = TEXT("WBP_ServerListElement");
    /* SlotUI */
    LiteralMessages.WBP_DraggableWidget = TEXT("WBP_DraggableWidget");
    LiteralMessages.WBP_BaseDragDropOperation = TEXT("WBP_BaseDragDropOperation");
    LiteralMessages.GetDefaultSlotImage_DefaultSlotImage = TEXT("DefaultSlotImage");
    /* EnhanceResultUI */
    LiteralMessages.EnhanceSuccessStack = TEXT("제련 성공 스택 +");
    LiteralMessages.IncreaseMessage     = TEXT("상승");
    LiteralMessages.FailureTextFormat   = TEXT("{0}{1}{2}");

     /* GameplayTagManager */
    LiteralMessages.Attribute_MainStat_Health = FTagPair(FName("Attribute.MainStat.Health"), TEXT("체력"));
    LiteralMessages.Attribute_MainStat_MaxHealth = FTagPair(FName("Attribute.MainStat.MaxHealth"), TEXT("최대 체력"));

    LiteralMessages.Action_Default_Move     = FTagPair(FName("Action.Default.Move"), TEXT("이동"));
	LiteralMessages.Action_Default_Attack   = FTagPair(FName("Action.Default.Attack"), TEXT("기본공격"));
	LiteralMessages.Action_Default_Jump     = FTagPair(FName("Action.Default.Jump"), TEXT("점프"));
	LiteralMessages.Action_Default_GuildOpen = FTagPair(FName("Action.Default.GuildOpen"), TEXT("길드창"));
	LiteralMessages.Action_Default_PlayMontage = FTagPair(FName("Action.Default.PlayMontage"), TEXT("애니메이션 실행"));
	LiteralMessages.Action_Default_HitCheck = FTagPair(FName("Action.Attack.HitCheck"), TEXT("공격판정"));
	
    LiteralMessages.Action_Skill_1 = FTagPair(FName("Action.Skill.1"), TEXT("1스킬"));
	LiteralMessages.Action_Skill_2 = FTagPair(FName("Action.Skill.2"), TEXT("2스킬"));
	LiteralMessages.Action_Skill_3 = FTagPair(FName("Action.Skill.3"), TEXT("3스킬"));
	LiteralMessages.Action_Skill_4 = FTagPair(FName("Action.Skill.4"), TEXT("4스킬"));
	LiteralMessages.Action_Skill_5 = FTagPair(FName("Action.Skill.5"), TEXT("5스킬"));
	LiteralMessages.Action_Skill_6 = FTagPair(FName("Action.Skill.6"), TEXT("6스킬"));
	LiteralMessages.Action_Skill_7 = FTagPair(FName("Action.Skill.7"), TEXT("7스킬"));
	LiteralMessages.Action_Skill_8 = FTagPair(FName("Action.Skill.8"), TEXT("8스킬"));
    LiteralMessages.Action_Skill_Type_Normal        = FTagPair(FName("Action.Skill.Type.Normal"), TEXT("Normal스킬"));
    LiteralMessages.Action_Skill_Type_Area          = FTagPair(FName("Action.Skill.Type.Area"), TEXT("Area스킬"));
    LiteralMessages.Action_Skill_Type_Holding       = FTagPair(FName("Action.Skill.Type.Holding"), TEXT("Holding스킬"));
    LiteralMessages.Action_Skill_Type_Casting       = FTagPair(FName("Action.Skill.Type.Casting"), TEXT("Casting스킬"));
    LiteralMessages.Action_Skill_Type_Movility      = FTagPair(FName("Action.Skill.Type.Movility"), TEXT("Movility스킬"));
    LiteralMessages.Action_Skill_Type_Targeting     = FTagPair(FName("Action.Skill.Type.Targeting"), TEXT("Targeting스킬"));
    LiteralMessages.Action_Skill_Type_Chain         = FTagPair(FName("Action.Skill.Type.Chain"), TEXT("Chain스킬"));
    LiteralMessages.Action_Skill_SwordsMan_SwordAura = FTagPair(FName("Action.Skill.SwordsMan.SwordAura"), TEXT("소드오러"));
    LiteralMessages.Action_Skill_Mage_Meteor        = FTagPair(FName("Action.Skill.Mage.Meteor"), TEXT("메테오"));
    LiteralMessages.Action_Skill_Mage_TrippleCircle = FTagPair(FName("Action.Skill.Mage.TrippleCircle"), TEXT("트리플서클"));

    LiteralMessages.Action_Interaction          = FTagPair(FName("Action.Interaction"), TEXT("상호작용"));
    LiteralMessages.Action_Interaction_Dialogue = FTagPair(FName("Action.Interaction.Dialogue"), TEXT("대화"));
    LiteralMessages.Action_Interaction_Logging  = FTagPair(FName("Action.Interaction.Logging"), TEXT("벌목"));
    
    LiteralMessages.Object_State_Hittable   = FTagPair(FName("Object.State.Hittable"), TEXT("공격가능"));
    LiteralMessages.Player_State_Attacking  = FTagPair(FName("Player.State.Attacking"), TEXT("공격중"));
    
    LiteralMessages.Abnormal_Stun           = FTagPair(FName("Abnormal.Stun"), TEXT("기절"));
    LiteralMessages.Abnormal_Bind           = FTagPair(FName("Abnormal.Bind"), TEXT("속박"));
    LiteralMessages.Abnormal_Frozen         = FTagPair(FName("Abnormal.Frozen"), TEXT("빙결"));
    LiteralMessages.Abnormal_Stiffen        = FTagPair(FName("Abnormal.Stiffen"), TEXT("경직"));
    LiteralMessages.Abnormal_Provoke        = FTagPair(FName("Abnormal.Provoke"), TEXT("도발"));
    LiteralMessages.Abnormal_Electric       = FTagPair(FName("Abnormal.Electric"), TEXT("감전"));
    LiteralMessages.Abnormal_Silence        = FTagPair(FName("Abnormal.Silence"), TEXT("침묵"));
    LiteralMessages.Abnormal_Burn           = FTagPair(FName("Abnormal.Burn"), TEXT("화상"));
    LiteralMessages.Abnormal_Poison         = FTagPair(FName("Abnormal.Poison"), TEXT("중독"));
    LiteralMessages.Abnormal_Slow           = FTagPair(FName("Abnormal.Slow"), TEXT("슬로우"));
    LiteralMessages.Abnormal_Bleeding       = FTagPair(FName("Abnormal.Bleeding"), TEXT("출혈"));

    LiteralMessages.Action_ItemQuickSlot_1 = FTagPair(FName("Action.ItemQuickSlot.1"), TEXT("아이템 퀵 슬롯 1"));
    LiteralMessages.Action_ItemQuickSlot_2 = FTagPair(FName("Action.ItemQuickSlot.2"), TEXT("아이템 퀵 슬롯 2"));
    LiteralMessages.Action_ItemQuickSlot_3 = FTagPair(FName("Action.ItemQuickSlot.3"), TEXT("아이템 퀵 슬롯 3"));
	LiteralMessages.Action_ItemQuickSlot_4 = FTagPair(FName("Action.ItemQuickSlot.4"), TEXT("아이템 퀵 슬롯 4"));
	LiteralMessages.Action_ItemQuickSlot_5 = FTagPair(FName("Action.ItemQuickSlot.5"), TEXT("아이템 퀵 슬롯 5"));
	LiteralMessages.Action_ItemQuickSlot_6 = FTagPair(FName("Action.ItemQuickSlot.6"), TEXT("아이템 퀵 슬롯 6"));
	LiteralMessages.Action_ItemQuickSlot_7 = FTagPair(FName("Action.ItemQuickSlot.7"), TEXT("아이템 퀵 슬롯 7"));
	LiteralMessages.Action_ItemQuickSlot_8 = FTagPair(FName("Action.ItemQuickSlot.8"), TEXT("아이템 퀵 슬롯 8"));
	LiteralMessages.Action_ItemQuickSlot_9 = FTagPair(FName("Action.ItemQuickSlot.9"), TEXT("아이템 퀵 슬롯 9"));
    // Page
    LiteralMessages.Page_InGame = FTagPair(FName("Page.InGame"), TEXT("인게임 페이지"));
    LiteralMessages.Page_Dialogue = FTagPair(FName("Page.Dialogue"), TEXT("대화 페이지"));
    // Action UI
    LiteralMessages.UI_Character_StatusDisplay         = FTagPair(FName("UI.Character.StatusDisplay"), TEXT("캐릭터 상태창"));
    LiteralMessages.UI_Character_Profile               = FTagPair(FName("UI.Character.Profile"), TEXT("캐릭터 스탯창"));
    LiteralMessages.UI_Character_Overhead              = FTagPair(FName("UI.Character.Overhead"), TEXT("캐릭터 체력바"));

    LiteralMessages.UI_Skill                           = FTagPair(FName("UI.Skill"), TEXT("스킬창"));
    LiteralMessages.UI_Skill_Upgrade                   = FTagPair(FName("UI.Skill.Upgrade"), TEXT("스킬 업그레이드"));
    LiteralMessages.UI_Skill_DetailInfo                = FTagPair(FName("UI.Skill.DetailInfo"), TEXT("스킬 정보창"));
    LiteralMessages.UI_Inventory                       = FTagPair(FName("UI.Inventory"), TEXT("인벤토리"));
    LiteralMessages.UI_ItemInformation                 = FTagPair(FName("UI.ItemInfomation"), TEXT("아이템 정보창"));
    LiteralMessages.UI_NPCShop                         = FTagPair(FName("UI.NPCShop"), TEXT("NPC 상점"));
    LiteralMessages.UI_NPCShop_Popup_Bundle            = FTagPair(FName("UI.NPCShop.Popup.Bundle"), TEXT("NPC 상점 묶음 구매"));
    LiteralMessages.UI_Chat                            = FTagPair(FName("UI.Chat"), TEXT("채팅창"));
    LiteralMessages.UI_Chat_Option                     = FTagPair(FName("UI.Chat.Option"), TEXT("채팅 옵션창"));
    LiteralMessages.UI_Quest                           = FTagPair(FName("UI.Quest"), TEXT("퀘스트 정보창"));
    LiteralMessages.UI_Quest_Dialogue                  = FTagPair(FName("UI.Quest.Dialogue"), TEXT("퀘스트 대화창"));
    LiteralMessages.UI_Option                          = FTagPair(FName("UI.Option"), TEXT("옵션"));
    LiteralMessages.UI_Option_GraphicsOption           = FTagPair(FName("UI.Option.GraphicsOption"), TEXT("그래픽 옵션"));
    LiteralMessages.UI_Option_AudioOption              = FTagPair(FName("UI.Option.AudioOption"), TEXT("오디오 옵션"));
    LiteralMessages.UI_Option_CommunityOption          = FTagPair(FName("UI.Option.CommunityOption"), TEXT("커뮤니티 옵션"));
    LiteralMessages.UI_Option_GameplayOption           = FTagPair(FName("UI.Option.GameplayOption"), TEXT("게임 플레이 옵션"));
    LiteralMessages.UI_Option_KeyOption                = FTagPair(FName("UI.Option.KeyOption"), TEXT("키 옵션"));
    LiteralMessages.UI_Post                            = FTagPair(FName("UI.Post"), TEXT("우편 시스템"));
    LiteralMessages.UI_Post_Alert                      = FTagPair(FName("UI.Post.Alert"), TEXT("우편 알림"));
    LiteralMessages.UI_Party                           = FTagPair(FName("UI.Party"), TEXT("파티창"));
    LiteralMessages.UI_Trade                           = FTagPair(FName("UI.Trade"), TEXT("개인 거래창"));
    LiteralMessages.UI_FriendList                      = FTagPair(FName("UI.FriendList"), TEXT("친구 목록"));
    LiteralMessages.UI_Guild                           = FTagPair(FName("UI.Guild"), TEXT("길드창"));
    LiteralMessages.UI_Report                          = FTagPair(FName("UI.Report"), TEXT("신고"));
    LiteralMessages.UI_Popup_ItemCountMessageBox       = FTagPair(FName("UI.Popup.ItemCountMessageBox"), TEXT("아이템 갯수 입력"));
    LiteralMessages.UI_Popup_NotificationMessageBox    = FTagPair(FName("UI.Popup.NotificationMessageBox"), TEXT("알림 박스"));
    LiteralMessages.UI_Popup_ConfirmMessageBox         = FTagPair(FName("UI.Popup.ConfirmMessageBox"), TEXT("확인 입력 박스"));
    LiteralMessages.UI_OtherPlayer_Menu                = FTagPair(FName("UI.OtherPlayer.Menu"), TEXT("플레이어 메뉴"));
    LiteralMessages.UI_OtherPlayer_OverHead            = FTagPair(FName("UI.OtherPlayer.OverHead"), TEXT("타 플레이어 체력바"));
    LiteralMessages.UI_OtherPlayer_Profile             = FTagPair(FName("UI.OtherPlayer.Profile"), TEXT("타 플레이어 상태창"));
    LiteralMessages.UI_MiniMap                         = FTagPair(FName("UI.MiniMap"), TEXT("미니맵"));
    LiteralMessages.UI_Badge                           = FTagPair(FName("UI.Badge"), TEXT("뱃지"));
    LiteralMessages.UI_Monster_OverHead                = FTagPair(FName("UI.Monster.OverHead"), TEXT("몬스터 상태"));
    LiteralMessages.UI_TimerProgressBar                = FTagPair(FName("UI.TimeProgressBar"), TEXT("프로그래스바"));
    LiteralMessages.UI_Menu                            = FTagPair(FName("UI.Menu"), TEXT("메뉴"));
    LiteralMessages.UI_Enhance                         = FTagPair(FName("UI.Enhance"), TEXT("강화"));
    // Input
	LiteralMessages.InputTag_LMB        = FTagPair(FName("Input.LMB"), TEXT("마우스 왼쪽 버튼"));
	LiteralMessages.InputTag_RMB        = FTagPair(FName("Input.RMB"), TEXT("마우스 오른쪽 버튼"));
    LiteralMessages.InputTag_Shift      = FTagPair(FName("Input.Shift"), TEXT("Shift"));
    LiteralMessages.InputTag_Ctrl       = FTagPair(FName("Input.Ctrl"), TEXT("Ctrl"));
    LiteralMessages.InputTag_ESC        = FTagPair(FName("Input.ESC"), TEXT("ESC"));
    LiteralMessages.InputTag_1          = FTagPair(FName("Input.1"), TEXT("1"));
    LiteralMessages.InputTag_2          = FTagPair(FName("Input.2"), TEXT("2"));
    LiteralMessages.InputTag_3          = FTagPair(FName("Input.3"), TEXT("3"));
    LiteralMessages.InputTag_4          = FTagPair(FName("Input.4"), TEXT("4"));
    LiteralMessages.InputTag_5          = FTagPair(FName("Input.5"), TEXT("5"));
    LiteralMessages.InputTag_6          = FTagPair(FName("Input.6"), TEXT("6"));
    LiteralMessages.InputTag_7          = FTagPair(FName("Input.7"), TEXT("7"));
    LiteralMessages.InputTag_8          = FTagPair(FName("Input.8"), TEXT("8"));
    LiteralMessages.InputTag_9          = FTagPair(FName("Input.9"), TEXT("9"));
    LiteralMessages.InputTag_A          = FTagPair(FName("Input.A"), TEXT("KeyBoard A"));
    LiteralMessages.InputTag_B          = FTagPair(FName("Input.B"), TEXT("KeyBoard B"));
    LiteralMessages.InputTag_C          = FTagPair(FName("Input.C"), TEXT("KeyBoard C"));
    LiteralMessages.InputTag_D          = FTagPair(FName("Input.D"), TEXT("KeyBoard D"));
    LiteralMessages.InputTag_E          = FTagPair(FName("Input.E"), TEXT("KeyBoard E"));
    LiteralMessages.InputTag_F          = FTagPair(FName("Input.F"), TEXT("KeyBoard F"));
    LiteralMessages.InputTag_G          = FTagPair(FName("Input.G"), TEXT("KeyBoard G"));
    LiteralMessages.InputTag_H          = FTagPair(FName("Input.H"), TEXT("KeyBoard H"));
    LiteralMessages.InputTag_I          = FTagPair(FName("Input.I"), TEXT("KeyBoard I"));
    LiteralMessages.InputTag_J          = FTagPair(FName("Input.J"), TEXT("KeyBoard J"));
    LiteralMessages.InputTag_K          = FTagPair(FName("Input.K"), TEXT("KeyBoard K"));
    LiteralMessages.InputTag_L          = FTagPair(FName("Input.L"), TEXT("KeyBoard L"));
    LiteralMessages.InputTag_M          = FTagPair(FName("Input.M"), TEXT("KeyBoard M"));
    LiteralMessages.InputTag_N          = FTagPair(FName("Input.N"), TEXT("KeyBoard N"));
    LiteralMessages.InputTag_O          = FTagPair(FName("Input.O"), TEXT("KeyBoard O"));
    LiteralMessages.InputTag_P          = FTagPair(FName("Input.P"), TEXT("KeyBoard P"));
    LiteralMessages.InputTag_Q          = FTagPair(FName("Input.Q"), TEXT("KeyBoard Q"));
    LiteralMessages.InputTag_R          = FTagPair(FName("Input.R"), TEXT("KeyBoard R"));
    LiteralMessages.InputTag_S          = FTagPair(FName("Input.S"), TEXT("KeyBoard S"));
    LiteralMessages.InputTag_T          = FTagPair(FName("Input.T"), TEXT("KeyBoard T"));
    LiteralMessages.InputTag_U          = FTagPair(FName("Input.U"), TEXT("KeyBoard U"));
    LiteralMessages.InputTag_V          = FTagPair(FName("Input.V"), TEXT("KeyBoard V"));
    LiteralMessages.InputTag_W          = FTagPair(FName("Input.W"), TEXT("KeyBoard W"));
    LiteralMessages.InputTag_X          = FTagPair(FName("Input.X"), TEXT("KeyBoard X"));
    LiteralMessages.InputTag_Y          = FTagPair(FName("Input.Y"), TEXT("KeyBoard Y"));
    LiteralMessages.InputTag_Z          = FTagPair(FName("Input.Z"), TEXT("KeyBoard Z"));
    LiteralMessages.InputTag_Alt_U      = FTagPair(FName("Input.Alt_U"), TEXT("KeyBoard Alt + U"));
}

FString LiteralManager::GetSkillTypeText(ESkillType type)
{
	FString result;
	switch (type)
	{
	case ESkillType::NORMAL:
		result = SkillType_Normal;
		break;
	case ESkillType::AREA:
		result = SkillType_Area;
		break;
	case ESkillType::HOLDING:
		result = SkillType_Holding;
		break;
	case ESkillType::CASTING:
		result = SkillType_Casting;
		break;
	case ESkillType::MOVILITY:
		result = SkillType_Mobility;
		break;
	case ESkillType::TARGETING:
		result = SkillType_Targeting;
		break;
	case ESkillType::CHAIN:
		result = SkillType_Chain;
		break;
	}

	return result;
}

FString LiteralManager::GetSkillCostText(ECostType type)
{
	FString result;
	switch (type)
	{
	case ECostType::MP:
		result = CostType_MP;
		break;
	case ECostType::HP:
		result = CostType_HP;
		break;
	}

	return result;
}
