// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubUI.h"
#include "Structs/UtilStructs.h"
#include "FriendListUI.generated.h"

class UFriendRequestMessageBox;
class UFriendRequestTabWidget;
class UExistingGroupList;
class UFriendRequestUI;
class UFriendButtonMenu;
class UGroupButtonMenu;
class UFriendInformation;
class UFriendTabWidget;
class UFriendButtonUI;
class UGroupCreationUI;
class UWidgetSwitcher;

/*
	친구목록의 모든 Tab이 존재하는 UI
*/

UCLASS()
class RLR_API UFriendListUI : public USubUI
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void Init();

    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    bool IsInUI(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

    UFUNCTION(BlueprintCallable)
    virtual void RefreshUI() override;

    UFUNCTION()
    void OnFriendRightMouseClicked(FVector2D ButtonAbsolutePosition, UFriendButtonUI* FriendButtonUI);
    UFUNCTION()
    void OnGroupRightMouseClicked(FVector2D ButtonAbsolutePosition, UGroupButtonUI* GroupButtonUI);

    UFUNCTION()
    void SetFriendData(TArray<FFriendGroupResult> NewFriendData);

    UFUNCTION()
    void SetFriendRequestData(TMap<int32, FString> NewFriendRequestData);

    UFUNCTION()
    TArray<FFriendGroupResult>& GetFriendData();

    UFUNCTION()
    void OnFriendTabButtonClicked();

    UFUNCTION()
    void OnFriendRequestTabButtonClicked();

    UFUNCTION()
    void OpenFriendInfoUI(int FriendSeq);
    
    UFUNCTION()
    void OpenFriendRequestUI(bool bOpen);
    UFUNCTION()
    void OpenFriendMenuUI(bool bOpen);
    UFUNCTION()
    void OpenAddGroupUI(bool bOpen);
    UFUNCTION()
    void OpenGroupMenuUI();

    UFUNCTION()
    void RemoveGroup(int OldGroupSeq);

    UFUNCTION()
    void MoveGroup();

    void SetFriendRequestMessageBox(FString& PlayerName);
    void SetMoveGroupMessageOpenState(bool bOpen);

public:
    UPROPERTY(VisibleAnywhere, meta = (BindWidget))
    TObjectPtr<UFriendRequestUI> FriendRequestUI;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget))
    TObjectPtr<UFriendButtonMenu> FriendMenuUI;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget))
    TObjectPtr<UGroupButtonMenu> GroupMenuUI;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget))
    TObjectPtr<UFriendInformation> FriendInfoUI;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget))
    TObjectPtr<UGroupCreationUI> GroupCreationUI;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget))
    TObjectPtr<UFriendTabWidget> FriendTabWidget;

    UPROPERTY(VisibleAnywhere, meta = (BindWidget))
    TObjectPtr<UFriendRequestTabWidget> FriendRequestTabWidget;

	UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* FriendWidgetSwitcher;

    UPROPERTY(meta = (BindWidget))
    UButton* FriendTabButton;

    UPROPERTY(meta = (BindWidget))
    UButton* FriendRequestTabButton;
    
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UFriendRequestMessageBox> FriendRequestMessageBoxClass;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FFriendGroupResult> FriendData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, FString> FriendRequestData;

private:
    bool bOpenRequestUI;
    bool bOpenFriendMenuUI;
    bool bOpenGroupMenuUI;
    bool bOpenFriendInfoUI;
    bool bOpenGroupCreationUI;
    bool bIsMoveGroupMessageBoxOpen;
    int32 SelectedFriend;
    int32 SelectedGroup;

    FVector2D GetButtonRightCenter(FVector2D ViewportSize);
	FVector2D FriendRelativePosition;
    FVector2D GroupRelativePosition;

    // FriendListUI.h
    FTimerHandle FriendRequestMessageBoxTimerHandle;
};
