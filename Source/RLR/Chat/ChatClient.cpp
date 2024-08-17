#include "ChatClient.h"
#include "UI/InGame/Chat/ChatUI.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

class UChatUI;
AChatClient::AChatClient()
{
    PrimaryActorTick.bCanEverTick = true;
    bConnected = false;
    ClientSocket = INVALID_SOCKET;
    
}
void AChatClient::SetUserName(FString PlayerID) {

    ClientId = PlayerID;
}
void AChatClient::BeginPlay()
{
    Super::BeginPlay();
    
}

void AChatClient::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AChatClient::ConnectToServer()
{
    if (ChatUI == nullptr) {
        UE_LOG(LogTemp, Log, TEXT("Chat UI 연결 제대로 안됌"));
    }
    else {
        UE_LOG(LogTemp, Log, TEXT("Chat UI 연결 제대로 됌"));
    }
    
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        UE_LOG(LogTemp, Error, TEXT("WSAStartup failed"));
        return;
    }

    ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ClientSocket == INVALID_SOCKET)
    {
        UE_LOG(LogTemp, Error, TEXT("Error creating socket: %d"), WSAGetLastError());
        WSACleanup();
        return;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6000); // Server port
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(ClientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        UE_LOG(LogTemp, Error, TEXT("Connect failed with error: %d"), WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return;
    }

    bConnected = true;
    UE_LOG(LogTemp, Log, TEXT("Connected to chat server"));

    // 서버에 아이디 전송
    SendMessageToServer(FString(ClientId));

    // 클라이언트로부터 메시지를 수신하는 스레드 시작
    std::thread clientThread(&AChatClient::ReceiveMessages, this);
    clientThread.detach(); // 스레드를 백그라운드에서 실행
}

void AChatClient::SendMessageToServer(const FString& Message)
{
    UE_LOG(LogTemp, Log, TEXT("Click button"));

    if (bConnected)
    {
        UE_LOG(LogTemp, Log, TEXT("클라이언트 연결 됨"));
        std::string msg = TCHAR_TO_UTF8(*Message);
        UE_LOG(LogTemp, Log, TEXT("%s 라고 보냈음"),&msg);
        send(ClientSocket, msg.c_str(), msg.length(), 0);
    }
  
}
void AChatClient::ReceiveMessages()
{
    FString LastMessage;
    while (bConnected)
    {
        char buffer[1024];
        int bytesReceived = recv(ClientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0';
            FString Message = UTF8_TO_TCHAR(buffer);
            UE_LOG(LogTemp, Log, TEXT("Received message: %s"), *Message);

            // 귓속말 메시지 로그 추가
            if (Message.Contains("Whisper from"))
            {
                UE_LOG(LogTemp, Log, TEXT("Received whisper message: %s"), *Message);
            }

            if (Message != LastMessage)  // 중복 메시지 처리 방지
            {
                LastMessage = Message;

                FFunctionGraphTask::CreateAndDispatchWhenReady([this, Message]()
                    {
                      /*  if (AMyPlayerController::GetInstance())
                        {
                            TArray<FString> Path;
                            
                            Message.ParseIntoArray( Path,TEXT("]"));
                            if (Path[0].Contains(TEXT("일반"))) {
                                AMyPlayerController::GetInstance()->UpdateChatUI(Message, ChatUI, 0);
                            }
                            else if (Path[0].Contains(TEXT("귓속말"))) {
                                AMyPlayerController::GetInstance()->UpdateChatUI(Message, ChatUI, 1);
                            }
                            else if (Path[0].Contains(TEXT("국가"))) {
                                AMyPlayerController::GetInstance()->UpdateChatUI(Message, ChatUI, 2);
                            }
                            else if (Path[0].Contains(TEXT("세계"))) {
                                AMyPlayerController::GetInstance()->UpdateChatUI(Message, ChatUI, 3);
                            }
                            else if (Path[0].Contains(TEXT("길드"))) {
                                AMyPlayerController::GetInstance()->UpdateChatUI(Message, ChatUI, 4);
                            }
                            else if (Path[0].Contains(TEXT("레이드"))) {
                                AMyPlayerController::GetInstance()->UpdateChatUI(Message, ChatUI, 5);
                            }
                            else if (Path[0].Contains(TEXT("파티"))) {
                                AMyPlayerController::GetInstance()->UpdateChatUI(Message, ChatUI, 6);
                            }
                            else if (Path[0].Contains(TEXT("대륙"))) {
                                AMyPlayerController::GetInstance()->UpdateChatUI(Message, ChatUI, 7);
                            }
                            else if (Path[0].Contains(TEXT("동료"))) {
                                AMyPlayerController::GetInstance()->UpdateChatUI(Message, ChatUI, 8);
                            }
                         
                            UE_LOG(LogTemp, Log, TEXT("PlayerController 체크"));
                            
                        } */
                    }, TStatId(), nullptr, ENamedThreads::GameThread);
            }
        }
        else if (bytesReceived == 0 || bytesReceived == SOCKET_ERROR)
        {
            bConnected = false;
            closesocket(ClientSocket);
            WSACleanup();
            UE_LOG(LogTemp, Log, TEXT("Disconnected from chat server"));
        }
    }
}
FString AChatClient::ParseWhisperMessage(const FString& Message, FString& OutTargetID)
{
    OutTargetID.Empty();

    if (Message.StartsWith(TEXT("/w ")))
    {
        TArray<FString> Parts;
        Message.ParseIntoArray(Parts, TEXT(" "), true);

        if (Parts.Num() >= 3)
        {
            OutTargetID = Parts[1];
            return Message.RightChop(Parts[0].Len() + Parts[1].Len() + 2);
        }
    }

    return Message;
}