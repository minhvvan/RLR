// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Option/KeyOption/KeyOption.h"
#include "UI/InGame/Option/KeyOption/KeyOptionElement.h"
#include "UI/InGame/CharacterStatusDisplay/CharacterStatusDisplay.h"
#include "UI/InGame/InGameMainUI.h"
#include "UI/MainUI.h"

#include "GameManager/GameplayTagManager.h"
#include "GameManager/UIManager.h"
#include "GameManager/GameManager.h"
#include "GameManager/DataManager.h"

#include "Components/InputKeySelector.h"
#include "Components/Button.h"

#include "Player/RLRPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetTree.h"
#include "Structs/UtilStructs.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "UObject/Package.h"
#include "AssetRegistry/AssetRegistryModule.h"

#if WITH_EDITOR
#include "UnrealEd.h"
#endif

void UKeyOption::NativeConstruct()
{
	Super::NativeConstruct();
	SetUITag(FGameplayTagManager::Get().UI_KeyOption);
	
	TArray<UWidget*> Array;
	WidgetTree->GetAllWidgets(Array);

	//ActionTag를 키값으로 맵을 만들어준다.
	for (auto Widget : Array)
	{
		if (UKeyOptionElement* OptionElement = Cast<UKeyOptionElement>(Widget))
		{
			
			if(OptionElement->ActionTag == FGameplayTagManager::Get().None)
				continue;

			KeyOptionList.Add(OptionElement->ActionTag, OptionElement);
		}
	}

	ConfirmButton->OnClicked.AddUniqueDynamic(this, &UKeyOption::OnClickedConfirmButton);
	CancelButton->OnClicked.AddUniqueDynamic(this, &UKeyOption::OnClickedCancelButton);

}

void UKeyOption::OpenUI()
{
	Super::OpenUI();
}

void UKeyOption::RefreshUI()
{
	Super::RefreshUI();
	LoadKeyOption();
}


void UKeyOption::LoadKeyOption()
{
	/*
		Input Config 의 설정들을 불러와서 UI에 적용한다.
	*/
	
	for (TTuple<FGameplayTag, UKeyOptionElement*> Find : KeyOptionList)
	{
		UKeyOptionElement* Element = Find.Value;
		if(IsValid(Element) == false)
			continue;

		//Action Tag에 맞는 input Tag를 찾아야 한다.
		FGameplayTag InputTag = GameInstance->GetDataManager()->GetInputConfig()->FindInputTagByActionTag(Element->ActionTag);

		if (InputTag == FGameplayTag::EmptyTag)
		{
			Element->SetInputTag(FGameplayTag::EmptyTag);
			continue;
		}
	

		Element->SetInputTag(InputTag);
		Element->RefreshUI();
	}
}

void UKeyOption::ApplyKeyOption()
{
	/*
		Key Option Element 정보들을 가져와서 적용한다.
	*/

	URLRInputConfig* InputConfig = GameInstance->GetDataManager()->GetInputConfig();
	if (IsValid(InputConfig) == false)
	{
		DEBUG_MESSAGE;
		return;
	}


	for (TTuple<FGameplayTag, UKeyOptionElement*> Find : KeyOptionList)
	{
		FGameplayTag ActionTag = Find.Key;
		UKeyOptionElement* Element = Find.Value;


		FGameplayTag OldInputTag = Element->InputTag;

		Element->ApplyInputTagOptions();
		FGameplayTag NewInputTag = Element->InputTag;

		//수정된게 없으면 무시.
		if(OldInputTag == NewInputTag)
			continue;

		//입력된 값이 없으면 무시
		if (NewInputTag == FGameplayTag::EmptyTag)
			continue;


		/*
			InputConfig에서 Input Tag, Input Action 은 고정
			수정되어야 할 건, 이것들과 연결된 Action Tag와 Input Type;

			InputConfig의  RLRInput 리스트 에서 New Input Tag와 맞는 값을 찾아서,
			Action Tag 와 Input Type  값을 바꿔준다.

			*/

		/*

			그런데 만약 다른 액션이 이미 할당되어 있던 곳이라면?

			방법1. 다른 값이 있으면 비워준다.
			방법2. 서로 위치를 바꿔준다.

					-> 방법 1. 일단 가른 값이 있으면 비워주는 방향으로.

		*/

		FRLRInput& RLRInput = InputConfig->FindRLRInputByInputTag(NewInputTag);
		if(RLRInput.InputAction == nullptr)
			continue;

		RLRInput.SetActionTag(ActionTag);
		RLRInput.SetInputType(Element->InputType);


		/*
			기존에 할당되어 있던 RLRInput 값은 비워준다.		

				현재 순차적으로 변경 중. 그래서 앞에 있던 다른 옵션이 먼저 값을 바꾸면서, 뭔가뭔가 순서가 꼬일 수도 있다.
				그러니 값을 비워주는 건, 먼저 값을 바꿔주고, 기존의 RLRInput 값에 그대로 값이 유지되어 있다면 비워준다.
		*/

		if (OldInputTag == FGameplayTag::EmptyTag)
			continue;

		FRLRInput& OldRLRInput = InputConfig->FindRLRInputByInputTag(OldInputTag);

		if (OldRLRInput.ActionTag == ActionTag)
		{
			OldRLRInput.ClearActionTagAndInputType();
		}
	}


	FString OutClassName;
	FString OutPackageName;
	FString OutObjectName;
	FString OutSubObjectName;
	FPackageName::SplitFullObjectPath(InputConfig->GetFullName(), OutClassName, OutPackageName, OutObjectName, OutSubObjectName);

	UE_LOG(LogTemp, Error, TEXT("OutClassName : %s  OutPackageName : %s  OutObjectName : %s  OutSubObjectName : %s"),
		*OutClassName,
		*OutPackageName,
		*OutObjectName,
		*OutSubObjectName);

	FString PackageName = OutPackageName;
	UPackage* Package = CreatePackage(*PackageName);
	Package->FullyLoad();
	Package->MarkPackageDirty();
	FAssetRegistryModule::AssetCreated(InputConfig);

	FString PackageFileName = FPackageName::LongPackageNameToFilename(
		PackageName, FPackageName::GetAssetPackageExtension());

	bool bSaved = UPackage::SavePackage(
		Package,
		InputConfig,
		EObjectFlags::RF_Public | EObjectFlags::RF_Standalone,
		*PackageFileName,
		GError, nullptr, true, true, SAVE_NoError);


	// 에셋의 수정 내용을 에디터에도 적용시켜준다.
	TArray<UObject*> ObjectsToSync;
	ObjectsToSync.Add(InputConfig);
#if WITH_EDITOR
	GEditor->SyncBrowserToObjects(ObjectsToSync);
#endif
	/*
		플레이어 InputComponent를 가져와서 다시 적용 시킨다.
	*/
	ARLRPlayerController* PC = Cast<ARLRPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (IsValid(PC) == false)
	{
		return;
	}

	PC->InitBinding();
	RefreshUI();

	/*
		퀵 슬롯도 업데이트
	*/
	auto UIManager = GetUIManager();
	if (!UIManager) return;

	UCharacterStatusDisplay* CharacterStatusDisplay = UIManager->GetSubUI<UCharacterStatusDisplay>(RLRTAG.UI_Character_StatusDisplay);
	if(IsValid(CharacterStatusDisplay) == false)
		return;

	CharacterStatusDisplay->LoadSkillQuickSlotData();
	CharacterStatusDisplay->LoadItemQuickSlotData();
}

void UKeyOption::CreateDataAsset()
{
	FString AssetName = RLRLITERAL.AssetName;
	FString PackageName = RLRLITERAL.PackageName;
	PackageName += AssetName;

	UPackage* Package = CreatePackage(*PackageName);
	Package->FullyLoad();

	URLRInputConfig* NewAsset = NewObject<URLRInputConfig>(
		Package, *AssetName, RF_Public | RF_Standalone | RF_MarkAsRootSet);

	FRLRInput test;
	test.ActionTag = FGameplayTagManager::Get().Action_Attack_HitCheck;
	NewAsset->InputList.Add(test);

	Package->MarkPackageDirty();
	FAssetRegistryModule::AssetCreated(NewAsset);

	FString PackageFileName = FPackageName::LongPackageNameToFilename(
		PackageName, FPackageName::GetAssetPackageExtension());

	bool bSaved = UPackage::SavePackage(
		Package,
		NewAsset,
		EObjectFlags::RF_Public | EObjectFlags::RF_Standalone,
		*PackageFileName,
		GError, nullptr, true, true, SAVE_NoError);

	TArray<UObject*> ObjectsToSync;
	ObjectsToSync.Add(NewAsset);
#if WITH_EDITOR
	GEditor->SyncBrowserToObjects(ObjectsToSync);
#endif
}



void UKeyOption::OnClickedConfirmButton()
{
	ApplyKeyOption();
	CloseUI();
}

void UKeyOption::OnClickedCancelButton()
{
	/*
		나중에 변경 취소 생기면 그냥 RefreshUI 때리면 된다. 어차피 값을 저장하지 않았으니, 기존에 있던 걸 다시 불러오면 그만.
	*/

	CloseUI();
}
