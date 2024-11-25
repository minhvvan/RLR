// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostTabWidget.h"
#include "UI/InGame/Post/PostButtonUI.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Popup/ConfirmMessageBox.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/MultiLineEditableText.h"
#include "Components/SizeBox.h"
#include "Components/GridPanel.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/PostalManager.h"
#include "GameManager/NetworkManager.h"

#include "Structs/UtilStructs.h"


void UPostTabWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (RemovePostButton)
    {
        RemovePostButton->OnClicked.AddUniqueDynamic(this, &UPostTabWidget::OpenRemovePostConfirmBox);
    }
    if (AcceptAllButton)
    {
        AcceptAllButton->OnClicked.AddUniqueDynamic(this, &UPostTabWidget::OnAcceptButtonClicked);
    }
    if (SelectAllCheckBox)
    {
        SelectAllCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UPostTabWidget::OnSelectAllCheckBoxChanged);
    }
    if (PostPageButton)
    {
        PostPageButton->OnClicked.AddUniqueDynamic(this, &UPostTabWidget::SwitchPostPage);
    }
    if (PrevPageButton)
    {
        PrevPageButton->OnClicked.AddUniqueDynamic(this, &UPostTabWidget::SwitchPrevPage);
    }
    if (ReplyButton)
    {
        ReplyButton->OnClicked.AddUniqueDynamic(this, &UPostTabWidget::OnReplyButtonClicked);
    }

    /* 우편 여러개 선택 후 첨부물 받기 or 우편 삭제 버튼 클릭 */
    if (ReceiveAttachmentsButton)
    {
        ReceiveAttachmentsButton->OnClicked.AddUniqueDynamic(this, &UPostTabWidget::OnReceiveAllAttachmentsButtonClicked);
    }
    if (RemoveSelectedButton)
    {
        RemoveSelectedButton->OnClicked.AddUniqueDynamic(this, &UPostTabWidget::OpenRemovePostsConfirmBox);
    }
}

void UPostTabWidget::OnSelectAllCheckBoxChanged(bool bIsChecked)
{
    UWidget* ActiveWidget = PageSwitcher->GetActiveWidget();
    if (UVerticalBox* ActiveVerticalBox = Cast<UVerticalBox>(ActiveWidget))
    {
        if (ActiveVerticalBox)
        {
            TArray<UWidget*> PostButtonsWidgets = ActiveVerticalBox->GetAllChildren();

            for (UWidget* Widget : PostButtonsWidgets)
            {
                // PostButtonUI인지 확인
                if (UPostButtonUI* PostButton = Cast<UPostButtonUI>(Widget))
                {
                    if (PostButton->SelectCheckBox)
                    {
                        PostButton->SelectCheckBox->SetIsChecked(bIsChecked);
                    }
                }
            }
        }
    }
}

void UPostTabWidget::UpdatePostList(const TArray<FPostResult>& Posts, bool bIsSent)
{
    bIsSentTab = bIsSent;
    ClearPostList();

    for (const FPostResult& Post : Posts)
    {
        AddPostButton(Post, bIsSentTab);
    }

    if (!bIsSentTab)
    {
        TArray<FPostResult> DeletionList = GameInstance->GetPostalManager()->GetAndClearPostDeletionList(false);
        for (const FPostResult& PostData : DeletionList)
        {
            /* TODO : 현재 postId가 1로 통일이라 우편 순서대로 삭제되는 중 나중에 고쳐질 것임*/
            //RemovePost(PostData);
        }
    }
}

void UPostTabWidget::RemovePost(FPostResult Post)
{
    AsyncTask(ENamedThreads::GameThread, [this, Post]()
        {
            if (PostButtons.Contains(Post.Title))
            {
                UPostButtonUI* PostButton = PostButtons[Post.Title];

                UWidget* ActiveWidget = PageSwitcher->GetActiveWidget();
                if (UVerticalBox* ActiveVerticalBox = Cast<UVerticalBox>(ActiveWidget))
                {
                    ActiveVerticalBox->RemoveChild(PostButton);

                    /* 현재 페이지에 존재하는 우편이 없다면 */
                    if (ActiveVerticalBox->GetChildrenCount() < 1)
                    {
                        PageSwitcher->RemoveChild(ActiveWidget);
                        int32 TotalPage = PageSwitcher->GetNumWidgets() > 0 ? PageSwitcher->GetNumWidgets() : 1;

                        FText PageText = FText::Format(
                            FText::FromString(TEXT("{0}/{1}")),
                            FText::AsNumber(PageSwitcher->GetActiveWidgetIndex() + 1),
                            FText::AsNumber(TotalPage)
                        );
                        CurrentPageText->SetText(PageText);
                    }
                }
                PostButton->SetButtonState(false);
            }

            /* TODO : 서버에 삭제된 우편을 제외한 post목록을 전달하여 목록 새로고침하기 */
            PostButtons.Remove(SelectedPost.Title);
            SelectedPost = FPostResult();
            SelectedPostButton = nullptr;
            UpdatePostDetails(SelectedPost);
            GameInstance->GetNetworkManager()->SendPostRemoveRequest(Post);
        });
}

void UPostTabWidget::OnAcceptButtonClicked()
{
    /*
		인벤토리에 아이템 추가, 재화 추가
		GameInstance->GetNetWorkManager()->SendPostReceivedRequest(Post);
    */
    GameInstance->GetNetworkManager()->SendPostReceivedRequest(SelectedPost);
}

void UPostTabWidget::OnRemoveButtonClicked()
{
    RemovePost(SelectedPost);
}

void UPostTabWidget::OnReceiveAllAttachmentsButtonClicked()
{
    UVerticalBox* ActiveVerticalBox = Cast<UVerticalBox>(PageSwitcher->GetActiveWidget());

    TArray<UWidget*> PostButtonsWidgets = ActiveVerticalBox->GetAllChildren();

    for (UWidget* Widget : PostButtonsWidgets)
    {
        if (UPostButtonUI* PostButton = Cast<UPostButtonUI>(Widget))
        {
            if (PostButton->SelectCheckBox && PostButton->SelectCheckBox->IsChecked())
            {
                FPostResult Post = PostButton->GetPostInfo();

                // 첨부물 받기 로직
                GameInstance->GetNetworkManager()->SendPostReceivedRequest(Post);
            }
        }
    }
}

void UPostTabWidget::OnRemoveSelectedButtonClicked()
{
    UWidget* ActiveWidget = PageSwitcher->GetActiveWidget();
    if (UVerticalBox* ActiveVerticalBox = Cast<UVerticalBox>(ActiveWidget))
    {
        TArray<UWidget*> PostButtonsWidgets = ActiveVerticalBox->GetAllChildren();

        for (UWidget* Widget : PostButtonsWidgets)
        {
            if (UPostButtonUI* PostButton = Cast<UPostButtonUI>(Widget))
            {
                if (PostButton->SelectCheckBox && PostButton->SelectCheckBox->IsChecked())
                {
                    FPostResult Post = PostButton->GetPostInfo();

                    // 삭제 로직
                    RemovePost(Post);
                }
            }
        }
    }
}

void UPostTabWidget::ClearPostList()
{
    if (!IsInGameThread())
    {
        AsyncTask(ENamedThreads::GameThread, [this]()
            {
                ClearPostList();
            });
        return;
    }

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

    if (PageSwitcher)
    {
        TArray<UWidget*> Slots = PageSwitcher->GetAllChildren();
        for (UWidget* slot : Slots)
        {
            if (UVerticalBox* VerticalBox = Cast<UVerticalBox>(slot))
            {
                PageSwitcher->RemoveChild(VerticalBox);
            }
        }
    }

    VerticalBoxes.Empty();
    PostButtons.Empty();
}

void UPostTabWidget::CreateNewPage()
{
    // 새 VerticalBox 생성
    CurrentVerticalBox = NewObject<UVerticalBox>(this);
    if (!CurrentVerticalBox || !PageSwitcher)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create new page."));
        return;
    }

    if (!VerticalBoxes.Contains(CurrentVerticalBox))
    {
        VerticalBoxes.Add(CurrentVerticalBox);
    }

    // 새 페이지를 WidgetSwitcher에 추가
    PageSwitcher->AddChild(CurrentVerticalBox);
    PageSwitcher->SetActiveWidget(CurrentVerticalBox);

    int32 CurrentIndex = PageSwitcher->GetActiveWidgetIndex();
    int32 TotalPages = PageSwitcher->GetNumWidgets();
    
    FText PageText = FText::Format(
        FText::FromString(TEXT("{0}/{1}")),
        FText::AsNumber(CurrentIndex + 1),
        FText::AsNumber(TotalPages)
    );

    CurrentPageText->SetText(PageText);
}

void UPostTabWidget::AddPostButton(const FPostResult& Post, bool bIsSent)
{
    AsyncTask(ENamedThreads::GameThread, [this, Post, bIsSent]()
        {
            if (PostButtonUIClass)
            {
                UPostButtonUI* PostButton = CreateWidget<UPostButtonUI>(this, PostButtonUIClass);
                if (PostButton)
                {
                    PostButton->SetPostInfo(Post, bIsSent);
                    PostButton->OnPostButtonClick.AddUObject(this, &UPostTabWidget::OnPostButtonClicked);
                    
                    if (PageSwitcher->GetChildrenCount() == 0 || VerticalBoxes.Last()->GetChildrenCount() >= MaxButtonsPerPage)
                        {
                            CreateNewPage();
                        }
                    VerticalBoxes.Last()->AddChild(PostButton);
                    PostButtons.Add(Post.Title, PostButton);
                }
            }
        });
}

void UPostTabWidget::UpdatePostDetails(const FPostResult& Post)
{
    SelectedPost = Post;
    
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
}

void UPostTabWidget::OnPostButtonClicked(const FPostResult& ClickedPost, UPostButtonUI* PostButtonUI)
{
    /* TODO : 현재 서버에서 postid를 1로 고정하고 있음, 나중에는 postid가 고유 값을 가질 것이기 때문에 이렇게 함 */
    // if(ClickedPost.PostId == SelectedPost.PostId) return;

    /* 이건 postid가 고유 값을 갖기 전까지 사용할 임시코드임, 눌렀던 버튼 또 눌렀을 때 */
    if(SelectedPost.PostId == ClickedPost.PostId && SelectedPost.ReceiverName == ClickedPost.ReceiverName && (SelectedPost.Title == ClickedPost.Title && SelectedPost.Content == ClickedPost.Content)) 
    {
        if (!SelectedPost.Title.IsEmpty() && PostButtons.Contains(SelectedPost.Title))
        {
            SelectedPostButton->SetButtonState(false);
            PostList_SizeBox->SetVisibility(ESlateVisibility::Hidden);
            SelectedPostButton = nullptr;
            SelectedPost = FPostResult();
            UpdatePostDetails(SelectedPost);
        }
        else
        {
            SelectedPostButton->SetButtonState(false);
            PostList_SizeBox->SetVisibility(ESlateVisibility::Hidden);
            SelectedPostButton = nullptr;
            SelectedPost = FPostResult();
            UpdatePostDetails(SelectedPost);
        }
        return;
    }
    PostButtonUI->SetButtonState(true);
    if (!SelectedPost.Title.IsEmpty() && PostButtons.Contains(SelectedPost.Title))
    {
        SelectedPostButton->SetButtonState(false);
    }
    PostList_SizeBox->SetVisibility(ESlateVisibility::Visible);
    UpdatePostDetails(ClickedPost);
    SelectedPostButton = PostButtonUI;
}

void UPostTabWidget::SwitchPostPage()
{
    if (!PageSwitcher)
        return;

    int32 CurrentIndex = PageSwitcher->GetActiveWidgetIndex();
    int32 TotalPages = PageSwitcher->GetNumWidgets();

    if (CurrentIndex < TotalPages - 1)
    {
        PageSwitcher->SetActiveWidgetIndex(CurrentIndex + 1);
        
        FText PageText = FText::Format(
            FText::FromString(TEXT("{0}/{1}")),
            FText::AsNumber(PageSwitcher->GetActiveWidgetIndex() + 1),
            FText::AsNumber(TotalPages)
        );

        CurrentPageText->SetText(PageText);
    }
}

void UPostTabWidget::SwitchPrevPage()
{
    if (!PageSwitcher)
        return;

    int32 CurrentIndex = PageSwitcher->GetActiveWidgetIndex();
    int32 TotalPages = PageSwitcher->GetNumWidgets();

    if(TotalPages == 0) TotalPages = 1;
    if (CurrentIndex > 0)
    {
        PageSwitcher->SetActiveWidgetIndex(CurrentIndex - 1);
    }

    FText PageText = FText::Format(
        FText::FromString(TEXT("{0}/{1}")),
        FText::AsNumber(PageSwitcher->GetActiveWidgetIndex() + 1),
        FText::AsNumber(TotalPages)
    );

    CurrentPageText->SetText(PageText);
}

void UPostTabWidget::OpenRemovePostsConfirmBox()
{
    /* 삭제 팝업 띄우기 -> Yes면 아래 내용 복붙 */
    OnRemovePostsButtonClicked.Broadcast();
}

void UPostTabWidget::OpenRemovePostConfirmBox()
{
    OnRemoveOnePostButtonClicked.Broadcast();
}

/* 우편 답신 기능 */
void UPostTabWidget::OnReplyButtonClicked()
{
    /* 우편 보낸 사람 ID 전달 */
    OnPostReplyButtonClicked.Broadcast(IdText->GetText());
}