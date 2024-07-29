// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Option/KeyOption/KeyOptionElement.h"

#include "Components/TextBlock.h"
#include "Components/InputKeySelector.h"
#include "GameManager/GameplayTagManager.h"

/*

	입력된 키를 어떻게?

*/

void UKeyOptionElement::NativeConstruct()
{
	Super::NativeConstruct();

}

void UKeyOptionElement::RefreshUI()
{
	Super::RefreshUI();


	if(InputTag == FGameplayTag::EmptyTag)
		return;

	FText InputText =  FText::FromString(InputTag.GetTagName().ToString());

	FString InputString = InputTag.GetTagName().ToString();
	FString Prefix = TEXT("Input.");

	// 'Input.' 이후의 문자열을 추출
	int32 PrefixLength = Prefix.Len();
	FString AfterPrefix = InputString.Mid(PrefixLength);

	TArray<FKey> KeyList;
	EKeys::GetAllKeys(KeyList);

	for (FKey& Key : KeyList)
	{
		if (Key.GetFName() == AfterPrefix)
		{
			FInputChord InputChord(Key);
			InputTagKeySelector_1->SetSelectedKey(InputChord);
			break;
		}
	}

}

void UKeyOptionElement::ApplyInputTagOptions()
{
	/*
		UI에서 입력된 인풋 값을 적용한다.
	*/
	/*
		지금은 일단 첫 번째 키만 다룬다.
		나중에 키 바인딩이 꽉 차면 두 번째 값도 다루게 될 건데, 과연 그렇게 될지는 의문.
	*/


	FText FirstKey = FText::Format(FText::FromString("Input.{0}"), InputTagKeySelector_1->GetSelectedKey().GetKeyText(true));
	//FText SecondKey = FText::Format(FText::FromString("Input.{0}"), InputTagKeySelector_2->GetKeySelectionText());

	FGameplayTag FindTag = UGameplayTagsManager::Get().RequestGameplayTag(FName(*FirstKey.ToString()), false);

	if (FindTag != FGameplayTag::EmptyTag)
	{
		SetInputTag(FindTag);
	}

}

void UKeyOptionElement::SetKeyOption(UInputAction* Action, EInputType Type, FGameplayTag TargetKeyTag, FGameplayTag TargetActionTag)
{
	InputAction = Action;
	InputType = Type;
	InputTag = TargetKeyTag;
	ActionTag =TargetActionTag;
}