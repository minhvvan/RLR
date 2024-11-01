// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include <Kismet/GameplayStatics.h>
#include <EnhancedInputSubsystems.h>
#include "GameFramework/Actor.h"

#include "Engine/DataAsset.h"
#include "GameManager/GameplayTagManager.h"
#include "PlayerCommands.generated.h"



/*
	InputAction과 GameplayTag를 연동하는 구조체.
	이걸 통해 EnhancedInputSystem과 결합하여 런타임중에 입력을 변경할 수 있게 한다.
*/


class ARLRPlayerController;


UENUM(BlueprintType)
enum class EInputType : uint8
{
	Skill,
	OpenUI,
	CloseUI,
	Consume,
	Action,
	Test,
	None,
};

USTRUCT(BlueprintType)
struct FRLRInput
{
	GENERATED_BODY()

	FRLRInput(){InputType = EInputType::None;};
	
	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	 FGameplayTag InputTag = FGameplayTag();

	 UPROPERTY(EditDefaultsOnly)
	 FGameplayTag ActionTag = FGameplayTag();

	 UPROPERTY(EditDefaultsOnly)
	 EInputType InputType = EInputType::None;

	 void SetInputAction(const UInputAction* NewAction){InputAction = NewAction;}
	 void SetInputTag(FGameplayTag NewTag){InputTag = NewTag; }
	 void SetActionTag(FGameplayTag NewTag){ActionTag = NewTag;}
	 void SetInputType(EInputType NewType){InputType = NewType;}

	 void ClearActionTagAndInputType(){ActionTag = FGameplayTag::EmptyTag; InputType = EInputType::None;}
	 void ClearInputActionAndTag(){InputAction = nullptr; InputTag = FGameplayTag::EmptyTag;};
};

UCLASS()
class RLR_API URLRInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:

	/*GameplayTag를 건네받으면, AbilityInputActions에 맵핑된 Input Action을 꺼내준다.*/
	const UInputAction* FindInputActionByInputTag(const FGameplayTag& InputTag) const;

	/*ActionTag를 건네 받으면 맵핑된 InputTag를 꺼내준다.*/
	const FGameplayTag FindInputTagByActionTag(const FGameplayTag& ActionTag) const;

	/*Input Tag와 맵핑된 RLRInput을 꺼내준다.*/
	FRLRInput& FindRLRInputByInputTag(const FGameplayTag& InputTag);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FRLRInput> InputList;
	FRLRInput EmptyRLRInput;

};


UCLASS()
class RLR_API APlayerCommands : public AActor
{
	GENERATED_BODY()

public:
	APlayerCommands();

	void BindDefaultAction(TObjectPtr<class ARLRPlayerController>);
	void BindInput(TObjectPtr<ARLRPlayerController> Controller);

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Move;

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* SPACE;

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* Attack;

	UPROPERTY(EditAnywhere, Category = Action);
	UInputAction* UserClick;

public:

	/*
		Key Binding  관련	
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLR | Input")
	TObjectPtr<URLRInputConfig> InputConfig;
};