// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "../../../Network/Proto/Packet.pb.h"
#include "GameManager/RLRStruct.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "PartyListElement.generated.h"

/**
 
	Party UI에 들어갈 플레이어 슬롯

 */

 class URichTextBlock;
 class UProgressBar;

UCLASS()
class RLR_API UPartyListElement : public UBaseUI, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void RefreshUI() override;
	void SetPercentHpBar(float Value);


	/*
		나중에 플레이어 이름에 특수한 효과를 적용할 수 있으므로 RichText 사용.
	*/
	void SetPlayerName(FString String);
	
	void SetUserCharacterData(const FUserCharacter& Data);
	FUserCharacter* GetUserCharacterData();


public:

	/*
		Bind
	*/
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<URichTextBlock>			PlayerNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UProgressBar>				PlayerProgressBar;

	/*
	
		버프 관련해서 프로젝트 진행이 더 된다면, 플레이어의 상태 이상을 알 수 있는 리스트를 추가해줄 것.

	*/

public:
	TSharedPtr<FUserCharacter> UserCharacterData;
};
