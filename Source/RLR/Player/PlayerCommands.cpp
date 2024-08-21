// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCommands.h"
#include "Player/RLRPlayerController.h"

#include "Player/RLREnhancedInputComponent.h"
#include "BlueprintFunctionLibrary/UtilBlueprintFunctionLibrary.h"
#include "GameManager/GameplayTagManager.h"

/*

		RLRInputConfig

*/

const UInputAction* URLRInputConfig::FindInputActionByInputTag(const FGameplayTag& InputTag) const
{
	for (const FRLRInput& RLRInput : InputList)
	{
		if (RLRInput.InputAction && RLRInput.InputTag == InputTag)
		{
			return RLRInput.InputAction;
		}

	}
	return nullptr;
}

const FGameplayTag URLRInputConfig::FindInputTagByActionTag(const FGameplayTag& ActionTag) const
{

	for (const FRLRInput& RLRInput : InputList)
	{
		if(RLRInput.ActionTag == ActionTag)
			return RLRInput.InputTag;

	}

	return FGameplayTag();
}

FRLRInput& URLRInputConfig::FindRLRInputByInputTag(const FGameplayTag& InputTag)
{
	for (FRLRInput& RLRInput : InputList)
	{
		if (RLRInput.InputTag == InputTag)
			return RLRInput;
	}


	return EmptyRLRInput;
}

/*
	
	PlayerCommands

*/

APlayerCommands::APlayerCommands()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCommands::BindDefaultAction(TObjectPtr<ARLRPlayerController> Controller)
{
	UEnhancedInputComponent* component = Cast<UEnhancedInputComponent>(Controller->InputComponent);
	if (component == nullptr) return;

	FGameplayTagManager TagManager = FGameplayTagManager::Get();
	component->BindAction(Move, ETriggerEvent::Started, Controller.Get(), &ARLRPlayerController::OnMoveStarted, TagManager.Action_Default_Move);
	component->BindAction(Move, ETriggerEvent::Triggered, Controller.Get(), &ARLRPlayerController::OnMove, TagManager.Action_Default_Move);
	component->BindAction(Move, ETriggerEvent::Completed, Controller.Get(), &ARLRPlayerController::OnMoveCompleted, TagManager.Action_Default_Move);
	
	component->BindAction(SPACE, ETriggerEvent::Started, Controller.Get(), &ARLRPlayerController::OnDefaultAction, TagManager.Action_Default_Jump);
	component->BindAction(Attack, ETriggerEvent::Started, Controller.Get(), &ARLRPlayerController::OnDefaultAction, TagManager.Action_Default_Attack);
}

void APlayerCommands::BindInput(TObjectPtr<ARLRPlayerController> Controller)
{
	if(IsValid(Controller) == false)
		return;
	 

	BindDefaultAction(Controller);

	/*
		InputConfig DataAsset을 이용해서 액션 바인딩을 해준다.
	*/

	Util::Checkf(InputConfig, TEXT("InputConfig is nullptr. 값을 할당해주세요."));
	URLREnhancedInputComponent* RLRInputComponent = CastChecked<URLREnhancedInputComponent>(Controller->InputComponent);
	Util::Checkf(RLRInputComponent, TEXT("URLREnhancedInputComponent  is nullptr."));

	for (const FRLRInput& Input : InputConfig->InputList)
	{
		if(Input.InputType == EInputType::None)
			continue;

		switch (Input.InputType)
		{
			case EInputType::Skill:
				RLRInputComponent->BindInputActions(Input, Controller.Get(), &ARLRPlayerController::OnSkillStarted, &ARLRPlayerController::OnSkillCompleted, &ARLRPlayerController::OnSkillHeld);
				break;

			case EInputType::OpenUI:
				RLRInputComponent->BindAction(Input.InputAction, ETriggerEvent::Started, Controller.Get(), &ARLRPlayerController::OnOpenUI, Input.ActionTag);
				break;

			case EInputType::Consume:
				RLRInputComponent->BindAction(Input.InputAction, ETriggerEvent::Started, Controller.Get(), &ARLRPlayerController::OnConsumeItem, Input.ActionTag);
				break;
			
			case EInputType::Action:
				RLRInputComponent->BindAction(Input.InputAction, ETriggerEvent::Started, Controller.Get(), &ARLRPlayerController::OnActionStart, Input.ActionTag);
				break;
			default:
				break;
		}
	}
}

