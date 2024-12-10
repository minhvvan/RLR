// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Post/PostTabWidget.h"
#include "UI/InGame/Post/PostButtonUI.h"
#include "UI/InGame/Post/PostOverlayUI.h"
#include "UI/InGame/Post/PostItemSlot.h"
#include "UI/InGame/Post/PostDetailUI.h"
#include "UI/InGame/Popup/ConfirmMessageBox.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/MultiLineEditableText.h"
#include "Components/VerticalBoxSlot.h"
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

    /* 날짜 파싱 및 최신 날짜가 먼저 오도록 정렬 */
    TArray<FPostResult> MutablePosts = Posts;
    SortPostsByDate(MutablePosts);

    /* 우편 개수 50개 제한 */
    if (MutablePosts.Num() >= 50)
    {
        /* 제일 오래된 우편부터 삭제 */
        RemoveOldestPost(MutablePosts.Last());
    }

    for (const FPostResult& Post : MutablePosts)
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

void UPostTabWidget::SortPostsByDate(TArray<FPostResult>& Posts)
{
    for (int32 i = 0; i < Posts.Num() - 1; ++i)
    {
        for (int32 j = 0; j < Posts.Num() - i - 1; ++j)
        {
            FDateTime DateA, DateB;

            if (FDateTime::Parse(Posts[j].PostDate, DateA) && FDateTime::Parse(Posts[j + 1].PostDate, DateB))
            {
                if (DateA < DateB) 
                {
                    Posts.Swap(j, j + 1);
                }
            }
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

                for (UWidget* Page : PageSwitcher->GetAllChildren())
                {
                    if (UVerticalBox* VerticalBox = Cast<UVerticalBox>(Page))
                    {
                        if (VerticalBox->RemoveChild(PostButton)) // 삭제 성공
                        {
                            // 페이지에 버튼이 없다면 해당 페이지도 삭제
                            if (VerticalBox->GetChildrenCount() < 1)
                            {
                                PageSwitcher->RemoveChild(Page);

                                int32 TotalPage = PageSwitcher->GetNumWidgets() > 0 ? PageSwitcher->GetNumWidgets() : 1;

                                FText PageText = FText::Format(
                                    FText::FromString(TEXT("{0}/{1}")),
                                    FText::AsNumber(PageSwitcher->GetActiveWidgetIndex() + 1),
                                    FText::AsNumber(TotalPage)
                                );
                                CurrentPageText->SetText(PageText);
                            }
                            break;
                        }
                    }
                }

                PostButton->SetButtonState(false);
            }
            PostButtons.Remove(Post.Title);
            // PostCount 감소 및 UI 업데이트
            postCount = FMath::Max(0, postCount - 1);
            PostCountText->SetText(FText::AsNumber(postCount));

            SelectedPost = FPostResult();
            SelectedPostButton = nullptr;
            UpdatePostDetails(SelectedPost);
            GameInstance->GetNetworkManager()->SendPostRemoveRequest(Post);
        });
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
    bool bIsBulkDelete = false;
    /* 체크 후 삭제 누른 경우 */
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
                    bIsBulkDelete = true;
                    FPostResult Post = PostButton->GetPostInfo();
                    // 삭제 로직
                    RemovePost(Post);
                }
            }
        }
    }
    /* 개별 삭제 누른 경우 */
    if (!bIsBulkDelete && SelectedPost.PostId != -1)
    {
        RemovePost(SelectedPost);
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

    PostOverlayUI->PostDetailUI->ClearPostSlots();

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
    postCount = 0;
    PostCountText->SetText(FText::AsNumber(postCount));
}

void UPostTabWidget::CreateNewPage()
{
    /* 8 페이지 이상이라면 더 이상 생성X */
    if(PageSwitcher->GetChildrenCount() >= 8) return;
    // 새 VerticalBox 생성
    NewPage = NewObject<UVerticalBox>(this);
    if (!NewPage || !PageSwitcher) return;

    if (!VerticalBoxes.Contains(NewPage))
    {
        VerticalBoxes.Add(NewPage);
    }

    // 새 페이지를 WidgetSwitcher에 추가
    PageSwitcher->AddChild(NewPage);
    PageSwitcher->SetActiveWidget(NewPage);

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
                    postCount++;
                    PostCountText->SetText(FText::AsNumber(postCount));
                }
            }
        });
}

void UPostTabWidget::UpdatePostDetails(const FPostResult& Post)
{
    SelectedPost = Post;
    
    PostOverlayUI->PostDetailUI->ClearPostSlots();
    PostOverlayUI->PostDetailUI->UpdatePostDetails(Post, bIsSentTab);
}

/* 우편 개수가 50개 이상일때 기존의 가장 오래된 우편 삭제 */
void UPostTabWidget::RemoveOldestPost(const FPostResult& Post)
{
    GameInstance->GetNetworkManager()->SendPostRemoveRequest(Post);
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
            PostOverlayUI->PostDetailUI->SetVisibility(ESlateVisibility::Hidden);
            SelectedPostButton = nullptr;
            SelectedPost = FPostResult();
            UpdatePostDetails(SelectedPost);
        }
        else
        {
            SelectedPostButton->SetButtonState(false);
            PostOverlayUI->PostDetailUI->SetVisibility(ESlateVisibility::Hidden);
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
    PostOverlayUI->PostDetailUI->SetVisibility(ESlateVisibility::Visible);
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

