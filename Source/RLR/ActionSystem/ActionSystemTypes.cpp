// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystem/ActionSystemTypes.h"
#include "ActionSystem/ActionSystemComponent.h"
#include "ActionSystem/Action/Action.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/MovementComponent.h"

UAnimInstance* FActionActorInfo::GetAnimInstance() const
{
	const USkeletalMeshComponent* SKMC = SkeletalMeshComponent.Get();

	if (SKMC) return SKMC->GetAnimInstance();
	return nullptr;
}

void FActionActorInfo::InitFromActor(AActor* Owner, AActor* Avatar, UActionSystemComponent* InASC)
{
	OwnerActor = Owner;
	AvatarActor = Avatar;
	ActionSystemComponent = InASC;

	if (AActor* const AvatarActorPtr = AvatarActor.Get())
	{
		// Grab Components that we care about
		SkeletalMeshComponent = AvatarActorPtr->FindComponentByClass<USkeletalMeshComponent>();
		MovementComponent = AvatarActorPtr->FindComponentByClass<UMovementComponent>();
	}
	else
	{
		SkeletalMeshComponent = nullptr;
		MovementComponent = nullptr;
	}
}

void FActionActorInfo::SetAvatarActor(AActor* Avatar)
{
	AvatarActor = Avatar;
}

void FActionActorInfo::ClearActorInfo()
{
	OwnerActor = nullptr;
	AvatarActor = nullptr;
	ActionSystemComponent = nullptr;
}

FActionSpec::FActionSpec(TSubclassOf<UAction> ActionClass, int32 InLevel, int32 InInputID)
	: Action(ActionClass ? ActionClass.GetDefaultObject() : nullptr)
	, Level(InLevel)
	, InputID(InInputID)
	, bCancelable(false)
{
}

FStat::FStat(FProperty* NewProperty)
{
	StatProperty = CastField<FNumericProperty>(NewProperty);

	if (!StatProperty.Get())
	{
		if (IsStatDataProperty(NewProperty))
		{
			StatProperty = NewProperty;
		}
	}
}

bool FStat::operator==(const FStat& Other) const
{
	return ((Other.StatProperty == StatProperty));
}

bool FStat::operator!=(const FStat& Other) const
{
	return ((Other.StatProperty != StatProperty));
}

bool FStat::IsStatDataProperty(const FProperty* NewProperty)
{
	const FStructProperty* StructProp = CastField<FStructProperty>(NewProperty);
	if (StructProp)
	{
		const UStruct* Struct = StructProp->Struct;
		if (Struct) return true;
	}

	return false;
}
