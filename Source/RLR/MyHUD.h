#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

// ���� ����
class UChatUI;
class UInGameMainUI;

UCLASS()
class RLR_API AMyHUD : public AHUD
{
    GENERATED_BODY()

public:
    AMyHUD();

    virtual void BeginPlay() override;


    UFUNCTION(BlueprintCallable)
    UInGameMainUI* GetInGameMainUI() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> InGameMainUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInGameMainUI> InGameMainUI;
};
