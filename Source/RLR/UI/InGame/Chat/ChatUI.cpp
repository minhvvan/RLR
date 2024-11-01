#include "ChatUI.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ComboBoxString.h"
#include "UI/Components/ComboBoxStringColor.h"
#include "Chat/ChatClient.h"
#include "ChatTabWidget.h"
#include "ChatOptionUI.h"
#include "GameManager/GameManager.h"
#include "GameManager/UIManager.h"
#include "UI/InGame/InGameMainUI.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "Structs/UtilStructs.h"
#include "Kismet/GameplayStatics.h"
#include "RLR.h"

void UChatUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (ChatInput)
	{
		ChatInput->OnTextCommitted.AddUniqueDynamic(this, &UChatUI::OnChatInputCommitted);
	}

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
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChatClient::StaticClass(), FoundActors );
	
	if(FoundActors.Num() <= 0)
		return;

	AChatClient* client = Cast<AChatClient>(FoundActors[0]);
	SetChatClient(client);

	CbbChatType->OnSelectionChanged.AddDynamic(this, &UChatUI::OnChatTypeChanged);
	CbbChatType->SetDefaultOptionColor(TextColor[EChatType::General]);

	//TODO: 채팅타입 추가
	ItemType.Add({ TEXT("전체"), EChatType::General });
	ItemType.Add({ TEXT("길드"), EChatType::Guild });
	ItemType.Add({ TEXT("파티"), EChatType::Party });

	//TODO: Prefix 추가
	Prefix.Add({ EChatType::General, TEXT("")});
	Prefix.Add({ EChatType::Guild, TEXT("/chat")});
	Prefix.Add({ EChatType::Whisper, TEXT("/w")});

	//TODO: Args 추가(길드 이름, 파티 이름(?)...)
	//Args.Add()
}

void UChatUI::InitButton()
{
	if (IsValid(SendButton))
	{
		SendButton->OnClicked.AddUniqueDynamic(this, &UChatUI::OnSendButtonClicked);
	}

	//채팅 옵션 버튼을 누르면 채팅 옵션 UI를 띄운다.
	if (IsValid(ChatOptionButton))
	{
		ChatOptionButton->OnClicked.AddUniqueDynamic(this, &UChatUI::OnChatOptionUIButtonClicked);
	}
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

	//인덱스값이랑 EChatType의 순서랑 맞춰주기.
	AddChatTabWidget(FText::FromString(TEXT("일반")), (int32)EChatType::General);
	AddChatTabWidget(FText::FromString(TEXT("귓속말")), (int32)EChatType::Whisper);
	AddChatTabWidget(FText::FromString(TEXT("국가")), (int32)EChatType::Country);
	AddChatTabWidget(FText::FromString(TEXT("세계")), (int32)EChatType::World);
	AddChatTabWidget(FText::FromString(TEXT("길드")), (int32)EChatType::Guild);
	AddChatTabWidget(FText::FromString(TEXT("레이드")), (int32)EChatType::Raid);
	AddChatTabWidget(FText::FromString(TEXT("파티")), (int32)EChatType::Party);
	AddChatTabWidget(FText::FromString(TEXT("대륙")), (int32)EChatType::Continent);
	AddChatTabWidget(FText::FromString(TEXT("근처")), (int32)EChatType::Nearby);

	if (TabContentSwitcher)
	{
		//TabContentSwitcher->SetActiveWidgetIndex(0);
		OnTabClicked(0);
	}
}

void UChatUI::AddPrefix(FString& Message)
{
	FString selected = CbbChatType->GetSelectedOption();
	if (!ItemType.Contains(selected)) return;
	EChatType chatType = ItemType[selected];

	if (chatType == EChatType::Whisper)
	{
		Message = FString::Printf(TEXT("%s %s %s"), *Prefix[chatType], *selected, *Message);
	}
	else
	{
		Message = FString::Printf(TEXT("%s %s %s"), *Prefix[chatType], *Args[chatType], *Message);
	}
}

void UChatUI::AddChatTabWidget(const FText& TabName, int32 TabIndex)
{
	if (!TabContainer || !TabContentSwitcher)
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
			UChatTabButton* Chatbutton = Cast<UChatTabButton>(NewTabButton->ChattingTabButton);
			if (IsValid(Chatbutton) == false)
				return;

			Chatbutton->SetIndex(TabIndex);

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
	UE_LOG(LogTemp, Log, TEXT("클릭 됨?"));
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

	SetCurrentChatTypeTab((EChatType)TabIndex);
	UpdateChatDisplay((EChatType)TabIndex);
}

void UChatUI::UpdateTabFilters(const FString& TabName, const TArray<EChatType>& FilteredChatTypes)
{
	if (TabFilters.Contains(TabName))
	{
		TabFilters[TabName] = FilteredChatTypes;
		UpdateChatDisplay(GetCurrentChatTypeTab());
	}
}

void UChatUI::AddWhisperChat(FString UserName)
{
	ItemType.Add({ UserName, EChatType::Whisper });

	CbbChatType->AddOption(UserName);
	CbbChatType->SetSelectedOption(UserName);
	CbbChatType->OnSelectionChanged.Broadcast(UserName, ESelectInfo::Type::Direct);
}

void UChatUI::AddChatTab(FString TabName, TArray<EChatType> FilteredChatTypes)
{
	TabFilters.Add(TabName, FilteredChatTypes);
	UpdateChatDisplay(GetCurrentChatTypeTab());
}

void UChatUI::CreateNewTab(const FString& TabName)
{
	if (!TabFilters.Contains(TabName))
	{
		TabFilters.Add(TabName, {});
	}
}

void UChatUI::SetChatClient(AChatClient* InChatClient)
{
	ChatClient = InChatClient;
}

void UChatUI::OnChatInputCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		OnSendButtonClicked();
	}
}

void UChatUI::OnChatTypeChanged(FString Item, ESelectInfo::Type SelectionType)
{
	if (!ItemType.Contains(Item)) return;
	EChatType chatType = ItemType[Item];

	CbbChatType->SetDefaultOptionColor(TextColor[chatType]);
}

void UChatUI::OnSendButtonClicked()
{
	//TODO: 파티, 길드 채팅 정책 필요
	// e.g) 파티가 없을때는 보내지 않음 

	if (ChatClient && ChatInput)
	{
		// 입력된 텍스트 가져오기
		FString Message = ChatInput->GetText().ToString();

		// 개행 문자 제거
		Message.RemoveFromEnd(TEXT("\n"));

		AddPrefix(Message);

		// 서버로 메시지 전송
		ChatClient->SendMessageToServer(Message);

		// 입력 필드 비우기
		ChatInput->SetText(FText::GetEmpty());
	}
}

void UChatUI::OnChatOptionUIButtonClicked()
{
	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (IsValid(GM) == false)
		return;

	UChatOptionUI* ChatOptionUI = GetUIManager()->GetPage<UInGameMainUI>(FGameplayTagManager::Get().Page_InGame)->GetChatOptionUI();

	if (IsValid(ChatOptionUI))
	{
		if (ChatOptionUI->GetVisibility() == ESlateVisibility::Hidden)
		{
			ChatOptionUI->OpenUI();
		}
		else
		{
			ChatOptionUI->CloseUI();
		}
	}
}

void UChatUI::AddChatMessage(FString Message, int ChatType)
{
	if (GEngine && GEngine->GameViewport)
	{
		UWorld* World = GEngine->GameViewport->GetWorld();
		if (World)
		{
			// 타이머 설정을 게임 스레드에서 실행하도록 람다 사용
			AsyncTask(ENamedThreads::GameThread, [this, World, ChatType, Message]()
				{
					FChatMessage infoMessage;
					infoMessage.Message = Message;
					infoMessage.ChatType = EChatType(ChatType);

					ChatMessages.Add(infoMessage);
					UpdateChatDisplay(GetCurrentChatTypeTab());
				});
		}
	}
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

			NewTextBlock->SetColorAndOpacity(TextColor[ChatMessage.ChatType]);
			ChatOutputBox->AddChild(NewTextBlock);
		}
	}
}

TArray<EChatType> UChatUI::GetSelectedChatTypes() const
{
	TArray<EChatType> SelectedChatTypes;

	UGameManager* GM = Cast<UGameManager>(GetGameInstance());
	if (IsValid(GM) == false)
		return SelectedChatTypes;

	for (TTuple<EChatType, bool> ChatOption : GM->GetGameOptionData()->ChatOption.bVisibleChatOption)
	{
		if (ChatOption.Value == true)
			SelectedChatTypes.Add(ChatOption.Key);
	}

	return SelectedChatTypes;
}



void UChatUI::SetCurrentChatTypeTab(EChatType SelectedChatType)
{
	CurrentChatTypeTab = SelectedChatType;
}
EChatType UChatUI::GetCurrentChatTypeTab()
{
	return CurrentChatTypeTab;
}

