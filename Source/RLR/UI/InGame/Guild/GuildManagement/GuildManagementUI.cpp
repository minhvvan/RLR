// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Guild/GuildManagement/GuildManagementUI.h"
#include "UI/InGame/Guild/GuildManagement/GuildIconImage.h"

#include "GameManager/GameManager.h"
#include "GameManager/GuildManager.h"
#include "GameManager/NetworkManager.h"

#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"


void UGuildManagementUI::NativeConstruct()
{
	if (ChangeGuildInfoButton)
	{
		ChangeGuildInfoButton->OnClicked.AddUniqueDynamic(this, &UGuildManagementUI::ChangeInfoButtonClicked);
	}
	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddUniqueDynamic(this, &UGuildManagementUI::ConfirmButtonClicked);
	}
	if (CancelButton)
	{
		CancelButton->OnClicked.AddUniqueDynamic(this, &UGuildManagementUI::CancelButtonClicked);
	}
	if (CloseChangeGuildInfoButton)
	{
		CloseChangeGuildInfoButton->OnClicked.AddUniqueDynamic(this, &UGuildManagementUI::CloseChangeGuildInfoButtonClicked);
	}
	if (NewGuildImage)
	{
		NewGuildImage->OnMouseButtonDownEvent.BindUFunction(this, FName("ChangeImageButtonClicked"));
	}
	/* Master 권한이 있다면 */
	if (GameInstance->GetGuildManager()->HasPermission(EGuildRole::MASTER))
	{
		EnableButtons(true);

		if (DeleteGuildButton)
		{
			DeleteGuildButton->OnClicked.AddUniqueDynamic(this, &UGuildManagementUI::DeleteGuildButtonClicked);
		}
	}
	else
	{
		EnableButtons(true);
	}
}

void UGuildManagementUI::ChangeInfoButtonClicked()
{
	if (bIsChangeGuildNameOpen)
	{
		bIsChangeGuildNameOpen = false;
		ChangeGuildInfoBorder->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		bIsChangeGuildNameOpen = true;
		ChangeGuildInfoBorder->SetVisibility(ESlateVisibility::Visible);
	}

	if (!IconGridPanel || !GuildIconImageClass) return;

	IconGridPanel->ClearChildren();

	TArray<FString> IconPaths;
	const FString FolderPath = FPaths::ProjectContentDir() + "Resource/ItemIcon/";
	IFileManager::Get().FindFilesRecursive(IconPaths, *FolderPath, TEXT("*.uasset"), true, false);

	int32 Row = 0;
	int32 Column = 0;

	for (const FString& Path : IconPaths)
	{
		UTexture2D* IconTexture = LoadTextureFromPath(Path);
		if (!IconTexture) continue;

		UGuildIconImage* IconImageWidget = CreateWidget<UGuildIconImage>(this, GuildIconImageClass);
		if (!IconImageWidget) continue;

		IconImageWidget->SetImage(IconTexture);
		IconImageWidget->GuildIconImageClicked.AddUniqueDynamic(this, &UGuildManagementUI::OnIconSelected);

		UGridSlot* GridSlot = IconGridPanel->AddChildToGrid(IconImageWidget, Row, Column);

		Column++;
		if (Column >= 6)
		{
			Column = 0;
			Row++;
		}
	}

	IconGridPanel->SetVisibility(ESlateVisibility::Visible);
}

void UGuildManagementUI::OnIconSelected(UGuildIconImage* ClickedGuildIconImage)
{
	if (!ClickedGuildIconImage) return;

	if (LastClickedImage && LastClickedImage != ClickedGuildIconImage)
	{
		LastClickedImage->UnHighlight();
	}

	LastClickedImage = ClickedGuildIconImage;
	LastClickedImage->Highlight();

	SelectedIconTexture = ClickedGuildIconImage->GetIconTexture();

	if (NewGuildImage && SelectedIconTexture)
	{
		NewGuildImage->SetBrushFromTexture(SelectedIconTexture);
	}
}

void UGuildManagementUI::ConfirmButtonClicked()
{
	ChangeGuildInfoBorder->SetVisibility(ESlateVisibility::Hidden);

	if (!NewGuildNameText->GetText().IsEmpty())
	{
		int32 guildSeq = GameInstance->GetGuildManager()->GetGuildInfo().guildSeq;
		GameInstance->GetNetworkManager()->SendChangeNameGuild(guildSeq, NewGuildNameText->GetText());
	}
	if (GuildIconImageClass != nullptr)
	{
		/* TODO : 이미지 설정하는 send 함수 만들어지면 호출해주기 */
	}
}

void UGuildManagementUI::CancelButtonClicked()
{
	ChangeGuildInfoBorder->SetVisibility(ESlateVisibility::Hidden);
	NewGuildNameText->SetText(FText::FromString(""));
}

void UGuildManagementUI::CloseChangeGuildInfoButtonClicked()
{
	ChangeGuildInfoBorder->SetVisibility(ESlateVisibility::Hidden);
	NewGuildNameText->SetText(FText::FromString(""));
}

/* 길드 탈퇴 */
void UGuildManagementUI::QuitGuldButtonClicked()
{
	int32 GuildSeq = GameInstance->GetGuildManager()->GetGuildInfo().guildSeq;
	int32 UserSeq = GameInstance->GetUserSeq();
	GameInstance->GetNetworkManager()->SendRemoveGuild(UserSeq, GuildSeq);
}

/* 길드 삭제 */
void UGuildManagementUI::DeleteGuildButtonClicked()
{
	int32 GuildSeq = GameInstance->GetGuildManager()->GetGuildInfo().guildSeq;
	GameInstance->GetNetworkManager()->SendDeleteGuild(GuildSeq);
}

/* 관리자 탭의 버튼들 모두 비활성화 */
void UGuildManagementUI::EnableButtons(bool bEnabled)
{
	ChangeGuildInfoButton->SetIsEnabled(bEnabled);
	ExpandGuildButton->SetIsEnabled(bEnabled);
	GrantPermissionButton->SetIsEnabled(bEnabled);
	UserRankUpgradeButton->SetIsEnabled(bEnabled);
	GuildRewardPayoutButton->SetIsEnabled(bEnabled);
	DeleteGuildButton->SetIsEnabled(bEnabled);
}

UTexture2D* UGuildManagementUI::LoadTextureFromPath(const FString& Path)
{
	if (Path.IsEmpty()) return nullptr;

	// 파일 경로를 Unreal Engine의 가상 경로로 변환
	FString GamePath = Path;
	GamePath.RemoveFromStart(FPaths::ProjectContentDir());
	GamePath = "/Game/" + GamePath;
	GamePath = FPaths::ChangeExtension(GamePath, "");

	UTexture2D* Texture2D = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *GamePath));
	return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *GamePath));
}