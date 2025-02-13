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
    bSentTab = bIsSentTab;
    if (bSentTab)
    {
        AcceptAllButton->SetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        AcceptAllButton->SetVisibility(ESlateVisibility::Visible);
        if (Post.IsReceived)
        {
            AcceptAllButton->SetIsEnabled(false);
        }
        else
        {
            AcceptAllButton->SetIsEnabled(true);
        }
    }

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

    ClearPostSlots();

    if (PostSlotGridPanel)
    {
        int32 SlotIndex = 0;

        // 최대 10개의 슬롯을 순회
        for (int32 i = 0; i < 10; i++)
        {
            UPostItemSlot* ItemSlot = nullptr;

            // 기존 슬롯이 있는 경우 가져오고, 없으면 새로 생성
            if (PostSlotGridPanel->GetChildrenCount() > i)
            {
                ItemSlot = Cast<UPostItemSlot>(PostSlotGridPanel->GetChildAt(i));
            }
            else
            {
                ItemSlot = CreateWidget<UPostItemSlot>(this, UPostItemSlot::StaticClass());
                if (ItemSlot)
                {
                    PostSlotGridPanel->AddChildToGrid(ItemSlot, i / 5, i % 5);
                }
            }

            if (ItemSlot)
            {
                // Post.ItemList에 있는 경우 슬롯에 설정
                if (SlotIndex < Post.ItemList.Num())
                {
                    const FItemData& ItemData = Post.ItemList[SlotIndex];

                    ItemSlot->SetItemData(ItemData);
                    ItemSlot->SetItemAmountShow(true);

                    // 아이템 이미지 설정
                    UTexture2D* ItemImage = ItemSlot->GetItemResourceData().ItemImage;
                    if (ItemImage)
                    {
                        ItemSlot->SetSlotImage(ItemImage);
                    }
                    else
                    {
                        UTexture2D* DefaultImage = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UI/DefaultItemIcon"));
                        ItemSlot->SetSlotImage(DefaultImage);
                    }

                    SlotIndex++;
                }
                else
                {
                    // 아이템이 없는 슬롯은 빈 슬롯으로 유지
                    UTexture2D* EmptySlotImage = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UI/EmptySlotIcon"));
                    ItemSlot->SetSlotImage(EmptySlotImage);
                }
            }
        }
    }

    if (TotalMoney)
    {
        TotalMoney->SetText(FText::AsNumber(Post.TotalMoney));
    }
    if (ReadStatus)
    {
        ReadStatus->SetText(FText::FromString(bIsSentTab ? RLRLITERAL.ReadStatusNotExist : RLRLITERAL.HasReadStatus));
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