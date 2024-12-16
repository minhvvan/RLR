// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/UtilStructs.h"
#include "FriendTabWidget.generated.h"


class UFriendConnectionStatusUI;
class UMoveGroupMessageBox;
class UGorupButtonDragDrop;
class UExistingGroupList;
class UFriendInformation;
class UFriendButtonMenu;
class UFriendRequestUI;
class UFriendButtonUI;
class UGroupButtonUI;
class UFriendListUI;
class UEditableText;
class UComboBoxString;
class UVerticalBox;
class UTextBlock;
class UScrollBox;
class USizeBox;
class UButton;

/*
	친구목록의 Tab
*/

UCLASS()
class RLR_API UFriendTabWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void NativeConstruct() override;
    
    void UpdateFriendTab(const TArray<FFriendGroupResult>& groupData);
    
    UFUNCTION()
    void RequestFriendButtonClicked();

    UFUNCTION()
    void OnPlayerStatusSettingClicked();

    UFUNCTION()
	void AddGroupButtonClicked();    
    UFUNCTION()
	void GroupClickedOnGroupList(UGroupButtonUI* GroupButtonUI);

    UFUNCTION()
    void UpdatePlayerConnectionStatus(FText StatusText);

    UFUNCTION()
    void OnFriendButtonClicked(int friendSeq, UFriendButtonUI* PostButtonUI);
    
    UFUNCTION()
    void OnFriendRightClick(FVector2D AbsolutePosition, UFriendButtonUI* FriendButtonUI);

    UFUNCTION()
    void OnGroupRightClick(FVector2D AbsolutePosition, UGroupButtonUI* GroupButtonUI);

    UFUNCTION()
    void RemoveGroup(int OldGroupSeq);

    UFUNCTION()
    void SearchFriend(const FText& Text);

    UFUNCTION()
    void ChangeGroupOrder();

    UFUNCTION()
    void ReorderGroups(UGroupButtonUI* DraggedButton, UGroupButtonUI* TargetButton);
    
    UFUNCTION()
    void UpdateGroupInfoUI();

    UFUNCTION()
    void CancelMoveGroup();

    void AddFriendButton(int friendSeq, int groupSeq, FString friendName);
    void AddGroupButton(int groupSeq, FString groupName);
    void AddDefaultGroup(const TArray<FFriendGroupResult>& groupData);

private:
    void ClearFriendList();

public:
    UPROPERTY(meta = (BindWidgetOptional))
    UButton* PlayerStatusSetting;

    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* PlayerStatusText;

    UPROPERTY(meta = (BindWidget))
    UScrollBox* FriendScrollBox;

    UPROPERTY(meta = (BindWigetOptional))
    USizeBox* GroupOrderSizeBox;

    UPROPERTY(meta = (BindWidgetOptional))
    UScrollBox* GroupOrderScrollBox;

    UPROPERTY(meta = (BindWidget))
    UEditableText* SearchFriendUI;
    
    UPROPERTY(meta = (BindWidgetOptional))
    UButton* GroupCreationButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* ChangeGroupOrderButton;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* FriendRequestButton;

    UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMoveGroupMessageBox> MoveGroupMessageBox;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UFriendButtonUI> FriendButtonUIClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGroupButtonUI> GroupButtonUIClass;    
    
    UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGroupButtonUI> GroupButtonInGroupListClass;

	UPROPERTY(EditAnywhere, Category = "DragAndDropUI")
	TSubclassOf<UGroupButtonUI> GroupButtonInGroupOrderClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UFriendConnectionStatusUI> FriendConnectionStatusClass;

    UPROPERTY()
    int SelectedFriend;
    int SelectedGroup;

    UPROPERTY()
    UFriendListUI* FriendListUI;

    UPROPERTY()
    TMap<int32, UFriendButtonUI*> FriendButtons;
    TMap<int32, UGroupButtonUI*> GroupButtons;

    UPROPERTY()
    TArray<UGroupButtonUI*> OrderedGroupButtons;
private:
    bool bGroupOrderOpen;
};
