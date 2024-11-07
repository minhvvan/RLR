// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseUI.h"
#include "UI/MainUI.h"

#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/DataManager.h"
#include "GameManager/NetworkManager.h"
#include "GameManager/PlayerManager.h"
#include "GameManager/InventoryManager.h"
#include "GameManager/PartyManager.h"
#include "Structs/UtilStructs.h"

#include "Components/Widget.h"
#include "Components/PanelWidget.h"
#include "ActionSystem/ActionSystemInterface.h"
#include "Blueprint/WidgetTree.h"

void UBaseUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBaseUI::NativeConstruct()
{
	Super::NativeConstruct();
	Init();
	BindWidget();
}

void UBaseUI::OpenUI()
{
	RefreshUI();
	GetUIManager()->OpenSubUI(UITag);
}

void UBaseUI::CloseUI()
{
	GetUIManager()->CloseSubUI(UITag);
}

void UBaseUI::BindWidget()
{
	TArray<UWidget*> Array;
	WidgetTree->GetAllWidgets(Array);

	for (auto Widget : Array)
	{
		if (UBaseUI* Child = Cast<UBaseUI>(Widget))
		{
			Child->SetParent(this);
		}
	}
}

void UBaseUI::SetInputMode()
{
	//특별한 경우가 없다면 그냥 Game And UI 모드.
	ChangeInputModeGameAndUI();
}

void UBaseUI::SetVisible(bool bVisible)
{
	if (bVisible) SetVisibility(ESlateVisibility::Visible);
	else SetVisibility(ESlateVisibility::Hidden);
}

UBaseUI* UBaseUI::GetParent()
{
	if (IsValid(Parent) == false)
	{
		Parent = GetUIManager()->GetPage<UBaseUI>(FGameplayTagManager::Get().Page_InGame);
	}
	return Parent;
}

void UBaseUI::SetActionSystemComponent(AActor* Owner)
{
	IActionSystemInterface* ASCInterface = Cast<IActionSystemInterface>(Owner);
	if (!ASCInterface) return;

	UActionSystemComponent* ASC = ASCInterface->GetActionSystemComponent();
	if (!ASC) return;

	ActionSystemComponent = ASC;
}

void UBaseUI::ChangeInputModeGameAndUI()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(IsValid(PlayerController) == false)
		return;

	UMainUI* MainUI = GameInstance->GetUIManager()->GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame);
	if(IsValid(MainUI) == false)
		return;


	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetWidgetToFocus(MainUI->TakeWidget());					// 포커스할 위젯 설정
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 마우스 잠금 설정
	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(true); 						// 마우스 커서를 화면에 표시
}

void UBaseUI::ChangeInputModeGameOnly()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (IsValid(PlayerController) == false)
		return;

	FInputModeGameOnly InputMode;	
	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(false);
}

void UBaseUI::ChangeInputModeUIOnly()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (IsValid(PlayerController) == false)
		return;

	UMainUI* MainUI = GameInstance->GetUIManager()->GetPage<UMainUI>(FGameplayTagManager::Get().Page_InGame);
	if (IsValid(MainUI) == false)
		return;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(MainUI->TakeWidget());					// 포커스할 위젯 설정
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 마우스 잠금 설정
	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(true);
}

UUIManager* UBaseUI::GetUIManager()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());

	if (GM)
	{
		return GM->GetUIManager();
	}

	return nullptr;
}

UGameManager* UBaseUI::GetGameManager()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());

	if (GM)
	{
		return GM;
	}

	return nullptr;
}

UNetworkManager* UBaseUI::GetNetworkManager()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());

	if (GM)
	{
		return GM->GetNetworkManager();
	}

	return nullptr;
}

UPlayerManager* UBaseUI::GetPlayerManager()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());

	if (GM)
	{
		return GM->GetPlayerManager();
	}

	return nullptr;
}

USkillManager* UBaseUI::GetSkillManager()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());

	if (GM)
	{
		return GM->GetSkillManager();
	}

	return nullptr;
}

UInventoryManager* UBaseUI::GetInventoryManager()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());

	if (GM)
	{
		return GM->GetInventoryManager();
	}

	return nullptr;
}

UDataManager* UBaseUI::GetDataManager()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());

	if (GM)
	{
		return GM->GetDataManager();
	}

	return nullptr;
}

UPartyManager* UBaseUI::GetPartyManager()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());

	if (GM)
	{
		return GM->GetPartyManager();
	}

	return nullptr;
}

void UBaseUI::OpenOtherUI(FGameplayTag Tag)
{
	GetUIManager()->OpenSubUI(Tag);
}
