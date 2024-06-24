#include "MyHUD.h"
#include "Chat/ChatUI.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/InGame/InGameMainUI.h"
#include "Blueprint/UserWidget.h"

AMyHUD::AMyHUD()
{
	static ConstructorHelpers::FClassFinder<UInGameMainUI> MainUIClass(TEXT("Blueprint'/Game/Blueprints/UI/InGame/WBP_InGameUI.WBP_InGameUI_C'"));
	if (MainUIClass.Succeeded())
	{
        InGameMainUIClass = MainUIClass.Class;
	}

    if (IsValid(InGameMainUI) == false && IsValid(InGameMainUIClass))
    {
        InGameMainUI = CreateWidget<UInGameMainUI>(GetWorld(), InGameMainUIClass);
        if (InGameMainUI)
        {
            InGameMainUI->AddToViewport();
        }
    }
}

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();



}

UInGameMainUI* AMyHUD::GetInGameMainUI() const
{
    return InGameMainUI;
}
