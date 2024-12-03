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
	FString TradeUI_Nickname;
	FString TradeUI_UserSeq;
	FString TradeUI_From;
	FString TradeUI_Gold;
	FString TradeUI_TradeRequest;
	FString TradeUI_TradeSuccess;
	FString TradeUI_TradeCanceled;
	FString TradeUI_TradeDenied;
	FString TradeUI_InputExceedsCurrentQuantity;
	FName TradeUI_OnClickedInventorySlot;
	FName TradeUI_OnClickedAcceptButton;
	FName TradeUI_OnClickedCancelButton;
	FName TradeUI_OnConfirmItemCountMessageBox;
	FName TradeUI_OnCancelItemCountMessageBox;
	/* EnhanceOverlayUI */
	FString Enhance_EnhancePrompt;
	FName Enhance_OnClickedAcceptButton;
	FName Enhance_OnClickedCancelButton;
	/* PostOverlayUI */
	FString PostUI_ReceivedPost;
	FString PostUI_SentPost;
	FString PostUI_RemovePrompt;
	FString PostUI_ExitPrompt;
	FName PostUI_OnClickedDeletePostsConfirmButton;
	FName PostUI_OnClickedCancelButton;
	FName PostUI_OnClickedAcceptButtonWhileWriting;

	/* Player Commands */
	FString Playercommands_InputConfigNull;
	FString Playercommands_URLREnhancedInputComponentNull;
	/* UItemCountMessageBox */
	FString ItemCountMsg_InputQuantity;

private:
	static LiteralManager LiteralMessages;
};