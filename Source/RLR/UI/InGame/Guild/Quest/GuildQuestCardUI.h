// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/UtilStructs.h"
#include "Structs/ObjectStructs.h"
#include "GuildQuestCardUI.generated.h"

class UBorder;
/**
 * 길드 의뢰탭에서 랜덤으로 생성되는 의뢰카드, EGuildQuestType에 따라 색상 변경됨
 */
UCLASS()
class RLR_API UGuildQuestCardUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetColorAsQuestType(FGuildQuest NewGuildQuestDatum);
	FQuest GetGuildQuestType();
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> Border;

	
private:
	FGuildQuest GuildQuestDatum;
};
