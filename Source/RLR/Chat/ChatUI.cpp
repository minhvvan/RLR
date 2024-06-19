#include "ChatUI.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "ChatClient.h"
#include "ChatTabWidget.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"

#include <Kismet/GameplayStatics.h>

void UChatUI::NativeConstruct()
{
    UE_LOG(LogTemp, Log, TEXT("NativeConstruct 실행 "));
    Super::NativeConstruct();

    if (ChatInput)
    {
        ChatInput->OnTextCommitted.AddUniqueDynamic(this, &UChatUI::OnChatInputCommitted);
        UE_LOG(LogTemp, Log, TEXT("chatinput 확인"));
    }

    //채팅창 관련 초기화
    ChatOptionUI->SetVisibility(ESlateVisibility::Hidden);
    InitButton();
    InitChatBox();

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(ChatInput->TakeWidget());
        PlayerController->SetInputMode(InputMode);
        PlayerController->bShowMouseCursor = true;
    }


    UE_LOG(LogTemp, Log, TEXT("NativeConstruct 완료  "));
    LoadChatOption();
}
void UChatUI::InitButton()
{
    if (IsValid(SendButton))
    {
        SendButton->OnClicked.AddUniqueDynamic(this, &UChatUI::OnSendButtonClicked);
        UE_LOG(LogTemp, Log, TEXT("SendButton 확인  "));
    }

    //채팅 옵션 버튼을 누르면 채팅 옵션 UI를 띄운다.
    if (IsValid(ChatOptionButton))
    {
		ChatOptionButton->OnClicked.AddUniqueDynamic(this, &UChatUI::OnChatOptionUIButtonClicked);
    }

    if (IsValid(ConfirmButton))
    {
        ConfirmButton->OnClicked.AddUniqueDynamic(this, &UChatUI::OnConfirmButtonClicked);
    }

    if (IsValid(CancelButton))
    {
        CancelButton->OnClicked.AddUniqueDynamic(this, &UChatUI::OnCancelButtonClicked);
    };

}
void UChatUI::InitChatBox()
{
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

    GeneralCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::General, GeneralCheckBox);

    WhisperCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::Whisper, WhisperCheckBox);

    CountryCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::Country, CountryCheckBox);

    WorldCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::World, WorldCheckBox);

    ContinentCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::Continent, ContinentCheckBox);

    RaidCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::Raid, RaidCheckBox);

    PartyCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::Party, PartyCheckBox);

    GuildCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::Guild, GuildCheckBox);

    NearbyCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::Nearby, NearbyCheckBox);

    //인덱스값이랑 EChatType의 순서랑 맞춰주기.
    AddChatTabWidget(FText::FromString(TEXT("일반")), 0);
    AddChatTabWidget(FText::FromString(TEXT("귓속말")), 1);
    AddChatTabWidget(FText::FromString(TEXT("국가")), 2);
    AddChatTabWidget(FText::FromString(TEXT("세계")), 3);
    AddChatTabWidget(FText::FromString(TEXT("길드")), 4);



    UE_LOG(LogTemp, Log, TEXT("WidgetSwitcher 자식 개수: %d"), TabContentSwitcher->GetChildrenCount());
    if (TabContentSwitcher)
    {
        //TabContentSwitcher->SetActiveWidgetIndex(0);
        OnTabClicked(0);
    }
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
            UChatTabButton* Chatbutton = Cast<UChatTabButton>(NewTabButton->ChattingTabButton);
            if(IsValid(Chatbutton) == false)
                return;

            Chatbutton->SetIndex(TabIndex);
           
            UE_LOG(LogTemp, Log, TEXT("버튼 인덱스 : %d"), Chatbutton->GetIndex());

            //
            Chatbutton->OnMyButtonClicked.AddUniqueDynamic(this, &UChatUI::HandleTabButtonClicked);
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

    SetCurrentChatType((EChatType)TabIndex);
    UpdateChatDisplay((EChatType)TabIndex);
}
void UChatUI::OnFilterChanged(bool bIsChecked)
{
    //필터가 바뀌어도 채팅 탭이 다를 수 있으니 현재 선택되어 있는 타입을 불러와준다.
    UpdateChatDisplay(GetCurrentChatType());

       
    //채팅 옵션을 저장해준다.
}
void UChatUI::UpdateTabFilters(const FString& TabName, const TArray<EChatType>& FilteredChatTypes)
{
    if (TabFilters.Contains(TabName))
    {
        TabFilters[TabName] = FilteredChatTypes;
        UpdateChatDisplay(GetCurrentChatType());
    }
}

void UChatUI::AddChatTab(FString TabName, TArray<EChatType> FilteredChatTypes)
{
    TabFilters.Add(TabName, FilteredChatTypes);
    UpdateChatDisplay(GetCurrentChatType());
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

void UChatUI::OnChatOptionUIButtonClicked()
{
    if (IsValid(ChatOptionUI))
    {
        ChatOptionUI->SetVisibility(ESlateVisibility::Visible);
    }
}

void UChatUI::OnConfirmButtonClicked()
{
    if (IsValid(ConfirmButton))
    {
        ChatOptionUI->SetVisibility(ESlateVisibility::Hidden);
        SaveChatOption();
    }
}

void UChatUI::OnCancelButtonClicked()
{
    if (IsValid(CancelButton))
    {
        ChatOptionUI->SetVisibility(ESlateVisibility::Hidden);
        LoadChatOption();
    }
}



void UChatUI::AddChatMessage(const FString& Message,int ChatType)
{
    FChatMessage infoMessage;
    infoMessage.Message = Message;
    infoMessage.ChatType = EChatType(ChatType);
    
    ChatMessages.Add(infoMessage);
    UpdateChatDisplay(GetCurrentChatType());
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

void UChatUI::UpdateChatDisplay(EChatType ChatType)
{
    if (!ChatOutputBox) return;

    //기존에 채팅 박스에 들어있는 채팅들을 전부 날린다.
    ChatOutputBox->ClearChildren();

    TArray<EChatType> SelectedChatTypes;
    
    //일반 탭을 눌렀을 경우 세팅해놓은 타입들의 채팅들을 전부 가져온다.
    if (ChatType == EChatType::General)
    {
        SelectedChatTypes = GetSelectedChatTypes();
    }
    else
    {
        SelectedChatTypes.Add(ChatType);
    }

    //ChatMessage에 보관되어 있는 채팅들을 타입에 맞게 다시 채팅 박스에 넣어준다.
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

    for (TTuple<EChatType, UCheckBox*> ChatBox : CheckBoxMap)
    {
        if(ChatBox.Value->IsChecked())
            SelectedChatTypes.Add(ChatBox.Key);
    }
    return SelectedChatTypes;
}

void UChatUI::SaveChatOption()
{

    if (IsValid(GameOptionData) == false)
    {

        LoadChatOption();

        //불러왔는데도 없으면 무언가 문제가 있는거므로 리턴.
        if (IsValid(GameOptionData) == false)
        {
            UUtilBlueprintFunctionLibrary::DebugLog(TEXT("게임 옵션 데이터를 불러올 수 없습니다. ChatUI.Cpp Error"));
            return;
        }
    }

    //체크 되어 있다면 True, 아니라면 False,
    for (TTuple<EChatType, UCheckBox*> ChatBox : CheckBoxMap)
    {
		bool Ret = GameOptionData->ChatOption.bVisibleChatOption.Contains(ChatBox.Key);
		if (Ret)
		{
			GameOptionData->ChatOption.bVisibleChatOption[ChatBox.Key] = ChatBox.Value->IsChecked();
		}
		else {
            //혹시라도 옵션 데이터에 해당 키에 맞는 밸류가 없으면 새로 추가해준다.
            GameOptionData->ChatOption.bVisibleChatOption.Add(ChatBox.Key, ChatBox.Value->IsChecked());
		}
    }

    UGameplayStatics::SaveGameToSlot(GameOptionData, UGameOptionData::SlotName, 0);
}

void UChatUI::LoadChatOption()
{
    FString SlotName = UGameOptionData::SlotName;
    bool Ret = UGameplayStatics::DoesSaveGameExist(SlotName, 0);

    //세이브 데이터가 있으면 불러오고, 없으면 임시적으로 새로 만든다
    if (Ret == true)
    {
        UGameOptionData* LoadGameOptionData = Cast<UGameOptionData>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

        if (IsValid(LoadGameOptionData) == false)
        {
            UUtilBlueprintFunctionLibrary::DebugLog(TEXT("LoadChatOption Fail. LoadGameOptionData Is Valid 확인."));
            return;
        }
        
        GameOptionData = LoadGameOptionData;
    }
    //나중에 삭제될 확률이 높은 코드. (나중에 옵션 데이터를 제대로 다뤄주게 되면 삭제될 것.)
    else if (Ret == false)
    {
         UGameOptionData* NewGameOptionData = Cast<UGameOptionData>(UGameplayStatics::CreateSaveGameObject(UGameOptionData::StaticClass()));
         if (IsValid(NewGameOptionData) == false)
         {
             UUtilBlueprintFunctionLibrary::DebugLog(TEXT("LoadChatOption Fail. NewGameOptionData Is Valid 확인."));
             return;
         }

         NewGameOptionData->Init();
         GameOptionData = NewGameOptionData;
    }

     //임시 코드.
    if(GameOptionData->ChatOption.bVisibleChatOption.Num() == 0)
        GameOptionData->Init();

    for (TTuple<EChatType, bool> ChatOption : GameOptionData->ChatOption.bVisibleChatOption)
    {
        if (CheckBoxMap.Find(ChatOption.Key))
        {
            bool IsChecked = ChatOption.Value;
            CheckBoxMap[ChatOption.Key]->SetIsChecked(IsChecked);
        }
    }
}

void UChatUI::SetCurrentChatType(EChatType SelectedChatType)
{
    CurrentChatType = SelectedChatType;
}
EChatType UChatUI::GetCurrentChatType()
{
    return CurrentChatType;
}