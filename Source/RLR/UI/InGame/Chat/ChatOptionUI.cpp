// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatOptionUI.h"
#include "GameOptionData/GameOptionData.h"
#include "GameManager/GameManager.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "UI/InGame/Chat/ChatUI.h"
#include "UI/InGame/InGameMainUI.h"


void UChatOptionUI::NativeConstruct()
{
    //필터가 바뀌어도 채팅 탭이 다를 수 있으니 현재 선택되어 있는 타입을 불러와준다.
    Super::NativeConstruct();
    LoadChatOption();
    Init();
}

void UChatOptionUI::Init()
{
    GeneralCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatOptionUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::General, GeneralCheckBox);

    WhisperCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatOptionUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::Whisper, WhisperCheckBox);

    CountryCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatOptionUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::Country, CountryCheckBox);

    WorldCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatOptionUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::World, WorldCheckBox);

    ContinentCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatOptionUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::Continent, ContinentCheckBox);

    RaidCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatOptionUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::Raid, RaidCheckBox);

    PartyCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatOptionUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::Party, PartyCheckBox);

    GuildCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatOptionUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::Guild, GuildCheckBox);

    NearbyCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UChatOptionUI::OnFilterChanged);
    CheckBoxMap.Add(EChatType::Nearby, NearbyCheckBox);

    if (IsValid(ConfirmButton))
    {
        ConfirmButton->OnClicked.AddUniqueDynamic(this, &UChatOptionUI::OnConfirmButtonClicked);
    }

    if (IsValid(CancelButton))
    {
        CancelButton->OnClicked.AddUniqueDynamic(this, &UChatOptionUI::OnCancelButtonClicked);
    };
}

void UChatOptionUI::OpenUI()
{
    Super::OpenUI();
    LoadChatOption();
}

void UChatOptionUI::CloseUI()
{
    Super::CloseUI();

}

void UChatOptionUI::OnFilterChanged(bool bIsChecked)
{

}

void UChatOptionUI::LoadChatOption()
{
    UGameManager* GM = Cast<UGameManager>(GetGameInstance());

    if (IsValid(GM) == false)
    {
        UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UChatOption::LoadChatOption Error."));
    }

    UGameOptionData* GameOptionData = GM->GetGameOptionData();

    for (TTuple<EChatType, bool> ChatOption : GameOptionData->ChatOption.bVisibleChatOption)
    {
        if (CheckBoxMap.Find(ChatOption.Key))
        {
            bool IsChecked = ChatOption.Value;
            CheckBoxMap[ChatOption.Key]->SetIsChecked(IsChecked);
        }
    }
}

void UChatOptionUI::SaveChatOption()
{
    UGameManager* GM = Cast<UGameManager>(GetGameInstance());

    if (IsValid(GM) == false)
    {
        UUtilBlueprintFunctionLibrary::DebugLog(TEXT("UChatOption::SaveChatOption Error."));
    }

    UGameOptionData* GameOptionData = GM->GetGameOptionData();

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

    GM->SaveGameOption();
}


void UChatOptionUI::OnConfirmButtonClicked()
{
    if (IsValid(ConfirmButton))
    {
        CloseUI();
        SaveChatOption();

        UChatUI* ChatUI = GetMainUI<UInGameMainUI>()->ChatUI;
        if(ChatUI)
            ChatUI->UpdateChatDisplay(ChatUI->GetCurrentChatTypeTab());
    }
}

void UChatOptionUI::OnCancelButtonClicked()
{
    if (IsValid(CancelButton))
    {
        CloseUI();
        LoadChatOption();
    }
}
