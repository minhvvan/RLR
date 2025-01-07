// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/UtilStructs.h"
#include "GuildMemberUI.generated.h"

class UGuildMemberButtonMenu;
class UGuildMember;
class UScrollBox;
/**
 * 길드원 목록 탭
 */
UCLASS()
class RLR_API UGuildMemberUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void UpdateGuildMemberUI(FGuildResult NewGuildData);
	TArray<TObjectPtr<UGuildMember>> GetGuildMembers();

	void AddGuildMembers(FGuildRank NewGuildMember);

	UFUNCTION()
	void OnGuildMemberRightClicked(FVector2D AbsolutePosition, UBaseGuildMember* GuildMemberButtonUI);

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGuildMemberButtonMenu> GuildMemberButtonMenu;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> GuildMemberScrollBox;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGuildMember> GuildMemberClass;

private:
	TArray<TObjectPtr<UGuildMember>> guildMembers;
	FGuildRank selectedGuildMember;
	bool bIsGuildMemberMenuOpen;
};
