#include "MyGameMode.h"
#include "MyPlayerController.h"
#include "MyHUD.h"

AMyGameMode::AMyGameMode()
{
    PlayerControllerClass = AMyPlayerController::StaticClass();
    HUDClass = AMyHUD::StaticClass();
}
