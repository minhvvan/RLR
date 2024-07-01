<<<<<<< Updated upstream
#include "MyHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/InGame/InGameMainUI.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

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
	
	AMyPlayerController* PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->InitializeChatUI(PC->GetChatClient());
	}
}
=======
#include "MyHUD.h"
#include "Chat/ChatUI.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

AMyHUD::AMyHUD()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> ChatUIBPClass(TEXT("/Game/Blueprints/ChatUI"));
    if (ChatUIBPClass.Succeeded())
    {
        ChatUIClass = ChatUIBPClass.Class;
    }

    if (!ChatUI && ChatUIClass)
    {
        ChatUI = CreateWidget<UChatUI>(GetWorld(), ChatUIClass);
        if (ChatUI)
        {
            ChatUI->AddToViewport();
        }
    }
}

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();

}

UChatUI* AMyHUD::GetChatUI() const
{
    return ChatUI;
}
>>>>>>> Stashed changes
