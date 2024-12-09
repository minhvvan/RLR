// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayTagManager.h"
#include "GameManager/LiteralManager.h"

FGameplayTagManager FGameplayTagManager::GameplayTags;

void FGameplayTagManager::Init()
{
	GameplayTags.Attributes_MainStat_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Attribute_MainStat_Health.TagName, RLRLITERAL.Attribute_MainStat_Health.TagDesc);
	GameplayTags.Attributes_MainStat_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Attribute_MainStat_MaxHealth.TagName, RLRLITERAL.Attribute_MainStat_MaxHealth.TagDesc);
	
	//Action
	GameplayTags.Action_Default_Move = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Default_Move.TagName, RLRLITERAL.Action_Default_Move.TagDesc);
	GameplayTags.Action_Default_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Default_Attack.TagName, RLRLITERAL.Action_Default_Attack.TagDesc);
	GameplayTags.Action_Default_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Default_Jump.TagName, RLRLITERAL.Action_Default_Jump.TagDesc);
	GameplayTags.Action_Default_GuildOpen = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Default_GuildOpen.TagName, RLRLITERAL.Action_Default_GuildOpen.TagDesc);
	GameplayTags.Action_Default_PlayMontage = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Default_PlayMontage.TagName, RLRLITERAL.Action_Default_PlayMontage.TagDesc);
	GameplayTags.Action_Attack_HitCheck = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Default_HitCheck.TagName, RLRLITERAL.Action_Default_HitCheck.TagDesc);
	
	//Skill
	GameplayTags.Action_Skill_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_1.TagName, RLRLITERAL.Action_Skill_1.TagDesc);
	GameplayTags.Action_Skill_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_2.TagName, RLRLITERAL.Action_Skill_2.TagDesc);
	GameplayTags.Action_Skill_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_3.TagName, RLRLITERAL.Action_Skill_3.TagDesc);
	GameplayTags.Action_Skill_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_4.TagName, RLRLITERAL.Action_Skill_4.TagDesc);
	GameplayTags.Action_Skill_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_5.TagName, RLRLITERAL.Action_Skill_5.TagDesc);
	GameplayTags.Action_Skill_6 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_6.TagName, RLRLITERAL.Action_Skill_6.TagDesc);
	GameplayTags.Action_Skill_7 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_7.TagName, RLRLITERAL.Action_Skill_7.TagDesc);
	GameplayTags.Action_Skill_8 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_8.TagName, RLRLITERAL.Action_Skill_8.TagDesc);
	
	//Skill.Type
	GameplayTags.Action_Skill_Type_Normal = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_Type_Normal.TagName, RLRLITERAL.Action_Skill_Type_Normal.TagDesc);
	GameplayTags.Action_Skill_Type_Area = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_Type_Area.TagName, RLRLITERAL.Action_Skill_Type_Area.TagDesc);
	GameplayTags.Action_Skill_Type_Holding = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_Type_Holding.TagName, RLRLITERAL.Action_Skill_Type_Holding.TagDesc);
	GameplayTags.Action_Skill_Type_Casting = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_Type_Casting.TagName, RLRLITERAL.Action_Skill_Type_Casting.TagDesc);
	GameplayTags.Action_Skill_Type_Movility = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_Type_Movility.TagName, RLRLITERAL.Action_Skill_Type_Movility.TagDesc);
	GameplayTags.Action_Skill_Type_Targeting = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_Type_Targeting.TagName, RLRLITERAL.Action_Skill_Type_Targeting.TagDesc);
	GameplayTags.Action_Skill_Type_Chain = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_Type_Chain.TagName, RLRLITERAL.Action_Skill_Type_Chain.TagDesc);
	
	GameplayTags.Action_Skill_SwordsMan_SwordAura = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_SwordsMan_SwordAura.TagName, RLRLITERAL.Action_Skill_SwordsMan_SwordAura.TagDesc);
	GameplayTags.Action_Skill_MAGE_Meteor = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_Mage_Meteor.TagName, RLRLITERAL.Action_Skill_Mage_Meteor.TagDesc);
	GameplayTags.Action_Skill_MAGE_TrippleCircle = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Skill_Mage_TrippleCircle.TagName, RLRLITERAL.Action_Skill_Mage_TrippleCircle.TagDesc);


	//Action.Interaction
	GameplayTags.Action_Interaction = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Interaction.TagName, RLRLITERAL.Action_Interaction.TagDesc);
	GameplayTags.Action_Interaction_Dialogue = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Interaction_Dialogue.TagName, RLRLITERAL.Action_Interaction_Dialogue.TagDesc);
	GameplayTags.Action_Interaction_Logging = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_Interaction_Logging.TagName, RLRLITERAL.Action_Interaction_Logging.TagDesc);
	
	//Object
	GameplayTags.Object_State_Hittable = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Object_State_Hittable.TagName, RLRLITERAL.Object_State_Hittable.TagDesc);
	
	//Player
	GameplayTags.Player_State_Attacking = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Player_State_Attacking.TagName, RLRLITERAL.Player_State_Attacking.TagDesc);

	//Abnormal
	GameplayTags.Abnormal_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Abnormal_Stun.TagName, RLRLITERAL.Abnormal_Stun.TagDesc);
	GameplayTags.Abnormal_Bind = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Abnormal_Bind.TagName, RLRLITERAL.Abnormal_Bind.TagDesc);
	GameplayTags.Abnormal_Frozen = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Abnormal_Frozen.TagName, RLRLITERAL.Abnormal_Frozen.TagDesc);
	GameplayTags.Abnormal_Stiffen = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Abnormal_Stiffen.TagName, RLRLITERAL.Abnormal_Stiffen.TagDesc);
	GameplayTags.Abnormal_Provoke = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Abnormal_Provoke.TagName, RLRLITERAL.Abnormal_Provoke.TagDesc);
	GameplayTags.Abnormal_Electric = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Abnormal_Electric.TagName, RLRLITERAL.Abnormal_Electric.TagDesc);
	GameplayTags.Abnormal_Silence = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Abnormal_Silence.TagName, RLRLITERAL.Abnormal_Silence.TagDesc);
	GameplayTags.Abnormal_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Abnormal_Burn.TagName, RLRLITERAL.Abnormal_Burn.TagDesc);
	GameplayTags.Abnormal_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Abnormal_Poison.TagName, RLRLITERAL.Abnormal_Poison.TagDesc);
	GameplayTags.Abnormal_Slow = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Abnormal_Slow.TagName, RLRLITERAL.Abnormal_Slow.TagDesc);
	GameplayTags.Abnormal_Bleeding = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Abnormal_Bleeding.TagName, RLRLITERAL.Abnormal_Bleeding.TagDesc);


	/*
		Action Item Quick Slot
	*/

	GameplayTags.Action_ItemQuickSlot_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_ItemQuickSlot_1.TagName, RLRLITERAL.Action_ItemQuickSlot_1.TagDesc);
	GameplayTags.Action_ItemQuickSlot_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_ItemQuickSlot_2.TagName, RLRLITERAL.Action_ItemQuickSlot_2.TagDesc);
	GameplayTags.Action_ItemQuickSlot_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_ItemQuickSlot_3.TagName, RLRLITERAL.Action_ItemQuickSlot_3.TagDesc);
	GameplayTags.Action_ItemQuickSlot_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_ItemQuickSlot_4.TagName, RLRLITERAL.Action_ItemQuickSlot_4.TagDesc);
	GameplayTags.Action_ItemQuickSlot_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_ItemQuickSlot_5.TagName, RLRLITERAL.Action_ItemQuickSlot_5.TagDesc);
	GameplayTags.Action_ItemQuickSlot_6 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_ItemQuickSlot_6.TagName, RLRLITERAL.Action_ItemQuickSlot_6.TagDesc);
	GameplayTags.Action_ItemQuickSlot_7 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_ItemQuickSlot_7.TagName, RLRLITERAL.Action_ItemQuickSlot_7.TagDesc);
	GameplayTags.Action_ItemQuickSlot_8 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_ItemQuickSlot_8.TagName, RLRLITERAL.Action_ItemQuickSlot_8.TagDesc);
	GameplayTags.Action_ItemQuickSlot_9 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Action_ItemQuickSlot_9.TagName, RLRLITERAL.Action_ItemQuickSlot_9.TagDesc);
	
	/*
	Page
	*/
	GameplayTags.Page_InGame = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Page_InGame.TagName, RLRLITERAL.Page_InGame.TagDesc);
	GameplayTags.Page_Dialogue = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.Page_Dialogue.TagName, RLRLITERAL.Page_Dialogue.TagDesc);

	/*
		Action UI
	*/
	GameplayTags.UI_Character_StatusDisplay = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Character_StatusDisplay.TagName, RLRLITERAL.UI_Character_StatusDisplay.TagDesc);
	GameplayTags.UI_Character_Profile = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Character_Profile.TagName, RLRLITERAL.UI_Character_Profile.TagDesc);
	GameplayTags.UI_Character_Overhead = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Character_Overhead.TagName, RLRLITERAL.UI_Character_Overhead.TagDesc);

	GameplayTags.UI_Skill = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Skill.TagName, RLRLITERAL.UI_Skill.TagDesc);
	GameplayTags.UI_Skill_Upgrade = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Skill_Upgrade.TagName, RLRLITERAL.UI_Skill_Upgrade.TagDesc);
	GameplayTags.UI_Skill_DetailInfo = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Skill_DetailInfo.TagName, RLRLITERAL.UI_Skill_DetailInfo.TagDesc);

	GameplayTags.UI_Inventory = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Inventory.TagName, RLRLITERAL.UI_Inventory.TagDesc);
	GameplayTags.UI_ItemInfomation = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_ItemInformation.TagName, RLRLITERAL.UI_ItemInformation.TagDesc);
	GameplayTags.UI_NPCShop = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_NPCShop.TagName, RLRLITERAL.UI_NPCShop.TagDesc);
	GameplayTags.UI_NPCShop_Popup_Bundle = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_NPCShop_Popup_Bundle.TagName, RLRLITERAL.UI_NPCShop_Popup_Bundle.TagDesc);

	GameplayTags.UI_Chat = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Chat.TagName, RLRLITERAL.UI_Chat.TagDesc);
	GameplayTags.UI_Chat_Option = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Chat_Option.TagName, RLRLITERAL.UI_Chat_Option.TagDesc);
	
	GameplayTags.UI_Quest = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Quest.TagName, RLRLITERAL.UI_Quest.TagDesc);
	GameplayTags.UI_Quest_Dialogue = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Quest_Dialogue.TagName, RLRLITERAL.UI_Quest_Dialogue.TagDesc);
	
	GameplayTags.UI_Option = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Option.TagName, RLRLITERAL.UI_Option.TagDesc);
	GameplayTags.UI_Option_GraphicsOption = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Option_GraphicsOption.TagName, RLRLITERAL.UI_Option_GraphicsOption.TagDesc);
	GameplayTags.UI_Option_AudioOption = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Option_AudioOption.TagName, RLRLITERAL.UI_Option_AudioOption.TagDesc);
	GameplayTags.UI_Option_CommunityOption = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Option_CommunityOption.TagName, RLRLITERAL.UI_Option_CommunityOption.TagDesc);
	GameplayTags.UI_Option_GameplayOption = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Option_GameplayOption.TagName, RLRLITERAL.UI_Option_GameplayOption.TagDesc);
	GameplayTags.UI_Option_KeyOption = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Option_KeyOption.TagName, RLRLITERAL.UI_Option_KeyOption.TagDesc);

	GameplayTags.UI_Post = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Post.TagName, RLRLITERAL.UI_Post.TagDesc);
	GameplayTags.UI_Post_Alert = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Post_Alert.TagName, RLRLITERAL.UI_Post_Alert.TagDesc);

	
	GameplayTags.UI_Party = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Party.TagName, RLRLITERAL.UI_Party.TagDesc);
	GameplayTags.UI_Trade = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Trade.TagName, RLRLITERAL.UI_Trade.TagDesc);
	GameplayTags.UI_FriendList = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_FriendList.TagName, RLRLITERAL.UI_FriendList.TagDesc);
	GameplayTags.UI_Guild = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Guild.TagName, RLRLITERAL.UI_Guild.TagDesc);
	GameplayTags.UI_Report = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Report.TagName, RLRLITERAL.UI_Report.TagDesc);
	
	GameplayTags.UI_Popup_ItemCountMessageBox = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Popup_ItemCountMessageBox.TagName, RLRLITERAL.UI_Popup_ItemCountMessageBox.TagDesc);
	GameplayTags.UI_Popup_NotificationMessageBox = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Popup_NotificationMessageBox.TagName, RLRLITERAL.UI_Popup_NotificationMessageBox.TagDesc);
	GameplayTags.UI_Popup_ConfirmMessageBox = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Popup_ConfirmMessageBox.TagName, RLRLITERAL.UI_Popup_ConfirmMessageBox.TagDesc);
	
	GameplayTags.UI_OtherPlayer_Menu = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_OtherPlayer_Menu.TagName, RLRLITERAL.UI_OtherPlayer_Menu.TagDesc);
	GameplayTags.UI_OtherPlayer_OverHead = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_OtherPlayer_OverHead.TagName, RLRLITERAL.UI_OtherPlayer_OverHead.TagDesc);
	GameplayTags.UI_OtherPlayer_Profile = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_OtherPlayer_Profile.TagName, RLRLITERAL.UI_OtherPlayer_Profile.TagDesc);
	
	GameplayTags.UI_MiniMap = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_MiniMap.TagName, RLRLITERAL.UI_MiniMap.TagDesc);
	GameplayTags.UI_Badge = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Badge.TagName, RLRLITERAL.UI_Badge.TagDesc);
	
	GameplayTags.UI_Montster_OverHead = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Monster_OverHead.TagName, RLRLITERAL.UI_Monster_OverHead.TagDesc);
	GameplayTags.UI_TimerProgressBar = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_TimerProgressBar.TagName, RLRLITERAL.UI_TimerProgressBar.TagDesc);
	
	GameplayTags.UI_Menu = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Menu.TagName, RLRLITERAL.UI_Menu.TagDesc);
	
	GameplayTags.UI_Enhance = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.UI_Enhance.TagName, RLRLITERAL.UI_Enhance.TagDesc);

	/*
		Input
	*/

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_LMB.TagName, RLRLITERAL.InputTag_LMB.TagDesc);
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_RMB.TagName, RLRLITERAL.InputTag_RMB.TagDesc);
	GameplayTags.InputTag_Shift = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_Shift.TagName, RLRLITERAL.InputTag_Shift.TagDesc);
	GameplayTags.InputTag_Ctrl = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_Ctrl.TagName, RLRLITERAL.InputTag_Ctrl.TagDesc);
	GameplayTags.InputTag_ESC = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_ESC.TagName, RLRLITERAL.InputTag_ESC.TagDesc);


	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_1.TagName, RLRLITERAL.InputTag_1.TagDesc);
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_2.TagName, RLRLITERAL.InputTag_2.TagDesc);
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_3.TagName, RLRLITERAL.InputTag_3.TagDesc);
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_4.TagName, RLRLITERAL.InputTag_4.TagDesc);
	GameplayTags.InputTag_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_5.TagName, RLRLITERAL.InputTag_5.TagDesc);
	GameplayTags.InputTag_6 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_6.TagName, RLRLITERAL.InputTag_6.TagDesc);
	GameplayTags.InputTag_7 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_7.TagName, RLRLITERAL.InputTag_7.TagDesc);
	GameplayTags.InputTag_8 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_8.TagName, RLRLITERAL.InputTag_8.TagDesc);
	GameplayTags.InputTag_9 = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_9.TagName, RLRLITERAL.InputTag_9.TagDesc);
																			  
	GameplayTags.InputTag_A = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_A.TagName, RLRLITERAL.InputTag_A.TagDesc);
	GameplayTags.InputTag_B = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_B.TagName, RLRLITERAL.InputTag_B.TagDesc);
	GameplayTags.InputTag_C = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_C.TagName, RLRLITERAL.InputTag_C.TagDesc);
	GameplayTags.InputTag_D = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_D.TagName, RLRLITERAL.InputTag_D.TagDesc);
	GameplayTags.InputTag_E = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_E.TagName, RLRLITERAL.InputTag_E.TagDesc);
	GameplayTags.InputTag_F = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_F.TagName, RLRLITERAL.InputTag_F.TagDesc);
	GameplayTags.InputTag_G = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_G.TagName, RLRLITERAL.InputTag_G.TagDesc);
	GameplayTags.InputTag_H = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_H.TagName, RLRLITERAL.InputTag_H.TagDesc);
	GameplayTags.InputTag_I = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_I.TagName, RLRLITERAL.InputTag_I.TagDesc);
	GameplayTags.InputTag_J = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_J.TagName, RLRLITERAL.InputTag_J.TagDesc);
	GameplayTags.InputTag_K = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_K.TagName, RLRLITERAL.InputTag_K.TagDesc);
	GameplayTags.InputTag_L = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_L.TagName, RLRLITERAL.InputTag_L.TagDesc);
	GameplayTags.InputTag_M = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_M.TagName, RLRLITERAL.InputTag_M.TagDesc);
	GameplayTags.InputTag_N = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_N.TagName, RLRLITERAL.InputTag_N.TagDesc);
	GameplayTags.InputTag_O = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_O.TagName, RLRLITERAL.InputTag_O.TagDesc);
	GameplayTags.InputTag_P = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_P.TagName, RLRLITERAL.InputTag_P.TagDesc);
	GameplayTags.InputTag_Q = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_Q.TagName, RLRLITERAL.InputTag_Q.TagDesc);
	GameplayTags.InputTag_R = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_R.TagName, RLRLITERAL.InputTag_R.TagDesc);
	GameplayTags.InputTag_S = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_S.TagName, RLRLITERAL.InputTag_S.TagDesc);
	GameplayTags.InputTag_T = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_T.TagName, RLRLITERAL.InputTag_T.TagDesc);
	GameplayTags.InputTag_U = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_U.TagName, RLRLITERAL.InputTag_U.TagDesc);
	GameplayTags.InputTag_V = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_V.TagName, RLRLITERAL.InputTag_V.TagDesc);
	GameplayTags.InputTag_W = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_W.TagName, RLRLITERAL.InputTag_W.TagDesc);
	GameplayTags.InputTag_X = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_X.TagName, RLRLITERAL.InputTag_X.TagDesc);
	GameplayTags.InputTag_Y = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_Y.TagName, RLRLITERAL.InputTag_Y.TagDesc);
	GameplayTags.InputTag_Z = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_Z.TagName, RLRLITERAL.InputTag_Z.TagDesc);
	GameplayTags.InputTag_Alt_U = UGameplayTagsManager::Get().AddNativeGameplayTag(RLRLITERAL.InputTag_Alt_U.TagName, RLRLITERAL.InputTag_Alt_U.TagDesc);

}

const FGameplayTagContainer* FGameplayTagManager::GetSkillTags()
{
	if (SkillTags.Num() != 8)
	{
		SkillTags.Reset(8);

		SkillTags.AddTag(GameplayTags.Action_Skill_1);
		SkillTags.AddTag(GameplayTags.Action_Skill_2);
		SkillTags.AddTag(GameplayTags.Action_Skill_3);
		SkillTags.AddTag(GameplayTags.Action_Skill_4);
		SkillTags.AddTag(GameplayTags.Action_Skill_5);
		SkillTags.AddTag(GameplayTags.Action_Skill_6);
		SkillTags.AddTag(GameplayTags.Action_Skill_7);
		SkillTags.AddTag(GameplayTags.Action_Skill_8);
	}

	return &SkillTags;
}

FGameplayTag FGameplayTagManager::GetAbnormalTag(int AbnormalType)
{
	if (AbnormalTags.Num() != 11)
	{
		AbnormalTags.Reset(11);

		AbnormalTags.AddTag(GameplayTags.Abnormal_Stun);
		AbnormalTags.AddTag(GameplayTags.Abnormal_Bind);
		AbnormalTags.AddTag(GameplayTags.Abnormal_Frozen);
		AbnormalTags.AddTag(GameplayTags.Abnormal_Stiffen);
		AbnormalTags.AddTag(GameplayTags.Abnormal_Provoke);
		AbnormalTags.AddTag(GameplayTags.Abnormal_Electric);
		AbnormalTags.AddTag(GameplayTags.Abnormal_Silence);
		AbnormalTags.AddTag(GameplayTags.Abnormal_Burn);
		AbnormalTags.AddTag(GameplayTags.Abnormal_Poison);
		AbnormalTags.AddTag(GameplayTags.Abnormal_Slow);
		AbnormalTags.AddTag(GameplayTags.Abnormal_Bleeding);
	}

	return AbnormalTags.GetByIndex(AbnormalType);
}

const FGameplayTagContainer* FGameplayTagManager::GetItemTags()
{
	if (ItemTags.Num() != 9)
	{
		ItemTags.Reset(9);

		ItemTags.AddTag(GameplayTags.Action_ItemQuickSlot_1);
		ItemTags.AddTag(GameplayTags.Action_ItemQuickSlot_2);
		ItemTags.AddTag(GameplayTags.Action_ItemQuickSlot_3);
		ItemTags.AddTag(GameplayTags.Action_ItemQuickSlot_4);
		ItemTags.AddTag(GameplayTags.Action_ItemQuickSlot_5);
		ItemTags.AddTag(GameplayTags.Action_ItemQuickSlot_6);
		ItemTags.AddTag(GameplayTags.Action_ItemQuickSlot_7);
		ItemTags.AddTag(GameplayTags.Action_ItemQuickSlot_8);
		ItemTags.AddTag(GameplayTags.Action_ItemQuickSlot_9);
	}

	return &ItemTags;
}
