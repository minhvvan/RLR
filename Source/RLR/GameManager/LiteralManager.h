// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Game내에서 사용하는 모든 문자열을 관리하는 클래스
 */
 #define RLRLITERAL LiteralManager::Get()

class RLR_API LiteralManager
{
public:
	static const LiteralManager& Get() { return LiteralMessages; }
	static void Init();

public:
	/* TradeUI */
	const TCHAR* TradeUI_Nickname;
	const TCHAR* TradeUI_UserSeq;
	const TCHAR* TradeUI_From;
	const TCHAR* TradeUI_Gold;
	const TCHAR* TradeUI_TradeRequest;
	const TCHAR* TradeUI_TradeSuccess;
	const TCHAR* TradeUI_TradeCanceled;
	const TCHAR* TradeUI_TradeDenied;
	const TCHAR* TradeUI_InputExceedsCurrentQuantity;
	FName TradeUI_OnClickedInventorySlot;
	FName TradeUI_OnClickedAcceptButton;
	FName TradeUI_OnClickedCancelButton;
	FName TradeUI_OnConfirmItemCountMessageBox;
	FName TradeUI_OnCancelItemCountMessageBox;
	/* EnhanceOverlayUI */
	const TCHAR* Enhance_EnhancePrompt;
	FName Enhance_OnClickedAcceptButton;
	FName Enhance_OnClickedCancelButton;
	/* PostOverlayUI */
	const TCHAR* PostUI_ReceivedPost;
	const TCHAR* PostUI_SentPost;
	const TCHAR* PostUI_RemovePrompt;
	const TCHAR* PostUI_ExitPrompt;
	FName PostUI_OnClickedDeletePostsConfirmButton;
	FName PostUI_OnClickedCancelButton;
	FName PostUI_OnClickedAcceptButtonWhileWriting;

	/* Player Commands */
	const TCHAR* Playercommands_InputConfigNull;
	const TCHAR* Playercommands_URLREnhancedInputComponentNull;
	/* UItemCountMessageBox */
	const TCHAR* ItemCountMsg_InputQuantity;

private:
	static LiteralManager LiteralMessages;
};