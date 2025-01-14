// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/BaseGuildMember.h"
#include "Components/TextBlock.h"

void UBaseGuildMember::NativeConstruct()
{
    Super::NativeConstruct();
}

void UBaseGuildMember::SetGuildMember(FGuildRank NewGuildMember)
{
    guildMember = NewGuildMember;

    SetUserNameText(guildMember.UserName);
}

FGuildRank UBaseGuildMember::GetGuildMember()
{
    return guildMember;
}

void UBaseGuildMember::SetUserNameText(FString GuildMemberName)
{
    UserNameText->SetText(FText::FromString(GuildMemberName));
}

FReply UBaseGuildMember::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
    // 우클릭 감지
    if (MouseEvent.IsControlDown() && MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {
        // 우클릭 시 메뉴 표시
        if (OnGuildMemberRightClicked.IsBound())
        {
            FVector2D LocalMousePosition = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());

            OnGuildMemberRightClicked.Broadcast(LocalMousePosition, this);
        }
        return FReply::Handled();
    }

    return Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);
}
