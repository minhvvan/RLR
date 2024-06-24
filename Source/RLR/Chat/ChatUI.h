#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "Components/HorizontalBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include <Components/EditableTextBox.h>
#include <Components/Button.h>
#include "ChatTabWidget.h"
#include "GameOptionData/GameOptionData.h"
#include "ChatUI.generated.h"



class AChatClient;
class UChatTabWidget;


//헤더 파일 관리를 위해 GameOptionData로 보내줌.
//UENUM(BlueprintType)
//enum class EChatType : uint8
//{
//    General = 0,
//    Whisper= 1,
//    Country = 2,
//    World = 3,
//    Guild = 4,
//    Raid = 5,
//    Party = 6,
//    Continent = 7,
//    Nearby = 8
//};

USTRUCT(BlueprintType)
struct FChatMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Message;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    EChatType ChatType;
};

UCLASS()
class RLR_API UChatUI : public UUserWidget
{
    GENERATED_BODY()

public:

    UPROPERTY(meta = (BindWidget))
    UCanvasPanel* ChatOptionUI;

    UPROPERTY(meta = (BindWidget))
    UScrollBox* ChatOutputBox;

    UPROPERTY(meta = (BindWidget))
    UEditableTextBox* ChatInput;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* UserNameBox;

    UPROPERTY(meta = (BindWidget))
    UButton* SendButton;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* GeneralCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* WhisperCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* GuildCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* RaidCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* PartyCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* CountryCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* ContinentCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* NearbyCheckBox;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* WorldCheckBox;

    UButton* LastClickedButton = nullptr;

     UPROPERTY(meta = (BindWidget))
    UButton* ConfirmButton;

     UPROPERTY(meta = (BindWidget))
    UButton* CancelButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ChatOptionButton;

    UPROPERTY(meta = (BindWidget))
    class UHorizontalBox* TabContainer;

    UPROPERTY(meta = (BindWidget))
    class UWidgetSwitcher* TabContentSwitcher;

     UPROPERTY()
    TMap<EChatType, UCheckBox*> CheckBoxMap;

    UPROPERTY()
    EChatType CurrentChatType = EChatType::General;
    void                SetCurrentChatType(EChatType SelectedChatType);
    EChatType   GetCurrentChatType();



    UFUNCTION(BlueprintCallable)
    void AddChatTabWidget(const FText& TabName, int32 TabIndex);

    UFUNCTION(BlueprintCallable)
    void HandleTabButtonClicked(UChatTabButton* ClickedButton);

    UFUNCTION(BlueprintCallable)
    void OnTabClicked(int32 index);

    UFUNCTION(BlueprintCallable)
    void AddChatMessage(const FString& Message, int ChatType);

    UFUNCTION(BlueprintCallable)
    void AddMessageToScrollBox(UScrollBox* ScrollBox, const FString& Message, FLinearColor Color);

    void AddChatTab(FString TabName, TArray<EChatType> FilteredChatTypes);
   

    UFUNCTION(BlueprintCallable)
    void SetUserNameText(FString PlayerID);

    UFUNCTION(BlueprintCallable)
    void SetChatClient(AChatClient* InChatClient);

    UFUNCTION(BlueprintCallable)
    void CreateNewTab(const FString& TabName);

    UFUNCTION(BlueprintCallable)
    void UpdateTabFilters(const FString& TabName, const TArray<EChatType>& FilteredChatTypes);

protected:
    virtual void NativeConstruct() override;

    void InitButton();
    void InitChatBox();

private:
    TMap<FString, TArray<EChatType>> TabFilters;
    TArray<FChatMessage> ChatMessages;
    TArray<TObjectPtr<UChatTabWidget>> ChatTabs;
    TMap<TObjectPtr<UButton>, int32> TabButtonToIndexMap;
    TObjectPtr<AChatClient> ChatClient;

    void UpdateChatDisplay(EChatType ChatType);

    UFUNCTION(BlueprintCallable)
    void OnChatInputCommitted(const FText& Text, ETextCommit::Type CommitMethod);


    //버튼 이벤트
    UFUNCTION(BlueprintCallable)
    void OnSendButtonClicked();

    UFUNCTION(BlueprintCallable)
    void OnChatOptionUIButtonClicked();

    UFUNCTION(BlueprintCallable)
    void OnConfirmButtonClicked();

     UFUNCTION(BlueprintCallable)
    void OnCancelButtonClicked();

    //

    UFUNCTION(BlueprintCallable)
    void OnFilterChanged(bool bIsChecked);

    //체크 되어 있는 채팅 타입들을 가져온다.
    TArray<EChatType> GetSelectedChatTypes() const;


public:

    //채팅 옵션을 저장해준다.
    UFUNCTION(BlueprintCallable)
    void SaveChatOption();

    //채팅 옵션을 불러온다.
    UFUNCTION(BlueprintCallable)
    void LoadChatOption();

    //임시 변수. 나중에 UI 매니저 만들면 따로 옮겨줄 것.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UGameOptionData* GameOptionData; 
};
