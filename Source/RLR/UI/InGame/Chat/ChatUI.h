#pragma once

#include "CoreMinimal.h"
#include "GameOptionData/GameOptionData.h"
#include "UI/SubUI.h"
#include "ChatUI.generated.h"



class AChatClient;
class UChatTabWidget;
class UScrollBox;
class UChatOptionUI;
class UWidgetSwitcher;
class UComboBoxStringColor;
class UEditableTextBox;
class UCheckBox;


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
class RLR_API UChatUI : public USubUI
{
    GENERATED_BODY()

public:
    UPROPERTY()
    EChatType       CurrentChatTypeTab = EChatType::General;
    void            SetCurrentChatTypeTab(EChatType SelectedChatType);
    EChatType       GetCurrentChatTypeTab();

    UFUNCTION(BlueprintCallable)
    void AddChatTabWidget(const FText& TabName, int32 TabIndex);

    UFUNCTION(BlueprintCallable)
    void HandleTabButtonClicked(UChatTabButton* ClickedButton);

    UFUNCTION(BlueprintCallable)
    void OnTabClicked(int32 index);

    UFUNCTION(BlueprintCallable)
    void AddChatMessage(FString Message, int ChatType);

    UFUNCTION(BlueprintCallable)
    void AddMessageToScrollBox(UScrollBox* ScrollBox, const FString& Message, FLinearColor Color);

    void AddChatTab(FString TabName, TArray<EChatType> FilteredChatTypes);
   
    UFUNCTION(BlueprintCallable)
    void SetChatClient(AChatClient* InChatClient);

    UFUNCTION(BlueprintCallable)
    void CreateNewTab(const FString& TabName);

    UFUNCTION(BlueprintCallable)
    void UpdateTabFilters(const FString& TabName, const TArray<EChatType>& FilteredChatTypes);

    void AddWhisperChat(FString UserName);

protected:
    virtual void NativeConstruct() override;
    void InitButton();
    void InitChatBox();

    void AddPrefix(FString& Message);

public:

    UPROPERTY(meta = (BindWidget))
    UScrollBox* ChatOutputBox;

    UPROPERTY(meta = (BindWidget))
    UEditableTextBox* ChatInput;

    UPROPERTY(meta = (BindWidget))
    UComboBoxStringColor* CbbChatType;

    UPROPERTY(meta = (BindWidget))
    UButton* SendButton;

    UButton* LastClickedButton = nullptr;

    UPROPERTY(meta = (BindWidget))
    UButton* ChatOptionButton;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UScrollBox* TabContainer;

    UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* TabContentSwitcher;

private:
    TMap<FString, TArray<EChatType>> TabFilters;
    TArray<FChatMessage> ChatMessages;
    TArray<TObjectPtr<UChatTabWidget>> ChatTabs;
    TMap<TObjectPtr<UButton>, int32> TabButtonToIndexMap;
    TObjectPtr<AChatClient> ChatClient;

    UPROPERTY(EditAnywhere, Category = chatType)
    TMap<EChatType, FString> Prefix;

    UPROPERTY(EditAnywhere, Category = chatType)
    TMap<EChatType, FString> Args;

    UPROPERTY(EditAnywhere, Category=chatType)
    TMap<FString, EChatType> ItemType;

    UPROPERTY(EditAnywhere, Category = chatType)
    TMap<EChatType, FSlateColor> TextColor;

public:
    void UpdateChatDisplay(EChatType ChatType);

    UFUNCTION(BlueprintCallable)
    void OnChatInputCommitted(const FText& Text, ETextCommit::Type CommitMethod);

    UFUNCTION()
    void OnChatTypeChanged(FString Item, ESelectInfo::Type SelectionType);

    //버튼 이벤트
    UFUNCTION(BlueprintCallable)
    void OnSendButtonClicked();

    UFUNCTION(BlueprintCallable)
    void OnChatOptionUIButtonClicked();

    //체크 되어 있는 채팅 타입들을 가져온다.
    TArray<EChatType> GetSelectedChatTypes() const;
};
