// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUI.h"
#include "UI/SubUI.h"
#include "OptionUI.generated.h"

/*
	옵션 UI

	1.그래픽
	2.오디오
	3.커뮤니티
	4.게임플레이
	5.단축키

	옵션 정보는 SaveData를 통해 로컬에서 저장
*/

class UGraphicsOption;
class UAudioOption;
class UCommunityOption;
class UGameplayOption;
class UKeyOption;

class UButton;
class UTextBlock;
class UWidgetSwitcher;

UENUM(BlueprintType)
enum class OptionUI_TabType : uint8
{
	GraphicsOption = 0,		//그래픽
	AudioOption = 1,		//오디오
	CommunityOption = 2,	//커뮤니티
	GameplayOption = 3,		//게임 플레이
	KeyOption = 4,			//단축키
	None = 5,
};

UCLASS()
class RLR_API UOptionUI : public USubUI
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void Init() override;
	virtual void RefreshUI() override;
	virtual void OpenUI() override;
	virtual void Clear() override;
	virtual void CloseUI() override;

public:

	void SaveGameOption();
	void LoadGameOption();	//게임 옵션 불러오기
	void ResetGameOption();	//게임 옵션 디폴트로 초기화

public:

	UFUNCTION()
	void OnClickedResetButton();
	UFUNCTION()
	void OnClickedApplyButton();
	UFUNCTION()
	void OnClickedConfirmButton();
	UFUNCTION()
	void OnClickedCancelButton();

public:

	//Tab 관련 함수
	void ChangeTab(OptionUI_TabType TabType);

public:

	/*
		bind
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> ResetButton;	//초기화

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> ApplyButton;	//적용

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> ConfirmButton;	//확인

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> CancelButton;	//취소

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> GraphicsOptionButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> AudioOptionButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> CommunityOptionButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> GameplayOptionButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButton> KeyOptionButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> OptionWidgetSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UGraphicsOption> GraphicsOption;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UAudioOption> AudioOption;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UCommunityOption> CommunityOption;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UGameplayOption> GameplayOption;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UKeyOption> KeyOption;
};
