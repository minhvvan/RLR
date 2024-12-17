// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/* GameplayTagManager */
struct FTagPair
{
	FName TagName;
	FString TagDesc;

	FTagPair()
		: TagName(NAME_None), TagDesc(TEXT("")) {}
	FTagPair(const FName& InTagName, const FString& InTagDesc)
		: TagName(InTagName), TagDesc(InTagDesc) {}
};

/**
 * RLRUE5 내에서 사용하는 모든 문자열을 관리하는 클래스
 */
 #define RLRLITERAL LiteralManager::Get()

class RLR_API LiteralManager
{
public:
	static const LiteralManager& Get() { return LiteralMessages; }
	static void Init();

public:
	/* TradeUI */
	FString TradeUI_Nickname;
	FString TradeUI_UserSeq;
	FString TradeUI_From;
	FString TradeUI_Gold;
	FString TradeUI_TradeRequest;
	FString TradeUI_TradeSuccess;
	FString TradeUI_TradeCanceled;
	FString TradeUI_TradeDenied;
	FString TradeUI_InputExceedsCurrentQuantity;
	FName	TradeUI_OnClickedInventorySlot;
	FName	TradeUI_OnClickedAcceptButton;
	FName	TradeUI_OnClickedCancelButton;
	FName	TradeUI_OnConfirmItemCountMessageBox;
	FName	TradeUI_OnCancelItemCountMessageBox;
	/* EnhanceOverlayUI */
	FString Enhance_EnhancePrompt;
	FName	Enhance_OnClickedAcceptButton;
	FName	Enhance_OnClickedCancelButton;
	/* PostOverlayUI */
	FString PostUI_ReceivedPost;
	FString PostUI_SentPost;
	FString PostUI_RemovePrompt;
	FString PostUI_ExitPrompt;
	FName	PostUI_OnClickedDeletePostsConfirmButton;
	FName	PostUI_OnClickedCancelButton;
	FName	PostUI_OnClickedAcceptButtonWhileWriting;

	/* Player Commands */
	FString Playercommands_InputConfigNull;
	FString Playercommands_URLREnhancedInputComponentNull;
	/* UItemCountMessageBox */
	FString ItemCountMsg_InputQuantity;
	
	/* DataManager */
	FString DT_ItemData_Path;
	FString DT_ItemResource_Path;
	FString DT_MonsterDataTable_Path;
	FString DT_SkillData_Path;
	FString DT_ActionResource_Path;
	FString RLRInputConfig_Path;
	FString DT_ResourceData_Path;
	FString DT_WidgetClassData_Path;
	FString DT_CharacterClassData_Path;
	FString DT_ObjectClassData_Path;
	FString DT_LevelData_Path;
	FString DT_MonsterClassData_Path;
	FString DT_ExpTable_Path;
	FString DT_AnimData_Path;
	FString	DataManager_SearchingByItemSeq;
	FString	DataManager_SearchingByTag;
	FString	DataManager_EmptyString;
	/* EffectManageer */
	FString DT_EffectData_Path;
	/* LevelTransitionVolume */
	FName	TransitionVolume_VolumeName;
	FName	TransitionVolume_OverlapOnlyPawn;
	/* RLRInteractableActor */
	FName	InteractableActor_InteractionComp;
	FName	InteractableActor_Mesh;
	FName	InteractableActor_InteractUI;
	/* RLRProjectile */
	FName	Projectile_CollisionComponent;
	FName	Projectile_Mesh;
	FName	Projectile_Movement;
	/* LevelManager */
	FName LevelName_Lobby;
	FName LevelName_Title;
	FName LevelName_InGame;
	FName LevelName_Dungeon;
	FName LevelName_TestMap2;
	FString LevelPath_Lobby;
	FString LevelPath_Title;
	FString LevelPath_InGame;
	FString LevelPath_Dungeon;
	FString LevelPath_TestMap2;
	/* NetworkManager */
	FString Network_LoginServerSocket;
	FString Network_LoginServerReceiverThread;
	FString Network_LobbyServerSocket;
	FString Network_LobbyServerReceiverThread;
	FString Network_MainServerSocket;
	FString Network_MainServerReceiverThread;
	FString Network_MonsterServerSocket;
	FString Network_MonsterServerReceiverThread;
	/* ObjectManager */
	FString RLRNonPlayerCharacter_Path;
	FString RLRInteractableActor_Path;
	/* OtehrUserManager */
	FString RLRPlayerCharacter_Path;
	/* PostalManager */
	FString WBP_PostAlertUI;
	/* RLRStruct */
	FString ItemRarity_Common;
	FString ItemRarity_Uncommon;
	FString ItemRarity_Rare;
	FString ItemRarity_Unique;
	FString ItemRarity_Epic;
	FString ItemRarity_Legend;
	FString ItemRarity_None;

	FString ItemType_Equipment;
	FString ItemType_Consumption;
	FString ItemType_Etc;
	FString ItemType_None;

	FString CharacterMainJobType_Swordsman;
	FString CharacterMainJobType_Thief;
	FString CharacterMainJobType_Mage;
	FString CharacterMainJobType_Archer;
	FString CharacterMainJobType_Priest;
	FString CharacterMainJobType_None;

	FString CharacterSubJobType_None;

	FString EquipmentType_Weapon;
	FString EquipmentType_SubWeapon;
	FString EquipmentType_Helmet;
	FString EquipmentType_UpperbodyArmor;
	FString EquipmentType_LowerboddyArmor;
	FString EquipmentType_Shoes;
	FString EquipmentType_Gloves;
	FString EquipmentType_Necklace;
	FString EquipmentType_Earring;
	FString EquipmentType_Ring;
	FString EquipmentType_Bracelet;
	FString EquipmentType_None;

	FString Unknown;
	/* PlayerStructs */
	FString TotalStatus_HP;
	FString TotalStatus_HP_Absorb;
	FString TotalStatus_MP;
	FString TotalStatus_MP_Absorb;
	FString TotalStatus_Strength;
	FString TotalStatus_Agility;
	FString TotalStatus_Intelligence;
	FString TotalStatus_MaxHP;
	FString TotalStatus_MaxMP;
	FString TotalStatus_Attack;
	FString TotalStatus_Defence;
	FString TotalStatus_Attack_Speed;
	FString TotalStatus_Move_Speed;
	FString TotalStatus_Life_Steal;
	FString TotalStatus_Critical_Chance;
	FString TotalStatus_Critical_Damage;
	FString TotalStatus_Avoid;
	FString TotalStatus_Cooldown_Reduction;

	/* UIManager */
	FString LevelName_Main;
	/* ChatClient */
	FString ChatType_General;
	FString ChatType_Whisper;
	FString ChatType_Country;
	FString ChatType_World;
	FString ChatType_Guild;
	FString ChatType_Raid;
	FString ChatType_Party;
	FString ChatType_Continent;
	FString ChatType_Fellow;
	FString ChatType_Nearby;
	FString ChatType_En_General;
	FString ChatType_En_Whisper;
	FString ChatType_En_Guild;
	FString ChatType_En_Party;
	FString ChatType_En_Continent;
	FString ChatType_En_Raid;
	FString ChatType_En_Country;
	FString ChatType_En_Nearby;
	FString ChatType_En_World;
	/* ActionPlayMontage */
	FName ActionPlayMontage_PlayAnim;
	/* ActionInteract */
	FName ActionInteract_PlayInteractAnim;
	/* ActionSkill_Holding */
	FName ActionSkill_Holding_HoldingLoop;
	FName ActionSkill_Holding_EndSection;
	/* ActionAttack */
	FName ActionAttack_PlayAttackAnim;
	/* StatSet */
	FString DT_AbnormalMark_Path;
	FString StatSet_EmptyString;
	/* RLRReticle */
	FName RLRReticle_Decal;
	/* LoadBalancerClient */
	FString LoadBalancerClient_LoadBalancerSocket;
	/* SkillStructs */
	FString SkillStructs_Name;
	FString SkillStructs_Job;
	FString SkillStructs_Level;
	FString SkillStructs_CostType;
	FString SkillStructs_Cost;
	FString SkillStructs_CoolTime;
	FString SkillStructs_SkillInfo;
	/* ItemQuickSlotcontainer */
	FString WBP_ItemQuickSlot;
	/* SkillQuickSlot */
	FString SkillQuickSlot_Prefix;
	/* SkillQuickSlotContainer */
	FString WBP_SkillQuickSlot;
	/* ChatUI */
	FString ChatUI_General;
	FString ChatUI_Guild;
	FString ChatUI_Party;
	FString ChatUI_GeneralCommand;
	FString ChatUI_ChatCommand;
	FString ChatUI_WhisperCommand;
	FString WBP_ChatTabWidget;
	/* FriendTabWidget */
	FString Friend_DefaultGroup;
	/* InventoryUI */
	FString WBP_InventorySlot;
	/* KeyOption */
	FString AssetName;
	FString PackageName;
	/* KeyOptionElement, TEXT("Input.{0}") */
	FString FirstKey_InputFormat;
	/* ItemCountMessageBox, TEXT("[{0}] {1}") */
	FString MessageTextFormat;
	/* PostDetailUI */
	FString HasReadStatus;
	FString ReadStatusNotExist;
	/* NPCPurchaseTab */
	FString WBP_NPCItemSlot;
	FString WBP_NPCCartSlot;
	FString WBP_NPCBundlePurchase;
	/* NPCShopUI */
	FName FunctionName_AddSaleItem;
	/* SkillSetting, TEXT("Action.Skill.{0}") */
	FString FirstKey_LoadSkill_Format;
	/* SkillSettingListSlotContainer */
	FString WBP_SkillSettingListSlot;
	/* Skill SettingQuickSlotContainer */
	FString WBP_SkillSettingQuickSlot;
	/* SkillTreeSlotContainer */
	FString WBP_SkillTreeSlot;
	/* TradList */
	FString WBP_TradeListElement;
	/* CharacterListUI */
	FString WBP_CharacterListElement;
	FString BP_DefaultPlayer;
	/* ServerList */
	FString WBP_ServerListElement;
	/* SlotUI */
	FString WBP_DraggableWidget;
	FString WBP_BaseDragDropOperation;
	FString GetDefaultSlotImage_DefaultSlotImage;
	/* EnhanceResultUI */
	FString EnhanceSuccessStack;
	FString IncreaseMessage;
	FString FailureTextFormat;
	/* AddFriendMessageBox & MoveGroupMessageBox */
	FString NullptrOption;

	/* GameplayTagManager */
	// Attribute_MainStat
	FTagPair Attribute_MainStat_Health;
	FTagPair Attribute_MainStat_MaxHealth;
	// Action
	FTagPair Action_Default_Move;
	FTagPair Action_Default_Attack;
	FTagPair Action_Default_Jump;
	FTagPair Action_Default_GuildOpen;
	FTagPair Action_Default_PlayMontage;
	FTagPair Action_Default_HitCheck;
	// Skill
	FTagPair Action_Skill_1;
	FTagPair Action_Skill_2;
	FTagPair Action_Skill_3;
	FTagPair Action_Skill_4;
	FTagPair Action_Skill_5;
	FTagPair Action_Skill_6;
	FTagPair Action_Skill_7;
	FTagPair Action_Skill_8;
	FTagPair Action_Skill_Type_Normal;
	FTagPair Action_Skill_Type_Area;
	FTagPair Action_Skill_Type_Holding;
	FTagPair Action_Skill_Type_Casting;
	FTagPair Action_Skill_Type_Movility;
	FTagPair Action_Skill_Type_Targeting;
	FTagPair Action_Skill_Type_Chain;
	FTagPair Action_Skill_SwordsMan_SwordAura;
	FTagPair Action_Skill_Mage_Meteor;
	FTagPair Action_Skill_Mage_TrippleCircle;
	// Interaction
	FTagPair Action_Interaction;
	FTagPair Action_Interaction_Dialogue;
	FTagPair Action_Interaction_Logging;
	// Object
	FTagPair Object_State_Hittable;
	// Player
	FTagPair Player_State_Attacking;
	//Abnormal
	FTagPair Abnormal_Stun;
	FTagPair Abnormal_Bind;
	FTagPair Abnormal_Frozen;
	FTagPair Abnormal_Stiffen;
	FTagPair Abnormal_Provoke;
	FTagPair Abnormal_Electric;
	FTagPair Abnormal_Silence;
	FTagPair Abnormal_Burn;
	FTagPair Abnormal_Poison;
	FTagPair Abnormal_Slow;
	FTagPair Abnormal_Bleeding;
	// Item Quick Slot
	FTagPair Action_ItemQuickSlot_1;
	FTagPair Action_ItemQuickSlot_2;
	FTagPair Action_ItemQuickSlot_3;
	FTagPair Action_ItemQuickSlot_4;
	FTagPair Action_ItemQuickSlot_5;
	FTagPair Action_ItemQuickSlot_6;
	FTagPair Action_ItemQuickSlot_7;
	FTagPair Action_ItemQuickSlot_8;
	FTagPair Action_ItemQuickSlot_9;
	// Page
	FTagPair Page_InGame;
	FTagPair Page_Dialogue;
	// Action UI
	FTagPair UI_Character_StatusDisplay;
	FTagPair UI_Character_Profile;
	FTagPair UI_Character_Overhead;
	FTagPair UI_Skill;
	FTagPair UI_Skill_Upgrade;
	FTagPair UI_Skill_DetailInfo;
	FTagPair UI_Inventory;
	FTagPair UI_ItemInformation;
	FTagPair UI_NPCShop;
	FTagPair UI_NPCShop_Popup_Bundle;
	FTagPair UI_Chat;
	FTagPair UI_Chat_Option;
	FTagPair UI_Quest;
	FTagPair UI_Quest_Dialogue;
	FTagPair UI_Option;
	FTagPair UI_Option_GraphicsOption;
	FTagPair UI_Option_AudioOption;
	FTagPair UI_Option_CommunityOption;
	FTagPair UI_Option_GameplayOption;
	FTagPair UI_Option_KeyOption;
	FTagPair UI_Post;
	FTagPair UI_Post_Alert;
	FTagPair UI_Party;
	FTagPair UI_Trade;
	FTagPair UI_FriendList;
	FTagPair UI_Guild;
	FTagPair UI_Report;
	FTagPair UI_Popup_ItemCountMessageBox;
	FTagPair UI_Popup_NotificationMessageBox;
	FTagPair UI_Popup_ConfirmMessageBox;
	FTagPair UI_OtherPlayer_Menu;
	FTagPair UI_OtherPlayer_OverHead;
	FTagPair UI_OtherPlayer_Profile;
	FTagPair UI_MiniMap;
	FTagPair UI_Badge;
	FTagPair UI_Monster_OverHead;
	FTagPair UI_TimerProgressBar;
	FTagPair UI_Menu;
	FTagPair UI_Enhance;
	// Input
	FTagPair InputTag_LMB;
	FTagPair InputTag_RMB;
	FTagPair InputTag_Shift;
	FTagPair InputTag_Ctrl;
	FTagPair InputTag_ESC;
	FTagPair InputTag_1;
	FTagPair InputTag_2;
	FTagPair InputTag_3;
	FTagPair InputTag_4;
	FTagPair InputTag_5;
	FTagPair InputTag_6;
	FTagPair InputTag_7;
	FTagPair InputTag_8;
	FTagPair InputTag_9;
	FTagPair InputTag_A;
	FTagPair InputTag_B;
	FTagPair InputTag_C;
	FTagPair InputTag_D;
	FTagPair InputTag_E;
	FTagPair InputTag_F;
	FTagPair InputTag_G;
	FTagPair InputTag_H;
	FTagPair InputTag_I;
	FTagPair InputTag_J;
	FTagPair InputTag_K;
	FTagPair InputTag_L;
	FTagPair InputTag_M;
	FTagPair InputTag_N;
	FTagPair InputTag_O;
	FTagPair InputTag_P;
	FTagPair InputTag_Q;
	FTagPair InputTag_R;
	FTagPair InputTag_S;
	FTagPair InputTag_T;
	FTagPair InputTag_U;
	FTagPair InputTag_V;
	FTagPair InputTag_W;
	FTagPair InputTag_X;
	FTagPair InputTag_Y;
	FTagPair InputTag_Z;
	FTagPair InputTag_Alt_U;

private:
	static LiteralManager LiteralMessages;
	LiteralManager();
};