// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/UtilStructs.h"
#include "BaseGuildMember.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGuildMemberRightClickedSignature, FVector2D, AbsolutePosition, UBaseGuildMember*, GuildMember);

class UTextBlock;
class UButton;
class UImage;
/**
 * Base Guild Member Button
 */
UCLASS()
class RLR_API UBaseGuildMember : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetGuildMember(FGuildRank NewGuildMember);
	FGuildRank GetGuildMember();

	void SetUserNameText(FString GuildMemberName);
	FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnGuildMemberRightClickedSignature OnGuildMemberRightClicked;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> UserNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> UserLevelText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> JobIconImage;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	bool bIsGuildJoinUserButton = false;

protected:
	UPROPERTY()
	FGuildRank guildMember;
};
