// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayTagManager.h"

FGameplayTagManager FGameplayTagManager::GameplayTags;

void FGameplayTagManager::Init()
{
	GameplayTags.Attributes_MainStat_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.MainStat.Health"), FString(TEXT("체력")));
	GameplayTags.Attributes_MainStat_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.MainStat.MaxHealth"), FString(TEXT("최대 체력")));
	
	//Action
	GameplayTags.Action_Default_Move = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Default.Move"), FString(TEXT("이동")));
	GameplayTags.Action_Default_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Default.Attack"), FString(TEXT("기본공격")));
	GameplayTags.Action_Default_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Default.Jump"), FString(TEXT("점프")));
	GameplayTags.Action_Default_PlayMontage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Default.PlayMontage"), FString(TEXT("애니메이션 실행")));
	
	GameplayTags.Action_Attack_HitCheck = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Attack.HitCheck"), FString(TEXT("공격판정")));
	
	//Skill
	GameplayTags.Action_Skill_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.1"), FString(TEXT("1스킬")));
	GameplayTags.Action_Skill_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.2"), FString(TEXT("2스킬")));
	GameplayTags.Action_Skill_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.3"), FString(TEXT("3스킬")));
	GameplayTags.Action_Skill_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.4"), FString(TEXT("4스킬")));
	GameplayTags.Action_Skill_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.5"), FString(TEXT("5스킬")));
	GameplayTags.Action_Skill_6 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.6"), FString(TEXT("6스킬")));
	GameplayTags.Action_Skill_7 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.7"), FString(TEXT("7스킬")));
	GameplayTags.Action_Skill_8 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.8"), FString(TEXT("8스킬")));
	
	//Skill.Type
	GameplayTags.Action_Skill_Type_Normal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Type.Normal"), FString(TEXT("Normal스킬")));
	GameplayTags.Action_Skill_Type_Area = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Type.Area"), FString(TEXT("Area스킬")));
	GameplayTags.Action_Skill_Type_Holding = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Type.Holding"), FString(TEXT("Holding스킬")));
	GameplayTags.Action_Skill_Type_Casting = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Type.Casting"), FString(TEXT("Casting스킬")));
	GameplayTags.Action_Skill_Type_Movility = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Type.Movility"), FString(TEXT("Movility스킬")));
	GameplayTags.Action_Skill_Type_Targeting = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Type.Targeting"), FString(TEXT("Targeting스킬")));
	GameplayTags.Action_Skill_Type_Chain = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.Type.Chain"), FString(TEXT("Chain스킬")));


	//Skill.Anim
	GameplayTags.Action_Skill_1_Anim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.1.Anim"), FString(TEXT("1애니메이션")));
	GameplayTags.Action_Skill_2_Anim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.2.Anim"), FString(TEXT("2애니메이션")));
	GameplayTags.Action_Skill_3_Anim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.3.Anim"), FString(TEXT("3애니메이션")));
	GameplayTags.Action_Skill_4_Anim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.4.Anim"), FString(TEXT("4애니메이션")));
	GameplayTags.Action_Skill_5_Anim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.5.Anim"), FString(TEXT("5애니메이션")));
	GameplayTags.Action_Skill_6_Anim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.6.Anim"), FString(TEXT("6애니메이션")));
	GameplayTags.Action_Skill_7_Anim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.7.Anim"), FString(TEXT("7애니메이션")));
	GameplayTags.Action_Skill_8_Anim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Skill.8.Anim"), FString(TEXT("8애니메이션")));
	
	//Action.Interaction
	GameplayTags.Action_Interaction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Interaction"), FString(TEXT("상호작용")));
	GameplayTags.Action_Interaction_Dialogue = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Interaction.Dialogue"), FString(TEXT("대화")));
	GameplayTags.Action_Interaction_Logging = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.Interaction.Logging"), FString(TEXT("벌목")));
	
	//Object
	GameplayTags.Object_State_Hittable = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Object.State.Hittable"), FString(TEXT("공격가능")));
	
	//Player
	GameplayTags.Player_State_Attacking = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.State.Attacking"), FString(TEXT("공격중")));

	//Abnormal
	GameplayTags.Abnormal_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abnormal.Stun"), FString(TEXT("기절")));
	GameplayTags.Abnormal_Bind = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abnormal.Bind"), FString(TEXT("속박")));
	GameplayTags.Abnormal_Frozen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abnormal.Frozen"), FString(TEXT("빙결")));
	GameplayTags.Abnormal_Stiffen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abnormal.Stiffen"), FString(TEXT("경직")));
	GameplayTags.Abnormal_Provoke = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abnormal.Provoke"), FString(TEXT("도발")));
	GameplayTags.Abnormal_Electric = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abnormal.Electric"), FString(TEXT("감전")));
	GameplayTags.Abnormal_Silence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abnormal.Silence"), FString(TEXT("침묵")));
	GameplayTags.Abnormal_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abnormal.Burn"), FString(TEXT("화상")));
	GameplayTags.Abnormal_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abnormal.Poison"), FString(TEXT("중독")));
	GameplayTags.Abnormal_Slow = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abnormal.Slow"), FString(TEXT("슬로우")));
	GameplayTags.Abnormal_Bleeding = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abnormal.Bleeding"), FString(TEXT("출혈")));


	/*
		Action Item Quick Slot
	*/

	GameplayTags.Action_ItemQuickSlot_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.ItemQuickSlot.1"), FString(TEXT("아이템 퀵 슬롯 1")));
	GameplayTags.Action_ItemQuickSlot_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.ItemQuickSlot.2"), FString(TEXT("아이템 퀵 슬롯 2")));
	GameplayTags.Action_ItemQuickSlot_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.ItemQuickSlot.3"), FString(TEXT("아이템 퀵 슬롯 3")));
	GameplayTags.Action_ItemQuickSlot_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.ItemQuickSlot.4"), FString(TEXT("아이템 퀵 슬롯 4")));
	GameplayTags.Action_ItemQuickSlot_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.ItemQuickSlot.5"), FString(TEXT("아이템 퀵 슬롯 5")));
	GameplayTags.Action_ItemQuickSlot_6 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.ItemQuickSlot.6"), FString(TEXT("아이템 퀵 슬롯 6")));
	GameplayTags.Action_ItemQuickSlot_7 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.ItemQuickSlot.7"), FString(TEXT("아이템 퀵 슬롯 7")));
	GameplayTags.Action_ItemQuickSlot_8 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.ItemQuickSlot.8"), FString(TEXT("아이템 퀵 슬롯 8")));
	GameplayTags.Action_ItemQuickSlot_9 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.ItemQuickSlot.9"), FString(TEXT("아이템 퀵 슬롯 9")));
	/*
		Action UI
	*/

	GameplayTags.UI_Inventory = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Inventory"), FString(TEXT("인벤토라")));
	GameplayTags.UI_ItemInfomation = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.ItemInfomation"), FString(TEXT("아이템 정보창")));
	GameplayTags.UI_CharacterStatus = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.CharacterStatus"), FString(TEXT("캐릭터창")));
	GameplayTags.UI_KeyOption = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.KeyOption"), FString(TEXT("키 옵션")));
	GameplayTags.UI_Skill = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Skill"), FString(TEXT("스킬창")));
	GameplayTags.UI_Quest = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Quest"), FString(TEXT("퀘스트 정보창")));
	GameplayTags.UI_Chat = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Chat"), FString(TEXT("채팅창")));
	GameplayTags.UI_ChatOption = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.ChatOption"), FString(TEXT("채팅 옵션창")));
	GameplayTags.UI_Party = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Party"), FString(TEXT("파티창")));

	GameplayTags.UI_Close = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Close"), FString(TEXT("특정 키 누르면 제일 앞에 있는 UI 닫기")));
	GameplayTags.UI_SkillUpgrade = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.UI_SkillUpgrade"), FString(TEXT("스킬 업그레이드")));


	GameplayTags.UI_Post = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Post"), FString(TEXT("우편 시스템")));
	GameplayTags.UI_OtherPlayerMenu = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.OtherPlayerMenu"), FString(TEXT("플레이어 메뉴")));
	GameplayTags.UI_OtherPlayerStatus = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.OtherPlayerStatus"), FString(TEXT("타 플레이어 상태창")));
	GameplayTags.UI_Report = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Report"), FString(TEXT("신고")));





	/*
		Input
	*/

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.LMB"), FString(TEXT("마우스 왼쪽 버튼")));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.RMB"), FString(TEXT("마우스 오른쪽 버튼")));
	GameplayTags.InputTag_Shift = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Shift"), FString(TEXT("Shift")));
	GameplayTags.InputTag_Ctrl = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Ctrl"), FString(TEXT("Ctrl")));
	GameplayTags.InputTag_ESC = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.ESC"), FString(TEXT("ESC")));


	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.1"), FString(TEXT("1")));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.2"), FString(TEXT("2")));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.3"), FString(TEXT("3")));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.4"), FString(TEXT("4")));
	GameplayTags.InputTag_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.5"), FString(TEXT("5")));
	GameplayTags.InputTag_6 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.6"), FString(TEXT("6")));
	GameplayTags.InputTag_7 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.7"), FString(TEXT("7")));
	GameplayTags.InputTag_8 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.8"), FString(TEXT("8")));
	GameplayTags.InputTag_9 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.9"), FString(TEXT("9")));

	GameplayTags.InputTag_A = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.A"), FString(TEXT("KeyBoard A")));
	GameplayTags.InputTag_B = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.B"), FString(TEXT("KeyBoard B")));
	GameplayTags.InputTag_C = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.C"), FString(TEXT("KeyBoard C")));
	GameplayTags.InputTag_D = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.D"), FString(TEXT("KeyBoard D")));
	GameplayTags.InputTag_E = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.E"), FString(TEXT("KeyBoard E")));
	GameplayTags.InputTag_F = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.F"), FString(TEXT("KeyBoard F")));
	GameplayTags.InputTag_G = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.G"), FString(TEXT("KeyBoard G")));
	GameplayTags.InputTag_H = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.H"), FString(TEXT("KeyBoard H")));
	GameplayTags.InputTag_I = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.I"), FString(TEXT("KeyBoard I")));
	GameplayTags.InputTag_J = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.J"), FString(TEXT("KeyBoard J")));
	GameplayTags.InputTag_K = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.K"), FString(TEXT("KeyBoard K")));
	GameplayTags.InputTag_L = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.L"), FString(TEXT("KeyBoard L")));
	GameplayTags.InputTag_M = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.M"), FString(TEXT("KeyBoard M")));
	GameplayTags.InputTag_N = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.N"), FString(TEXT("KeyBoard N")));
	GameplayTags.InputTag_O = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.O"), FString(TEXT("KeyBoard O")));
	GameplayTags.InputTag_P = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.P"), FString(TEXT("KeyBoard P")));
	GameplayTags.InputTag_Q = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Q"), FString(TEXT("KeyBoard Q")));
	GameplayTags.InputTag_R = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.R"), FString(TEXT("KeyBoard R")));
	GameplayTags.InputTag_S = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.S"), FString(TEXT("KeyBoard S")));
	GameplayTags.InputTag_T = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.T"), FString(TEXT("KeyBoard T")));
	GameplayTags.InputTag_U = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.U"), FString(TEXT("KeyBoard U")));
	GameplayTags.InputTag_V = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.V"), FString(TEXT("KeyBoard V")));
	GameplayTags.InputTag_W = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.W"), FString(TEXT("KeyBoard W")));
	GameplayTags.InputTag_X = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.X"), FString(TEXT("KeyBoard X")));
	GameplayTags.InputTag_Y = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Y"), FString(TEXT("KeyBoard Y")));
	GameplayTags.InputTag_Z = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Z"), FString(TEXT("KeyBoard Z")));


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

const FGameplayTagContainer* FGameplayTagManager::GetSkillAnimTags()
{
	if (SkillAnimTags.Num() != 8)
	{
		SkillAnimTags.Reset(8);

		SkillAnimTags.AddTag(GameplayTags.Action_Skill_1_Anim);
		SkillAnimTags.AddTag(GameplayTags.Action_Skill_2_Anim);
		SkillAnimTags.AddTag(GameplayTags.Action_Skill_3_Anim);
		SkillAnimTags.AddTag(GameplayTags.Action_Skill_4_Anim);
		SkillAnimTags.AddTag(GameplayTags.Action_Skill_5_Anim);
		SkillAnimTags.AddTag(GameplayTags.Action_Skill_6_Anim);
		SkillAnimTags.AddTag(GameplayTags.Action_Skill_7_Anim);
		SkillAnimTags.AddTag(GameplayTags.Action_Skill_8_Anim);
	}

	return &SkillAnimTags;
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
