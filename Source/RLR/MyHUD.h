#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

// ���� ����
class UChatUI;
class UInGameMainUI;
class UMainUI;

UCLASS()
class RLR_API AMyHUD : public AHUD
{
    GENERATED_BODY()

public:
    AMyHUD();

    virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMainUI> MainUIClass;
};
