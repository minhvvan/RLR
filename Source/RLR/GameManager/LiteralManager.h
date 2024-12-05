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
	FTagPair UI_KeyOption;
	FTagPair UI_Quest;
	FTagPair UI_Quest_Dialogue;
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