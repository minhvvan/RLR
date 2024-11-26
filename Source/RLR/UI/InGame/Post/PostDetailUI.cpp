// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostDetailUI.h"
#include "UI/InGame/Post/PostItemSlot.h"

#include "GameManager/GameManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/UIManager.h"

#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UPostDetailUI::NativeConstruct()
{
    if (RemovePostButton)
    {
        RemovePostButton->OnClicked.AddUniqueDynamic(this, &UPostDetailUI::OpenRemovePostConfirmBox);
    }
    if (AcceptAllButton)
    {
        AcceptAllButton->OnClicked.AddUniqueDynamic(this, &UPostDetailUI::OnAcceptButtonClicked);
    }
    if (ReplyButton)
    {
        ReplyButton->OnClicked.AddUniqueDynamic(this, &UPostDetailUI::OnReplyButtonClicked);
    }
}

void UPostDetailUI::UpdatePostDetails(const FPostResult& Post, bool bIsSentTab)
{
    if (IdText)
    {
        IdText->SetText(FText::FromString(bIsSentTab ? Post.ReceiverName : Post.SenderName));
    }
    if (PostTitleText)
    {
        PostTitleText->SetText(FText::FromString(Post.Title));
    }
    if (PostContentText)
    {
        PostContentText->SetText(FText::FromString(Post.Content));
    }
    if (PostSlotGridPanel)
    {
        int32 SlotIndex = 0;

        for (const auto& ItemValuePair : Post.ItemValues)
        {
            int64 ItemId = ItemValuePair.Key;
            int32 ItemCount = ItemValuePair.Value;

            for (int32 Count = 0; Count < ItemCount; Count++)
            {
                // 슬롯 가져오기
                UPostItemSlot* ItemSlot = Cast<UPostItemSlot>(PostSlotGridPanel->GetChildAt(SlotIndex));
                if (ItemSlot)
                {
                    // 아이템 데이터 설정
                    ItemSlot->SetSlot(ItemId);
                }

                // 다음 슬롯으로 이동
                SlotIndex++;
            }
        }
    }
    if (TotalMoney)
    {
        TotalMoney->SetText(FText::AsNumber(Post.TotalMoney));
    }
    if (ReadStatus)
    {
        ReadStatus->SetText(FText::FromString(bIsSentTab ? "" : "Read"));
    }

    SelectedPost = Post;
}

void UPostDetailUI::ClearPostSlots()
{
    if (PostSlotGridPanel)
    {
        TArray<UWidget*> Slots = PostSlotGridPanel->GetAllChildren();
        for (UWidget* slot : Slots)
        {
            if (UPostItemSlot* ItemSlot = Cast<UPostItemSlot>(slot))
            {
                ItemSlot->Clear();
            }
        }
    }
}

void UPostDetailUI::SetTabNameText(FText TabName)
{
    TabNameText->SetText(TabName);
}

void UPostDetailUI::OpenRemovePostConfirmBox()
{
    OnRemoveOnePostButtonClicked.Broadcast();
}

/* 우편 답신 기능 */
void UPostDetailUI::OnReplyButtonClicked()
{
    /* 우편 보낸 사람 ID 전달 */
    OnPostReplyButtonClicked.Broadcast(IdText->GetText());
}
/* 우편 첨부물 받기 */
void UPostDetailUI::OnAcceptButtonClicked()
{
    /*
        인벤토리에 아이템 추가, 재화 추가
    */
    GameInstance->GetNetworkManager()->SendPostReceivedRequest(SelectedPost);
}