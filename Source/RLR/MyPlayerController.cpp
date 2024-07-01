#include "MyPlayerController.h"
#include "Chat/ChatClient.h"
#include "UI/InGame/Chat/ChatUI.h"
#include "MyHUD.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/InGame/InGameHUD.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "MariaDBActor.h"
AMyPlayerController* AMyPlayerController::Instance = nullptr;

AMyPlayerController::AMyPlayerController()
{
    PlayerID = FString();
    Instance = this;
}

AMyPlayerController* AMyPlayerController::GetInstance()
{
  
    return Instance;
}

AMyPlayerController::~AMyPlayerController()
{
}

void AMyPlayerController::BeginPlay()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMariaDBActor::StaticClass(), FoundActors);

   /// MariaDBActor를 찾았을 경우에만 플레이어 ID 가져오기
    if (FoundActors.Num() > 0)
    {
        // 첫 번째로 찾은 MariaDBActor에 대한 포인터 가져오기
        AMariaDBActor* MariaDBActor = Cast<AMariaDBActor>(FoundActors[0]);
        if (MariaDBActor)
        {
            // MariaDBActor에서 플레이어 ID 가져와서 PlayerID에 할당
            PlayerID = MariaDBActor->GetPlayerID();
        }
    }

    // 플레이어 ID 확인하기
    UE_LOG(LogTemp, Warning, TEXT("Player ID: %s"), *PlayerID);
    Super::BeginPlay();
    // ChatClient가 스폰되지 않았다면 스폰합니다.
    if (!ChatClient)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetPawn();

        ChatClient = GetWorld()->SpawnActor<AChatClient>(AChatClient::StaticClass(), SpawnParams);
        if (ChatClient)
        {
            
            UE_LOG(LogTemp, Log, TEXT("ChatClient spawned: %s"), *ChatClient->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to spawn ChatClient"));
        }
    }
    if (!GameClient)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetPawn();

        GameClient = GetWorld()->SpawnActor<AGameClient>(AGameClient::StaticClass(), SpawnParams);
        if (GameClient)
        {

            UE_LOG(LogTemp, Log, TEXT("GameClient spawned: %s"), *GameClient->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to spawn GameClient"));
        }
    }
  //  InitializeChatUI(ChatClient);
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    
    FindChatClient();
}
void AMyPlayerController::UpdateChatUI(const FString& Message, UChatUI* UI, int ChatType)
{
    UE_LOG(LogTemp, Log, TEXT("UpdateChatUI 실행"));

    if (UI)
    {
        UE_LOG(LogTemp, Log, TEXT("UI는 있음"));

        
        UI->AddChatMessage(Message,ChatType);
    }
}
void AMyPlayerController::InitializeChatUI(AChatClient* ChatClient2)
{
	UE_LOG(LogTemp, Log, TEXT("Init Chat UI Start!!"));
    AInGameHUD* HUD = Cast<AInGameHUD>(GetHUD());
	if (HUD)
    {

        UGameManager* GM = Cast<UGameManager>(GetGameInstance());
        GM->GetUIManager()->OpenMainUI(HUD->MainUIClass);
        UChatUI* ChatUI = Cast<UInGameMainUI>(GM->GetUIManager()->GetMainUI())->GetChatUI();

        if (ChatUI)
        {
            UE_LOG(LogTemp, Log, TEXT("UChatUI is Vaild"));
            ChatUI->SetUserNameText(PlayerID);
            ChatClient2->ChatUI = ChatUI;
            ChatClient2->SetUserName(PlayerID);
            ChatUI->SetChatClient(ChatClient2);
            ChatClient2->ConnectToServer();

        }
    }
}
void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);
}

void AMyPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GameClient)
    {
        //UE_LOG(LogTemp, Log, TEXT("Game Client 있음"));
        CurrentLocation = GetPawn()->GetActorLocation();

        if (FVector::Dist(CurrentLocation, LastLocation) > Threshold)
        {
            SendMovementToServer();
            LastLocation = CurrentLocation;
        }
    }
}

void AMyPlayerController::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), Value);
    }
}

void AMyPlayerController::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), Value);
    }
}

void AMyPlayerController::SendMovementToServer()
{
    if (GameClient)
    {
        int32 PlayerId = GetUniqueID();
        FVector ActorLocation = GetPawn()->GetActorLocation();
    }
}
void AMyPlayerController::FindChatClient()
{
    UE_LOG(LogTemp, Warning, TEXT("FindChat Start!!"));
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChatClient::StaticClass(), FoundActors);

    if (FoundActors.Num() > 0)
    {
        ChatClient = Cast<AChatClient>(FoundActors[0]);
        UE_LOG(LogTemp, Log, TEXT("ChatClient found: %s"), *ChatClient->GetName());

        // ChatClient�� ã�� �� �ٽ� InitializeChatUI ȣ��
        InitializeChatUI(ChatClient);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("FindChat Failed!"));
    }
}
