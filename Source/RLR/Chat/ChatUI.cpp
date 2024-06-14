#include "ChatUI.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "ChatClient.h"
#include "ChatTabWidget.h"
#include <Kismet/GameplayStatics.h>

void UChatUI::NativeConstruct()
{
    UE_LOG(LogTemp, Log, TEXT("NativeConstruct 실행 "));
    Super::NativeConstruct();

    if (ChatInput)
    {
        ChatInput->OnTextCommitted.AddDynamic(this, &UChatUI::OnChatInputCommitted);
        UE_LOG(LogTemp, Log, TEXT("chatinput 확인"));
    }

    if (SendButton)
    {
        SendButton->OnClicked.AddDynamic(this, &UChatUI::OnSendButtonClicked);
        UE_LOG(LogTemp, Log, TEXT("SendButton 확인  "));
    }
   
    TabFilters.Add("General", { EChatType::General });
    TabFilters.Add("Guild", { EChatType::Guild });
    TabFilters.Add("Party", { EChatType::Party });
    TabFilters.Add("Continent", { EChatType::Continent });
    TabFilters.Add("Raid", { EChatType::Raid });
    TabFilters.Add("Whisper", { EChatType::Whisper });
    TabFilters.Add("Country", { EChatType::Country });
    TabFilters.Add("Nearby", { EChatType::Nearby });
    TabFilters.Add("World", { EChatType::World });
    // 체크박스 초기화 및 이벤트 바인딩
 
    GeneralCheckBox->OnCheckStateChanged.AddDynamic(this, &UChatUI::OnFilterChanged);
   
    WhisperCheckBox->OnCheckStateChanged.AddDynamic(this, &UChatUI::OnFilterChanged);
    
    CountryCheckBox->OnCheckStateChanged.AddDynamic(this, &UChatUI::OnFilterChanged);
   
    WorldCheckBox->OnCheckStateChanged.AddDynamic(this, &UChatUI::OnFilterChanged);
   
    ContinentCheckBox->OnCheckStateChanged.AddDynamic(this, &UChatUI::OnFilterChanged);
    
    RaidCheckBox->OnCheckStateChanged.AddDynamic(this, &UChatUI::OnFilterChanged);
    
    PartyCheckBox->OnCheckStateChanged.AddDynamic(this, &UChatUI::OnFilterChanged);
    
    GuildCheckBox->OnCheckStateChanged.AddDynamic(this, &UChatUI::OnFilterChanged);
    NearbyCheckBox->OnCheckStateChanged.AddDynamic(this, &UChatUI::OnFilterChanged);
  

    AddChatTabWidget(FText::FromString("채팅탭 1"),0 );
    AddChatTabWidget(FText::FromString("채팅탭 2"), 1);
    AddChatTabWidget(FText::FromString("채팅탭 3"), 2);
    UE_LOG(LogTemp, Log, TEXT("WidgetSwitcher 자식 개수: %d"), TabContentSwitcher->GetChildrenCount());
    if (TabContentSwitcher)
    {
        TabContentSwitcher->SetActiveWidgetIndex(0);
    }
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(ChatInput->TakeWidget());
        PlayerController->SetInputMode(InputMode);
        PlayerController->bShowMouseCursor = true;
    }
    
    
    UE_LOG(LogTemp, Log, TEXT("NativeConstruct 완료  "));
}
void UChatUI::AddChatTabWidget(const FText& TabName, int32 TabIndex)
{
    if(!TabContainer || !TabContentSwitcher)
    {
        UE_LOG(LogTemp, Error, TEXT("TabContainer 또는 TabContentSwitcher가 유효하지 않습니다."));
        return;
    }

    // Create a new tab widget and add it to the TabContainer
    UChatTabWidget* NewTabButton = CreateWidget<UChatTabWidget>(this, LoadClass<UUserWidget>(nullptr, TEXT("/Game/Blueprints/ChatTabWidget.ChatTabWidget_C")));
    if (NewTabButton)
    {
        NewTabButton->SetTabName(TabName);

        // Dynamically bind the button click event
        if (NewTabButton->ChattingTabButton)
        {
            UE_LOG(LogTemp, Log, TEXT("ChattingTabButton 확인."));
            UChatTabButton* Chatbutton = static_cast<UChatTabButton*>(NewTabButton->ChattingTabButton);

            Chatbutton->SetIndex(TabIndex);
           
            UE_LOG(LogTemp, Log, TEXT("버튼 인덱스 : %d"), Chatbutton->GetIndex());
            Chatbutton->OnMyButtonClicked.AddDynamic(this, &UChatUI::HandleTabButtonClicked);
            TabButtonToIndexMap.Add(NewTabButton->ChattingTabButton, TabIndex);
        }
     
        TabContainer->AddChild(NewTabButton);
       
        ChatTabs.Add(NewTabButton);
      

        // Add the new tab content to the WidgetSwitcher
        
       
        if (TabContentSwitcher)
        {
            UScrollBox* NewTextBlock = NewObject<UScrollBox>(TabContentSwitcher);
            


            UE_LOG(LogTemp, Log, TEXT("Tab 추가 완료: %s"), *TabName.ToString());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("TabContent 생성 실패"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Tab 생성 실패"));
    }
}
void UChatUI::HandleTabButtonClicked(UChatTabButton* ClickedButton) {
    UE_LOG(LogTemp, Log, TEXT("클릭 됨?") );
    if (ClickedButton)
    {
        OnTabClicked(ClickedButton->GetIndex());

        // 다른 로직 추가
    }
}

void UChatUI::OnTabClicked(int32 TabIndex)
{
    if (TabContentSwitcher)
    {
        // Set the active widget index of the WidgetSwitcher
        TabContentSwitcher->SetActiveWidgetIndex(TabIndex);
       
    }

    // Optional: Highlight the selected tab
    for (int32 i = 0; i < ChatTabs.Num(); ++i)
    {
        ChatTabs[i]->ChattingTabButton->SetIsEnabled(i != TabIndex);
    }
}
void UChatUI::OnFilterChanged(bool bIsChecked)
{
    UpdateChatDisplay();
}
void UChatUI::UpdateTabFilters(const FString& TabName, const TArray<EChatType>& FilteredChatTypes)
{
    if (TabFilters.Contains(TabName))
    {
        TabFilters[TabName] = FilteredChatTypes;
        UpdateChatDisplay();
    }
}

void UChatUI::AddChatTab(FString TabName, TArray<EChatType> FilteredChatTypes)
{
    TabFilters.Add(TabName, FilteredChatTypes);
    UpdateChatDisplay();
}



void UChatUI::CreateNewTab(const FString& TabName)
{
    if (!TabFilters.Contains(TabName))
    {
        TabFilters.Add(TabName, {});
    }
}

void UChatUI::SetUserNameText(FString PlayerID)
{
    UserNameBox->SetText(FText::FromString(PlayerID));
}

void UChatUI::SetChatClient(AChatClient* InChatClient)
{
    ChatClient = InChatClient;
}

void UChatUI::OnChatInputCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
    UE_LOG(LogTemp, Log, TEXT("키입력은 먹히는거지 ? "));
    if (CommitMethod == ETextCommit::OnEnter)
    {
        UE_LOG(LogTemp, Log, TEXT("엔터는 먹히는거지 ? "));
        OnSendButtonClicked();
    }
}

void UChatUI::OnSendButtonClicked()
{
    UE_LOG(LogTemp, Log, TEXT("클릭은 먹히는거지 ? "));
    if (ChatClient && ChatInput)
    {
        UE_LOG(LogTemp, Log, TEXT("설마 여길 안들어오나?"));
        // 입력된 텍스트 가져오기
        FString Message = ChatInput->GetText().ToString();

        // 개행 문자 제거
        Message.RemoveFromEnd(TEXT("\n"));

        // 서버로 메시지 전송
        ChatClient->SendMessageToServer(Message);

        // 입력 필드 비우기
        ChatInput->SetText(FText::GetEmpty());
    }
}



void UChatUI::AddChatMessage(const FString& Message,int ChatType)
{
    FChatMessage infoMessage;
    infoMessage.Message = Message;
    infoMessage.ChatType = EChatType(ChatType);
    
    ChatMessages.Add(infoMessage);
    UpdateChatDisplay();
}

void UChatUI::AddMessageToScrollBox(UScrollBox* ScrollBox, const FString& Message, FLinearColor Color)
{
    if (ScrollBox)
    {
        UTextBlock* TextBlock = NewObject<UTextBlock>(ScrollBox);
        if (TextBlock)
        {
            TextBlock->SetText(FText::FromString(Message));
            TextBlock->SetColorAndOpacity(FSlateColor(Color));
            ScrollBox->AddChild(TextBlock);
        }
    }
}

void UChatUI::UpdateChatDisplay()
{
    if (!ChatOutputBox) return;

    ChatOutputBox->ClearChildren();

    TArray<EChatType> SelectedChatTypes = GetSelectedChatTypes();

    for (const FChatMessage& ChatMessage : ChatMessages)
    {
        if (SelectedChatTypes.Contains(ChatMessage.ChatType))
        {
            UTextBlock* NewTextBlock = NewObject<UTextBlock>(ChatOutputBox);
            NewTextBlock->SetText(FText::FromString(ChatMessage.Message));

            switch (ChatMessage.ChatType)
            {
            case EChatType::General:
                NewTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::White));
                break;
            case EChatType::Whisper:
                NewTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
                break;
            case EChatType::Country:
                NewTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Blue));
                break;
            case EChatType::World:
                NewTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
                break;
            case EChatType::Guild:
                NewTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Black));
                break;
            case EChatType::Raid:
                NewTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
                break;
            case EChatType::Party:
                NewTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Blue));
                break;
            case EChatType::Continent:
                NewTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Gray));
                break;
            }

            ChatOutputBox->AddChild(NewTextBlock);
        }
    }
}

TArray<EChatType> UChatUI::GetSelectedChatTypes() const
{
    TArray<EChatType> SelectedChatTypes;

    if (GeneralCheckBox->IsChecked())
    {
        SelectedChatTypes.Add(EChatType::General);
    }
    if (WhisperCheckBox->IsChecked())
    {
        SelectedChatTypes.Add(EChatType::Whisper);
    }
    if (CountryCheckBox->IsChecked())
    {
        SelectedChatTypes.Add(EChatType::Country);
    }
    if (WorldCheckBox->IsChecked())
    {
        SelectedChatTypes.Add(EChatType::World);
    }
    if (GuildCheckBox->IsChecked())
    {
        SelectedChatTypes.Add(EChatType::Guild);
    }
    if (RaidCheckBox->IsChecked())
    {
        SelectedChatTypes.Add(EChatType::Raid);
    }
    if (PartyCheckBox->IsChecked())
    {
        SelectedChatTypes.Add(EChatType::Party);
    }
    if (ContinentCheckBox->IsChecked())
    {
        SelectedChatTypes.Add(EChatType::Continent);
    }

    return SelectedChatTypes;
}
