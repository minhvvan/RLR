#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

// ���� ����
class UChatUI;

UCLASS()
class RLR_API AMyHUD : public AHUD
{
    GENERATED_BODY()

public:
    AMyHUD();

    virtual void BeginPlay() override;

    UChatUI* GetChatUI() const;

private:
    UPROPERTY()
    UChatUI* ChatUI;

    TSubclassOf<UUserWidget> ChatUIClass;
};
