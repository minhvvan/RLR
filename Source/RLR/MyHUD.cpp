#include "MyHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/InGame/InGameMainUI.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "Blueprint/UserWidget.h"

AMyHUD::AMyHUD()
{
	static ConstructorHelpers::FClassFinder<UInGameMainUI> UIClass(TEXT("Blueprint'/Game/Blueprints/UI/InGame/WBP_InGameUI.WBP_InGameUI_C'"));
	if (UIClass.Succeeded())
	{
		MainUIClass = UIClass.Class;
	}
}

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();

}
