// ChatClient.h

#pragma once

#include "CoreMinimal.h"
#include "Windows/AllowWindowsPlatformTypes.h"

#include <winsock2.h>
#include "Windows/HideWindowsPlatformTypes.h"
#include "MyPlayerController.h" 
#pragma comment(lib, "ws2_32.lib")
#include "GameFramework/Actor.h"
#include "ChatClient.generated.h"

class UChatUI;

UCLASS()
class RLR_API AChatClient : public AActor
{
    GENERATED_BODY()

public:
    AChatClient();

    void SetUserName(FString PlayerID);

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void ConnectToServer();

    UFUNCTION(BlueprintCallable)
    void SendMessageToServer(const FString& Message);

    UFUNCTION(BlueprintCallable)
    void ReceiveMessages();

    FString ParseWhisperMessage(const FString& Message, FString& OutTargetID);

 

private:
    SOCKET ClientSocket;
    bool bConnected;
    FString ClientId;


public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UChatUI* ChatUI;
};
