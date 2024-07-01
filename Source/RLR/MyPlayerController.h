#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Chat/GameClient.h"
#include "MyPlayerController.generated.h"


// ���� ����
class AChatClient;
class UChatUI;


UCLASS()
class RLR_API AMyPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AMyPlayerController();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
    FString PlayerID;
    void UpdateChatUI(const FString& Message, UChatUI* UI, int Chattype);
    static AMyPlayerController* GetInstance();
protected:
    virtual ~AMyPlayerController();
    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;
    virtual void SetupInputComponent() override;
    virtual void Tick(float DeltaTime) override;
    

    
    static AMyPlayerController* Instance;



private:
    AChatClient* ChatClient;
    AGameClient* GameClient;
    void MoveForward(float Value);
    void MoveRight(float Value);

    FVector CurrentLocation;
    FVector LastLocation;
    float Threshold = 10.0f;
    void SendMovementToServer();
    void FindChatClient();

public:
	AChatClient* GetChatClient() { return ChatClient; };
    void InitializeChatUI(AChatClient* ChatClient2);
};
