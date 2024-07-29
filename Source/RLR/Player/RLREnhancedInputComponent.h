// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Player/PlayerCommands.h"
#include "RLREnhancedInputComponent.generated.h"

/**
 

 */
UCLASS()
class RLR_API URLREnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindInputActions(const FRLRInput&Input, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedRunc, HeldFuncType HeldFunc);

};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
inline void URLREnhancedInputComponent::BindInputActions(const FRLRInput& Input, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedRunc, HeldFuncType HeldFunc)
{
	if (Input.InputAction && Input.InputTag.IsValid())
	{
		if (PressedFunc)
		{
			BindAction(Input.InputAction, ETriggerEvent::Started, Object, PressedFunc, Input.ActionTag);
		}

		if (ReleasedRunc)
		{
			BindAction(Input.InputAction, ETriggerEvent::Completed, Object, ReleasedRunc, Input.ActionTag);
		}

		if (HeldFunc)
		{
			BindAction(Input.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Input.ActionTag);
		}
	}

}