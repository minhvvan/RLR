#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "Components/HorizontalBox.h"
#include "Components/WidgetSwitcher.h"
#include <Components/EditableTextBox.h>
#include <Components/Button.h>
#include "ChatTabWidget.h"
#include "ChatUI.generated.h"



class AChatClient;

UENUM(BlueprintType)
enum class EChatType : uint8
{
    General,
    Whisper,
    Country,
    World,
    Guild,
    Raid,
    Party,
    Continent,
    Nearby
};

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
    class UHorizontalBox* TabContainer;

    UPROPERTY(meta = (BindWidget))
    class UWidgetSwitcher* TabContentSwitcher;

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

private:
    TMap<FString, TArray<EChatType>> TabFilters;
    TArray<FChatMessage> ChatMessages;
    TArray<class UChatTabWidget*> ChatTabs;
    TMap<UButton*, int32> TabButtonToIndexMap;
    AChatClient* ChatClient;

    void UpdateChatDisplay();

    UFUNCTION(BlueprintCallable)
    void OnChatInputCommitted(const FText& Text, ETextCommit::Type CommitMethod);


    UFUNCTION(BlueprintCallable)
    void OnSendButtonClicked();

   
  



    UFUNCTION(BlueprintCallable)
    void OnFilterChanged(bool bIsChecked);

    TArray<EChatType> GetSelectedChatTypes() const;
};
