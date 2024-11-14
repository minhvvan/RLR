// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "BadgeUI.generated.h"

class UExpProgressBar;
/**
 * 
 */
UCLASS()
class RLR_API UBadgeUI : public UBaseUI
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 userLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
		TObjectPtr<UExpProgressBar> ExpProgressBar;

	UFUNCTION(BlueprintCallable)
	void UpdateExp(int32 newExp);

protected:
	virtual void NativeConstruct() override;

private:
	void SetUserLevel();
	bool IsLevelUP();


	
};
