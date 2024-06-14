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
