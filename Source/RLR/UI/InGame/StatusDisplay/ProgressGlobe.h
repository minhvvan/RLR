// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "ProgressGlobe.generated.h"

/**
 * 
 */

 class UProgressBar;
 class UImage;

UCLASS()
class RLR_API UProgressGlobe : public UBaseUI
{
	GENERATED_BODY()


public:

	virtual void NativeConstruct();

	virtual void NativeTick(FGeometry MyGeometry, float InDeltaTime);

	UFUNCTION(BlueprintCallable)
	void SetGlobePercent(float Value);

	//Globe에 수치 입력 후, 일정 시간 딜레이 후에 Ghost에 값을 넣기 위한 블루프린트 함수.
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void GlobePercentSet(float Value);

	UFUNCTION(BlueprintCallable)
	void SetGhostPercent(float Value);



	UFUNCTION(BlueprintCallable)
	void InterptGhostGlobe(float DeltaTime);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_Ghost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_Globe;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UImage> Image_Glass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UImage> Image_Background;

public:


	UPROPERTY()
	bool GlobeInitialized = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GhostPercentTarget = 0;

	UPROPERTY()
	float GhostInterpSpeed = 1.0f;
};
