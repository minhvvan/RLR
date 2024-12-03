// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/LiteralManager.h"

LiteralManager LiteralManager::LiteralMessages;

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


    /* Player Commands */
    LiteralMessages.Playercommands_InputConfigNull = TEXT("InputConfig is nullptr. 값을 할당해주세요.");
    LiteralMessages.Playercommands_URLREnhancedInputComponentNull = TEXT("URLREnhancedInputComponent  is nullptr.");

    /* UItemCountMessageBox */
    LiteralMessages.ItemCountMsg_InputQuantity = TEXT("갯수 입력");
}